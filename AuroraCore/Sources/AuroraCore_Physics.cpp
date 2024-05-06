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



AuroraCore::Physics::DynamicEntity::DynamicEntity()
{

}

AuroraCore::Physics::DynamicEntity::DynamicEntity(const Math::Vec2f& _Position, const HitBox& _Box)
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

void AuroraCore::Physics::DynamicEntity::SetForce(Math::Vec2f& _Force)
{
	Force = _Force;
}

void AuroraCore::Physics::DynamicEntity::SetMass(float& _Mass)
{
	Mass = _Mass;
}

void AuroraCore::Physics::DynamicEntity::SetElasticity(Math::Vec2f& _Elasticity)
{
	Elasticity = _Elasticity;
}

std::vector<bool>& AuroraCore::Physics::DynamicEntity::GetLayerResponse()
{
	return LayerResponse;
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

AuroraCore::Physics::Scene::~Scene()
{

}

AuroraCore::Physics::Scene::Scene(Scene&& _Other) noexcept : Entities(std::move(_Other.Entities))
{

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
