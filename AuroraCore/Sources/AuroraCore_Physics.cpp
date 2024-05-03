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

AuroraCore::Physics::HitBox& AuroraCore::Physics::HitBox::operator=(HitBox&& _Other) noexcept
{
	Boxes = _Other.Boxes;

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
