#include "..\Headers\AuroraCore.hpp"



const bool AuroraCore::Physics::AABB::CheckCollision(const AABB& _Box1, const AABB& _Box2, const AuroraCore::Math::Vec2f& _Position1, const AuroraCore::Math::Vec2f& _Position2)
{
	bool _ColidesX = false;
	bool _ColidesY = false;

	if (_Box1.X + _Position1.x <= _Box2.X + _Position2.x)
	{
		if (_Box1.X + _Position1.x + _Box1.Width > _Box2.X + _Position2.x)
		{
			_ColidesX = true;
		}
	}
	else
	{
		if (_Box2.X + _Position2.x + _Box2.Width > _Box1.X + _Position1.x)
		{
			_ColidesX = true;
		}
	}

	if (_Box1.Y + _Position1.y <= _Box2.Y + _Position2.y)
	{
		if (_Box1.Y + _Position1.y + _Box1.Height > _Box2.Y + _Position2.y)
		{
			_ColidesY = true;
		}
	}
	else
	{
		if (_Box2.Y + _Position2.y + _Box2.Height > _Box1.Y + _Position1.y)
		{
			_ColidesY = true;
		}
	}

	return _ColidesX && _ColidesY;
}



const bool AuroraCore::Physics::HitBox::CheckCollision(const HitBox& _Box1, const HitBox& _Box2, const AuroraCore::Math::Vec2f& _Position1, const AuroraCore::Math::Vec2f& _Position2)
{
	for (size_t _Index1 = 0; _Index1 < _Box1.Boxes.size(); _Index1++)
	{
		for (size_t _Index2 = 0; _Index2 < _Box2.Boxes.size(); _Index2++)
		{
			if (AABB::CheckCollision(_Box1.Boxes[_Index1], _Box2.Boxes[_Index2], _Position1, _Position2))
			{
				return true;
			}
		}
	}

	return false;
}



AuroraCore::Physics::Entity::Entity() : Position(Math::Vec2f(0.0f, 0.0f)), Box()
{

}

AuroraCore::Physics::Entity::Entity(const Math::Vec2f& _Position, const HitBox& _Box) : Position(_Position), Box(_Box)
{

}

AuroraCore::Physics::Entity::~Entity()
{

}



AuroraCore::Physics::DynamicEntity::DynamicEntity() : Entity(), LayerResponse(), Velocity(Math::Vec2f(0.0f, 0.0f)), Force(Math::Vec2f(0.0f, 0.0f)), Mass(1.0f), Elasticity(Math::Vec2f(0.0f, 0.0f)), Drag(Math::Vec2f(0.0f, 0.0f)), GravitationalAcceleration(Math::Vec2f(0.0f, -9.8f))
{

}

AuroraCore::Physics::DynamicEntity::DynamicEntity(const Math::Vec2f& _Position, const HitBox& _Box, const std::vector<bool>& _LayerResponse, const Math::Vec2f& _Velocity, const Math::Vec2f& _Force, const float _Mass, const Math::Vec2f& _Elasticity, const Math::Vec2f& _Drag, const Math::Vec2f& _GravitationalAcceleration) : Entity(_Position, _Box), LayerResponse(_LayerResponse), Velocity(_Velocity), Force(_Force), Mass(_Mass), Elasticity(_Elasticity), Drag(_Drag), GravitationalAcceleration(_GravitationalAcceleration)
{

}

AuroraCore::Physics::DynamicEntity::~DynamicEntity()
{

}



static const float Sign(const float _Value)
{
	return (float)(_Value > 0.0f) - (float)(_Value < 0.0f);
}

// In ce directie trebuie sa mergi dupa ce detectezi o coliziune si cat pentru a o rezolva

const float AuroraCore::Physics::ResolveCollision(const float _Start1, const float _Width1, const float _Start2, const float _Width2, const bool _Increas)
{
	if (_Increas)
	{
		return (_Start2 + _Width2) - _Start1;
	}
	else
	{
		return _Start2 - (_Start1 + _Width1);
	}

	return 0.0f;
}

// Rezolva inconsistente cauzate de delta time. Inainte player ul mergea la stanga, decelera, iar apoi accelera foarte putin la dreapta si tot oscila in jurul pozitiei curente

const float AuroraCore::Physics::ComputeMaxDecelerationForce(const float _Force, const float _Velocity, const float _Mass, const float _DeltaTime)
{
	if (!_DeltaTime)
	{
		return 0.0f;
	}

	return Sign(-_Velocity) * Math::Min(_Force, abs(_Velocity / _DeltaTime * _Mass));
}

// Rezolva inconsistente cauzate de delta time. Viteza acum da CAP la valoarea dorita indiferent de frame rate

const float AuroraCore::Physics::ComputeMaxAccelerationForce(const float _MaxVelocity, const float _Force, const float _Velocity, const float _Mass, const float _DeltaTime)
{
	if (!_DeltaTime || (Sign(_Velocity) == Sign(_MaxVelocity) && abs(_Velocity) >= abs(_MaxVelocity)))
	{
		return 0.0f;
	}

	return Sign(_MaxVelocity) * Math::Min(_Force, abs((_MaxVelocity - _Velocity) / _DeltaTime * _Mass));
}



// Updateaza scenta
// Posibilitati:
// Y
//   Layer resp
//     Dynamic
//     Static
//   No resp
//     Dynamic
//     Static
// X
//   Layer resp
//     Dynamic
//     Static
//   No resp
//     Dynamic
//     Static

void AuroraCore::Physics::Scene::Update(const float _DeltaTime)
{
	// Pentru fiecare entitate dinamica din fiecare layer

	for (size_t _LayerIndex1 = 0; _LayerIndex1 < Layers.size(); _LayerIndex1++)
	{
		for (size_t _EntityIndex1 = 0; _EntityIndex1 < Layers[_LayerIndex1].size(); _EntityIndex1++)
		{
			if (!dynamic_cast<DynamicEntity*>(Layers[_LayerIndex1][_EntityIndex1]))
			{
				continue;
			}

			// Updateaza o

			DynamicEntity& _Entity = *(DynamicEntity*)(Layers[_LayerIndex1][_EntityIndex1]);

			_Entity.Force += _Entity.GravitationalAcceleration * _Entity.Mass;
			_Entity.Force += Math::Vec2f(Physics::ComputeMaxDecelerationForce(abs(_Entity.Velocity.x * _Entity.Velocity.Magnitude() * _Entity.Drag.x), _Entity.Velocity.x, _Entity.Mass, _DeltaTime), Physics::ComputeMaxDecelerationForce(abs(_Entity.Velocity.y * _Entity.Velocity.Magnitude() * _Entity.Drag.y), _Entity.Velocity.y, _Entity.Mass, _DeltaTime));

			// Updateaza o pe y

			_Entity.Velocity.y += _Entity.Force.y / _Entity.Mass * _DeltaTime;
			_Entity.Position.y += _Entity.Velocity.y * abs(_DeltaTime);
			_Entity.Force.y = 0.0f;

			// Verifica de coliziuni

			for (size_t _LayerIndex2 = 0; _LayerIndex2 < Layers.size(); _LayerIndex2++)
			{
				if (!_Entity.LayerResponse[_LayerIndex2])
				{
					continue;
				}

				for (size_t _EntityIndex2 = 0; _EntityIndex2 < Layers[_LayerIndex2].size(); _EntityIndex2++)
				{
					if (_LayerIndex1 == _LayerIndex2 && _EntityIndex1 == _EntityIndex2)
					{
						continue;
					}

					if (dynamic_cast<DynamicEntity*>(Layers[_LayerIndex2][_EntityIndex2]))
					{
						DynamicEntity& _CollisionEntity = *(DynamicEntity*)(Layers[_LayerIndex2][_EntityIndex2]);

						bool _FoundCollision = false;

						for (size_t _BoxIndex1 = 0; _BoxIndex1 < _Entity.Box.Boxes.size(); _BoxIndex1++)
						{
							const AABB& _Box1 = _Entity.Box.Boxes[_BoxIndex1];

							for (size_t _BoxIndex2 = 0; _BoxIndex2 < _CollisionEntity.Box.Boxes.size(); _BoxIndex2++)
							{
								const AABB& _Box2 = _CollisionEntity.Box.Boxes[_BoxIndex2];

								// Coliziune Y Layer resp Dynamic

								if (AABB::CheckCollision(_Box1, _Box2, _Entity.Position, _CollisionEntity.Position))
								{
									float _V0Plastic = (_Entity.Mass * _Entity.Velocity.y + _CollisionEntity.Mass * _CollisionEntity.Velocity.y) / (_Entity.Mass + _CollisionEntity.Mass);
									float _V1Elastic = ((_Entity.Mass - _CollisionEntity.Mass) * _Entity.Velocity.y + 2.0f * _CollisionEntity.Mass * _CollisionEntity.Velocity.y) / (_Entity.Mass + _CollisionEntity.Mass);
									float _V2Elastic = (2.0f * _Entity.Mass * _Entity.Velocity.y + (_CollisionEntity.Mass - _Entity.Mass) * _CollisionEntity.Velocity.y) / (_Entity.Mass + _CollisionEntity.Mass);

									_Entity.Position.y += ResolveCollision(_Box1.Y + _Entity.Position.y, _Box1.Height, _Box2.Y + _CollisionEntity.Position.y, _Box2.Height, _Entity.Velocity.y <= 0);
									_Entity.Velocity.y = Math::Mix(_V0Plastic, _V1Elastic, _Entity.Elasticity.y * 0.5f + _CollisionEntity.Elasticity.y * 0.5f);

									if (_CollisionEntity.LayerResponse[_LayerIndex1])
									{
										_CollisionEntity.Velocity.y = Math::Mix(_V0Plastic, _V2Elastic, _Entity.Elasticity.y * 0.5f + _CollisionEntity.Elasticity.y * 0.5f);
									}

									_FoundCollision = true;
								}
							}
						}

						if (_FoundCollision && CallBack)
						{
							CallBack(_Entity, _CollisionEntity);
						}
					}
					else
					{
						Entity& _CollisionEntity = *Layers[_LayerIndex2][_EntityIndex2];

						bool _FoundCollision = false;

						for (size_t _BoxIndex1 = 0; _BoxIndex1 < _Entity.Box.Boxes.size(); _BoxIndex1++)
						{
							const AABB& _Box1 = _Entity.Box.Boxes[_BoxIndex1];

							for (size_t _BoxIndex2 = 0; _BoxIndex2 < _CollisionEntity.Box.Boxes.size(); _BoxIndex2++)
							{
								const AABB& _Box2 = _CollisionEntity.Box.Boxes[_BoxIndex2];

								// Coliziune Y Layer resp Static

								if (AABB::CheckCollision(_Box1, _Box2, _Entity.Position, _CollisionEntity.Position))
								{
									_Entity.Position.y += ResolveCollision(_Box1.Y + _Entity.Position.y, _Box1.Height, _Box2.Y + _CollisionEntity.Position.y, _Box2.Height, _Entity.Velocity.y <= 0);
									_Entity.Velocity.y = -_Entity.Velocity.y * _Entity.Elasticity.y;

									_FoundCollision = true;
								}
							}
						}

						if (_FoundCollision && CallBack)
						{
							CallBack(_Entity, _CollisionEntity);
						}
					}
				}
			}

			for (size_t _LayerIndex2 = 0; _LayerIndex2 < Layers.size(); _LayerIndex2++)
			{
				if (_Entity.LayerResponse[_LayerIndex2])
				{
					continue;
				}

				for (size_t _EntityIndex2 = 0; _EntityIndex2 < Layers[_LayerIndex2].size(); _EntityIndex2++)
				{
					if (_LayerIndex1 == _LayerIndex2 && _EntityIndex1 == _EntityIndex2)
					{
						continue;
					}

					if (dynamic_cast<DynamicEntity*>(Layers[_LayerIndex2][_EntityIndex2]))
					{
						DynamicEntity& _CollisionEntity = *(DynamicEntity*)(Layers[_LayerIndex2][_EntityIndex2]);

						bool _FoundCollision = false;

						for (size_t _BoxIndex1 = 0; _BoxIndex1 < _Entity.Box.Boxes.size(); _BoxIndex1++)
						{
							const AABB& _Box1 = _Entity.Box.Boxes[_BoxIndex1];

							for (size_t _BoxIndex2 = 0; _BoxIndex2 < _CollisionEntity.Box.Boxes.size(); _BoxIndex2++)
							{
								const AABB& _Box2 = _CollisionEntity.Box.Boxes[_BoxIndex2];

								// Coliziune Y No resp Dynamic

								if (AABB::CheckCollision(_Box1, _Box2, _Entity.Position, _CollisionEntity.Position))
								{
									if (_CollisionEntity.LayerResponse[_LayerIndex1])
									{
										float _VPlastic = _Entity.Velocity.y;
										float _VElastic = (2.0f * _Entity.Mass * _Entity.Velocity.y + (_CollisionEntity.Mass - _Entity.Mass) * _CollisionEntity.Velocity.y) / (_Entity.Mass + _CollisionEntity.Mass);

										_CollisionEntity.Position.y += ResolveCollision(_Box2.Y + _CollisionEntity.Position.y, _Box2.Height, _Box1.Y + _Entity.Position.y, _Box1.Height, _Entity.Velocity.y >= 0);
										_CollisionEntity.Velocity.y = Math::Mix(_VPlastic, _VElastic, _CollisionEntity.Elasticity.y);
									}

									_FoundCollision = true;
								}
							}
						}

						if (_FoundCollision && CallBack)
						{
							CallBack(_Entity, _CollisionEntity);
						}
					}
					else
					{
						Entity& _CollisionEntity = *Layers[_LayerIndex2][_EntityIndex2];

						bool _FoundCollision = false;

						for (size_t _BoxIndex1 = 0; _BoxIndex1 < _Entity.Box.Boxes.size(); _BoxIndex1++)
						{
							const AABB& _Box1 = _Entity.Box.Boxes[_BoxIndex1];

							for (size_t _BoxIndex2 = 0; _BoxIndex2 < _CollisionEntity.Box.Boxes.size(); _BoxIndex2++)
							{
								const AABB& _Box2 = _CollisionEntity.Box.Boxes[_BoxIndex2];

								// Coliziune Y No resp Static

								if (AABB::CheckCollision(_Box1, _Box2, _Entity.Position, _CollisionEntity.Position))
								{
									_FoundCollision = true;
								}
							}
						}

						if (_FoundCollision && CallBack)
						{
							CallBack(_Entity, _CollisionEntity);
						}
					}
				}
			}

			// Updateaza o pe x

			_Entity.Velocity.x += _Entity.Force.x / _Entity.Mass * _DeltaTime;
			_Entity.Position.x += _Entity.Velocity.x * abs(_DeltaTime);
			_Entity.Force.x = 0.0f;

			// Verifica de coliziuni

			for (size_t _LayerIndex2 = 0; _LayerIndex2 < Layers.size(); _LayerIndex2++)
			{
				if (!_Entity.LayerResponse[_LayerIndex2])
				{
					continue;
				}

				for (size_t _EntityIndex2 = 0; _EntityIndex2 < Layers[_LayerIndex2].size(); _EntityIndex2++)
				{
					if (_LayerIndex1 == _LayerIndex2 && _EntityIndex1 == _EntityIndex2)
					{
						continue;
					}

					if (dynamic_cast<DynamicEntity*>(Layers[_LayerIndex2][_EntityIndex2]))
					{
						DynamicEntity& _CollisionEntity = *(DynamicEntity*)(Layers[_LayerIndex2][_EntityIndex2]);

						bool _FoundCollision = false;

						for (size_t _BoxIndex1 = 0; _BoxIndex1 < _Entity.Box.Boxes.size(); _BoxIndex1++)
						{
							const AABB& _Box1 = _Entity.Box.Boxes[_BoxIndex1];

							for (size_t _BoxIndex2 = 0; _BoxIndex2 < _CollisionEntity.Box.Boxes.size(); _BoxIndex2++)
							{
								const AABB& _Box2 = _CollisionEntity.Box.Boxes[_BoxIndex2];

								// Coliziune X Layer resp Dynamic

								if (AABB::CheckCollision(_Box1, _Box2, _Entity.Position, _CollisionEntity.Position))
								{
									float _V0Plastic = (_Entity.Mass * _Entity.Velocity.x + _CollisionEntity.Mass * _CollisionEntity.Velocity.x) / (_Entity.Mass + _CollisionEntity.Mass);
									float _V1Elastic = ((_Entity.Mass - _CollisionEntity.Mass) * _Entity.Velocity.x + 2.0f * _CollisionEntity.Mass * _CollisionEntity.Velocity.x) / (_Entity.Mass + _CollisionEntity.Mass);
									float _V2Elastic = (2.0f * _Entity.Mass * _Entity.Velocity.x + (_CollisionEntity.Mass - _Entity.Mass) * _CollisionEntity.Velocity.x) / (_Entity.Mass + _CollisionEntity.Mass);

									_Entity.Position.x += ResolveCollision(_Box1.X + _Entity.Position.x, _Box1.Width, _Box2.X + _CollisionEntity.Position.x, _Box2.Width, _Entity.Velocity.x <= 0);
									_Entity.Velocity.x = Math::Mix(_V0Plastic, _V1Elastic, _Entity.Elasticity.x * 0.5f + _CollisionEntity.Elasticity.x * 0.5f);

									if (_CollisionEntity.LayerResponse[_LayerIndex1])
									{
										_CollisionEntity.Velocity.x = Math::Mix(_V0Plastic, _V2Elastic, _Entity.Elasticity.x * 0.5f + _CollisionEntity.Elasticity.x * 0.5f);
									}

									_FoundCollision = true;
								}
							}
						}

						if (_FoundCollision && CallBack)
						{
							CallBack(_Entity, _CollisionEntity);
						}
					}
					else
					{
						Entity& _CollisionEntity = *Layers[_LayerIndex2][_EntityIndex2];

						bool _FoundCollision = false;

						for (size_t _BoxIndex1 = 0; _BoxIndex1 < _Entity.Box.Boxes.size(); _BoxIndex1++)
						{
							const AABB& _Box1 = _Entity.Box.Boxes[_BoxIndex1];

							for (size_t _BoxIndex2 = 0; _BoxIndex2 < _CollisionEntity.Box.Boxes.size(); _BoxIndex2++)
							{
								const AABB& _Box2 = _CollisionEntity.Box.Boxes[_BoxIndex2];

								// Coliziune X Layer resp Static

								if (AABB::CheckCollision(_Box1, _Box2, _Entity.Position, _CollisionEntity.Position))
								{
									_Entity.Position.x += ResolveCollision(_Box1.X + _Entity.Position.x, _Box1.Width, _Box2.X + _CollisionEntity.Position.x, _Box2.Width, _Entity.Velocity.x <= 0);
									_Entity.Velocity.x = -_Entity.Velocity.x * _Entity.Elasticity.x;

									_FoundCollision = true;
								}
							}
						}

						if (_FoundCollision && CallBack)
						{
							CallBack(_Entity, _CollisionEntity);
						}
					}
				}
			}

			for (size_t _LayerIndex2 = 0; _LayerIndex2 < Layers.size(); _LayerIndex2++)
			{
				if (_Entity.LayerResponse[_LayerIndex2])
				{
					continue;
				}

				for (size_t _EntityIndex2 = 0; _EntityIndex2 < Layers[_LayerIndex2].size(); _EntityIndex2++)
				{
					if (_LayerIndex1 == _LayerIndex2 && _EntityIndex1 == _EntityIndex2)
					{
						continue;
					}

					if (dynamic_cast<DynamicEntity*>(Layers[_LayerIndex2][_EntityIndex2]))
					{
						DynamicEntity& _CollisionEntity = *(DynamicEntity*)(Layers[_LayerIndex2][_EntityIndex2]);

						bool _FoundCollision = false;

						for (size_t _BoxIndex1 = 0; _BoxIndex1 < _Entity.Box.Boxes.size(); _BoxIndex1++)
						{
							const AABB& _Box1 = _Entity.Box.Boxes[_BoxIndex1];

							for (size_t _BoxIndex2 = 0; _BoxIndex2 < _CollisionEntity.Box.Boxes.size(); _BoxIndex2++)
							{
								const AABB& _Box2 = _CollisionEntity.Box.Boxes[_BoxIndex2];

								// Coliziune X No resp Dynamic

								if (AABB::CheckCollision(_Box1, _Box2, _Entity.Position, _CollisionEntity.Position))
								{
									if (_CollisionEntity.LayerResponse[_LayerIndex1])
									{
										float _VPlastic = _Entity.Velocity.x;
										float _VElastic = (2.0f * _Entity.Mass * _Entity.Velocity.x + (_CollisionEntity.Mass - _Entity.Mass) * _CollisionEntity.Velocity.x) / (_Entity.Mass + _CollisionEntity.Mass);

										_CollisionEntity.Position.x += ResolveCollision(_Box2.X + _CollisionEntity.Position.x, _Box2.Width, _Box1.X + _Entity.Position.x, _Box1.Width, _Entity.Velocity.x >= 0);
										_CollisionEntity.Velocity.x = Math::Mix(_VPlastic, _VElastic, _CollisionEntity.Elasticity.x);
									}

									_FoundCollision = true;
								}
							}
						}

						if (_FoundCollision && CallBack)
						{
							CallBack(_Entity, _CollisionEntity);
						}
					}
					else
					{
						Entity& _CollisionEntity = *Layers[_LayerIndex2][_EntityIndex2];

						bool _FoundCollision = false;

						for (size_t _BoxIndex1 = 0; _BoxIndex1 < _Entity.Box.Boxes.size(); _BoxIndex1++)
						{
							const AABB& _Box1 = _Entity.Box.Boxes[_BoxIndex1];

							for (size_t _BoxIndex2 = 0; _BoxIndex2 < _CollisionEntity.Box.Boxes.size(); _BoxIndex2++)
							{
								const AABB& _Box2 = _CollisionEntity.Box.Boxes[_BoxIndex2];

								// Coliziune X No resp Static

								if (AABB::CheckCollision(_Box1, _Box2, _Entity.Position, _CollisionEntity.Position))
								{
									_FoundCollision = true;
								}
							}
						}

						if (_FoundCollision && CallBack)
						{
							CallBack(_Entity, _CollisionEntity);
						}
					}
				}
			}
		}
	}
}
