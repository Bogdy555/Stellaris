#include "..\Headers\Stellaris.hpp"



Stellaris::RunTime::PlayMenu* Stellaris::RunTime::PlayMenu::CurrentPlayMenu = nullptr;
const float Stellaris::RunTime::PlayMenu::ParticleLifeTime = 1.0f;
const float Stellaris::RunTime::PlayMenu::TotalTime = 60.0f;



Stellaris::RunTime::PlayMenu::PlayMenu() : AuroraCore::RunTime::Menu(), Keys(), ControllerStates(), AnimationTime(0.0f), WorldMatrix(), World(), Player(), Flying(false), LastLeft(false), Star(), Particles(), ParticlesTime(), HitStar(false), TimeFromStart(0.0f)
{

}

Stellaris::RunTime::PlayMenu::~PlayMenu()
{

}

const uint64_t Stellaris::RunTime::PlayMenu::GetType() const
{
	return _PlayMenu;
}

void Stellaris::RunTime::PlayMenu::SetupScene()
{
	Application& _Application = *(Application*)(GetApplicationObj());

	_Application.SetScore(0);

	{
		AuroraCore::Graphics::Assets::Image _WorldMap;

		if (_WorldMap.Load(L".\\Map.bmp"))
		{
			// Fara parity checks pentru a face mai usor modding ul
			for (size_t _Y = 0; _Y < _WorldMap.GetHeight(); _Y++)
			{
				WorldMatrix.push_back(std::vector<bool>(_WorldMap.GetWidth()));

				for (size_t _X = 0; _X < _WorldMap.GetWidth(); _X++)
				{
					WorldMatrix[_Y][_X] = _WorldMap[(_X + _Y * _WorldMap.GetWidth()) * 4 + 0] != 0 || _WorldMap[(_X + _Y * _WorldMap.GetWidth()) * 4 + 1] != 0 || _WorldMap[(_X + _Y * _WorldMap.GetWidth()) * 4 + 2] != 0;
				}
			}
		}
		else
		{
			// In caz ca nu exista o mapa genereaza una default goala
			WorldMatrix =
			{
				{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
				{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
				{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
				{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
				{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
				{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
				{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
				{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
				{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
			};
		}
	}

	World.Position = AuroraCore::Math::Vec2f(0.0f, 0.0f);
	// Genereaza hitbox pentru lume
	for (size_t _Y = 0; _Y < WorldMatrix.size(); _Y++)
	{
		for (size_t _X = 0; _X < WorldMatrix[_Y].size(); _X++)
		{
			if (WorldMatrix[_Y][_X])
			{
				World.Box.Boxes.push_back(AuroraCore::Physics::AABB((float)(_X) - 0.5f, (float)(_Y) - 0.5f, 1.0f, 1.0f));
			}
		}
	}

	LastLeft = false;
	Flying = false;

	Player.Position = AuroraCore::Math::Vec2f(5.0f, 5.0f);
	Player.Box.Boxes.push_back(AuroraCore::Physics::AABB(-0.5f, -0.5f, 1.0f, 1.0f));
	Player.LayerResponse = { true, false, false, false };
	Player.Velocity = AuroraCore::Math::Vec2f(0.0f, 0.0f);
	Player.Force = AuroraCore::Math::Vec2f(0.0f, 0.0f);
	Player.Mass = 1.0f;
	Player.Elasticity = AuroraCore::Math::Vec2f(0.5f, 0.5f);
	Player.Drag = AuroraCore::Math::Vec2f(0.0f, 0.0f);
	Player.GravitationalAcceleration = AuroraCore::Math::Vec2f(0.0f, -9.8f);

	GenerateStarPosition();
	Star.Box.Boxes.push_back(AuroraCore::Physics::AABB(-0.5f, -0.5f, 1.0f, 1.0f));
}

void Stellaris::RunTime::PlayMenu::CleanUpScene()
{
	Star.Box.Boxes.clear();

	Player.Box.Boxes.clear();
	Player.LayerResponse.clear();

	World.Box.Boxes.clear();

	WorldMatrix.clear();

	for (size_t _Index = 0; _Index < Particles.size(); _Index++)
	{
		delete Particles[_Index];
	}

	Particles.clear();
}

void Stellaris::RunTime::PlayMenu::SpawnParticle()
{
	AuroraCore::Physics::DynamicEntity* _Particle = new AuroraCore::Physics::DynamicEntity;

	_Particle->Position = Player.Position;
	_Particle->Box.Boxes.push_back(AuroraCore::Physics::AABB(-0.0625f, -0.0625f, 0.125f, 0.125f));
	_Particle->LayerResponse = { true, false, false, false };
	_Particle->Velocity = AuroraCore::Math::Vec2f((float)(rand() % 101) / 100.0f * 10.0f - 5.0f, -10.0f);
	_Particle->Force = AuroraCore::Math::Vec2f(0.0f, 0.0f);
	_Particle->Mass = 0.125f;
	_Particle->Elasticity = AuroraCore::Math::Vec2f(0.8f, 0.8f);
	_Particle->Drag = AuroraCore::Math::Vec2f(0.0f, 0.0f);
	_Particle->GravitationalAcceleration = AuroraCore::Math::Vec2f(0.0f, -9.8f);

	Particles.push_back(_Particle);
	ParticlesTime.push_back(0.0f);
}

void Stellaris::RunTime::PlayMenu::UpdateParticles()
{
	// Sterge toate particulele care nu ar mai trebui sa fie "in viata"

	for (size_t _Index = 0; _Index < ParticlesTime.size(); _Index++)
	{
		ParticlesTime[_Index] += GetTimeStep();

		if (ParticlesTime[_Index] >= ParticleLifeTime)
		{
			ParticlesTime.erase(ParticlesTime.begin() + _Index);
			delete Particles[_Index];
			Particles.erase(Particles.begin() + _Index);
			_Index--;
		}
	}
}

void Stellaris::RunTime::PlayMenu::PhysicsCallback(AuroraCore::Physics::Entity& _Entity1, AuroraCore::Physics::Entity& _Entity2)
{
	if ((&CurrentPlayMenu->Player == &_Entity1 && &CurrentPlayMenu->Star == &_Entity2) || (&CurrentPlayMenu->Star == &_Entity1 && &CurrentPlayMenu->Player == &_Entity2))
	{
		CurrentPlayMenu->HitStar = true;
	}
}

void Stellaris::RunTime::PlayMenu::GenerateStarPosition()
{
	size_t _NewPosX = rand() % WorldMatrix[0].size(), _NewPosY = rand() % WorldMatrix.size();

	// Asigura ca steaua nu se poate spawna intr un bloc, indiferent de mapa
	// Atata timp cat mapa nu are "insule" de aer atunci e garantat ca steaua e accesibila

	while (WorldMatrix[_NewPosY][_NewPosX])
	{
		_NewPosX = rand() % WorldMatrix[0].size();
		_NewPosY = rand() % WorldMatrix.size();
	}

	Star.Position = AuroraCore::Math::Vec2f((float)(_NewPosX), (float)(_NewPosY));
}

void Stellaris::RunTime::PlayMenu::Setup()
{
	CurrentPlayMenu = this;
	HitStar = false;

	AnimationTime = 0.0f;
	TimeFromStart = 0.0f;

	DeleteInput();

	SetupScene();

	TurnOn();
}

void Stellaris::RunTime::PlayMenu::Update()
{
	AURORA_CORE_LOG_OUTPUT_DEBUG_LINE(AURORA_CORE_TO_STRING(1.0f / GetFrameTime(AuroraCore::_Previous)).c_str());

	Input();
	Engine();
	FrameBuild();
}

void Stellaris::RunTime::PlayMenu::Stop()
{
	CleanUpScene();
}

void Stellaris::RunTime::PlayMenu::Input()
{
	Application* _ApplicationObj = (Application*)(GetApplicationObj());

	AuroraCore::Window& _MainWindow = _ApplicationObj->GetMainWindow();

	Window::Data& _MainWindowData = _ApplicationObj->GetMainWindowData();

	_MainWindowData.InputMutex->lock();

	for (size_t _Index = 0; _Index < 256; _Index++)
	{
		Keys[AuroraCore::_Previous][_Index] = Keys[AuroraCore::_Current][_Index];
		Keys[AuroraCore::_Current][_Index] = _MainWindowData.Keys[_Index];
	}

	_MainWindowData.InputMutex->unlock();

	ControllerStates[AuroraCore::_Previous] = ControllerStates[AuroraCore::_Current];
	AuroraCore::Input::Controller::GetState(0, ControllerStates[AuroraCore::_Current]);

	_MainWindowData.InputMutex->lock();

	if (!_MainWindowData.Focus)
	{
		DeleteInput();
	}

	_MainWindowData.InputMutex->unlock();
}

void Stellaris::RunTime::PlayMenu::DeleteInput()
{
	for (size_t _Index = 0; _Index < 256; _Index++)
	{
		Keys[AuroraCore::_Previous][_Index] = false;
		Keys[AuroraCore::_Current][_Index] = false;
	}

	AuroraCore::Input::Controller::CleanState(ControllerStates[AuroraCore::_Previous]);
	AuroraCore::Input::Controller::CleanState(ControllerStates[AuroraCore::_Current]);
}

void Stellaris::RunTime::PlayMenu::Engine()
{
	Application* _ApplicationObj = (Application*)(GetApplicationObj());

	AuroraCore::Window& _MainWindow = _ApplicationObj->GetMainWindow();

	Window::Data& _MainWindowData = _ApplicationObj->GetMainWindowData();

	if ((Keys[AuroraCore::_Previous][VK_F11] || ControllerStates[AuroraCore::_Previous].ShoulderRight) && !(Keys[AuroraCore::_Current][VK_F11] || ControllerStates[AuroraCore::_Current].ShoulderRight))
	{
		_ApplicationObj->UpdateFullScreen();
	}

	if ((Keys[AuroraCore::_Previous]['M'] || ControllerStates[AuroraCore::_Previous].Back) && !(Keys[AuroraCore::_Current]['M'] || ControllerStates[AuroraCore::_Current].Back))
	{
		_ApplicationObj->UpdateMute();
	}

	if ((Keys[AuroraCore::_Previous][VK_ESCAPE] || ControllerStates[AuroraCore::_Previous].ButtonB) && !(Keys[AuroraCore::_Current][VK_ESCAPE] || ControllerStates[AuroraCore::_Current].ButtonB))
	{
		Close(_StartMenu);
	}

	UpdateParticles();

	// Miscare in jos

	if ((Keys[AuroraCore::_Current]['S'] || ControllerStates[AuroraCore::_Current].YLeft < 0.0f) && (!Keys[AuroraCore::_Current][VK_SPACE] && !ControllerStates[AuroraCore::_Current].ButtonA))
	{
		float _Multiplyer = AuroraCore::Math::Max(abs(ControllerStates[AuroraCore::_Current].YLeft), 1.0f * Keys[AuroraCore::_Current]['S']);

		Player.Force.y += -20.0f * _Multiplyer;
	}

	// Miscare in sus

	Flying = false;

	if ((Keys[AuroraCore::_Current][VK_SPACE] || ControllerStates[AuroraCore::_Current].ButtonA) && (!Keys[AuroraCore::_Current]['S'] && ControllerStates[AuroraCore::_Current].YLeft >= 0.0f))
	{
		if (Player.Velocity.y <= 15.0f)
		{
			Player.Force.y += 9.8f * Player.Mass;
		}
		else
		{
			if (Player.Velocity.y + Player.GravitationalAcceleration.y * GetTimeStep() <= 15.0f)
			{
				Player.Force += (15.0f - (Player.Velocity.y + Player.GravitationalAcceleration.y * GetTimeStep())) / GetTimeStep();
			}
		}
		Player.Force.y += AuroraCore::Physics::ComputeMaxAccelerationForce(15.0f, 30.0f, Player.Velocity.y, Player.Mass, GetTimeStep());

		static float _Accumulation = 0.0f;
		_Accumulation += GetTimeStep();

		float _SpawnRate = 0.01f;

		if (_Accumulation > _SpawnRate)
		{
			uint64_t _Count = (uint64_t)(_Accumulation / _SpawnRate);
			_Accumulation -= _SpawnRate * (float)(_Count);

			for (size_t _Index = 0; _Index < _Count; _Index++)
			{
				SpawnParticle();
			}
		}

		Flying = true;
	}

	// Miscare la stanga

	if ((Keys[AuroraCore::_Current]['A'] || ControllerStates[AuroraCore::_Current].XLeft < 0.0f) && (!Keys[AuroraCore::_Current]['D'] && ControllerStates[AuroraCore::_Current].XLeft <= 0.0f))
	{
		float _Multiplyer = AuroraCore::Math::Max(abs(ControllerStates[AuroraCore::_Current].XLeft), 1.0f * Keys[AuroraCore::_Current]['A']);

		Player.Force.x += AuroraCore::Physics::ComputeMaxAccelerationForce(-15.0f, 20.0f * _Multiplyer, Player.Velocity.x, Player.Mass, GetTimeStep());
		LastLeft = true;
	}

	// Miscare la dreapta

	if ((Keys[AuroraCore::_Current]['D'] || ControllerStates[AuroraCore::_Current].XLeft > 0.0f) && (!Keys[AuroraCore::_Current]['A'] && ControllerStates[AuroraCore::_Current].XLeft >= 0.0f))
	{
		float _Multiplyer = AuroraCore::Math::Max(abs(ControllerStates[AuroraCore::_Current].XLeft), 1.0f * Keys[AuroraCore::_Current]['D']);

		Player.Force.x += AuroraCore::Physics::ComputeMaxAccelerationForce(15.0f, 20.0f * _Multiplyer, Player.Velocity.x, Player.Mass, GetTimeStep());
		LastLeft = false;
	}

	// Decelerare daca nu sunt apasate input uri sau daca sunt apasate intr un mod care nu are sens

	if ((!(Keys[AuroraCore::_Current]['A'] || ControllerStates[AuroraCore::_Current].XLeft < 0.0f) && !(Keys[AuroraCore::_Current]['D'] || ControllerStates[AuroraCore::_Current].XLeft > 0.0f)) || ((Keys[AuroraCore::_Current]['A'] || ControllerStates[AuroraCore::_Current].XLeft < 0.0f) && (Keys[AuroraCore::_Current]['D'] || ControllerStates[AuroraCore::_Current].XLeft > 0.0f)))
	{
		Player.Force.x += AuroraCore::Physics::ComputeMaxDecelerationForce(10.0f, Player.Velocity.x, Player.Mass, GetTimeStep());
	}

	// Pregatirea si rularea scenei de physics

	AuroraCore::Physics::Scene _PhysicsScene;

	_PhysicsScene.CallBack = PhysicsCallback;

	_PhysicsScene.Layers.push_back(std::vector<AuroraCore::Physics::Entity*>());
	_PhysicsScene.Layers.push_back(std::vector<AuroraCore::Physics::Entity*>());
	_PhysicsScene.Layers.push_back(std::vector<AuroraCore::Physics::Entity*>());
	_PhysicsScene.Layers.push_back(std::vector<AuroraCore::Physics::Entity*>());

	_PhysicsScene.Layers[0].push_back(&World);
	_PhysicsScene.Layers[1].push_back(&Player);
	_PhysicsScene.Layers[2].push_back(&Star);
	for (size_t _Index = 0; _Index < Particles.size(); _Index++)
	{
		_PhysicsScene.Layers[3].push_back(Particles[_Index]);
	}

	_PhysicsScene.Update(GetTimeStep());

	if (HitStar)
	{
		_ApplicationObj->SetScore(_ApplicationObj->GetScore() + 1);
		_ApplicationObj->PlayCollectSound();

		GenerateStarPosition();

		HitStar = false;
	}

	_ApplicationObj->SetSync(_MainWindow.GetRefreshRate());

	_MainWindowData.CloseMutex->lock();

	if (_MainWindowData.Close)
	{
		_ApplicationObj->Close(0);
	}

	_MainWindowData.CloseMutex->unlock();

	_ApplicationObj->UpdateSound();

	AnimationTime += GetTimeStep();

	while (AnimationTime >= 0.75f)
	{
		AnimationTime -= 0.75f;
	}

	TimeFromStart += GetTimeStep();

	if (TimeFromStart >= TotalTime)
	{
		Close(_RestartMenu);
	}
}

void Stellaris::RunTime::PlayMenu::FrameBuild()
{
	Application& _Application = *(Application*)(GetApplicationObj());
	AuroraCore::Window& _Wnd = _Application.GetMainWindow();
	Window::Data& _WndData = *(Window::Data*)(_Wnd.GetUserData());
	AuroraCore::AssetManager& _Assets = _Application.GetAssets();

	AuroraCore::Graphics::GL::Texture2D& _WhiteTexture = *(AuroraCore::Graphics::GL::Texture2D*)(_Assets.GetAssetData(L"WhiteTexture"));
	AuroraCore::Graphics::GL::Texture2D& _TextAttlass = *(AuroraCore::Graphics::GL::Texture2D*)(_Assets.GetAssetData(L"TextAttlass"));
	AuroraCore::Graphics::GL::Texture2D& _Sprites = *(AuroraCore::Graphics::GL::Texture2D*)(_Assets.GetAssetData(L"Sprites"));
	AuroraCore::Graphics::GL::Texture2D& _Background = *(AuroraCore::Graphics::GL::Texture2D*)(_Assets.GetAssetData(L"Background"));
	AuroraCore::Graphics::GL::Shader& _DefaultShader = *(AuroraCore::Graphics::GL::Shader*)(_Assets.GetAssetData(L"DefaultShader"));
	AuroraCore::Graphics::GL::VertexAttribArray& _VAO = *(AuroraCore::Graphics::GL::VertexAttribArray*)(_Assets.GetAssetData(L"VAO"));
	AuroraCore::Graphics::GL::Mesh& _Quad = *(AuroraCore::Graphics::GL::Mesh*)(_Assets.GetAssetData(L"Quad"));

	size_t _Width = 0, _Height = 0;
	_Wnd.GetClientSize(_Width, _Height);

	_WndData.Context->Bind();

	PAINTSTRUCT _PaintStruct = { 0 };

	HDC _WndDC = BeginPaint(_Wnd, &_PaintStruct);

	AuroraCore::Graphics::GL::glEnable(GL_BLEND);
	AuroraCore::Graphics::GL::glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	AuroraCore::Graphics::GL::glEnable(GL_DEPTH_TEST);
	AuroraCore::Graphics::GL::glDepthFunc(GL_LEQUAL);
	AuroraCore::Graphics::GL::glEnable(GL_CULL_FACE);
	AuroraCore::Graphics::GL::glCullFace(GL_BACK);
	AuroraCore::Graphics::GL::glFrontFace(GL_CW);

	AuroraCore::Graphics::GL::glViewport(0, 0, (int)(_Width), (int)(_Height));

	AuroraCore::Graphics::GL::glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	AuroraCore::Graphics::GL::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	AuroraCore::Graphics::GL::glActiveTexture(GL_TEXTURE0);
	_WhiteTexture.Bind();

	AuroraCore::Graphics::GL::glActiveTexture(GL_TEXTURE1);
	_TextAttlass.Bind();

	AuroraCore::Graphics::GL::glActiveTexture(GL_TEXTURE2);
	_Sprites.Bind();

	AuroraCore::Graphics::GL::glActiveTexture(GL_TEXTURE3);
	_Background.Bind();

	_DefaultShader.Bind();
	_VAO.Bind();
	_Quad.IBO.Bind();
	_Quad.VBO.Bind();

	AuroraCore::Math::Vec2f _SpritesLookup[] = 
	{
		AuroraCore::Math::Vec2f(0.0f / 8.0f, 0.0f / 3.0f),
		AuroraCore::Math::Vec2f(1.0f / 8.0f, 0.0f / 3.0f),
		AuroraCore::Math::Vec2f(0.0f / 8.0f, 2.0f / 3.0f),
		AuroraCore::Math::Vec2f(1.0f / 8.0f, 2.0f / 3.0f),
		AuroraCore::Math::Vec2f(2.0f / 8.0f, 2.0f / 3.0f),
		AuroraCore::Math::Vec2f(3.0f / 8.0f, 2.0f / 3.0f),
		AuroraCore::Math::Vec2f(4.0f / 8.0f, 2.0f / 3.0f),
		AuroraCore::Math::Vec2f(5.0f / 8.0f, 2.0f / 3.0f),
		AuroraCore::Math::Vec2f(6.0f / 8.0f, 2.0f / 3.0f),
		AuroraCore::Math::Vec2f(7.0f / 8.0f, 2.0f / 3.0f)
	};

	enum SpriteIndexes : const size_t
	{
		_GrassSprite = 0,
		_DirtSprite = 1,
		_PlayerIdleLeft = 2,
		_PlayerIdleRight = 3,
		_PlayerWalkLeft1 = 4,
		_PlayerWalkLeft2 = 5,
		_PlayerWalkLeft3 = 6,
		_PlayerWalkRight1 = 7,
		_PlayerWalkRight2 = 8,
		_PlayerWalkRight3 = 9
	};

	std::vector<AuroraCore::Math::Vec2f> _StarSprites =
	{
		AuroraCore::Math::Vec2f(0.0f / 8.0f, 1.0f / 3.0f),
		AuroraCore::Math::Vec2f(1.0f / 8.0f, 1.0f / 3.0f),
		AuroraCore::Math::Vec2f(2.0f / 8.0f, 1.0f / 3.0f),
		AuroraCore::Math::Vec2f(3.0f / 8.0f, 1.0f / 3.0f),
		AuroraCore::Math::Vec2f(4.0f / 8.0f, 1.0f / 3.0f),
		AuroraCore::Math::Vec2f(5.0f / 8.0f, 1.0f / 3.0f)
	};

	{
		AuroraCore::Graphics::GL::CameraStruct _Camera;
		_Camera.Fov = 1.0f;

		AuroraCore::Graphics::GL::MeshWorldDataStruct _WorldData;
		if ((float)(_Width) / (float)(_Height) >= 16.0f / 9.0f)
		{
			_WorldData.Scale.x = (float)(_Width) / (float)(_Height);
			_WorldData.Scale.y = _WorldData.Scale.x / 16.0f * 9.0f;
		}
		else
		{
			_WorldData.Scale.x = 16.0f / 9.0f;
		}

		AuroraCore::Graphics::GL::MaterialStruct _Material;
		_Material.TextureAlbedo = 3;

		_Application.RenderSprite((float)(_Width) / (float)(_Height), _Camera, _WorldData, _Material, _DefaultShader);
	}

	for (size_t _Y = 0; _Y < WorldMatrix.size() - 1; _Y++)
	{
		for (size_t _X = 0; _X < WorldMatrix[_Y].size(); _X++)
		{
			if (WorldMatrix[_Y][_X])
			{
				AuroraCore::Graphics::GL::CameraStruct _Camera;
				_Camera.Position = Player.Position;

				AuroraCore::Graphics::GL::MeshWorldDataStruct _WorldData;
				_WorldData.Position = AuroraCore::Math::Vec3f((float)(_X), (float)(_Y), 0.0f);

				AuroraCore::Graphics::GL::MaterialStruct _Material;
				_Material.TextureAlbedo = 2;
				_Material.Size = AuroraCore::Math::Vec2f(1.0f / 8.0f, 1.0f / 3.0f);

				if (WorldMatrix[_Y + 1][_X])
				{
					_Material.Start = _SpritesLookup[_DirtSprite];
				}
				else
				{
					_Material.Start = _SpritesLookup[_GrassSprite];
				}

				_Application.RenderSprite((float)(_Width) / (float)(_Height), _Camera, _WorldData, _Material, _DefaultShader);
			}
		}
	}

	for (size_t _X = 0; _X < WorldMatrix[WorldMatrix.size() - 1].size(); _X++)
	{
		if (WorldMatrix[WorldMatrix.size() - 1][_X])
		{
			AuroraCore::Graphics::GL::CameraStruct _Camera;
			_Camera.Position = Player.Position;

			AuroraCore::Graphics::GL::MeshWorldDataStruct _WorldData;
			_WorldData.Position = AuroraCore::Math::Vec3f((float)(_X), (float)(WorldMatrix.size() - 1), 0.0f);

			AuroraCore::Graphics::GL::MaterialStruct _Material;
			_Material.TextureAlbedo = 2;
			_Material.Size = AuroraCore::Math::Vec2f(1.0f / 8.0f, 1.0f / 3.0f);
			_Material.Start = _SpritesLookup[_GrassSprite];

			_Application.RenderSprite((float)(_Width) / (float)(_Height), _Camera, _WorldData, _Material, _DefaultShader);
		}
	}

	for (size_t _Index = 0; _Index < Particles.size(); _Index++)
	{
		AuroraCore::Graphics::GL::CameraStruct _Camera;
		_Camera.Position = Player.Position;

		AuroraCore::Graphics::GL::MeshWorldDataStruct _WorldData;
		_WorldData.Position = AuroraCore::Math::Vec3f(Particles[_Index]->Position, 0.0f);
		_WorldData.Scale.x = 0.125f;
		_WorldData.Scale.y = 0.125f;

		AuroraCore::Graphics::GL::MaterialStruct _Material;
		_Material.TextureAlbedo = 0;
		_Material.Color = AuroraCore::Math::Vec4f(0.9f, 0.4f, 0.2f, (ParticleLifeTime - ParticlesTime[_Index]) / ParticleLifeTime * 0.3f);

		_Application.RenderSprite((float)(_Width) / (float)(_Height), _Camera, _WorldData, _Material, _DefaultShader);
	}

	{
		AuroraCore::Graphics::GL::CameraStruct _Camera;
		_Camera.Position = Player.Position;

		AuroraCore::Graphics::GL::MeshWorldDataStruct _WorldData;
		_WorldData.Position = AuroraCore::Math::Vec3f(Star.Position, 0.0f);

		AuroraCore::Graphics::GL::MaterialStruct _Material;
		_Material.TextureAlbedo = 2;
		_Material.Start = _StarSprites[rand() % _StarSprites.size()];
		_Material.Size = AuroraCore::Math::Vec2f(1.0f / 8.0f, 1.0f / 3.0f);

		_Application.RenderSprite((float)(_Width) / (float)(_Height), _Camera, _WorldData, _Material, _DefaultShader);
	}

	{
		AuroraCore::Graphics::GL::CameraStruct _Camera;
		_Camera.Position = Player.Position;

		AuroraCore::Graphics::GL::MeshWorldDataStruct _WorldData;
		_WorldData.Position = AuroraCore::Math::Vec3f(Player.Position, 0.0f);

		AuroraCore::Graphics::GL::MaterialStruct _Material;
		_Material.TextureAlbedo = 2;
		_Material.Size = AuroraCore::Math::Vec2f(1.0f / 8.0f, 1.0f / 3.0f);

		if (LastLeft)
		{
			if (Flying)
			{
				_Material.Start = _SpritesLookup[_PlayerWalkLeft1 + (size_t)(AnimationTime * 4.0f)];
			}
			else
			{
				_Material.Start = _SpritesLookup[_PlayerIdleLeft];
			}
		}
		else
		{
			if (Flying)
			{
				_Material.Start = _SpritesLookup[_PlayerWalkRight1 + (size_t)(AnimationTime * 4.0f)];
			}
			else
			{
				_Material.Start = _SpritesLookup[_PlayerIdleRight];
			}
		}

		_Application.RenderSprite((float)(_Width) / (float)(_Height), _Camera, _WorldData, _Material, _DefaultShader);
	}

	AuroraCore::Graphics::GL::glDisable(GL_DEPTH_TEST);

	{
		std::string _Score = "SCORE:" + std::to_string(_Application.GetScore());

		AuroraCore::Graphics::GL::MeshWorldDataStruct _WorldData;

		_WorldData.Position = AuroraCore::Math::Vec3f(-(float)(_Score.length() - 1) / 2.0f, 9.0f, 0.0f);
		_WorldData.Scale = AuroraCore::Math::Vec2f(1.0f, 1.0f);
		_WorldData.Angle = 0.0f;

		_Application.RenderText(_Score.c_str(), (float)(_Width) / (float)(_Height), 20.0f, _WorldData, 1, AuroraCore::Math::Vec4f(1.0f, 1.0f, 1.0f, 1.0f), _DefaultShader);
	}

	{
		AuroraCore::Graphics::GL::CameraStruct _Camera;

		_Camera.Fov = 1.0f;

		AuroraCore::Graphics::GL::MeshWorldDataStruct _WorldData;

		_WorldData.Position = AuroraCore::Math::Vec3f(0.0f, -0.5f + 0.0125f, 0.0f);
		_WorldData.Scale = AuroraCore::Math::Vec2f(AuroraCore::Math::Clamp(TotalTime - TimeFromStart, 0.0f, TotalTime) / TotalTime * (float)(_Width) / (float)(_Height), 0.025f);

		AuroraCore::Graphics::GL::MaterialStruct _Material;

		_Material.TextureAlbedo = 0;
		_Material.Color = AuroraCore::Math::Vec4f::Mix(AuroraCore::Math::Vec4f(0.0f, 1.0f, 0.0f, 1.0f), AuroraCore::Math::Vec4f(1.0f, 0.0f, 0.0f, 1.0f), AuroraCore::Math::Clamp(TimeFromStart, 0.0f, TotalTime) / TotalTime);

		_Application.RenderSprite((float)(_Width) / (float)(_Height), _Camera, _WorldData, _Material, _DefaultShader);
	}

	AuroraCore::Graphics::GL::wglSwapIntervalEXT(1);

	SwapBuffers(_WndDC);

	EndPaint(_Wnd, &_PaintStruct);
}
