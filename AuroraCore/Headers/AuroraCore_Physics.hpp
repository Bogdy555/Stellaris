#ifndef AuroraCore_Physics_hpp

#define AuroraCore_Physics_hpp



#include "AuroraCore.hpp"



namespace AuroraCore
{

	namespace Physics
	{

		struct AABB
		{

			Math::Vec2f Position;
			Math::Vec2f Size;

			static const bool CheckCollision(const AABB& _Box1, const AABB& _Box2, const Math::Vec2f& Item1Position, const Math::Vec2f& Item2Position);

		};

		class HitBox
		{

		public:

			HitBox();
			HitBox(const HitBox& _Other) = delete;
			HitBox(HitBox&& _Other) noexcept;
			~HitBox();

			static const bool CheckCollision(const HitBox& _HitBox1, const HitBox& _HitBox2, const Math::Vec2f& _Entity1Position, const Math::Vec2f& _Entity2Position);

			void Add(const AABB& _Box);
			void Remove(const size_t _Index);
			void Clear();
			const size_t Size() const;
			
			HitBox& operator= (const HitBox& _Other) noexcept;
			HitBox& operator= (HitBox&& _Other) noexcept;
			AABB& operator[] (const size_t _Index);
			const AABB& operator[] (const size_t _Index) const;
		
		private:

			std::vector<AABB> Boxes;
		
		};

		class Entity
		{

		public:

			Entity();
			Entity(const Math::Vec2f& _Position, const HitBox& _Box);
			virtual ~Entity();

			void SetPosition(Math::Vec2f& _Position);
			void SetHitBox(HitBox& _Box);

			Math::Vec2f& GetPosition();
			HitBox& GetBox();

		protected:
	
			Math::Vec2f Position;
			HitBox Box;

		};

		class DynamicEntity : Entity
		{

		public:
			
			DynamicEntity();
			DynamicEntity(const Math::Vec2f& _Position, const HitBox& _Box);
			~DynamicEntity();

			void SetLayerResponse(std::vector<bool>& _LayerResponse);
			void SetVelocity(Math::Vec2f& _Velocity);
			void SetForce(Math::Vec2f& _Force);
			void SetMass(float& _Mass);
			void SetElasticity(Math::Vec2f& _Elasticity);

			std::vector<bool>& GetLayerResponse();
			Math::Vec2f& GetVelocity();
			Math::Vec2f& GetForce();
			float& GetMass();
			Math::Vec2f& GetElasticity();

		private:

			std::vector<bool> LayerResponse;
			Math::Vec2f Velocity;
			Math::Vec2f Force;
			float Mass;
			Math::Vec2f Elasticity;

		};

		class Scene
		{

		public:

			Scene();
			~Scene();
			Scene(const Scene& _Other) = delete;
			Scene(Scene&& _Other) noexcept;

			Scene& operator= (const Scene& _Other) noexcept;
			Scene& operator= (Scene&& _Other) noexcept;

		private:

			std::vector<std::vector<Entity*>> Entities;

		};

	}

}



#endif
