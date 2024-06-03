#include <AuroraCore.hpp>



#pragma comment(lib, "AuroraCore.lib")



size_t TestNumber = 0;
size_t Fails = 0;



#define UNIT_TEST(Condition) if (!(Condition))\
{\
	Fails++;\
	std::wcout << L"Error on test #" << TestNumber << L" line " << __LINE__ << L" condition " << #Condition << L'\n';\
}\
TestNumber++



void MathUnitTest()
{
	{
		float _A = 0.0f;
		float _B = 1.0f;

		AuroraCore::Math::Swap(_A, _B);

		UNIT_TEST(_A == 1.0f && _B == 0.0f);
	}

	UNIT_TEST(AuroraCore::Math::Clamp(-1.0f, 0.0f, 1.0f) == 0.0f);
	UNIT_TEST(AuroraCore::Math::Clamp(2.0f, 0.0f, 1.0f) == 1.0f);
	UNIT_TEST(AuroraCore::Math::Clamp(0.5f, 0.0f, 1.0f) == 0.5f);

	UNIT_TEST(AuroraCore::Math::Mix(0.0f, 1.0f, 0.5f) == 0.5f);
	UNIT_TEST(AuroraCore::Math::Mix(0.0f, 1.0f, -0.5f) == -0.5f);
	UNIT_TEST(AuroraCore::Math::Mix(0.0f, 1.0f, 1.5f) == 1.5f);

	UNIT_TEST(AuroraCore::Math::Min(0.0f, 1.0f) == 0.0f);
	UNIT_TEST(AuroraCore::Math::Min(1.0f, 0.0f) == 0.0f);

	UNIT_TEST(AuroraCore::Math::Max(0.0f, 1.0f) == 1.0f);
	UNIT_TEST(AuroraCore::Math::Max(1.0f, 0.0f) == 1.0f);

	UNIT_TEST(AuroraCore::Math::Vec4f(1.0f, 0.0f, 0.0f, 1.0f) + AuroraCore::Math::Vec4f(0.0f, 1.0f, 0.0f, 1.0f) == AuroraCore::Math::Vec4f(1.0f, 1.0f, 0.0f, 2.0f));
	UNIT_TEST(AuroraCore::Math::Vec4f(1.0f, 0.0f, 0.0f, 1.0f) - AuroraCore::Math::Vec4f(0.0f, 1.0f, 0.0f, 1.0f) == AuroraCore::Math::Vec4f(1.0f, -1.0f, 0.0f, 0.0f));
	UNIT_TEST(AuroraCore::Math::Vec4f(1.0f, 0.0f, 0.0f, 1.0f) * AuroraCore::Math::Vec4f(0.0f, 1.0f, 0.0f, 1.0f) == AuroraCore::Math::Vec4f(0.0f, 0.0f, 0.0f, 1.0f));
	UNIT_TEST(AuroraCore::Math::Vec4f(2.0f, 2.0f, 2.0f, 2.0f) / AuroraCore::Math::Vec4f(2.0f, 2.0f, 2.0f, 2.0f) == AuroraCore::Math::Vec4f(1.0f, 1.0f, 1.0f, 1.0f));

	UNIT_TEST(AuroraCore::Math::Vec3f(1.0f, 0.0f, 0.0f).Magnitude() == 1.0f);

	UNIT_TEST(-AuroraCore::Math::Vec4f(1.0f, 0.0f, 0.0f, 1.0f) == AuroraCore::Math::Vec4f(-1.0f, 0.0f, 0.0f, -1.0f));

	UNIT_TEST(AuroraCore::Math::Vec3f(1.0f, 0.0f, 0.0f) == AuroraCore::Math::Vec3f(1.0f, 0.0f, 0.0f));
	UNIT_TEST(AuroraCore::Math::Vec3f(1.0f, 0.0f, 0.0f) != AuroraCore::Math::Vec3f(1.0f, 1.0f, 0.0f));

	UNIT_TEST(AuroraCore::Math::Vec3f(1.0f, 0.0f, 0.0f).GetAngle(AuroraCore::Math::Vec3f(0.0f, 1.0f, 0.0f), AuroraCore::Math::Vec3f(0.0f, 0.0f, 1.0f)) == AuroraCore::Math::Pi / 2.0f);

	UNIT_TEST(AuroraCore::Math::Vec3f::Distance(AuroraCore::Math::Vec3f(0.0f, 3.0f, 0.0f), AuroraCore::Math::Vec3f(4.0f, 0.0f, 0.0f)) == 5.0f);

	UNIT_TEST(abs(AuroraCore::Math::Vec3f::Dot(AuroraCore::Math::Vec3f(1.0f, 3.0f, 2.0f), AuroraCore::Math::Vec3f(4.0f, 12.0f, 8.0f)) - AuroraCore::Math::Vec3f(1.0f, 3.0f, 2.0f).Magnitude() * AuroraCore::Math::Vec3f(4.0f, 12.0f, 8.0f).Magnitude()) <= 0.0001f);

	{
		AuroraCore::Math::Vec3f _A(1.0f, 0.0f, 0.0f);
		AuroraCore::Math::Vec3f _B(0.0f, 1.0f, 0.0f);
		AuroraCore::Math::Vec3f _C = AuroraCore::Math::Vec3f::Cross(_A, _B);

		UNIT_TEST(AuroraCore::Math::Vec3f::Dot(_A, _C) == 0.0f);
		UNIT_TEST(AuroraCore::Math::Vec3f::Dot(_B, _C) == 0.0f);
	}

	{
		AuroraCore::Math::Vec3f _L(1.0f, -1.0f, 0.0f);
		AuroraCore::Math::Vec3f _N = AuroraCore::Math::Vec3f(0.0f, 1.0f, 0.0f);
		AuroraCore::Math::Vec3f _R = AuroraCore::Math::Vec3f::Reflect(_L, _N);

		UNIT_TEST(AuroraCore::Math::Vec3f::Dot(-_L, _N) == AuroraCore::Math::Vec3f::Dot(_R, _N));
	}

	{
		AuroraCore::Math::Mat2f _A;

		_A[0][0] = 0.0f; _A[0][1] = 1.0f;
		_A[1][0] = 2.0f; _A[1][1] = 0.0f;

		AuroraCore::Math::Mat2f _B;

		_B[0][0] = 0.0f; _B[0][1] = 2.0f;
		_B[1][0] = 1.0f; _B[1][1] = 0.0f;

		UNIT_TEST(_A.Transposed() == _B);
	}

	{
		AuroraCore::Math::Mat3f _A;

		_A[0][0] = 1.0f; _A[0][1] = 2.0f; _A[0][2] = 5.0f;
		_A[1][0] = 2.0f; _A[1][1] = 3.0f; _A[1][2] = 5.0f;
		_A[2][0] = 1.0f; _A[2][1] = 4.0f; _A[2][2] = 5.0f;

		UNIT_TEST(_A * _A.Inversed() == AuroraCore::Math::Mat3f::GetScale(1.0f, 1.0f, 1.0f));
	}

	{
		AuroraCore::Math::Vec3f _Vec(1.0f, 0.0f, 0.0f);

		AuroraCore::Math::Vec3f _Rotated = AuroraCore::Math::Mat3f::GetRotation(-AuroraCore::Math::Pi / 2.0f, AuroraCore::Math::Vec3f(0.0f, 1.0f, 0.0f)) * _Vec;
		UNIT_TEST(abs(_Rotated.x - 0.0f) <= 0.0001f && abs(_Rotated.y - 0.0f) <= 0.0001f && abs(_Rotated.z - 1.0f) <= 0.0001f);

		AuroraCore::Math::Vec3f _Scaled = AuroraCore::Math::Mat3f::GetScale(2.0f, 1.0f, 2.0f) * _Vec;
		UNIT_TEST(abs(_Scaled.x - 2.0f) <= 0.0001f && abs(_Scaled.y - 0.0f) <= 0.0001f && abs(_Scaled.z - 0.0f) <= 0.0001f);
	}
}



void AssetManagerUnitTest()
{
	AuroraCore::AssetManager _AssetManager;

	int _Asset = 0;
	float _FloatAsset = 0.0f;

	UNIT_TEST(_AssetManager.AddAsset(nullptr, L"No name") == false);
	UNIT_TEST(_AssetManager.AddAsset(&_Asset, nullptr) == false);
	UNIT_TEST(_AssetManager.AddAsset(&_Asset, L"Magic int") == true);
	UNIT_TEST(_AssetManager.GetAssetData(L"Magic INT") == nullptr);
	UNIT_TEST(_AssetManager.GetAssetData(L"Magic int") != nullptr);
	UNIT_TEST(_AssetManager.AddAsset(&_FloatAsset, L"Magic int") == false);
	UNIT_TEST(_AssetManager.AddAsset(&_FloatAsset, L"Magic float") == true);

	*(int*)(_AssetManager.GetAssetData(L"Magic int")) += 1;
	UNIT_TEST(_Asset == 1);

	*(float*)(_AssetManager.GetAssetData(L"Magic float")) += 1;
	UNIT_TEST(_FloatAsset == 1.0f);

	UNIT_TEST(_AssetManager.GetAssetsCount() == 2);
	_AssetManager.RemoveAllAssets();
	UNIT_TEST(_AssetManager.GetAssetsCount() == 0);
}



bool PhysicsCallBackLineHit = false;

void PhysicsCallBack(AuroraCore::Physics::Entity& _A, AuroraCore::Physics::Entity& _B)
{
	PhysicsCallBackLineHit = true;
}



void PhysicsUnitTest()
{
	{
		AuroraCore::Physics::Scene _Scene;

		_Scene.CallBack = PhysicsCallBack;
		_Scene.Layers.push_back(std::vector<AuroraCore::Physics::Entity*>());

		AuroraCore::Physics::DynamicEntity _Player;

		_Scene.Layers[0].push_back(&_Player);

		_Player.Position = AuroraCore::Math::Vec2f(0.0f, 0.0f);
		_Player.Box.Boxes.push_back(AuroraCore::Physics::AABB(-0.5f, -0.5f, 1.0f, 1.0f));
		_Player.LayerResponse = { false };
		_Player.Velocity = AuroraCore::Math::Vec2f(0.0f, 0.0f);
		_Player.Force = AuroraCore::Math::Vec2f(0.0f, 0.0f);
		_Player.Mass = 1.0f;
		_Player.Elasticity = AuroraCore::Math::Vec2f(0.0f, 0.0f);
		_Player.Drag = AuroraCore::Math::Vec2f(0.0f, 0.0f);
		_Player.GravitationalAcceleration = AuroraCore::Math::Vec2f(0.0f, -9.8f);

		_Scene.Update(0.0f);
		UNIT_TEST(_Player.Position == AuroraCore::Math::Vec2f(0.0f, 0.0f));

		_Scene.Update(1.0f);
		UNIT_TEST(_Player.Position == AuroraCore::Math::Vec2f(0.0f, -9.8f));

		AuroraCore::Physics::DynamicEntity _Player2;

		_Scene.Layers[0].push_back(&_Player2);

		_Player2.Position = AuroraCore::Math::Vec2f(0.0f, -9.8f);
		_Player2.Box.Boxes.push_back(AuroraCore::Physics::AABB(-0.5f, -0.5f, 1.0f, 1.0f));
		_Player2.LayerResponse = { false };
		_Player2.Velocity = AuroraCore::Math::Vec2f(0.0f, 0.0f);
		_Player2.Force = AuroraCore::Math::Vec2f(0.0f, 0.0f);
		_Player2.Mass = 1.0f;
		_Player2.Elasticity = AuroraCore::Math::Vec2f(0.0f, 0.0f);
		_Player2.Drag = AuroraCore::Math::Vec2f(0.0f, 0.0f);
		_Player2.GravitationalAcceleration = AuroraCore::Math::Vec2f(0.0f, -9.8f);

		_Scene.Update(0.0f);
		UNIT_TEST(PhysicsCallBackLineHit);

		_Scene.Update(1.0f);
		UNIT_TEST(abs(_Player.Position.y - (-29.4f)) <= 0.0001f);
		UNIT_TEST(abs(_Player2.Position.y - (-19.6f)) <= 0.0001f);
		UNIT_TEST(AuroraCore::Physics::HitBox::CheckCollision(_Player.Box, _Player2.Box, _Player.Position, _Player2.Position) == false);
	}

	{
		AuroraCore::Physics::AABB _A(-0.5f, -0.5f, 1.0f, 1.0f);
		AuroraCore::Physics::AABB _B(-0.5f, -0.5f, 1.0f, 1.0f);

		UNIT_TEST(AuroraCore::Physics::AABB::CheckCollision(_A, _B, AuroraCore::Math::Vec2f(0.0f, 0.0f), AuroraCore::Math::Vec2f(0.0f, 0.5f)));
		UNIT_TEST(AuroraCore::Physics::ResolveCollision(_A.Y, _A.Height, _B.Y + 0.5f, _B.Height, false) == -0.5f);
		UNIT_TEST(AuroraCore::Physics::ResolveCollision(_A.Y, _A.Height, _B.Y + 0.5f, _B.Height, true) == 1.5f);
	}

	{
		AuroraCore::Physics::HitBox _A;
		AuroraCore::Physics::HitBox _B;

		_A.Boxes.push_back(AuroraCore::Physics::AABB(-0.5f, -0.5f, 1.0f, 1.0f));
		_B.Boxes.push_back(AuroraCore::Physics::AABB(-0.5f, -0.5f, 1.0f, 1.0f));

		UNIT_TEST(AuroraCore::Physics::HitBox::CheckCollision(_A, _B, AuroraCore::Math::Vec2f(0.0f, 0.0f), AuroraCore::Math::Vec2f(0.0f, 0.5f)));
	}
}



int WINAPI wWinMain(_In_ HINSTANCE _hInstance, _In_opt_ HINSTANCE _hPrevInstance, _In_ LPWSTR _CmdLine, _In_ int _ShowCmd)
{
	MathUnitTest();
	AssetManagerUnitTest();
	PhysicsUnitTest();

	if (Fails != 0)
	{
		std::wcout << L'\n';
	}

	std::wcout << L"Total:  " << TestNumber << L'\n';
	std::wcout << L"Passed: " << TestNumber - Fails << L'\n';
	std::wcout << L"Failed: " << Fails << L'\n';

	return 0;
}
