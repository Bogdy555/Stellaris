#ifndef AuroraCore_Physics_hpp

#define AuroraCore_Physics_hpp



#include "AuroraCore.hpp"



namespace AuroraCore
{

	namespace Physics
	{

		struct AABB
		{

			float X = -0.5f, Y = -0.5f, Width = 1.0f, Height = 1.0f;

			static const bool CheckCollision(const AABB& _Box1, const AABB& _Box2, const Math::Vec2f& _Position1, const Math::Vec2f& _Position2);

		};

		struct HitBox
		{

			std::vector<AABB> Boxes;

			static const bool CheckCollision(const HitBox& _Box1, const HitBox& _Box2, const Math::Vec2f& _Position1, const Math::Vec2f& _Position2);

		};

		class Entity
		{

		public:

			Entity();
			Entity(const Math::Vec2f& _Position, const HitBox& _Box);
			virtual ~Entity();

			Math::Vec2f Position;
			HitBox Box;

		};

		class DynamicEntity : public Entity
		{

		public:

			DynamicEntity();
			DynamicEntity(const Math::Vec2f& _Position, const HitBox& _Box, const std::vector<bool>& _LayerResponse, const Math::Vec2f& _Velocity, const Math::Vec2f& _Force, const float _Mass, const Math::Vec2f& _Elasticity, const Math::Vec2f& _Drag, const Math::Vec2f& _GravitationalAcceleration);
			~DynamicEntity();

			std::vector<bool> LayerResponse;
			Math::Vec2f Velocity;
			Math::Vec2f Force;
			float Mass;
			Math::Vec2f Elasticity;
			Math::Vec2f Drag;
			Math::Vec2f GravitationalAcceleration;

		};

		class Scene
		{

		public:

			std::vector<std::vector<Entity*>> Layers;
			void (*CallBack)(Entity& _Entity1, Entity& _Entity2) = nullptr;

			void Update(const float _DeltaTime);

		};

		const float ResolveCollision(const float _Start1, const float _Width1, const float _Start2, const float _Width2, const bool _Increas);
		const float ComputeMaxDecelerationForce(const float _Force, const float _Velocity, const float _Mass, const float _DeltaTime);
		const float ComputeMaxAccelerationForce(const float _MaxVelocity, const float _Force, const float _Velocity, const float _Mass, const float _DeltaTime);

	}

}



#endif
