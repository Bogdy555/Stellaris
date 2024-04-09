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
			const size_t Size();
			
			HitBox& operator= (const HitBox& _Other) = delete;
			HitBox& operator= (HitBox&& _Other) noexcept;
			AABB& operator[] (const size_t _Index);
			const AABB& operator[] (const size_t _Index) const;
		
		private:

			std::vector<AABB> Boxes;
		
		};

	}

}



#endif
