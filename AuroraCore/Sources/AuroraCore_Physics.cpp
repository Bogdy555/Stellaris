#include "..\Headers\AuroraCore.hpp"



const bool AuroraCore::Physics::AABB::CheckCollision(const AABB& _Box1, const AABB& _Box2, const Math::Vec2f& _Entity1Position, const Math::Vec2f& _Entity2Position)
{
	if ((_Box1.Position.x - (_Box1.Size.x / 2) + _Entity1Position.x) >= (_Box2.Position.x + (_Box2.Size.x / 2) + _Entity2Position.x))
	{
		return false;
	}
	if ((_Box1.Position.x + (_Box1.Size.x / 2) + _Entity1Position.x) <= (_Box2.Position.x - (_Box2.Size.x / 2) + _Entity2Position.x))
	{
		return false;
	}

	if ((_Box1.Position.y - (_Box1.Size.y / 2) + _Entity1Position.y) >= (_Box2.Position.y + (_Box2.Size.y / 2) + _Entity2Position.y))
	{
		return false;
	}
	if ((_Box1.Position.y + (_Box1.Size.y / 2) + _Entity1Position.y) <= (_Box2.Position.y - (_Box2.Size.y / 2) + _Entity2Position.y))
	{
		return false;
	}
	
	return true;
}



AuroraCore::Physics::HitBox::HitBox()
{

}

AuroraCore::Physics::HitBox::HitBox(HitBox&& _Other) noexcept : Boxes(std::move(_Other.Boxes))
{

}

AuroraCore::Physics::HitBox::~HitBox()
{

}

const bool AuroraCore::Physics::HitBox::CheckCollision(const HitBox& _HitBox1, const HitBox& _HitBox2, const Math::Vec2f& _Entity1Position, const Math::Vec2f& _Entity2Position)
{
	for (const auto& _Box1 : _HitBox1.Boxes)
	{
		for (const auto& _Box2 : _HitBox2.Boxes)
		{
			if (AABB::CheckCollision(_Box1, _Box2, _Entity1Position, _Entity2Position))
			{
				return true;
			}
		}
	}

	return false;
}

void AuroraCore::Physics::HitBox::Add(const AABB& _Box)
{
	Boxes.push_back(_Box);
}

void AuroraCore::Physics::HitBox::Remove(const size_t _Index)
{
	Boxes.erase(Boxes.begin() + _Index);
}

void AuroraCore::Physics::HitBox::Clear()
{
	Boxes.clear();
}

const size_t AuroraCore::Physics::HitBox::Size() const
{
	return Boxes.size();
}


AuroraCore::Physics::HitBox& AuroraCore::Physics::HitBox::operator= (const AuroraCore::Physics::HitBox& _Other) noexcept
{
	std::copy(_Other.Boxes.begin(), _Other.Boxes.end(), Boxes.begin());

	return *this;
}

AuroraCore::Physics::HitBox& AuroraCore::Physics::HitBox::operator=(HitBox&& _Other) noexcept
{
	Boxes = std::move(_Other.Boxes);

	return *this;
}

AuroraCore::Physics::AABB& AuroraCore::Physics::HitBox::operator[](const size_t _Index)
{
	return Boxes[_Index];
}

const AuroraCore::Physics::AABB& AuroraCore::Physics::HitBox::operator[](const size_t _Index) const
{
	return Boxes[_Index];
}



AuroraCore::Physics::Entity::Entity()
{

}

AuroraCore::Physics::Entity::Entity(const Math::Vec2f& _Position, const HitBox& _Box)
{
	Position = _Position;
	Box = _Box;
}

AuroraCore::Physics::Entity::~Entity()
{

}

void AuroraCore::Physics::Entity::SetPosition(Math::Vec2f& _Position)
{
	Position = _Position;
}

void AuroraCore::Physics::Entity::SetXPosition(float _x)
{
	Position.x = _x;
}

void AuroraCore::Physics::Entity::SetYPosition(float _y)
{
	Position.y = _y;
}

void AuroraCore::Physics::Entity::SetHitBox(HitBox& _Box)
{
	Box = _Box;
}

AuroraCore::Math::Vec2f& AuroraCore::Physics::Entity::GetPosition()
{
	return Position;
}

AuroraCore::Physics::HitBox& AuroraCore::Physics::Entity::GetBox()
{
	return Box;
}



AuroraCore::Physics::DynamicEntity::DynamicEntity() : Entity(), LayerResponse(), Velocity(), Force(), Mass(), Elasticity()
{

}

AuroraCore::Physics::DynamicEntity::DynamicEntity(const Math::Vec2f& _Position, const HitBox& _Box) : Entity(), LayerResponse(), Velocity(), Force(), Mass(), Elasticity()
{
	Position = _Position;
	Box = _Box;
}

AuroraCore::Physics::DynamicEntity::~DynamicEntity()
{

}

void AuroraCore::Physics::DynamicEntity::SetLayerResponse(std::vector<bool>& _LayerResponse)
{
	LayerResponse = _LayerResponse;
}

void AuroraCore::Physics::DynamicEntity::SetVelocity(Math::Vec2f& _Velocity)
{
	Velocity = _Velocity;
}

void AuroraCore::Physics::DynamicEntity::SetXVelocity(float _Velocity)
{
	Velocity.x = _Velocity;
}

void AuroraCore::Physics::DynamicEntity::SetYVelocity(float _Velocity)
{
	Velocity.y = _Velocity;
}

void AuroraCore::Physics::DynamicEntity::SetForce(Math::Vec2f& _Force)
{
	Force = _Force;
}

void AuroraCore::Physics::DynamicEntity::SetXForce(float _Force)
{
	Force.x = _Force;
}

void AuroraCore::Physics::DynamicEntity::SetYForce(float _Force)
{
	Force.y = _Force;
}

void AuroraCore::Physics::DynamicEntity::SetMass(float _Mass)
{
	Mass = _Mass;
}

void AuroraCore::Physics::DynamicEntity::SetElasticity(Math::Vec2f& _Elasticity)
{
	Elasticity = _Elasticity;
}

void AuroraCore::Physics::DynamicEntity::SetXElasticity(float _Elasticity)
{
	Elasticity.x = _Elasticity;
}

void AuroraCore::Physics::DynamicEntity::SetYElasticity(float _Elasticity)
{
	Elasticity.y = _Elasticity;
}

std::vector<bool>& AuroraCore::Physics::DynamicEntity::GetLayerResponseVec()
{
	return LayerResponse;
}

const bool& AuroraCore::Physics::DynamicEntity::GetLayerResponse(const size_t& _Index)
{
	return LayerResponse[_Index];
}

AuroraCore::Math::Vec2f& AuroraCore::Physics::DynamicEntity::GetVelocity()
{
	return Velocity;
}

AuroraCore::Math::Vec2f& AuroraCore::Physics::DynamicEntity::GetForce()
{
	return Force;
}

float& AuroraCore::Physics::DynamicEntity::GetMass()
{
	return Mass;
}

AuroraCore::Math::Vec2f& AuroraCore::Physics::DynamicEntity::GetElasticity()
{
	return Elasticity;
}



AuroraCore::Physics::Scene::Scene()
{

}

AuroraCore::Physics::Scene::Scene(Scene&& _Other) noexcept : Entities(std::move(_Other.Entities))
{

}

AuroraCore::Physics::Scene::~Scene()
{

}

void AuroraCore::Physics::Scene::AddEntity(const size_t _LayerIndex, Entity* _Entity)
{
	Entities[_LayerIndex].push_back(_Entity);
}

void AuroraCore::Physics::Scene::RemoveEntity(const size_t _LayerIndex, const size_t _EntityIndex)
{
	Entities[_LayerIndex].erase(Entities[_LayerIndex].begin() + _EntityIndex);
}

const float ResolveCollision(const float& _Position1, const float& _Position2, const float& _Size1, const float& _Size2, const bool& _PositiveVelocity)
{
	float _Vec = 0.0f;

	if (_PositiveVelocity)
	{
		_Vec = _Position2 - _Size1 - _Position1;
	}
	else
	{
		_Vec = _Position2 + _Size2 - _Position1;
	}

	return _Position1 + _Vec;
}

void AuroraCore::Physics::Scene::Update(float& _DeltaTime, void (*_CallBack)(Entity* _Entity1, Entity* _Entity2))
{
	for (size_t _LayerIndex1 = 0; _LayerIndex1 < Entities.size(); _LayerIndex1++)
	{
		for (const auto& _Entity1 : Entities[_LayerIndex1])
		{
			DynamicEntity* _DynamicEntity1 = dynamic_cast<DynamicEntity*>(_Entity1);

			if (!_DynamicEntity1)
			{
				continue;
			}
			
			float& _Position = _DynamicEntity1->GetPosition().y;
			float& _Speed = _DynamicEntity1->GetVelocity().y;
			float& _Force = _DynamicEntity1->GetForce().y;
			float& _Mass = _DynamicEntity1->GetMass();

			float _OldPosition = _Position;
			float _OldSpeed = _Speed;

			_Position += _Speed * _DeltaTime;
			_Speed += (_Force / _Mass) * _DeltaTime;

			for (size_t _LayerIndex2 = 0; _LayerIndex2 < Entities.size(); _LayerIndex2++)
			{
				if (_DynamicEntity1->GetLayerResponse(_LayerIndex2))
				{
					for (const auto& _Entity2 : Entities[_LayerIndex2])
					{
						DynamicEntity* _DynamicEntity2 = dynamic_cast<DynamicEntity*>(_Entity2);
						if (_DynamicEntity2)
						{
							if (_DynamicEntity1 == _DynamicEntity2)
							{
								continue;
							}

							bool _FoundCollision = false;
							
							for (size_t _AABBIndex1 = 0; _AABBIndex1 < _Entity1->GetBox().Size(); _AABBIndex1++)
							{
								for (size_t _AABBIndex2 = 0; _AABBIndex2 < _Entity2->GetBox().Size(); _AABBIndex2++)
								{
									if (AABB::CheckCollision(_Entity1->GetBox()[_AABBIndex1], _Entity2->GetBox()[_AABBIndex2], _Entity1->GetPosition(), _Entity2->GetPosition()))
									{
										_FoundCollision = true;
										_Position = ResolveCollision(_Position + _Entity1->GetBox()[_AABBIndex1].Position.y - _Entity1->GetBox()[_AABBIndex1].Size.y / 2,
											_Entity2->GetPosition().y + _Entity2->GetBox()[_AABBIndex2].Position.y - _Entity2->GetBox()[_AABBIndex2].Size.y / 2,
											_Entity1->GetBox()[_AABBIndex1].Size.y,
											_Entity2->GetBox()[_AABBIndex2].Size.y,
											_OldSpeed >= 0.0f
										);

										float _V0Plastic = (_DynamicEntity1->GetMass() * _DynamicEntity1->GetVelocity().y + _DynamicEntity2->GetMass() * _DynamicEntity2->GetVelocity().y) / (_DynamicEntity1->GetMass() + _DynamicEntity2->GetMass());
										float _V1Elastic = ((_DynamicEntity1->GetMass() - _DynamicEntity2->GetMass()) * _DynamicEntity1->GetVelocity().y + 2.0f * _DynamicEntity2->GetMass() * _DynamicEntity2->GetVelocity().y) / (_DynamicEntity1->GetMass() + _DynamicEntity2->GetMass());
										float _V2Elastic = (2.0f * _DynamicEntity1->GetMass() * _DynamicEntity1->GetVelocity().y + (_DynamicEntity2->GetMass() - _DynamicEntity1->GetMass()) * _DynamicEntity2->GetVelocity().y) / (_DynamicEntity1->GetMass() + _DynamicEntity2->GetMass());
										
										_Speed = Math::Mix(_V0Plastic, _V1Elastic, _DynamicEntity1->GetElasticity().y * 0.5f + _DynamicEntity2->GetElasticity().y * 0.5f);
										if (_DynamicEntity2->GetLayerResponse(_LayerIndex1))
										{
											_DynamicEntity2->GetVelocity().y = Math::Mix(_V0Plastic, _V2Elastic, _DynamicEntity1->GetElasticity().y * 0.5f + _DynamicEntity2->GetElasticity().y * 0.5f);
										}
									}
								}
							}

							if (_FoundCollision)
							{
								if (_CallBack)
								{
									_CallBack(_Entity1, _Entity2);
								}
							}
						}
						else
						{
							bool _FoundCollision = false;

							for (size_t _AABBIndex1 = 0; _AABBIndex1 < _Entity1->GetBox().Size(); _AABBIndex1++)
							{
								for (size_t _AABBIndex2 = 0; _AABBIndex2 < _Entity2->GetBox().Size(); _AABBIndex2++)
								{
									if (AABB::CheckCollision(_Entity1->GetBox()[_AABBIndex1], _Entity2->GetBox()[_AABBIndex2], _Entity1->GetPosition(), _Entity2->GetPosition()))
									{
										_FoundCollision = true;
										_Position = ResolveCollision(_Position + _Entity1->GetBox()[_AABBIndex1].Position.y - _Entity1->GetBox()[_AABBIndex1].Size.y / 2,
											_Entity2->GetPosition().y + _Entity2->GetBox()[_AABBIndex2].Position.y - _Entity2->GetBox()[_AABBIndex2].Size.y / 2,
											_Entity1->GetBox()[_AABBIndex1].Size.y,
											_Entity2->GetBox()[_AABBIndex2].Size.y,
											_OldSpeed >= 0.0f
										);
										_Speed = -_Speed * _DynamicEntity1->GetElasticity().y;
									}
								}
							}

							if (_FoundCollision)
							{
								if (_CallBack)
								{
									_CallBack(_Entity1, _Entity2);
								}
							}
						}
					}
				}
				else
				{
					for (const auto& _Entity2 : Entities[_LayerIndex2])
					{
						DynamicEntity* _DynamicEntity2 = dynamic_cast<DynamicEntity*>(_Entity2);
						if (_DynamicEntity2)
						{
							if (_DynamicEntity1 == _DynamicEntity2)
							{
								continue;
							}

							if (HitBox::CheckCollision(_Entity1->GetBox(), _Entity2->GetBox(), _Entity1->GetPosition(), _Entity2->GetPosition()))
							{
								if (_CallBack)
								{
									_CallBack(_Entity1, _Entity2);
								}
							}
						}
						else
						{
							if (HitBox::CheckCollision(_Entity1->GetBox(), _Entity2->GetBox(), _Entity1->GetPosition(), _Entity2->GetPosition()))
							{
								if (_CallBack)
								{
									_CallBack(_Entity1, _Entity2);
								}
							}
						}
					}
				}
				
			}
		}
	}

	for (size_t _LayerIndex1 = 0; _LayerIndex1 < Entities.size(); _LayerIndex1++)
	{
		for (const auto& _Entity1 : Entities[_LayerIndex1])
		{
			DynamicEntity* _DynamicEntity1 = dynamic_cast<DynamicEntity*>(_Entity1);

			if (!_DynamicEntity1)
			{
				continue;
			}

			float& _Position = _DynamicEntity1->GetPosition().x;
			float& _Speed = _DynamicEntity1->GetVelocity().x;
			float& _Force = _DynamicEntity1->GetForce().x;
			float& _Mass = _DynamicEntity1->GetMass();

			float _OldPosition = _Position;
			float _OldSpeed = _Speed;

			_Position += _Speed * _DeltaTime;
			_Speed += (_Force / _Mass) * _DeltaTime;

			for (size_t _LayerIndex2 = 0; _LayerIndex2 < Entities.size(); _LayerIndex2++)
			{
				if (_DynamicEntity1->GetLayerResponse(_LayerIndex2))
				{
					for (const auto& _Entity2 : Entities[_LayerIndex2])
					{
						DynamicEntity* _DynamicEntity2 = dynamic_cast<DynamicEntity*>(_Entity2);
						if (_DynamicEntity2)
						{
							if (_DynamicEntity1 == _DynamicEntity2)
							{
								continue;
							}

							bool _FoundCollision = false;

							for (size_t _AABBIndex1 = 0; _AABBIndex1 < _Entity1->GetBox().Size(); _AABBIndex1++)
							{
								for (size_t _AABBIndex2 = 0; _AABBIndex2 < _Entity2->GetBox().Size(); _AABBIndex2++)
								{
									if (AABB::CheckCollision(_Entity1->GetBox()[_AABBIndex1], _Entity2->GetBox()[_AABBIndex2], _Entity1->GetPosition(), _Entity2->GetPosition()))
									{
										_FoundCollision = true;
										_Position = ResolveCollision(_Position + _Entity1->GetBox()[_AABBIndex1].Position.x - _Entity1->GetBox()[_AABBIndex1].Size.x / 2,
											_Entity2->GetPosition().x + _Entity2->GetBox()[_AABBIndex2].Position.x - _Entity2->GetBox()[_AABBIndex2].Size.x / 2,
											_Entity1->GetBox()[_AABBIndex1].Size.x,
											_Entity2->GetBox()[_AABBIndex2].Size.x,
											_OldSpeed >= 0.0f
										);

										float _V0Plastic = (_DynamicEntity1->GetMass() * _DynamicEntity1->GetVelocity().x + _DynamicEntity2->GetMass() * _DynamicEntity2->GetVelocity().x) / (_DynamicEntity1->GetMass() + _DynamicEntity2->GetMass());
										float _V1Elastic = ((_DynamicEntity1->GetMass() - _DynamicEntity2->GetMass()) * _DynamicEntity1->GetVelocity().x + 2.0f * _DynamicEntity2->GetMass() * _DynamicEntity2->GetVelocity().x) / (_DynamicEntity1->GetMass() + _DynamicEntity2->GetMass());
										float _V2Elastic = (2.0f * _DynamicEntity1->GetMass() * _DynamicEntity1->GetVelocity().x + (_DynamicEntity2->GetMass() - _DynamicEntity1->GetMass()) * _DynamicEntity2->GetVelocity().x) / (_DynamicEntity1->GetMass() + _DynamicEntity2->GetMass());

										_Speed = Math::Mix(_V0Plastic, _V1Elastic, _DynamicEntity1->GetElasticity().x * 0.5f + _DynamicEntity2->GetElasticity().x * 0.5f);
										if (_DynamicEntity2->GetLayerResponse(_LayerIndex1))
										{
											_DynamicEntity2->GetVelocity().x = Math::Mix(_V0Plastic, _V2Elastic, _DynamicEntity1->GetElasticity().x * 0.5f + _DynamicEntity2->GetElasticity().x * 0.5f);
										}
									}
								}
							}

							if (_FoundCollision)
							{
								if (_CallBack)
								{
									_CallBack(_Entity1, _Entity2);
								}
							}
						}
						else
						{
							bool _FoundCollision = false;

							for (size_t _AABBIndex1 = 0; _AABBIndex1 < _Entity1->GetBox().Size(); _AABBIndex1++)
							{
								for (size_t _AABBIndex2 = 0; _AABBIndex2 < _Entity2->GetBox().Size(); _AABBIndex2++)
								{
									if (AABB::CheckCollision(_Entity1->GetBox()[_AABBIndex1], _Entity2->GetBox()[_AABBIndex2], _Entity1->GetPosition(), _Entity2->GetPosition()))
									{
										_FoundCollision = true;
										_Position = ResolveCollision(_Position + _Entity1->GetBox()[_AABBIndex1].Position.x - _Entity1->GetBox()[_AABBIndex1].Size.x / 2,
											_Entity2->GetPosition().x + _Entity2->GetBox()[_AABBIndex2].Position.x - _Entity2->GetBox()[_AABBIndex2].Size.x / 2,
											_Entity1->GetBox()[_AABBIndex1].Size.x,
											_Entity2->GetBox()[_AABBIndex2].Size.x,
											_OldSpeed >= 0.0f
										);
										_Speed = -_Speed * _DynamicEntity1->GetElasticity().x;
									}
								}
							}

							if (_FoundCollision)
							{
								if (_CallBack)
								{
									_CallBack(_Entity1, _Entity2);
								}
							}
						}
					}
				}
				else
				{
					for (const auto& _Entity2 : Entities[_LayerIndex2])
					{
						DynamicEntity* _DynamicEntity2 = dynamic_cast<DynamicEntity*>(_Entity2);
						if (_DynamicEntity2)
						{
							if (_DynamicEntity1 == _DynamicEntity2)
							{
								continue;
							}

							if (HitBox::CheckCollision(_Entity1->GetBox(), _Entity2->GetBox(), _Entity1->GetPosition(), _Entity2->GetPosition()))
							{
								if (_CallBack)
								{
									_CallBack(_Entity1, _Entity2);
								}
							}
						}
						else
						{
							if (HitBox::CheckCollision(_Entity1->GetBox(), _Entity2->GetBox(), _Entity1->GetPosition(), _Entity2->GetPosition()))
							{
								if (_CallBack)
								{
									_CallBack(_Entity1, _Entity2);
								}
							}
						}
					}
				}

			}
		}
	}
}

AuroraCore::Physics::Scene& AuroraCore::Physics::Scene::operator=(const Scene& _Other) noexcept
{
	std::copy(_Other.Entities.begin(), _Other.Entities.end(), Entities.begin());

	return *this;
}

AuroraCore::Physics::Scene& AuroraCore::Physics::Scene::operator=(Scene&& _Other) noexcept
{
	Entities = std::move(_Other.Entities);

	return *this;
}
