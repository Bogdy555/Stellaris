#include "..\Headers\AuroraCore.hpp"



const float AuroraCore::Math::Pi = 3.14159265f;
const float AuroraCore::Math::DegreesToRadians = 3.14159265f / 180.0f;
const float AuroraCore::Math::RadiansToDegrees = 180.0f / 3.14159265f;



void AuroraCore::Math::Swap(float& _A, float& _B)
{
	float _Aux = _A;
	_A = _B;
	_B = _Aux;
}

const float AuroraCore::Math::Clamp(const float _Value, const float _Min, const float _Max)
{
	return _Value * (_Min <= _Value && _Value <= _Max) + _Min * (_Min > _Value) + _Max * (_Value > _Max);
}

const float AuroraCore::Math::Mix(const float _A, const float _B, const float _Percentage)
{
	return _A + (_B - _A) * _Percentage;
}

const float AuroraCore::Math::Min(const float _A, const float _B)
{
	return _A * (_A <= _B) + _B * (_A > _B);
}

const float AuroraCore::Math::Max(const float _A, const float _B)
{
	return _A * (_A >= _B) + _B * (_A < _B);
}



AuroraCore::Math::Vec2f::Vec2f() : x(0.0f), y(0.0f)
{

}

AuroraCore::Math::Vec2f::Vec2f(const float _x, const float _y) : x(_x), y(_y)
{

}

AuroraCore::Math::Vec2f::Vec2f(const Vec2f& _Other) : x(_Other.x), y(_Other.y)
{

}

AuroraCore::Math::Vec2f::Vec2f(Vec2f&& _Other) noexcept : x(_Other.x), y(_Other.y)
{

}

AuroraCore::Math::Vec2f::~Vec2f()
{

}

float* AuroraCore::Math::Vec2f::Data()
{
	return &x;
}

const float* AuroraCore::Math::Vec2f::Data() const
{
	return &x;
}

const float AuroraCore::Math::Vec2f::Magnitude() const
{
	return sqrtf(x * x + y * y);
}

const AuroraCore::Math::Vec2f& AuroraCore::Math::Vec2f::Normalize()
{
	*this /= Magnitude();

	return *this;
}

const AuroraCore::Math::Vec2f AuroraCore::Math::Vec2f::Normalized() const
{
	return *this / Magnitude();
}

const AuroraCore::Math::Vec2f& AuroraCore::Math::Vec2f::operator+ () const
{
	return *this;
}

const AuroraCore::Math::Vec2f AuroraCore::Math::Vec2f::operator- () const
{
	return Vec2f(-x, -y);
}

const AuroraCore::Math::Vec2f AuroraCore::Math::Vec2f::operator+ (const Vec2f& _Other) const
{
	return Vec2f(x + _Other.x, y + _Other.y);
}

const AuroraCore::Math::Vec2f& AuroraCore::Math::Vec2f::operator+= (const Vec2f& _Other)
{
	x += _Other.x;
	y += _Other.y;

	return *this;
}

const AuroraCore::Math::Vec2f AuroraCore::Math::Vec2f::operator+ (const float _Scale) const
{
	return Vec2f(x + _Scale, y + _Scale);
}

const AuroraCore::Math::Vec2f& AuroraCore::Math::Vec2f::operator+= (const float _Scale)
{
	x += _Scale;
	y += _Scale;

	return *this;
}

const AuroraCore::Math::Vec2f AuroraCore::Math::Vec2f::operator- (const Vec2f& _Other) const
{
	return Vec2f(x - _Other.x, y - _Other.y);
}

const AuroraCore::Math::Vec2f& AuroraCore::Math::Vec2f::operator-= (const Vec2f& _Other)
{
	x -= _Other.x;
	y -= _Other.y;

	return *this;
}

const AuroraCore::Math::Vec2f AuroraCore::Math::Vec2f::operator- (const float _Scale) const
{
	return Vec2f(x - _Scale, y - _Scale);
}

const AuroraCore::Math::Vec2f& AuroraCore::Math::Vec2f::operator-= (const float _Scale)
{
	x -= _Scale;
	y -= _Scale;

	return *this;
}

const AuroraCore::Math::Vec2f AuroraCore::Math::Vec2f::operator* (const Vec2f& _Other) const
{
	return Vec2f(x * _Other.x, y * _Other.y);
}

const AuroraCore::Math::Vec2f& AuroraCore::Math::Vec2f::operator*= (const Vec2f& _Other)
{
	x *= _Other.x;
	y *= _Other.y;

	return *this;
}

const AuroraCore::Math::Vec2f AuroraCore::Math::Vec2f::operator* (const float _Scale) const
{
	return Vec2f(x * _Scale, y * _Scale);
}

const AuroraCore::Math::Vec2f& AuroraCore::Math::Vec2f::operator*= (const float _Scale)
{
	x *= _Scale;
	y *= _Scale;

	return *this;
}

const AuroraCore::Math::Vec2f AuroraCore::Math::Vec2f::operator/ (const Vec2f& _Other) const
{
	return Vec2f(x / _Other.x, y / _Other.y);
}

const AuroraCore::Math::Vec2f& AuroraCore::Math::Vec2f::operator/= (const Vec2f& _Other)
{
	x /= _Other.x;
	y /= _Other.y;

	return *this;
}

const AuroraCore::Math::Vec2f AuroraCore::Math::Vec2f::operator/ (const float _Scale) const
{
	return Vec2f(x / _Scale, y / _Scale);
}

const AuroraCore::Math::Vec2f& AuroraCore::Math::Vec2f::operator/= (const float _Scale)
{
	x /= _Scale;
	y /= _Scale;

	return *this;
}

const bool AuroraCore::Math::Vec2f::operator== (const Vec2f& _Other) const
{
	return x == _Other.x && y == _Other.y;
}

const bool AuroraCore::Math::Vec2f::operator!= (const Vec2f& _Other) const
{
	return x != _Other.x || y != _Other.y;
}

float& AuroraCore::Math::Vec2f::operator[] (const size_t _Index)
{
	return (&x)[_Index];
}

const float& AuroraCore::Math::Vec2f::operator[] (const size_t _Index) const
{
	return (&x)[_Index];
}

const AuroraCore::Math::Vec2f& AuroraCore::Math::Vec2f::operator= (const Vec2f& _Other)
{
	x = _Other.x;
	y = _Other.y;

	return *this;
}

const AuroraCore::Math::Vec2f& AuroraCore::Math::Vec2f::operator= (Vec2f&& _Other) noexcept
{
	x = _Other.x;
	y = _Other.y;

	return *this;
}

const float AuroraCore::Math::Vec2f::GetAngle(const Vec2f& _A, const Vec2f& _B)
{
	return acosf(Dot(_A.Normalized(), _B.Normalized()));
}

const float AuroraCore::Math::Vec2f::Distance(const Vec2f& _A, const Vec2f& _B)
{
	return (_B - _A).Magnitude();
}

const float AuroraCore::Math::Vec2f::Dot(const Vec2f& _A, const Vec2f& _B)
{
	return _A.x * _B.x + _A.y * _B.y;
}

const AuroraCore::Math::Vec2f AuroraCore::Math::Vec2f::Clamp(const Vec2f& _Value, const Vec2f& _Min, const Vec2f& _Max)
{
	return Vec2f(AuroraCore::Math::Clamp(_Value.x, _Min.x, _Max.x), AuroraCore::Math::Clamp(_Value.y, _Min.y, _Max.y));
}

const AuroraCore::Math::Vec2f AuroraCore::Math::Vec2f::Mix(const Vec2f& _A, const Vec2f& _B, const float _Percentage)
{
	return Vec2f(AuroraCore::Math::Mix(_A.x, _B.x, _Percentage), AuroraCore::Math::Mix(_A.y, _B.y, _Percentage));
}

const AuroraCore::Math::Vec2f AuroraCore::Math::Vec2f::Pow(const Vec2f& _Base, const Vec2f& _Pow)
{
	return Vec2f(powf(_Base.x, _Pow.x), powf(_Base.y, _Pow.y));
}

const AuroraCore::Math::Vec2f AuroraCore::Math::Vec2f::Exp(const Vec2f& _Pow)
{
	return Vec2f(expf(_Pow.x), expf(_Pow.y));
}

const AuroraCore::Math::Vec2f AuroraCore::Math::Vec2f::Min(const Vec2f& _A, const Vec2f& _B)
{
	return Vec2f(AuroraCore::Math::Min(_A.x, _B.x), AuroraCore::Math::Min(_A.y, _B.y));
}

const AuroraCore::Math::Vec2f AuroraCore::Math::Vec2f::Max(const Vec2f& _A, const Vec2f& _B)
{
	return Vec2f(AuroraCore::Math::Max(_A.x, _B.x), AuroraCore::Math::Max(_A.y, _B.y));
}

const AuroraCore::Math::Vec2f AuroraCore::Math::Vec2f::Reflect(const Vec2f& _Vec, const Vec2f& _Normal)
{
	return _Vec - _Normal * 2.0f * Dot(_Vec, _Normal) / _Normal.Magnitude() / _Normal.Magnitude();
}



AuroraCore::Math::Vec3f::Vec3f() : x(0.0f), y(0.0f), z(0.0f)
{

}

AuroraCore::Math::Vec3f::Vec3f(const float _x, const float _y, const float _z) : x(_x), y(_y), z(_z)
{

}

AuroraCore::Math::Vec3f::Vec3f(const Vec3f& _Other) : x(_Other.x), y(_Other.y), z(_Other.z)
{

}

AuroraCore::Math::Vec3f::Vec3f(Vec3f&& _Other) noexcept : x(_Other.x), y(_Other.y), z(_Other.z)
{

}

AuroraCore::Math::Vec3f::Vec3f(const Vec2f& _Other, const float _z) : x(_Other.x), y(_Other.y), z(_z)
{

}

AuroraCore::Math::Vec3f::~Vec3f()
{

}

AuroraCore::Math::Vec3f::operator const AuroraCore::Math::Vec2f() const
{
	return Vec2f(x, y);
}

float* AuroraCore::Math::Vec3f::Data()
{
	return &x;
}

const float* AuroraCore::Math::Vec3f::Data() const
{
	return &x;
}

const float AuroraCore::Math::Vec3f::Magnitude() const
{
	return sqrtf(x * x + y * y + z * z);
}

const AuroraCore::Math::Vec3f& AuroraCore::Math::Vec3f::Normalize()
{
	*this /= Magnitude();

	return *this;
}

const AuroraCore::Math::Vec3f AuroraCore::Math::Vec3f::Normalized() const
{
	return *this / Magnitude();
}

const AuroraCore::Math::Vec3f& AuroraCore::Math::Vec3f::operator+ () const
{
	return *this;
}

const AuroraCore::Math::Vec3f AuroraCore::Math::Vec3f::operator- () const
{
	return Vec3f(-x, -y, -z);
}

const AuroraCore::Math::Vec3f AuroraCore::Math::Vec3f::operator+ (const Vec3f& _Other) const
{
	return Vec3f(x + _Other.x, y + _Other.y, z + _Other.z);
}

const AuroraCore::Math::Vec3f& AuroraCore::Math::Vec3f::operator+= (const Vec3f& _Other)
{
	x += _Other.x;
	y += _Other.y;
	z += _Other.z;

	return *this;
}

const AuroraCore::Math::Vec3f AuroraCore::Math::Vec3f::operator+ (const float _Scale) const
{
	return Vec3f(x + _Scale, y + _Scale, z + _Scale);
}

const AuroraCore::Math::Vec3f& AuroraCore::Math::Vec3f::operator+= (const float _Scale)
{
	x += _Scale;
	y += _Scale;
	z += _Scale;

	return *this;
}

const AuroraCore::Math::Vec3f AuroraCore::Math::Vec3f::operator- (const Vec3f& _Other) const
{
	return Vec3f(x - _Other.x, y - _Other.y, z - _Other.z);
}

const AuroraCore::Math::Vec3f& AuroraCore::Math::Vec3f::operator-= (const Vec3f& _Other)
{
	x -= _Other.x;
	y -= _Other.y;
	z -= _Other.z;

	return *this;
}

const AuroraCore::Math::Vec3f AuroraCore::Math::Vec3f::operator- (const float _Scale) const
{
	return Vec3f(x - _Scale, y - _Scale, z - _Scale);
}

const AuroraCore::Math::Vec3f& AuroraCore::Math::Vec3f::operator-= (const float _Scale)
{
	x -= _Scale;
	y -= _Scale;
	z -= _Scale;

	return *this;
}

const AuroraCore::Math::Vec3f AuroraCore::Math::Vec3f::operator* (const Vec3f& _Other) const
{
	return Vec3f(x * _Other.x, y * _Other.y, z * _Other.z);
}

const AuroraCore::Math::Vec3f& AuroraCore::Math::Vec3f::operator*= (const Vec3f& _Other)
{
	x *= _Other.x;
	y *= _Other.y;
	z *= _Other.z;

	return *this;
}

const AuroraCore::Math::Vec3f AuroraCore::Math::Vec3f::operator* (const float _Scale) const
{
	return Vec3f(x * _Scale, y * _Scale, z * _Scale);
}

const AuroraCore::Math::Vec3f& AuroraCore::Math::Vec3f::operator*= (const float _Scale)
{
	x *= _Scale;
	y *= _Scale;
	z *= _Scale;

	return *this;
}

const AuroraCore::Math::Vec3f AuroraCore::Math::Vec3f::operator/ (const Vec3f& _Other) const
{
	return Vec3f(x / _Other.x, y / _Other.y, z / _Other.z);
}

const AuroraCore::Math::Vec3f& AuroraCore::Math::Vec3f::operator/= (const Vec3f& _Other)
{
	x /= _Other.x;
	y /= _Other.y;
	z /= _Other.z;

	return *this;
}

const AuroraCore::Math::Vec3f AuroraCore::Math::Vec3f::operator/ (const float _Scale) const
{
	return Vec3f(x / _Scale, y / _Scale, z / _Scale);
}

const AuroraCore::Math::Vec3f& AuroraCore::Math::Vec3f::operator/= (const float _Scale)
{
	x /= _Scale;
	y /= _Scale;
	z /= _Scale;

	return *this;
}

const bool AuroraCore::Math::Vec3f::operator== (const Vec3f& _Other) const
{
	return x == _Other.x && y == _Other.y && z == _Other.z;
}

const bool AuroraCore::Math::Vec3f::operator!= (const Vec3f& _Other) const
{
	return x != _Other.x || y != _Other.y || z != _Other.z;
}

float& AuroraCore::Math::Vec3f::operator[] (const size_t _Index)
{
	return (&x)[_Index];
}

const float& AuroraCore::Math::Vec3f::operator[] (const size_t _Index) const
{
	return (&x)[_Index];
}

const AuroraCore::Math::Vec3f& AuroraCore::Math::Vec3f::operator= (const Vec3f& _Other)
{
	x = _Other.x;
	y = _Other.y;
	z = _Other.z;

	return *this;
}

const AuroraCore::Math::Vec3f& AuroraCore::Math::Vec3f::operator= (Vec3f&& _Other) noexcept
{
	x = _Other.x;
	y = _Other.y;
	z = _Other.z;

	return *this;
}

const float AuroraCore::Math::Vec3f::GetAngle(const Vec3f& _A, const Vec3f& _B)
{
	return acosf(Dot(_A.Normalized(), _B.Normalized()));
}

const float AuroraCore::Math::Vec3f::Distance(const Vec3f& _A, const Vec3f& _B)
{
	return (_B - _A).Magnitude();
}

const float AuroraCore::Math::Vec3f::Dot(const Vec3f& _A, const Vec3f& _B)
{
	return _A.x * _B.x + _A.y * _B.y + _A.z * _B.z;
}

const AuroraCore::Math::Vec3f AuroraCore::Math::Vec3f::Cross(const Vec3f& _A, const Vec3f& _B)
{
	return Vec3f(_A.y * _B.z - _A.z * _B.y, _A.z * _B.x - _A.x * _B.z, _A.x * _B.y - _A.y * _B.x);
}

const AuroraCore::Math::Vec3f AuroraCore::Math::Vec3f::Clamp(const Vec3f& _Value, const Vec3f& _Min, const Vec3f& _Max)
{
	return Vec3f(AuroraCore::Math::Clamp(_Value.x, _Min.x, _Max.x), AuroraCore::Math::Clamp(_Value.y, _Min.y, _Max.y), AuroraCore::Math::Clamp(_Value.z, _Min.z, _Max.z));
}

const AuroraCore::Math::Vec3f AuroraCore::Math::Vec3f::Mix(const Vec3f& _A, const Vec3f& _B, const float _Percentage)
{
	return Vec3f(AuroraCore::Math::Mix(_A.x, _B.x, _Percentage), AuroraCore::Math::Mix(_A.y, _B.y, _Percentage), AuroraCore::Math::Mix(_A.z, _B.z, _Percentage));
}

const AuroraCore::Math::Vec3f AuroraCore::Math::Vec3f::Pow(const Vec3f& _Base, const Vec3f& _Pow)
{
	return Vec3f(powf(_Base.x, _Pow.x), powf(_Base.y, _Pow.y), powf(_Base.z, _Pow.z));
}

const AuroraCore::Math::Vec3f AuroraCore::Math::Vec3f::Exp(const Vec3f& _Pow)
{
	return Vec3f(expf(_Pow.x), expf(_Pow.y), expf(_Pow.z));
}

const AuroraCore::Math::Vec3f AuroraCore::Math::Vec3f::Min(const Vec3f& _A, const Vec3f& _B)
{
	return Vec3f(AuroraCore::Math::Min(_A.x, _B.x), AuroraCore::Math::Min(_A.y, _B.y), AuroraCore::Math::Min(_A.z, _B.z));
}

const AuroraCore::Math::Vec3f AuroraCore::Math::Vec3f::Max(const Vec3f& _A, const Vec3f& _B)
{
	return Vec3f(AuroraCore::Math::Max(_A.x, _B.x), AuroraCore::Math::Max(_A.y, _B.y), AuroraCore::Math::Max(_A.z, _B.z));
}

const AuroraCore::Math::Vec3f AuroraCore::Math::Vec3f::Reflect(const Vec3f& _Vec, const Vec3f& _Normal)
{
	return _Vec - _Normal * 2.0f * Dot(_Vec, _Normal) / _Normal.Magnitude() / _Normal.Magnitude();
}



AuroraCore::Math::Vec4f::Vec4f() : x(0.0f), y(0.0f), z(0.0f), w(0.0f)
{

}

AuroraCore::Math::Vec4f::Vec4f(const float _x, const float _y, const float _z, const float _w) : x(_x), y(_y), z(_z), w(_w)
{

}

AuroraCore::Math::Vec4f::Vec4f(const Vec4f& _Other) : x(_Other.x), y(_Other.y), z(_Other.z), w(_Other.w)
{

}

AuroraCore::Math::Vec4f::Vec4f(Vec4f&& _Other) noexcept : x(_Other.x), y(_Other.y), z(_Other.z), w(_Other.w)
{

}

AuroraCore::Math::Vec4f::Vec4f(const Vec2f& _Other, const float _z, const float _w) : x(_Other.x), y(_Other.y), z(_z), w(_w)
{

}

AuroraCore::Math::Vec4f::Vec4f(const Vec3f& _Other, const float _w) : x(_Other.x), y(_Other.y), z(_Other.z), w(_w)
{

}

AuroraCore::Math::Vec4f::~Vec4f()
{

}

AuroraCore::Math::Vec4f::operator const AuroraCore::Math::Vec2f() const
{
	return Vec2f(x, y);
}

AuroraCore::Math::Vec4f::operator const AuroraCore::Math::Vec3f() const
{
	return Vec3f(x, y, z);
}

float* AuroraCore::Math::Vec4f::Data()
{
	return &x;
}

const float* AuroraCore::Math::Vec4f::Data() const
{
	return &x;
}

const float AuroraCore::Math::Vec4f::Magnitude() const
{
	return sqrtf(x * x + y * y + z * z + w * w);
}

const AuroraCore::Math::Vec4f& AuroraCore::Math::Vec4f::Normalize()
{
	*this /= Magnitude();

	return *this;
}

const AuroraCore::Math::Vec4f AuroraCore::Math::Vec4f::Normalized() const
{
	return *this / Magnitude();
}

const AuroraCore::Math::Vec4f& AuroraCore::Math::Vec4f::operator+ () const
{
	return *this;
}

const AuroraCore::Math::Vec4f AuroraCore::Math::Vec4f::operator- () const
{
	return Vec4f(-x, -y, -z, -w);
}

const AuroraCore::Math::Vec4f AuroraCore::Math::Vec4f::operator+ (const Vec4f& _Other) const
{
	return Vec4f(x + _Other.x, y + _Other.y, z + _Other.z, w + _Other.w);
}

const AuroraCore::Math::Vec4f& AuroraCore::Math::Vec4f::operator+= (const Vec4f& _Other)
{
	x += _Other.x;
	y += _Other.y;
	z += _Other.z;
	w += _Other.w;

	return *this;
}

const AuroraCore::Math::Vec4f AuroraCore::Math::Vec4f::operator+ (const float _Scale) const
{
	return Vec4f(x + _Scale, y + _Scale, z + _Scale, w + _Scale);
}

const AuroraCore::Math::Vec4f& AuroraCore::Math::Vec4f::operator+= (const float _Scale)
{
	x += _Scale;
	y += _Scale;
	z += _Scale;
	w += _Scale;

	return *this;
}

const AuroraCore::Math::Vec4f AuroraCore::Math::Vec4f::operator- (const Vec4f& _Other) const
{
	return Vec4f(x - _Other.x, y - _Other.y, z - _Other.z, w - _Other.w);
}

const AuroraCore::Math::Vec4f& AuroraCore::Math::Vec4f::operator-= (const Vec4f& _Other)
{
	x -= _Other.x;
	y -= _Other.y;
	z -= _Other.z;
	w -= _Other.w;

	return *this;
}

const AuroraCore::Math::Vec4f AuroraCore::Math::Vec4f::operator- (const float _Scale) const
{
	return Vec4f(x - _Scale, y - _Scale, z - _Scale, w - _Scale);
}

const AuroraCore::Math::Vec4f& AuroraCore::Math::Vec4f::operator-= (const float _Scale)
{
	x -= _Scale;
	y -= _Scale;
	z -= _Scale;
	w -= _Scale;

	return *this;
}

const AuroraCore::Math::Vec4f AuroraCore::Math::Vec4f::operator* (const Vec4f& _Other) const
{
	return Vec4f(x * _Other.x, y * _Other.y, z * _Other.z, w * _Other.w);
}

const AuroraCore::Math::Vec4f& AuroraCore::Math::Vec4f::operator*= (const Vec4f& _Other)
{
	x *= _Other.x;
	y *= _Other.y;
	z *= _Other.z;
	w *= _Other.w;

	return *this;
}

const AuroraCore::Math::Vec4f AuroraCore::Math::Vec4f::operator* (const float _Scale) const
{
	return Vec4f(x * _Scale, y * _Scale, z * _Scale, w * _Scale);
}

const AuroraCore::Math::Vec4f& AuroraCore::Math::Vec4f::operator*= (const float _Scale)
{
	x *= _Scale;
	y *= _Scale;
	z *= _Scale;
	w *= _Scale;

	return *this;
}

const AuroraCore::Math::Vec4f AuroraCore::Math::Vec4f::operator/ (const Vec4f& _Other) const
{
	return Vec4f(x / _Other.x, y / _Other.y, z / _Other.z, w / _Other.w);
}

const AuroraCore::Math::Vec4f& AuroraCore::Math::Vec4f::operator/= (const Vec4f& _Other)
{
	x /= _Other.x;
	y /= _Other.y;
	z /= _Other.z;
	w /= _Other.w;

	return *this;
}

const AuroraCore::Math::Vec4f AuroraCore::Math::Vec4f::operator/ (const float _Scale) const
{
	return Vec4f(x / _Scale, y / _Scale, z / _Scale, w / _Scale);
}

const AuroraCore::Math::Vec4f& AuroraCore::Math::Vec4f::operator/= (const float _Scale)
{
	x /= _Scale;
	y /= _Scale;
	z /= _Scale;
	w /= _Scale;

	return *this;
}

const bool AuroraCore::Math::Vec4f::operator== (const Vec4f& _Other) const
{
	return x == _Other.x && y == _Other.y && z == _Other.z && w == _Other.w;
}

const bool AuroraCore::Math::Vec4f::operator!= (const Vec4f& _Other) const
{
	return x != _Other.x || y != _Other.y || z != _Other.z || w != _Other.w;
}

float& AuroraCore::Math::Vec4f::operator[] (const size_t _Index)
{
	return (&x)[_Index];
}

const float& AuroraCore::Math::Vec4f::operator[] (const size_t _Index) const
{
	return (&x)[_Index];
}

const AuroraCore::Math::Vec4f& AuroraCore::Math::Vec4f::operator= (const Vec4f& _Other)
{
	x = _Other.x;
	y = _Other.y;
	z = _Other.z;
	w = _Other.w;

	return *this;
}

const AuroraCore::Math::Vec4f& AuroraCore::Math::Vec4f::operator= (Vec4f&& _Other) noexcept
{
	x = _Other.x;
	y = _Other.y;
	z = _Other.z;
	w = _Other.w;

	return *this;
}

const float AuroraCore::Math::Vec4f::GetAngle(const Vec4f& _A, const Vec4f& _B)
{
	return acosf(Vec3f::Dot(((Vec3f)(_A)).Normalized(), ((Vec3f)(_B)).Normalized()));
}

const float AuroraCore::Math::Vec4f::Distance(const Vec4f& _A, const Vec4f& _B)
{
	return (_B - _A).Magnitude();
}

const float AuroraCore::Math::Vec4f::Dot(const Vec4f& _A, const Vec4f& _B)
{
	return _A.x * _B.x + _A.y * _B.y + _A.z * _B.z + _A.w * _B.w;
}

const AuroraCore::Math::Vec4f AuroraCore::Math::Vec4f::Cross(const Vec4f& _A, const Vec4f& _B)
{
	return Vec4f(_A.y * _B.z - _A.z * _B.y, _A.z * _B.x - _A.x * _B.z, _A.x * _B.y - _A.y * _B.x, 1.0f);
}

const AuroraCore::Math::Vec4f AuroraCore::Math::Vec4f::Clamp(const Vec4f& _Value, const Vec4f& _Min, const Vec4f& _Max)
{
	return Vec4f(AuroraCore::Math::Clamp(_Value.x, _Min.x, _Max.x), AuroraCore::Math::Clamp(_Value.y, _Min.y, _Max.y), AuroraCore::Math::Clamp(_Value.z, _Min.z, _Max.z), AuroraCore::Math::Clamp(_Value.w, _Min.w, _Max.w));
}

const AuroraCore::Math::Vec4f AuroraCore::Math::Vec4f::Mix(const Vec4f& _A, const Vec4f& _B, const float _Percentage)
{
	return Vec4f(AuroraCore::Math::Mix(_A.x, _B.x, _Percentage), AuroraCore::Math::Mix(_A.y, _B.y, _Percentage), AuroraCore::Math::Mix(_A.z, _B.z, _Percentage), AuroraCore::Math::Mix(_A.w, _B.w, _Percentage));
}

const AuroraCore::Math::Vec4f AuroraCore::Math::Vec4f::Pow(const Vec4f& _Base, const Vec4f& _Pow)
{
	return Vec4f(powf(_Base.x, _Pow.x), powf(_Base.y, _Pow.y), powf(_Base.z, _Pow.z), powf(_Base.w, _Pow.w));
}

const AuroraCore::Math::Vec4f AuroraCore::Math::Vec4f::Exp(const Vec4f& _Pow)
{
	return Vec4f(expf(_Pow.x), expf(_Pow.y), expf(_Pow.z), expf(_Pow.w));
}

const AuroraCore::Math::Vec4f AuroraCore::Math::Vec4f::Min(const Vec4f& _A, const Vec4f& _B)
{
	return Vec4f(AuroraCore::Math::Min(_A.x, _B.x), AuroraCore::Math::Min(_A.y, _B.y), AuroraCore::Math::Min(_A.z, _B.z), AuroraCore::Math::Min(_A.w, _B.w));
}

const AuroraCore::Math::Vec4f AuroraCore::Math::Vec4f::Max(const Vec4f& _A, const Vec4f& _B)
{
	return Vec4f(AuroraCore::Math::Max(_A.x, _B.x), AuroraCore::Math::Max(_A.y, _B.y), AuroraCore::Math::Max(_A.z, _B.z), AuroraCore::Math::Max(_A.w, _B.w));
}

const AuroraCore::Math::Vec4f AuroraCore::Math::Vec4f::Reflect(const Vec4f& _Vec, const Vec4f& _Normal)
{
	return _Vec - _Normal * 2.0f * Dot(_Vec, _Normal) / _Normal.Magnitude() / _Normal.Magnitude();
}



AuroraCore::Math::Mat2f::Mat2f() : Matrix()
{
	Matrix[0][0] = 1.0f; Matrix[0][1] = 0.0f;
	Matrix[1][0] = 0.0f; Matrix[1][1] = 1.0f;
}

AuroraCore::Math::Mat2f::Mat2f(const Mat2f& _Other) : Matrix()
{
	Matrix[0][0] = _Other[0][0]; Matrix[0][1] = _Other[0][1];
	Matrix[1][0] = _Other[1][0]; Matrix[1][1] = _Other[1][1];
}

AuroraCore::Math::Mat2f::Mat2f(Mat2f&& _Other) noexcept : Matrix()
{
	Matrix[0][0] = _Other[0][0]; Matrix[0][1] = _Other[0][1];
	Matrix[1][0] = _Other[1][0]; Matrix[1][1] = _Other[1][1];
}

AuroraCore::Math::Mat2f::~Mat2f()
{

}

float* AuroraCore::Math::Mat2f::Data()
{
	return (float*)(Matrix);
}

const float* AuroraCore::Math::Mat2f::Data() const
{
	return (const float*)(Matrix);
}

const float AuroraCore::Math::Mat2f::Determinant() const
{
	return Matrix[0][0] * Matrix[1][1] - Matrix[0][1] * Matrix[1][0];
}

const float AuroraCore::Math::Mat2f::Trace() const
{
	return Matrix[0][0] + Matrix[1][1];
}

const AuroraCore::Math::Mat2f& AuroraCore::Math::Mat2f::Transpose()
{
	Swap(Matrix[0][1], Matrix[1][0]);

	return *this;
}

const AuroraCore::Math::Mat2f AuroraCore::Math::Mat2f::Transposed() const
{
	return Mat2f(*this).Transpose();
}

const AuroraCore::Math::Mat2f& AuroraCore::Math::Mat2f::Inverse()
{
	Mat2f _Matrix;

	_Matrix[0][0] = Matrix[1][1]; _Matrix[0][1] = -Matrix[0][1];
	_Matrix[1][0] = -Matrix[1][0]; _Matrix[1][1] = Matrix[0][0];

	_Matrix /= Determinant();

	*this = _Matrix;

	return *this;
}

const AuroraCore::Math::Mat2f AuroraCore::Math::Mat2f::Inversed() const
{
	return Mat2f(*this).Inverse();
}

const AuroraCore::Math::Mat2f& AuroraCore::Math::Mat2f::operator+ () const
{
	return *this;
}

const AuroraCore::Math::Mat2f AuroraCore::Math::Mat2f::operator- () const
{
	Mat2f _Matrix;

	_Matrix[0][0] = -Matrix[0][0]; _Matrix[0][1] = -Matrix[0][1];
	_Matrix[1][0] = -Matrix[1][0]; _Matrix[1][1] = -Matrix[1][1];

	return _Matrix;
}

const AuroraCore::Math::Vec2f AuroraCore::Math::Mat2f::operator* (const Vec2f& _Vec) const
{
	return Vec2f
	(
		Matrix[0][0] * _Vec.x + Matrix[0][1] * _Vec.y,
		Matrix[1][0] * _Vec.x + Matrix[1][1] * _Vec.y
	);
}

const AuroraCore::Math::Mat2f AuroraCore::Math::Mat2f::operator+ (const Mat2f& _Other) const
{
	Mat2f _Matrix(*this);

	_Matrix[0][0] += _Other[0][0]; _Matrix[0][1] += _Other[0][1];
	_Matrix[1][0] += _Other[1][0]; _Matrix[1][1] += _Other[1][1];

	return _Matrix;
}

const AuroraCore::Math::Mat2f& AuroraCore::Math::Mat2f::operator+= (const Mat2f& _Other)
{
	Matrix[0][0] += _Other[0][0]; Matrix[0][1] += _Other[0][1];
	Matrix[1][0] += _Other[1][0]; Matrix[1][1] += _Other[1][1];

	return *this;
}

const AuroraCore::Math::Mat2f AuroraCore::Math::Mat2f::operator+ (const float _Scale) const
{
	Mat2f _Matrix(*this);

	_Matrix[0][0] += _Scale; _Matrix[0][1] += _Scale;
	_Matrix[1][0] += _Scale; _Matrix[1][1] += _Scale;

	return _Matrix;
}

const AuroraCore::Math::Mat2f& AuroraCore::Math::Mat2f::operator+= (const float _Scale)
{
	Matrix[0][0] += _Scale; Matrix[0][1] += _Scale;
	Matrix[1][0] += _Scale; Matrix[1][1] += _Scale;

	return *this;
}

const AuroraCore::Math::Mat2f AuroraCore::Math::Mat2f::operator- (const Mat2f& _Other) const
{
	Mat2f _Matrix(*this);

	_Matrix[0][0] -= _Other[0][0]; _Matrix[0][1] -= _Other[0][1];
	_Matrix[1][0] -= _Other[1][0]; _Matrix[1][1] -= _Other[1][1];

	return _Matrix;
}

const AuroraCore::Math::Mat2f& AuroraCore::Math::Mat2f::operator-= (const Mat2f& _Other)
{
	Matrix[0][0] -= _Other[0][0]; Matrix[0][1] -= _Other[0][1];
	Matrix[1][0] -= _Other[1][0]; Matrix[1][1] -= _Other[1][1];

	return *this;
}

const AuroraCore::Math::Mat2f AuroraCore::Math::Mat2f::operator- (const float _Scale) const
{
	Mat2f _Matrix(*this);

	_Matrix[0][0] -= _Scale; _Matrix[0][1] -= _Scale;
	_Matrix[1][0] -= _Scale; _Matrix[1][1] -= _Scale;

	return _Matrix;
}

const AuroraCore::Math::Mat2f& AuroraCore::Math::Mat2f::operator-= (const float _Scale)
{
	Matrix[0][0] -= _Scale; Matrix[0][1] -= _Scale;
	Matrix[1][0] -= _Scale; Matrix[1][1] -= _Scale;

	return *this;
}

const AuroraCore::Math::Mat2f AuroraCore::Math::Mat2f::operator* (const Mat2f& _Other) const
{
	Mat2f _Matrix;

	_Matrix[0][0] = Matrix[0][0] * _Other[0][0] + Matrix[0][1] * _Other[1][0];
	_Matrix[0][1] = Matrix[0][0] * _Other[0][1] + Matrix[0][1] * _Other[1][1];
	_Matrix[1][0] = Matrix[1][0] * _Other[0][0] + Matrix[1][1] * _Other[1][0];
	_Matrix[1][1] = Matrix[1][0] * _Other[0][1] + Matrix[1][1] * _Other[1][1];

	return _Matrix;
}

const AuroraCore::Math::Mat2f& AuroraCore::Math::Mat2f::operator*= (const Mat2f& _Other)
{
	Mat2f _Matrix;

	_Matrix[0][0] = Matrix[0][0] * _Other[0][0] + Matrix[0][1] * _Other[1][0];
	_Matrix[0][1] = Matrix[0][0] * _Other[0][1] + Matrix[0][1] * _Other[1][1];
	_Matrix[1][0] = Matrix[1][0] * _Other[0][0] + Matrix[1][1] * _Other[1][0];
	_Matrix[1][1] = Matrix[1][0] * _Other[0][1] + Matrix[1][1] * _Other[1][1];

	*this = _Matrix;

	return *this;
}

const AuroraCore::Math::Mat2f AuroraCore::Math::Mat2f::operator* (const float _Scale) const
{
	Mat2f _Matrix(*this);

	_Matrix[0][0] *= _Scale; _Matrix[0][1] *= _Scale;
	_Matrix[1][0] *= _Scale; _Matrix[1][1] *= _Scale;

	return _Matrix;
}

const AuroraCore::Math::Mat2f& AuroraCore::Math::Mat2f::operator*= (const float _Scale)
{
	Matrix[0][0] *= _Scale; Matrix[0][1] *= _Scale;
	Matrix[1][0] *= _Scale; Matrix[1][1] *= _Scale;

	return *this;
}

const AuroraCore::Math::Mat2f AuroraCore::Math::Mat2f::operator/ (const float _Scale) const
{
	Mat2f _Matrix(*this);

	_Matrix[0][0] /= _Scale; _Matrix[0][1] /= _Scale;
	_Matrix[1][0] /= _Scale; _Matrix[1][1] /= _Scale;

	return _Matrix;
}

const AuroraCore::Math::Mat2f& AuroraCore::Math::Mat2f::operator/= (const float _Scale)
{
	Matrix[0][0] /= _Scale; Matrix[0][1] /= _Scale;
	Matrix[1][0] /= _Scale; Matrix[1][1] /= _Scale;

	return *this;
}

const bool AuroraCore::Math::Mat2f::operator== (const Mat2f& _Other) const
{
	return
		Matrix[0][0] == _Other[0][0] && Matrix[0][1] == _Other[0][1] &&
		Matrix[1][0] == _Other[1][0] && Matrix[1][1] == _Other[1][1];
}

const bool AuroraCore::Math::Mat2f::operator!= (const Mat2f& _Other) const
{
	return
		Matrix[0][0] != _Other[0][0] || Matrix[0][1] != _Other[0][1] ||
		Matrix[1][0] != _Other[1][0] || Matrix[1][1] != _Other[1][1];
}

float* AuroraCore::Math::Mat2f::operator[] (const size_t _Index)
{
	return Matrix[_Index].Data();
}

const float* AuroraCore::Math::Mat2f::operator[] (const size_t _Index) const
{
	return Matrix[_Index].Data();
}

const AuroraCore::Math::Mat2f& AuroraCore::Math::Mat2f::operator= (const Mat2f& _Other)
{
	Matrix[0][0] = _Other[0][0]; Matrix[0][1] = _Other[0][1];
	Matrix[1][0] = _Other[1][0]; Matrix[1][1] = _Other[1][1];

	return *this;
}

const AuroraCore::Math::Mat2f& AuroraCore::Math::Mat2f::operator= (Mat2f&& _Other) noexcept
{
	Matrix[0][0] = _Other[0][0]; Matrix[0][1] = _Other[0][1];
	Matrix[1][0] = _Other[1][0]; Matrix[1][1] = _Other[1][1];

	return *this;
}

const AuroraCore::Math::Mat2f AuroraCore::Math::Mat2f::GetScale(const float _x, const float _y)
{
	Mat2f _Matrix;

	_Matrix[0][0] = _x;
	_Matrix[1][1] = _y;

	return _Matrix;
}

const AuroraCore::Math::Mat2f AuroraCore::Math::Mat2f::GetFill(const float _Value)
{
	Mat2f _Matrix;

	_Matrix[0][0] = _Value; _Matrix[0][1] = _Value;
	_Matrix[1][0] = _Value; _Matrix[1][1] = _Value;

	return _Matrix;
}

const AuroraCore::Math::Mat2f AuroraCore::Math::Mat2f::GetShear(const float _Value, const size_t _ShearedAxis, const size_t _ShearByAxis)
{
	Mat2f _Matrix;

	_Matrix[_ShearedAxis][_ShearByAxis] = _Value;

	return _Matrix;
}

const AuroraCore::Math::Mat2f AuroraCore::Math::Mat2f::GetRotation(const float _Angle)
{
	Mat2f _Matrix;

	float _Sin = sinf(_Angle);
	float _Cos = cosf(_Angle);

	_Matrix[0][0] = _Cos; _Matrix[0][1] = -_Sin;
	_Matrix[1][0] = _Sin; _Matrix[1][1] = _Cos;

	return _Matrix;
}



AuroraCore::Math::Mat3f::Mat3f() : Matrix()
{
	Matrix[0][0] = 1.0f; Matrix[0][1] = 0.0f; Matrix[0][2] = 0.0f;
	Matrix[1][0] = 0.0f; Matrix[1][1] = 1.0f; Matrix[1][2] = 0.0f;
	Matrix[2][0] = 0.0f; Matrix[2][1] = 0.0f; Matrix[2][2] = 1.0f;
}

AuroraCore::Math::Mat3f::Mat3f(const Mat3f& _Other) : Matrix()
{
	Matrix[0][0] = _Other[0][0]; Matrix[0][1] = _Other[0][1]; Matrix[0][2] = _Other[0][2];
	Matrix[1][0] = _Other[1][0]; Matrix[1][1] = _Other[1][1]; Matrix[1][2] = _Other[1][2];
	Matrix[2][0] = _Other[2][0]; Matrix[2][1] = _Other[2][1]; Matrix[2][2] = _Other[2][2];
}

AuroraCore::Math::Mat3f::Mat3f(Mat3f&& _Other) noexcept : Matrix()
{
	Matrix[0][0] = _Other[0][0]; Matrix[0][1] = _Other[0][1]; Matrix[0][2] = _Other[0][2];
	Matrix[1][0] = _Other[1][0]; Matrix[1][1] = _Other[1][1]; Matrix[1][2] = _Other[1][2];
	Matrix[2][0] = _Other[2][0]; Matrix[2][1] = _Other[2][1]; Matrix[2][2] = _Other[2][2];
}

AuroraCore::Math::Mat3f::Mat3f(const Mat2f& _Other) : Matrix()
{
	Matrix[0][0] = _Other[0][0]; Matrix[0][1] = _Other[0][1]; Matrix[0][2] = 0.0f;
	Matrix[1][0] = _Other[1][0]; Matrix[1][1] = _Other[1][1]; Matrix[1][2] = 0.0f;
	Matrix[2][0] = 0.0f; Matrix[2][1] = 0.0f; Matrix[2][2] = 1.0f;
}

AuroraCore::Math::Mat3f::~Mat3f()
{

}

AuroraCore::Math::Mat3f::operator const AuroraCore::Math::Mat2f() const
{
	Mat2f _Matrix;

	_Matrix[0][0] = Matrix[0][0]; _Matrix[0][1] = Matrix[0][1];
	_Matrix[1][0] = Matrix[1][0]; _Matrix[1][1] = Matrix[1][1];

	return _Matrix;
}

float* AuroraCore::Math::Mat3f::Data()
{
	return (float*)(Matrix);
}

const float* AuroraCore::Math::Mat3f::Data() const
{
	return (const float*)(Matrix);
}

const float AuroraCore::Math::Mat3f::Determinant() const
{
	return
		Matrix[0][0] * Matrix[1][1] * Matrix[2][2] +
		Matrix[0][2] * Matrix[1][0] * Matrix[2][1] +
		Matrix[0][1] * Matrix[1][2] * Matrix[2][0] -
		Matrix[0][2] * Matrix[1][1] * Matrix[2][0] -
		Matrix[0][0] * Matrix[1][2] * Matrix[2][1] -
		Matrix[0][1] * Matrix[1][0] * Matrix[2][2];
}

const float AuroraCore::Math::Mat3f::Trace() const
{
	return Matrix[0][0] + Matrix[1][1] + Matrix[2][2];
}

const AuroraCore::Math::Mat3f& AuroraCore::Math::Mat3f::Transpose()
{
	Swap(Matrix[0][1], Matrix[1][0]);
	Swap(Matrix[0][2], Matrix[2][0]);
	Swap(Matrix[1][2], Matrix[2][1]);

	return *this;
}

const AuroraCore::Math::Mat3f AuroraCore::Math::Mat3f::Transposed() const
{
	return Mat3f(*this).Transpose();
}

const AuroraCore::Math::Mat3f& AuroraCore::Math::Mat3f::Inverse()
{
	Mat3f _Matrix;

	Mat2f _DetMat;

	_DetMat[0][0] = Matrix[1][1]; _DetMat[0][1] = Matrix[2][1];
	_DetMat[1][0] = Matrix[1][2]; _DetMat[1][1] = Matrix[2][2];

	_Matrix[0][0] = _DetMat.Determinant();

	_DetMat[0][0] = Matrix[0][1]; _DetMat[0][1] = Matrix[2][1];
	_DetMat[1][0] = Matrix[0][2]; _DetMat[1][1] = Matrix[2][2];

	_Matrix[0][1] = -_DetMat.Determinant();

	_DetMat[0][0] = Matrix[0][1]; _DetMat[0][1] = Matrix[1][1];
	_DetMat[1][0] = Matrix[0][2]; _DetMat[1][1] = Matrix[1][2];

	_Matrix[0][2] = _DetMat.Determinant();

	_DetMat[0][0] = Matrix[1][0]; _DetMat[0][1] = Matrix[2][0];
	_DetMat[1][0] = Matrix[1][2]; _DetMat[1][1] = Matrix[2][2];

	_Matrix[1][0] = -_DetMat.Determinant();

	_DetMat[0][0] = Matrix[0][0]; _DetMat[0][1] = Matrix[2][0];
	_DetMat[1][0] = Matrix[0][2]; _DetMat[1][1] = Matrix[2][2];

	_Matrix[1][1] = _DetMat.Determinant();

	_DetMat[0][0] = Matrix[0][0]; _DetMat[0][1] = Matrix[1][0];
	_DetMat[1][0] = Matrix[0][2]; _DetMat[1][1] = Matrix[1][2];

	_Matrix[1][2] = -_DetMat.Determinant();

	_DetMat[0][0] = Matrix[1][0]; _DetMat[0][1] = Matrix[2][0];
	_DetMat[1][0] = Matrix[1][1]; _DetMat[1][1] = Matrix[2][1];

	_Matrix[2][0] = _DetMat.Determinant();

	_DetMat[0][0] = Matrix[0][0]; _DetMat[0][1] = Matrix[2][0];
	_DetMat[1][0] = Matrix[0][1]; _DetMat[1][1] = Matrix[2][1];

	_Matrix[2][1] = -_DetMat.Determinant();

	_DetMat[0][0] = Matrix[0][0]; _DetMat[0][1] = Matrix[1][0];
	_DetMat[1][0] = Matrix[0][1]; _DetMat[1][1] = Matrix[1][1];

	_Matrix[2][2] = _DetMat.Determinant();

	_Matrix /= Determinant();

	*this = _Matrix;

	return *this;
}

const AuroraCore::Math::Mat3f AuroraCore::Math::Mat3f::Inversed() const
{
	return Mat3f(*this).Inverse();
}

const AuroraCore::Math::Mat3f& AuroraCore::Math::Mat3f::operator+ () const
{
	return *this;
}

const AuroraCore::Math::Mat3f AuroraCore::Math::Mat3f::operator- () const
{
	Mat3f _Matrix;

	_Matrix[0][0] = -Matrix[0][0]; _Matrix[0][1] = -Matrix[0][1]; _Matrix[0][2] = -Matrix[0][2];
	_Matrix[1][0] = -Matrix[1][0]; _Matrix[1][1] = -Matrix[1][1]; _Matrix[1][2] = -Matrix[1][2];
	_Matrix[2][0] = -Matrix[2][0]; _Matrix[2][1] = -Matrix[2][1]; _Matrix[2][2] = -Matrix[2][2];

	return _Matrix;
}

const AuroraCore::Math::Vec3f AuroraCore::Math::Mat3f::operator* (const Vec3f& _Vec) const
{
	return Vec3f
	(
		Matrix[0][0] * _Vec.x + Matrix[0][1] * _Vec.y + Matrix[0][2] * _Vec.z,
		Matrix[1][0] * _Vec.x + Matrix[1][1] * _Vec.y + Matrix[1][2] * _Vec.z,
		Matrix[2][0] * _Vec.x + Matrix[2][1] * _Vec.y + Matrix[2][2] * _Vec.z
	);
}

const AuroraCore::Math::Mat3f AuroraCore::Math::Mat3f::operator+ (const Mat3f& _Other) const
{
	Mat3f _Matrix(*this);

	_Matrix[0][0] += _Other[0][0]; _Matrix[0][1] += _Other[0][1]; _Matrix[0][2] += _Other[0][2];
	_Matrix[1][0] += _Other[1][0]; _Matrix[1][1] += _Other[1][1]; _Matrix[1][2] += _Other[1][2];
	_Matrix[2][0] += _Other[2][0]; _Matrix[2][1] += _Other[2][1]; _Matrix[2][2] += _Other[2][2];

	return _Matrix;
}

const AuroraCore::Math::Mat3f& AuroraCore::Math::Mat3f::operator+= (const Mat3f& _Other)
{
	Matrix[0][0] += _Other[0][0]; Matrix[0][1] += _Other[0][1]; Matrix[0][2] += _Other[0][2];
	Matrix[1][0] += _Other[1][0]; Matrix[1][1] += _Other[1][1]; Matrix[1][2] += _Other[1][2];
	Matrix[2][0] += _Other[2][0]; Matrix[2][1] += _Other[2][1]; Matrix[2][2] += _Other[2][2];

	return *this;
}

const AuroraCore::Math::Mat3f AuroraCore::Math::Mat3f::operator+ (const float _Scale) const
{
	Mat3f _Matrix(*this);

	_Matrix[0][0] += _Scale; _Matrix[0][1] += _Scale; _Matrix[0][2] += _Scale;
	_Matrix[1][0] += _Scale; _Matrix[1][1] += _Scale; _Matrix[1][2] += _Scale;
	_Matrix[2][0] += _Scale; _Matrix[2][1] += _Scale; _Matrix[2][2] += _Scale;

	return _Matrix;
}

const AuroraCore::Math::Mat3f& AuroraCore::Math::Mat3f::operator+= (const float _Scale)
{
	Matrix[0][0] += _Scale; Matrix[0][1] += _Scale; Matrix[0][2] += _Scale;
	Matrix[1][0] += _Scale; Matrix[1][1] += _Scale; Matrix[1][2] += _Scale;
	Matrix[2][0] += _Scale; Matrix[2][1] += _Scale; Matrix[2][2] += _Scale;

	return *this;
}

const AuroraCore::Math::Mat3f AuroraCore::Math::Mat3f::operator- (const Mat3f& _Other) const
{
	Mat3f _Matrix(*this);

	_Matrix[0][0] -= _Other[0][0]; _Matrix[0][1] -= _Other[0][1]; _Matrix[0][2] -= _Other[0][2];
	_Matrix[1][0] -= _Other[1][0]; _Matrix[1][1] -= _Other[1][1]; _Matrix[1][2] -= _Other[1][2];
	_Matrix[2][0] -= _Other[2][0]; _Matrix[2][1] -= _Other[2][1]; _Matrix[2][2] -= _Other[2][2];

	return _Matrix;
}

const AuroraCore::Math::Mat3f& AuroraCore::Math::Mat3f::operator-= (const Mat3f& _Other)
{
	Matrix[0][0] -= _Other[0][0]; Matrix[0][1] -= _Other[0][1]; Matrix[0][2] -= _Other[0][2];
	Matrix[1][0] -= _Other[1][0]; Matrix[1][1] -= _Other[1][1]; Matrix[1][2] -= _Other[1][2];
	Matrix[2][0] -= _Other[2][0]; Matrix[2][1] -= _Other[2][1]; Matrix[2][2] -= _Other[2][2];

	return *this;
}

const AuroraCore::Math::Mat3f AuroraCore::Math::Mat3f::operator- (const float _Scale) const
{
	Mat3f _Matrix(*this);

	_Matrix[0][0] -= _Scale; _Matrix[0][1] -= _Scale; _Matrix[0][2] -= _Scale;
	_Matrix[1][0] -= _Scale; _Matrix[1][1] -= _Scale; _Matrix[1][2] -= _Scale;
	_Matrix[2][0] -= _Scale; _Matrix[2][1] -= _Scale; _Matrix[2][2] -= _Scale;

	return _Matrix;
}

const AuroraCore::Math::Mat3f& AuroraCore::Math::Mat3f::operator-= (const float _Scale)
{
	Matrix[0][0] -= _Scale; Matrix[0][1] -= _Scale; Matrix[0][2] -= _Scale;
	Matrix[1][0] -= _Scale; Matrix[1][1] -= _Scale; Matrix[1][2] -= _Scale;
	Matrix[2][0] -= _Scale; Matrix[2][1] -= _Scale; Matrix[2][2] -= _Scale;

	return *this;
}

const AuroraCore::Math::Mat3f AuroraCore::Math::Mat3f::operator* (const Mat3f& _Other) const
{
	Mat3f _Matrix;

	_Matrix[0][0] = Matrix[0][0] * _Other[0][0] + Matrix[0][1] * _Other[1][0] + Matrix[0][2] * _Other[2][0];
	_Matrix[0][1] = Matrix[0][0] * _Other[0][1] + Matrix[0][1] * _Other[1][1] + Matrix[0][2] * _Other[2][1];
	_Matrix[0][2] = Matrix[0][0] * _Other[0][2] + Matrix[0][1] * _Other[1][2] + Matrix[0][2] * _Other[2][2];

	_Matrix[1][0] = Matrix[1][0] * _Other[0][0] + Matrix[1][1] * _Other[1][0] + Matrix[1][2] * _Other[2][0];
	_Matrix[1][1] = Matrix[1][0] * _Other[0][1] + Matrix[1][1] * _Other[1][1] + Matrix[1][2] * _Other[2][1];
	_Matrix[1][2] = Matrix[1][0] * _Other[0][2] + Matrix[1][1] * _Other[1][2] + Matrix[1][2] * _Other[2][2];

	_Matrix[2][0] = Matrix[2][0] * _Other[0][0] + Matrix[2][1] * _Other[1][0] + Matrix[2][2] * _Other[2][0];
	_Matrix[2][1] = Matrix[2][0] * _Other[0][1] + Matrix[2][1] * _Other[1][1] + Matrix[2][2] * _Other[2][1];
	_Matrix[2][2] = Matrix[2][0] * _Other[0][2] + Matrix[2][1] * _Other[1][2] + Matrix[2][2] * _Other[2][2];

	return _Matrix;
}

const AuroraCore::Math::Mat3f& AuroraCore::Math::Mat3f::operator*= (const Mat3f& _Other)
{
	Mat3f _Matrix;

	_Matrix[0][0] = Matrix[0][0] * _Other[0][0] + Matrix[0][1] * _Other[1][0] + Matrix[0][2] * _Other[2][0];
	_Matrix[0][1] = Matrix[0][0] * _Other[0][1] + Matrix[0][1] * _Other[1][1] + Matrix[0][2] * _Other[2][1];
	_Matrix[0][2] = Matrix[0][0] * _Other[0][2] + Matrix[0][1] * _Other[1][2] + Matrix[0][2] * _Other[2][2];

	_Matrix[1][0] = Matrix[1][0] * _Other[0][0] + Matrix[1][1] * _Other[1][0] + Matrix[1][2] * _Other[2][0];
	_Matrix[1][1] = Matrix[1][0] * _Other[0][1] + Matrix[1][1] * _Other[1][1] + Matrix[1][2] * _Other[2][1];
	_Matrix[1][2] = Matrix[1][0] * _Other[0][2] + Matrix[1][1] * _Other[1][2] + Matrix[1][2] * _Other[2][2];

	_Matrix[2][0] = Matrix[2][0] * _Other[0][0] + Matrix[2][1] * _Other[1][0] + Matrix[2][2] * _Other[2][0];
	_Matrix[2][1] = Matrix[2][0] * _Other[0][1] + Matrix[2][1] * _Other[1][1] + Matrix[2][2] * _Other[2][1];
	_Matrix[2][2] = Matrix[2][0] * _Other[0][2] + Matrix[2][1] * _Other[1][2] + Matrix[2][2] * _Other[2][2];

	*this = _Matrix;

	return *this;
}

const AuroraCore::Math::Mat3f AuroraCore::Math::Mat3f::operator* (const float _Scale) const
{
	Mat3f _Matrix(*this);

	_Matrix[0][0] *= _Scale; _Matrix[0][1] *= _Scale; _Matrix[0][2] *= _Scale;
	_Matrix[1][0] *= _Scale; _Matrix[1][1] *= _Scale; _Matrix[1][2] *= _Scale;
	_Matrix[2][0] *= _Scale; _Matrix[2][1] *= _Scale; _Matrix[2][2] *= _Scale;

	return _Matrix;
}

const AuroraCore::Math::Mat3f& AuroraCore::Math::Mat3f::operator*= (const float _Scale)
{
	Matrix[0][0] *= _Scale; Matrix[0][1] *= _Scale; Matrix[0][2] *= _Scale;
	Matrix[1][0] *= _Scale; Matrix[1][1] *= _Scale; Matrix[1][2] *= _Scale;
	Matrix[2][0] *= _Scale; Matrix[2][1] *= _Scale; Matrix[2][2] *= _Scale;

	return *this;
}

const AuroraCore::Math::Mat3f AuroraCore::Math::Mat3f::operator/ (const float _Scale) const
{
	Mat3f _Matrix(*this);

	_Matrix[0][0] /= _Scale; _Matrix[0][1] /= _Scale; _Matrix[0][2] /= _Scale;
	_Matrix[1][0] /= _Scale; _Matrix[1][1] /= _Scale; _Matrix[1][2] /= _Scale;
	_Matrix[2][0] /= _Scale; _Matrix[2][1] /= _Scale; _Matrix[2][2] /= _Scale;

	return _Matrix;
}

const AuroraCore::Math::Mat3f& AuroraCore::Math::Mat3f::operator/= (const float _Scale)
{
	Matrix[0][0] /= _Scale; Matrix[0][1] /= _Scale; Matrix[0][2] /= _Scale;
	Matrix[1][0] /= _Scale; Matrix[1][1] /= _Scale; Matrix[1][2] /= _Scale;
	Matrix[2][0] /= _Scale; Matrix[2][1] /= _Scale; Matrix[2][2] /= _Scale;

	return *this;
}

const bool AuroraCore::Math::Mat3f::operator== (const Mat3f& _Other) const
{
	return
		Matrix[0][0] == _Other[0][0] && Matrix[0][1] == _Other[0][1] && Matrix[0][2] == _Other[0][2] &&
		Matrix[1][0] == _Other[1][0] && Matrix[1][1] == _Other[1][1] && Matrix[1][2] == _Other[1][2] &&
		Matrix[2][0] == _Other[2][0] && Matrix[2][1] == _Other[2][1] && Matrix[2][2] == _Other[2][2];
}

const bool AuroraCore::Math::Mat3f::operator!= (const Mat3f& _Other) const
{
	return
		Matrix[0][0] != _Other[0][0] || Matrix[0][1] != _Other[0][1] || Matrix[0][2] != _Other[0][2] ||
		Matrix[1][0] != _Other[1][0] || Matrix[1][1] != _Other[1][1] || Matrix[1][2] != _Other[1][2] ||
		Matrix[2][0] != _Other[2][0] || Matrix[2][1] != _Other[2][1] || Matrix[2][2] != _Other[2][2];
}

float* AuroraCore::Math::Mat3f::operator[] (const size_t _Index)
{
	return Matrix[_Index].Data();
}

const float* AuroraCore::Math::Mat3f::operator[] (const size_t _Index) const
{
	return Matrix[_Index].Data();
}

const AuroraCore::Math::Mat3f& AuroraCore::Math::Mat3f::operator= (const Mat3f& _Other)
{
	Matrix[0][0] = _Other[0][0]; Matrix[0][1] = _Other[0][1]; Matrix[0][2] = _Other[0][2];
	Matrix[1][0] = _Other[1][0]; Matrix[1][1] = _Other[1][1]; Matrix[1][2] = _Other[1][2];
	Matrix[2][0] = _Other[2][0]; Matrix[2][1] = _Other[2][1]; Matrix[2][2] = _Other[2][2];

	return *this;
}

const AuroraCore::Math::Mat3f& AuroraCore::Math::Mat3f::operator= (Mat3f&& _Other) noexcept
{
	Matrix[0][0] = _Other[0][0]; Matrix[0][1] = _Other[0][1]; Matrix[0][2] = _Other[0][2];
	Matrix[1][0] = _Other[1][0]; Matrix[1][1] = _Other[1][1]; Matrix[1][2] = _Other[1][2];
	Matrix[2][0] = _Other[2][0]; Matrix[2][1] = _Other[2][1]; Matrix[2][2] = _Other[2][2];

	return *this;
}

const AuroraCore::Math::Mat3f AuroraCore::Math::Mat3f::GetScale(const float _x, const float _y, const float _z)
{
	Mat3f _Matrix;

	_Matrix[0][0] = _x;
	_Matrix[1][1] = _y;
	_Matrix[2][2] = _z;

	return _Matrix;
}

const AuroraCore::Math::Mat3f AuroraCore::Math::Mat3f::GetFill(const float _Value)
{
	Mat3f _Matrix;

	_Matrix[0][0] = _Value; _Matrix[0][1] = _Value; _Matrix[0][2] = _Value;
	_Matrix[1][0] = _Value; _Matrix[1][1] = _Value; _Matrix[1][2] = _Value;
	_Matrix[2][0] = _Value; _Matrix[2][1] = _Value; _Matrix[2][2] = _Value;

	return _Matrix;
}

const AuroraCore::Math::Mat3f AuroraCore::Math::Mat3f::GetShear(const float _Value, const size_t _ShearedAxis, const size_t _ShearByAxis)
{
	Mat3f _Matrix;

	_Matrix[_ShearedAxis][_ShearByAxis] = _Value;

	return _Matrix;
}

const AuroraCore::Math::Mat3f AuroraCore::Math::Mat3f::GetRotation(const float _Angle, const Vec3f& _RotationAxis)
{
	Mat3f _Matrix;

	float _Sin = sinf(_Angle);
	float _Cos = cosf(_Angle);

	_Matrix[0][0] = _Cos + _RotationAxis.x * _RotationAxis.x * (1.0f - _Cos);
	_Matrix[0][1] = _RotationAxis.x * _RotationAxis.y * (1.0f - _Cos) - _RotationAxis.z * _Sin;
	_Matrix[0][2] = _RotationAxis.x * _RotationAxis.z * (1.0f - _Cos) + _RotationAxis.y * _Sin;

	_Matrix[1][0] = _RotationAxis.y * _RotationAxis.x * (1.0f - _Cos) + _RotationAxis.z * _Sin;
	_Matrix[1][1] = _Cos + _RotationAxis.y * _RotationAxis.y * (1.0f - _Cos);
	_Matrix[1][2] = _RotationAxis.y * _RotationAxis.z * (1.0f - _Cos) - _RotationAxis.x * _Sin;

	_Matrix[2][0] = _RotationAxis.z * _RotationAxis.x * (1.0f - _Cos) - _RotationAxis.y * _Sin;
	_Matrix[2][1] = _RotationAxis.z * _RotationAxis.y * (1.0f - _Cos) + _RotationAxis.x * _Sin;
	_Matrix[2][2] = _Cos + _RotationAxis.z * _RotationAxis.z * (1.0f - _Cos);

	return _Matrix;
}

const AuroraCore::Math::Mat3f AuroraCore::Math::Mat3f::GetTranslation(const Vec2f& _Coords)
{
	Mat3f _Matrix;

	_Matrix[0][2] = _Coords.x;
	_Matrix[1][2] = _Coords.y;

	return _Matrix;
}

const AuroraCore::Math::Mat3f AuroraCore::Math::Mat3f::GetOrtho(const float _Left, const float _Right, const float _Bottom, const float _Top)
{
	Mat3f _Matrix;

	_Matrix[0][0] = 2.0f / (_Right - _Left);
	_Matrix[1][1] = 2.0f / (_Top - _Bottom);

	_Matrix[0][2] = (_Right + _Left) / (_Left - _Right);
	_Matrix[1][2] = (_Top + _Bottom) / (_Bottom - _Top);

	return _Matrix;
}



AuroraCore::Math::Mat4f::Mat4f() : Matrix()
{
	Matrix[0][0] = 1.0f; Matrix[0][1] = 0.0f; Matrix[0][2] = 0.0f; Matrix[0][3] = 0.0f;
	Matrix[1][0] = 0.0f; Matrix[1][1] = 1.0f; Matrix[1][2] = 0.0f; Matrix[1][3] = 0.0f;
	Matrix[2][0] = 0.0f; Matrix[2][1] = 0.0f; Matrix[2][2] = 1.0f; Matrix[2][3] = 0.0f;
	Matrix[3][0] = 0.0f; Matrix[3][1] = 0.0f; Matrix[3][2] = 0.0f; Matrix[3][3] = 1.0f;
}

AuroraCore::Math::Mat4f::Mat4f(const Mat4f& _Other) : Matrix()
{
	Matrix[0][0] = _Other[0][0]; Matrix[0][1] = _Other[0][1]; Matrix[0][2] = _Other[0][2]; Matrix[0][3] = _Other[0][3];
	Matrix[1][0] = _Other[1][0]; Matrix[1][1] = _Other[1][1]; Matrix[1][2] = _Other[1][2]; Matrix[1][3] = _Other[1][3];
	Matrix[2][0] = _Other[2][0]; Matrix[2][1] = _Other[2][1]; Matrix[2][2] = _Other[2][2]; Matrix[2][3] = _Other[2][3];
	Matrix[3][0] = _Other[3][0]; Matrix[3][1] = _Other[3][1]; Matrix[3][2] = _Other[3][2]; Matrix[3][3] = _Other[3][3];
}

AuroraCore::Math::Mat4f::Mat4f(Mat4f&& _Other) noexcept : Matrix()
{
	Matrix[0][0] = _Other[0][0]; Matrix[0][1] = _Other[0][1]; Matrix[0][2] = _Other[0][2]; Matrix[0][3] = _Other[0][3];
	Matrix[1][0] = _Other[1][0]; Matrix[1][1] = _Other[1][1]; Matrix[1][2] = _Other[1][2]; Matrix[1][3] = _Other[1][3];
	Matrix[2][0] = _Other[2][0]; Matrix[2][1] = _Other[2][1]; Matrix[2][2] = _Other[2][2]; Matrix[2][3] = _Other[2][3];
	Matrix[3][0] = _Other[3][0]; Matrix[3][1] = _Other[3][1]; Matrix[3][2] = _Other[3][2]; Matrix[3][3] = _Other[3][3];
}

AuroraCore::Math::Mat4f::Mat4f(const Mat2f& _Other) : Matrix()
{
	Matrix[0][0] = _Other[0][0]; Matrix[0][1] = _Other[0][1]; Matrix[0][2] = 0.0f; Matrix[0][3] = 0.0f;
	Matrix[1][0] = _Other[1][0]; Matrix[1][1] = _Other[1][1]; Matrix[1][2] = 0.0f; Matrix[1][3] = 0.0f;
	Matrix[2][0] = 0.0f; Matrix[2][1] = 0.0f; Matrix[2][2] = 1.0f; Matrix[2][3] = 0.0f;
	Matrix[3][0] = 0.0f; Matrix[3][1] = 0.0f; Matrix[3][2] = 0.0f; Matrix[3][3] = 1.0f;
}

AuroraCore::Math::Mat4f::Mat4f(const Mat3f& _Other) : Matrix()
{
	Matrix[0][0] = _Other[0][0]; Matrix[0][1] = _Other[0][1]; Matrix[0][2] = _Other[0][2]; Matrix[0][3] = 0.0f;
	Matrix[1][0] = _Other[1][0]; Matrix[1][1] = _Other[1][1]; Matrix[1][2] = _Other[1][2]; Matrix[1][3] = 0.0f;
	Matrix[2][0] = _Other[2][0]; Matrix[2][1] = _Other[2][1]; Matrix[2][2] = _Other[2][2]; Matrix[2][3] = 0.0f;
	Matrix[3][0] = 0.0f; Matrix[3][1] = 0.0f; Matrix[3][2] = 0.0f; Matrix[3][3] = 1.0f;
}

AuroraCore::Math::Mat4f::~Mat4f()
{

}

AuroraCore::Math::Mat4f::operator const AuroraCore::Math::Mat2f() const
{
	Mat2f _Matrix;

	_Matrix[0][0] = Matrix[0][0]; _Matrix[0][1] = Matrix[0][1];
	_Matrix[1][0] = Matrix[1][0]; _Matrix[1][1] = Matrix[1][1];

	return _Matrix;
}

AuroraCore::Math::Mat4f::operator const AuroraCore::Math::Mat3f() const
{
	Mat3f _Matrix;

	_Matrix[0][0] = Matrix[0][0]; _Matrix[0][1] = Matrix[0][1]; _Matrix[0][2] = Matrix[0][2];
	_Matrix[1][0] = Matrix[1][0]; _Matrix[1][1] = Matrix[1][1]; _Matrix[1][2] = Matrix[1][2];
	_Matrix[2][0] = Matrix[2][0]; _Matrix[2][1] = Matrix[2][1]; _Matrix[2][2] = Matrix[2][2];

	return _Matrix;
}

float* AuroraCore::Math::Mat4f::Data()
{
	return (float*)(Matrix);
}

const float* AuroraCore::Math::Mat4f::Data() const
{
	return (const float*)(Matrix);
}

const float AuroraCore::Math::Mat4f::Determinant() const
{
	Mat3f _Mat[4];

	_Mat[0][0][0] = Matrix[1][1]; _Mat[0][0][1] = Matrix[1][2]; _Mat[0][0][2] = Matrix[1][3];
	_Mat[0][1][0] = Matrix[2][1]; _Mat[0][1][1] = Matrix[2][2]; _Mat[0][1][2] = Matrix[2][3];
	_Mat[0][2][0] = Matrix[3][1]; _Mat[0][2][1] = Matrix[3][2]; _Mat[0][2][2] = Matrix[3][3];

	_Mat[1][0][0] = Matrix[0][1]; _Mat[1][0][1] = Matrix[0][2]; _Mat[1][0][2] = Matrix[0][3];
	_Mat[1][1][0] = Matrix[2][1]; _Mat[1][1][1] = Matrix[2][2]; _Mat[1][1][2] = Matrix[2][3];
	_Mat[1][2][0] = Matrix[3][1]; _Mat[1][2][1] = Matrix[3][2]; _Mat[1][2][2] = Matrix[3][3];

	_Mat[2][0][0] = Matrix[0][1]; _Mat[2][0][1] = Matrix[0][2]; _Mat[2][0][2] = Matrix[0][3];
	_Mat[2][1][0] = Matrix[1][1]; _Mat[2][1][1] = Matrix[1][2]; _Mat[2][1][2] = Matrix[1][3];
	_Mat[2][2][0] = Matrix[3][1]; _Mat[2][2][1] = Matrix[3][2]; _Mat[2][2][2] = Matrix[3][3];

	_Mat[3][0][0] = Matrix[0][1]; _Mat[3][0][1] = Matrix[0][2]; _Mat[3][0][2] = Matrix[0][3];
	_Mat[3][1][0] = Matrix[1][1]; _Mat[3][1][1] = Matrix[1][2]; _Mat[3][1][2] = Matrix[1][3];
	_Mat[3][2][0] = Matrix[2][1]; _Mat[3][2][1] = Matrix[2][2]; _Mat[3][2][2] = Matrix[2][3];

	return
		Matrix[0][0] * _Mat[0].Determinant() -
		Matrix[1][0] * _Mat[1].Determinant() +
		Matrix[2][0] * _Mat[2].Determinant() -
		Matrix[3][0] * _Mat[3].Determinant();
}

const float AuroraCore::Math::Mat4f::Trace() const
{
	return Matrix[0][0] + Matrix[1][1] + Matrix[2][2] + Matrix[3][3];
}

const AuroraCore::Math::Mat4f& AuroraCore::Math::Mat4f::Transpose()
{
	Swap(Matrix[0][1], Matrix[1][0]);
	Swap(Matrix[0][2], Matrix[2][0]);
	Swap(Matrix[0][3], Matrix[3][0]);
	Swap(Matrix[1][2], Matrix[2][1]);
	Swap(Matrix[1][3], Matrix[3][1]);
	Swap(Matrix[2][3], Matrix[3][2]);

	return *this;
}

const AuroraCore::Math::Mat4f AuroraCore::Math::Mat4f::Transposed() const
{
	return Mat4f(*this).Transpose();
}

const AuroraCore::Math::Mat4f& AuroraCore::Math::Mat4f::Inverse()
{
	Mat4f _Matrix;

	Mat3f _DetMat;

	_DetMat[0][0] = Matrix[1][1]; _DetMat[0][1] = Matrix[2][1]; _DetMat[0][2] = Matrix[3][1];
	_DetMat[1][0] = Matrix[1][2]; _DetMat[1][1] = Matrix[2][2]; _DetMat[1][2] = Matrix[3][2];
	_DetMat[2][0] = Matrix[1][3]; _DetMat[2][1] = Matrix[2][3]; _DetMat[2][2] = Matrix[3][3];

	_Matrix[0][0] = _DetMat.Determinant();

	_DetMat[0][0] = Matrix[0][1]; _DetMat[0][1] = Matrix[2][1]; _DetMat[0][2] = Matrix[3][1];
	_DetMat[1][0] = Matrix[0][2]; _DetMat[1][1] = Matrix[2][2]; _DetMat[1][2] = Matrix[3][2];
	_DetMat[2][0] = Matrix[0][3]; _DetMat[2][1] = Matrix[2][3]; _DetMat[2][2] = Matrix[3][3];

	_Matrix[0][1] = -_DetMat.Determinant();

	_DetMat[0][0] = Matrix[0][1]; _DetMat[0][1] = Matrix[1][1]; _DetMat[0][2] = Matrix[3][1];
	_DetMat[1][0] = Matrix[0][2]; _DetMat[1][1] = Matrix[1][2]; _DetMat[1][2] = Matrix[3][2];
	_DetMat[2][0] = Matrix[0][3]; _DetMat[2][1] = Matrix[1][3]; _DetMat[2][2] = Matrix[3][3];

	_Matrix[0][2] = _DetMat.Determinant();

	_DetMat[0][0] = Matrix[0][1]; _DetMat[0][1] = Matrix[1][1]; _DetMat[0][2] = Matrix[2][1];
	_DetMat[1][0] = Matrix[0][2]; _DetMat[1][1] = Matrix[1][2]; _DetMat[1][2] = Matrix[2][2];
	_DetMat[2][0] = Matrix[0][3]; _DetMat[2][1] = Matrix[1][3]; _DetMat[2][2] = Matrix[2][3];

	_Matrix[0][3] = -_DetMat.Determinant();

	_DetMat[0][0] = Matrix[1][0]; _DetMat[0][1] = Matrix[2][0]; _DetMat[0][2] = Matrix[3][0];
	_DetMat[1][0] = Matrix[1][2]; _DetMat[1][1] = Matrix[2][2]; _DetMat[1][2] = Matrix[3][2];
	_DetMat[2][0] = Matrix[1][3]; _DetMat[2][1] = Matrix[2][3]; _DetMat[2][2] = Matrix[3][3];

	_Matrix[1][0] = -_DetMat.Determinant();

	_DetMat[0][0] = Matrix[0][0]; _DetMat[0][1] = Matrix[2][0]; _DetMat[0][2] = Matrix[3][0];
	_DetMat[1][0] = Matrix[0][2]; _DetMat[1][1] = Matrix[2][2]; _DetMat[1][2] = Matrix[3][2];
	_DetMat[2][0] = Matrix[0][3]; _DetMat[2][1] = Matrix[2][3]; _DetMat[2][2] = Matrix[3][3];

	_Matrix[1][1] = _DetMat.Determinant();

	_DetMat[0][0] = Matrix[0][0]; _DetMat[0][1] = Matrix[1][0]; _DetMat[0][2] = Matrix[3][0];
	_DetMat[1][0] = Matrix[0][2]; _DetMat[1][1] = Matrix[1][2]; _DetMat[1][2] = Matrix[3][2];
	_DetMat[2][0] = Matrix[0][3]; _DetMat[2][1] = Matrix[1][3]; _DetMat[2][2] = Matrix[3][3];

	_Matrix[1][2] = -_DetMat.Determinant();

	_DetMat[0][0] = Matrix[0][0]; _DetMat[0][1] = Matrix[1][0]; _DetMat[0][2] = Matrix[2][0];
	_DetMat[1][0] = Matrix[0][2]; _DetMat[1][1] = Matrix[1][2]; _DetMat[1][2] = Matrix[2][2];
	_DetMat[2][0] = Matrix[0][3]; _DetMat[2][1] = Matrix[1][3]; _DetMat[2][2] = Matrix[2][3];

	_Matrix[1][3] = _DetMat.Determinant();

	_DetMat[0][0] = Matrix[1][0]; _DetMat[0][1] = Matrix[2][0]; _DetMat[0][2] = Matrix[3][0];
	_DetMat[1][0] = Matrix[1][1]; _DetMat[1][1] = Matrix[2][1]; _DetMat[1][2] = Matrix[3][1];
	_DetMat[2][0] = Matrix[1][3]; _DetMat[2][1] = Matrix[2][3]; _DetMat[2][2] = Matrix[3][3];

	_Matrix[2][0] = _DetMat.Determinant();

	_DetMat[0][0] = Matrix[0][0]; _DetMat[0][1] = Matrix[2][0]; _DetMat[0][2] = Matrix[3][0];
	_DetMat[1][0] = Matrix[0][1]; _DetMat[1][1] = Matrix[2][1]; _DetMat[1][2] = Matrix[3][1];
	_DetMat[2][0] = Matrix[0][3]; _DetMat[2][1] = Matrix[2][3]; _DetMat[2][2] = Matrix[3][3];

	_Matrix[2][1] = -_DetMat.Determinant();

	_DetMat[0][0] = Matrix[0][0]; _DetMat[0][1] = Matrix[1][0]; _DetMat[0][2] = Matrix[3][0];
	_DetMat[1][0] = Matrix[0][1]; _DetMat[1][1] = Matrix[1][1]; _DetMat[1][2] = Matrix[3][1];
	_DetMat[2][0] = Matrix[0][3]; _DetMat[2][1] = Matrix[1][3]; _DetMat[2][2] = Matrix[3][3];

	_Matrix[2][2] = _DetMat.Determinant();

	_DetMat[0][0] = Matrix[0][0]; _DetMat[0][1] = Matrix[1][0]; _DetMat[0][2] = Matrix[2][0];
	_DetMat[1][0] = Matrix[0][1]; _DetMat[1][1] = Matrix[1][1]; _DetMat[1][2] = Matrix[2][1];
	_DetMat[2][0] = Matrix[0][3]; _DetMat[2][1] = Matrix[1][3]; _DetMat[2][2] = Matrix[2][3];

	_Matrix[2][3] = -_DetMat.Determinant();

	_DetMat[0][0] = Matrix[1][0]; _DetMat[0][1] = Matrix[2][0]; _DetMat[0][2] = Matrix[3][0];
	_DetMat[1][0] = Matrix[1][1]; _DetMat[1][1] = Matrix[2][1]; _DetMat[1][2] = Matrix[3][1];
	_DetMat[2][0] = Matrix[1][2]; _DetMat[2][1] = Matrix[2][2]; _DetMat[2][2] = Matrix[3][2];

	_Matrix[3][0] = -_DetMat.Determinant();

	_DetMat[0][0] = Matrix[0][0]; _DetMat[0][1] = Matrix[2][0]; _DetMat[0][2] = Matrix[3][0];
	_DetMat[1][0] = Matrix[0][1]; _DetMat[1][1] = Matrix[2][1]; _DetMat[1][2] = Matrix[3][1];
	_DetMat[2][0] = Matrix[0][2]; _DetMat[2][1] = Matrix[2][2]; _DetMat[2][2] = Matrix[3][2];

	_Matrix[3][1] = _DetMat.Determinant();

	_DetMat[0][0] = Matrix[0][0]; _DetMat[0][1] = Matrix[1][0]; _DetMat[0][2] = Matrix[3][0];
	_DetMat[1][0] = Matrix[0][1]; _DetMat[1][1] = Matrix[1][1]; _DetMat[1][2] = Matrix[3][1];
	_DetMat[2][0] = Matrix[0][2]; _DetMat[2][1] = Matrix[1][2]; _DetMat[2][2] = Matrix[3][2];

	_Matrix[3][2] = -_DetMat.Determinant();

	_DetMat[0][0] = Matrix[0][0]; _DetMat[0][1] = Matrix[1][0]; _DetMat[0][2] = Matrix[2][0];
	_DetMat[1][0] = Matrix[0][1]; _DetMat[1][1] = Matrix[1][1]; _DetMat[1][2] = Matrix[2][1];
	_DetMat[2][0] = Matrix[0][2]; _DetMat[2][1] = Matrix[1][2]; _DetMat[2][2] = Matrix[2][2];

	_Matrix[3][3] = _DetMat.Determinant();

	_Matrix /= Determinant();

	*this = _Matrix;

	return *this;
}

const AuroraCore::Math::Mat4f AuroraCore::Math::Mat4f::Inversed() const
{
	return Mat4f(*this).Inverse();
}

const AuroraCore::Math::Mat4f& AuroraCore::Math::Mat4f::operator+ () const
{
	return *this;
}

const AuroraCore::Math::Mat4f AuroraCore::Math::Mat4f::operator- () const
{
	Mat4f _Matrix;

	_Matrix[0][0] = -Matrix[0][0]; _Matrix[0][1] = -Matrix[0][1]; _Matrix[0][2] = -Matrix[0][2]; _Matrix[0][3] = -Matrix[0][3];
	_Matrix[1][0] = -Matrix[1][0]; _Matrix[1][1] = -Matrix[1][1]; _Matrix[1][2] = -Matrix[1][2]; _Matrix[1][3] = -Matrix[1][3];
	_Matrix[2][0] = -Matrix[2][0]; _Matrix[2][1] = -Matrix[2][1]; _Matrix[2][2] = -Matrix[2][2]; _Matrix[2][3] = -Matrix[2][3];
	_Matrix[3][0] = -Matrix[3][0]; _Matrix[3][1] = -Matrix[3][1]; _Matrix[3][2] = -Matrix[3][2]; _Matrix[3][3] = -Matrix[3][3];

	return _Matrix;
}

const AuroraCore::Math::Vec4f AuroraCore::Math::Mat4f::operator* (const Vec4f& _Vec) const
{
	return Vec4f
	(
		Matrix[0][0] * _Vec.x + Matrix[0][1] * _Vec.y + Matrix[0][2] * _Vec.z + +Matrix[0][3] * _Vec.w,
		Matrix[1][0] * _Vec.x + Matrix[1][1] * _Vec.y + Matrix[1][2] * _Vec.z + +Matrix[1][3] * _Vec.w,
		Matrix[2][0] * _Vec.x + Matrix[2][1] * _Vec.y + Matrix[2][2] * _Vec.z + +Matrix[2][3] * _Vec.w,
		Matrix[3][0] * _Vec.x + Matrix[3][1] * _Vec.y + Matrix[3][2] * _Vec.z + +Matrix[3][3] * _Vec.w
	);
}

const AuroraCore::Math::Mat4f AuroraCore::Math::Mat4f::operator+ (const Mat4f& _Other) const
{
	Mat4f _Matrix(*this);

	_Matrix[0][0] += _Other[0][0]; _Matrix[0][1] += _Other[0][1]; _Matrix[0][2] += _Other[0][2]; _Matrix[0][3] += _Other[0][3];
	_Matrix[1][0] += _Other[1][0]; _Matrix[1][1] += _Other[1][1]; _Matrix[1][2] += _Other[1][2]; _Matrix[1][3] += _Other[1][3];
	_Matrix[2][0] += _Other[2][0]; _Matrix[2][1] += _Other[2][1]; _Matrix[2][2] += _Other[2][2]; _Matrix[2][3] += _Other[2][3];
	_Matrix[3][0] += _Other[3][0]; _Matrix[3][1] += _Other[3][1]; _Matrix[3][2] += _Other[3][2]; _Matrix[3][3] += _Other[3][3];

	return _Matrix;
}

const AuroraCore::Math::Mat4f& AuroraCore::Math::Mat4f::operator+= (const Mat4f& _Other)
{
	Matrix[0][0] += _Other[0][0]; Matrix[0][1] += _Other[0][1]; Matrix[0][2] += _Other[0][2]; Matrix[0][3] += _Other[0][3];
	Matrix[1][0] += _Other[1][0]; Matrix[1][1] += _Other[1][1]; Matrix[1][2] += _Other[1][2]; Matrix[1][3] += _Other[1][3];
	Matrix[2][0] += _Other[2][0]; Matrix[2][1] += _Other[2][1]; Matrix[2][2] += _Other[2][2]; Matrix[2][3] += _Other[2][3];
	Matrix[3][0] += _Other[3][0]; Matrix[3][1] += _Other[3][1]; Matrix[3][2] += _Other[3][2]; Matrix[3][3] += _Other[3][3];

	return *this;
}

const AuroraCore::Math::Mat4f AuroraCore::Math::Mat4f::operator+ (const float _Scale) const
{
	Mat4f _Matrix(*this);

	_Matrix[0][0] += _Scale; _Matrix[0][1] += _Scale; _Matrix[0][2] += _Scale; _Matrix[0][3] += _Scale;
	_Matrix[1][0] += _Scale; _Matrix[1][1] += _Scale; _Matrix[1][2] += _Scale; _Matrix[1][3] += _Scale;
	_Matrix[2][0] += _Scale; _Matrix[2][1] += _Scale; _Matrix[2][2] += _Scale; _Matrix[2][3] += _Scale;
	_Matrix[3][0] += _Scale; _Matrix[3][1] += _Scale; _Matrix[3][2] += _Scale; _Matrix[3][3] += _Scale;

	return _Matrix;
}

const AuroraCore::Math::Mat4f& AuroraCore::Math::Mat4f::operator+= (const float _Scale)
{
	Matrix[0][0] += _Scale; Matrix[0][1] += _Scale; Matrix[0][2] += _Scale; Matrix[0][3] += _Scale;
	Matrix[1][0] += _Scale; Matrix[1][1] += _Scale; Matrix[1][2] += _Scale; Matrix[1][3] += _Scale;
	Matrix[2][0] += _Scale; Matrix[2][1] += _Scale; Matrix[2][2] += _Scale; Matrix[2][3] += _Scale;
	Matrix[3][0] += _Scale; Matrix[3][1] += _Scale; Matrix[3][2] += _Scale; Matrix[3][3] += _Scale;

	return *this;
}

const AuroraCore::Math::Mat4f AuroraCore::Math::Mat4f::operator- (const Mat4f& _Other) const
{
	Mat4f _Matrix(*this);

	_Matrix[0][0] -= _Other[0][0]; _Matrix[0][1] -= _Other[0][1]; _Matrix[0][2] -= _Other[0][2]; _Matrix[0][3] -= _Other[0][3];
	_Matrix[1][0] -= _Other[1][0]; _Matrix[1][1] -= _Other[1][1]; _Matrix[1][2] -= _Other[1][2]; _Matrix[1][3] -= _Other[1][3];
	_Matrix[2][0] -= _Other[2][0]; _Matrix[2][1] -= _Other[2][1]; _Matrix[2][2] -= _Other[2][2]; _Matrix[2][3] -= _Other[2][3];
	_Matrix[3][0] -= _Other[3][0]; _Matrix[3][1] -= _Other[3][1]; _Matrix[3][2] -= _Other[3][2]; _Matrix[3][3] -= _Other[3][3];

	return _Matrix;
}

const AuroraCore::Math::Mat4f& AuroraCore::Math::Mat4f::operator-= (const Mat4f& _Other)
{
	Matrix[0][0] -= _Other[0][0]; Matrix[0][1] -= _Other[0][1]; Matrix[0][2] -= _Other[0][2]; Matrix[0][3] -= _Other[0][3];
	Matrix[1][0] -= _Other[1][0]; Matrix[1][1] -= _Other[1][1]; Matrix[1][2] -= _Other[1][2]; Matrix[1][3] -= _Other[1][3];
	Matrix[2][0] -= _Other[2][0]; Matrix[2][1] -= _Other[2][1]; Matrix[2][2] -= _Other[2][2]; Matrix[2][3] -= _Other[2][3];
	Matrix[3][0] -= _Other[3][0]; Matrix[3][1] -= _Other[3][1]; Matrix[3][2] -= _Other[3][2]; Matrix[3][3] -= _Other[3][3];

	return *this;
}

const AuroraCore::Math::Mat4f AuroraCore::Math::Mat4f::operator- (const float _Scale) const
{
	Mat4f _Matrix(*this);

	_Matrix[0][0] -= _Scale; _Matrix[0][1] -= _Scale; _Matrix[0][2] -= _Scale; _Matrix[0][3] -= _Scale;
	_Matrix[1][0] -= _Scale; _Matrix[1][1] -= _Scale; _Matrix[1][2] -= _Scale; _Matrix[1][3] -= _Scale;
	_Matrix[2][0] -= _Scale; _Matrix[2][1] -= _Scale; _Matrix[2][2] -= _Scale; _Matrix[2][3] -= _Scale;
	_Matrix[3][0] -= _Scale; _Matrix[3][1] -= _Scale; _Matrix[3][2] -= _Scale; _Matrix[3][3] -= _Scale;

	return _Matrix;
}

const AuroraCore::Math::Mat4f& AuroraCore::Math::Mat4f::operator-= (const float _Scale)
{
	Matrix[0][0] -= _Scale; Matrix[0][1] -= _Scale; Matrix[0][2] -= _Scale; Matrix[0][3] -= _Scale;
	Matrix[1][0] -= _Scale; Matrix[1][1] -= _Scale; Matrix[1][2] -= _Scale; Matrix[1][3] -= _Scale;
	Matrix[2][0] -= _Scale; Matrix[2][1] -= _Scale; Matrix[2][2] -= _Scale; Matrix[2][3] -= _Scale;
	Matrix[3][0] -= _Scale; Matrix[3][1] -= _Scale; Matrix[3][2] -= _Scale; Matrix[3][3] -= _Scale;

	return *this;
}

const AuroraCore::Math::Mat4f AuroraCore::Math::Mat4f::operator* (const Mat4f& _Other) const
{
	Mat4f _Matrix;

	_Matrix[0][0] = Matrix[0][0] * _Other[0][0] + Matrix[0][1] * _Other[1][0] + Matrix[0][2] * _Other[2][0] + Matrix[0][3] * _Other[3][0];
	_Matrix[0][1] = Matrix[0][0] * _Other[0][1] + Matrix[0][1] * _Other[1][1] + Matrix[0][2] * _Other[2][1] + Matrix[0][3] * _Other[3][1];
	_Matrix[0][2] = Matrix[0][0] * _Other[0][2] + Matrix[0][1] * _Other[1][2] + Matrix[0][2] * _Other[2][2] + Matrix[0][3] * _Other[3][2];
	_Matrix[0][3] = Matrix[0][0] * _Other[0][3] + Matrix[0][1] * _Other[1][3] + Matrix[0][2] * _Other[2][3] + Matrix[0][3] * _Other[3][3];

	_Matrix[1][0] = Matrix[1][0] * _Other[0][0] + Matrix[1][1] * _Other[1][0] + Matrix[1][2] * _Other[2][0] + Matrix[1][3] * _Other[3][0];
	_Matrix[1][1] = Matrix[1][0] * _Other[0][1] + Matrix[1][1] * _Other[1][1] + Matrix[1][2] * _Other[2][1] + Matrix[1][3] * _Other[3][1];
	_Matrix[1][2] = Matrix[1][0] * _Other[0][2] + Matrix[1][1] * _Other[1][2] + Matrix[1][2] * _Other[2][2] + Matrix[1][3] * _Other[3][2];
	_Matrix[1][3] = Matrix[1][0] * _Other[0][3] + Matrix[1][1] * _Other[1][3] + Matrix[1][2] * _Other[2][3] + Matrix[1][3] * _Other[3][3];

	_Matrix[2][0] = Matrix[2][0] * _Other[0][0] + Matrix[2][1] * _Other[1][0] + Matrix[2][2] * _Other[2][0] + Matrix[2][3] * _Other[3][0];
	_Matrix[2][1] = Matrix[2][0] * _Other[0][1] + Matrix[2][1] * _Other[1][1] + Matrix[2][2] * _Other[2][1] + Matrix[2][3] * _Other[3][1];
	_Matrix[2][2] = Matrix[2][0] * _Other[0][2] + Matrix[2][1] * _Other[1][2] + Matrix[2][2] * _Other[2][2] + Matrix[2][3] * _Other[3][2];
	_Matrix[2][3] = Matrix[2][0] * _Other[0][3] + Matrix[2][1] * _Other[1][3] + Matrix[2][2] * _Other[2][3] + Matrix[2][3] * _Other[3][3];

	_Matrix[3][0] = Matrix[3][0] * _Other[0][0] + Matrix[3][1] * _Other[1][0] + Matrix[3][2] * _Other[2][0] + Matrix[3][3] * _Other[3][0];
	_Matrix[3][1] = Matrix[3][0] * _Other[0][1] + Matrix[3][1] * _Other[1][1] + Matrix[3][2] * _Other[2][1] + Matrix[3][3] * _Other[3][1];
	_Matrix[3][2] = Matrix[3][0] * _Other[0][2] + Matrix[3][1] * _Other[1][2] + Matrix[3][2] * _Other[2][2] + Matrix[3][3] * _Other[3][2];
	_Matrix[3][3] = Matrix[3][0] * _Other[0][3] + Matrix[3][1] * _Other[1][3] + Matrix[3][2] * _Other[2][3] + Matrix[3][3] * _Other[3][3];

	return _Matrix;
}

const AuroraCore::Math::Mat4f& AuroraCore::Math::Mat4f::operator*= (const Mat4f& _Other)
{
	Mat4f _Matrix;

	_Matrix[0][0] = Matrix[0][0] * _Other[0][0] + Matrix[0][1] * _Other[1][0] + Matrix[0][2] * _Other[2][0] + Matrix[0][3] * _Other[3][0];
	_Matrix[0][1] = Matrix[0][0] * _Other[0][1] + Matrix[0][1] * _Other[1][1] + Matrix[0][2] * _Other[2][1] + Matrix[0][3] * _Other[3][1];
	_Matrix[0][2] = Matrix[0][0] * _Other[0][2] + Matrix[0][1] * _Other[1][2] + Matrix[0][2] * _Other[2][2] + Matrix[0][3] * _Other[3][2];
	_Matrix[0][3] = Matrix[0][0] * _Other[0][3] + Matrix[0][1] * _Other[1][3] + Matrix[0][2] * _Other[2][3] + Matrix[0][3] * _Other[3][3];

	_Matrix[1][0] = Matrix[1][0] * _Other[0][0] + Matrix[1][1] * _Other[1][0] + Matrix[1][2] * _Other[2][0] + Matrix[1][3] * _Other[3][0];
	_Matrix[1][1] = Matrix[1][0] * _Other[0][1] + Matrix[1][1] * _Other[1][1] + Matrix[1][2] * _Other[2][1] + Matrix[1][3] * _Other[3][1];
	_Matrix[1][2] = Matrix[1][0] * _Other[0][2] + Matrix[1][1] * _Other[1][2] + Matrix[1][2] * _Other[2][2] + Matrix[1][3] * _Other[3][2];
	_Matrix[1][3] = Matrix[1][0] * _Other[0][3] + Matrix[1][1] * _Other[1][3] + Matrix[1][2] * _Other[2][3] + Matrix[1][3] * _Other[3][3];

	_Matrix[2][0] = Matrix[2][0] * _Other[0][0] + Matrix[2][1] * _Other[1][0] + Matrix[2][2] * _Other[2][0] + Matrix[2][3] * _Other[3][0];
	_Matrix[2][1] = Matrix[2][0] * _Other[0][1] + Matrix[2][1] * _Other[1][1] + Matrix[2][2] * _Other[2][1] + Matrix[2][3] * _Other[3][1];
	_Matrix[2][2] = Matrix[2][0] * _Other[0][2] + Matrix[2][1] * _Other[1][2] + Matrix[2][2] * _Other[2][2] + Matrix[2][3] * _Other[3][2];
	_Matrix[2][3] = Matrix[2][0] * _Other[0][3] + Matrix[2][1] * _Other[1][3] + Matrix[2][2] * _Other[2][3] + Matrix[2][3] * _Other[3][3];

	_Matrix[3][0] = Matrix[3][0] * _Other[0][0] + Matrix[3][1] * _Other[1][0] + Matrix[3][2] * _Other[2][0] + Matrix[3][3] * _Other[3][0];
	_Matrix[3][1] = Matrix[3][0] * _Other[0][1] + Matrix[3][1] * _Other[1][1] + Matrix[3][2] * _Other[2][1] + Matrix[3][3] * _Other[3][1];
	_Matrix[3][2] = Matrix[3][0] * _Other[0][2] + Matrix[3][1] * _Other[1][2] + Matrix[3][2] * _Other[2][2] + Matrix[3][3] * _Other[3][2];
	_Matrix[3][3] = Matrix[3][0] * _Other[0][3] + Matrix[3][1] * _Other[1][3] + Matrix[3][2] * _Other[2][3] + Matrix[3][3] * _Other[3][3];

	*this = _Matrix;

	return *this;
}

const AuroraCore::Math::Mat4f AuroraCore::Math::Mat4f::operator* (const float _Scale) const
{
	Mat4f _Matrix(*this);

	_Matrix[0][0] *= _Scale; _Matrix[0][1] *= _Scale; _Matrix[0][2] *= _Scale; _Matrix[0][3] *= _Scale;
	_Matrix[1][0] *= _Scale; _Matrix[1][1] *= _Scale; _Matrix[1][2] *= _Scale; _Matrix[1][3] *= _Scale;
	_Matrix[2][0] *= _Scale; _Matrix[2][1] *= _Scale; _Matrix[2][2] *= _Scale; _Matrix[2][3] *= _Scale;
	_Matrix[3][0] *= _Scale; _Matrix[3][1] *= _Scale; _Matrix[3][2] *= _Scale; _Matrix[3][3] *= _Scale;

	return _Matrix;
}

const AuroraCore::Math::Mat4f& AuroraCore::Math::Mat4f::operator*= (const float _Scale)
{
	Matrix[0][0] *= _Scale; Matrix[0][1] *= _Scale; Matrix[0][2] *= _Scale; Matrix[0][3] *= _Scale;
	Matrix[1][0] *= _Scale; Matrix[1][1] *= _Scale; Matrix[1][2] *= _Scale; Matrix[1][3] *= _Scale;
	Matrix[2][0] *= _Scale; Matrix[2][1] *= _Scale; Matrix[2][2] *= _Scale; Matrix[2][3] *= _Scale;
	Matrix[3][0] *= _Scale; Matrix[3][1] *= _Scale; Matrix[3][2] *= _Scale; Matrix[3][3] *= _Scale;

	return *this;
}

const AuroraCore::Math::Mat4f AuroraCore::Math::Mat4f::operator/ (const float _Scale) const
{
	Mat4f _Matrix(*this);

	_Matrix[0][0] /= _Scale; _Matrix[0][1] /= _Scale; _Matrix[0][2] /= _Scale; _Matrix[0][3] /= _Scale;
	_Matrix[1][0] /= _Scale; _Matrix[1][1] /= _Scale; _Matrix[1][2] /= _Scale; _Matrix[1][3] /= _Scale;
	_Matrix[2][0] /= _Scale; _Matrix[2][1] /= _Scale; _Matrix[2][2] /= _Scale; _Matrix[2][3] /= _Scale;
	_Matrix[3][0] /= _Scale; _Matrix[3][1] /= _Scale; _Matrix[3][2] /= _Scale; _Matrix[3][3] /= _Scale;

	return _Matrix;
}

const AuroraCore::Math::Mat4f& AuroraCore::Math::Mat4f::operator/= (const float _Scale)
{
	Matrix[0][0] /= _Scale; Matrix[0][1] /= _Scale; Matrix[0][2] /= _Scale; Matrix[0][3] /= _Scale;
	Matrix[1][0] /= _Scale; Matrix[1][1] /= _Scale; Matrix[1][2] /= _Scale; Matrix[1][3] /= _Scale;
	Matrix[2][0] /= _Scale; Matrix[2][1] /= _Scale; Matrix[2][2] /= _Scale; Matrix[2][3] /= _Scale;
	Matrix[3][0] /= _Scale; Matrix[3][1] /= _Scale; Matrix[3][2] /= _Scale; Matrix[3][3] /= _Scale;

	return *this;
}

const bool AuroraCore::Math::Mat4f::operator== (const Mat4f& _Other) const
{
	return
		Matrix[0][0] == _Other[0][0] && Matrix[0][1] == _Other[0][1] && Matrix[0][2] == _Other[0][2] && Matrix[0][3] == _Other[0][3] &&
		Matrix[1][0] == _Other[1][0] && Matrix[1][1] == _Other[1][1] && Matrix[1][2] == _Other[1][2] && Matrix[1][3] == _Other[1][3] &&
		Matrix[2][0] == _Other[2][0] && Matrix[2][1] == _Other[2][1] && Matrix[2][2] == _Other[2][2] && Matrix[2][3] == _Other[2][3] &&
		Matrix[3][0] == _Other[3][0] && Matrix[3][1] == _Other[3][1] && Matrix[3][2] == _Other[3][2] && Matrix[3][3] == _Other[3][3];
}

const bool AuroraCore::Math::Mat4f::operator!= (const Mat4f& _Other) const
{
	return
		Matrix[0][0] != _Other[0][0] || Matrix[0][1] != _Other[0][1] || Matrix[0][2] != _Other[0][2] || Matrix[0][3] != _Other[0][3] ||
		Matrix[1][0] != _Other[1][0] || Matrix[1][1] != _Other[1][1] || Matrix[1][2] != _Other[1][2] || Matrix[1][3] != _Other[1][3] ||
		Matrix[2][0] != _Other[2][0] || Matrix[2][1] != _Other[2][1] || Matrix[2][2] != _Other[2][2] || Matrix[2][3] != _Other[2][3] ||
		Matrix[3][0] != _Other[3][0] || Matrix[3][1] != _Other[3][1] || Matrix[3][2] != _Other[3][2] || Matrix[3][3] != _Other[3][3];
}

float* AuroraCore::Math::Mat4f::operator[] (const size_t _Index)
{
	return Matrix[_Index].Data();
}

const float* AuroraCore::Math::Mat4f::operator[] (const size_t _Index) const
{
	return Matrix[_Index].Data();
}

const AuroraCore::Math::Mat4f& AuroraCore::Math::Mat4f::operator= (const Mat4f& _Other)
{
	Matrix[0][0] = _Other[0][0]; Matrix[0][1] = _Other[0][1]; Matrix[0][2] = _Other[0][2]; Matrix[0][3] = _Other[0][3];
	Matrix[1][0] = _Other[1][0]; Matrix[1][1] = _Other[1][1]; Matrix[1][2] = _Other[1][2]; Matrix[1][3] = _Other[1][3];
	Matrix[2][0] = _Other[2][0]; Matrix[2][1] = _Other[2][1]; Matrix[2][2] = _Other[2][2]; Matrix[2][3] = _Other[2][3];
	Matrix[3][0] = _Other[3][0]; Matrix[3][1] = _Other[3][1]; Matrix[3][2] = _Other[3][2]; Matrix[3][3] = _Other[3][3];

	return *this;
}

const AuroraCore::Math::Mat4f& AuroraCore::Math::Mat4f::operator= (Mat4f&& _Other) noexcept
{
	Matrix[0][0] = _Other[0][0]; Matrix[0][1] = _Other[0][1]; Matrix[0][2] = _Other[0][2]; Matrix[0][3] = _Other[0][3];
	Matrix[1][0] = _Other[1][0]; Matrix[1][1] = _Other[1][1]; Matrix[1][2] = _Other[1][2]; Matrix[1][3] = _Other[1][3];
	Matrix[2][0] = _Other[2][0]; Matrix[2][1] = _Other[2][1]; Matrix[2][2] = _Other[2][2]; Matrix[2][3] = _Other[2][3];
	Matrix[3][0] = _Other[3][0]; Matrix[3][1] = _Other[3][1]; Matrix[3][2] = _Other[3][2]; Matrix[3][3] = _Other[3][3];

	return *this;
}

const AuroraCore::Math::Mat4f AuroraCore::Math::Mat4f::GetScale(const float _x, const float _y, const float _z, const float _w)
{
	Mat4f _Matrix;

	_Matrix[0][0] = _x;
	_Matrix[1][1] = _y;
	_Matrix[2][2] = _z;
	_Matrix[3][3] = _w;

	return _Matrix;
}

const AuroraCore::Math::Mat4f AuroraCore::Math::Mat4f::GetFill(const float _Value)
{
	Mat4f _Matrix;

	_Matrix[0][0] = _Value; _Matrix[0][1] = _Value; _Matrix[0][2] = _Value; _Matrix[0][3] = _Value;
	_Matrix[1][0] = _Value; _Matrix[1][1] = _Value; _Matrix[1][2] = _Value; _Matrix[1][3] = _Value;
	_Matrix[2][0] = _Value; _Matrix[2][1] = _Value; _Matrix[2][2] = _Value; _Matrix[2][3] = _Value;
	_Matrix[3][0] = _Value; _Matrix[3][1] = _Value; _Matrix[3][2] = _Value; _Matrix[3][3] = _Value;

	return _Matrix;
}

const AuroraCore::Math::Mat4f AuroraCore::Math::Mat4f::GetShear(const float _Value, const size_t _ShearedAxis, const size_t _ShearByAxis)
{
	Mat4f _Matrix;

	_Matrix[_ShearedAxis][_ShearByAxis] = _Value;

	return _Matrix;
}

const AuroraCore::Math::Mat4f AuroraCore::Math::Mat4f::GetRotation(const float _Angle, const Vec3f& _RotationAxis)
{
	Mat4f _Matrix;

	float _Sin = sinf(_Angle);
	float _Cos = cosf(_Angle);

	_Matrix[0][0] = _Cos + _RotationAxis.x * _RotationAxis.x * (1.0f - _Cos);
	_Matrix[0][1] = _RotationAxis.x * _RotationAxis.y * (1.0f - _Cos) - _RotationAxis.z * _Sin;
	_Matrix[0][2] = _RotationAxis.x * _RotationAxis.z * (1.0f - _Cos) + _RotationAxis.y * _Sin;

	_Matrix[1][0] = _RotationAxis.y * _RotationAxis.x * (1.0f - _Cos) + _RotationAxis.z * _Sin;
	_Matrix[1][1] = _Cos + _RotationAxis.y * _RotationAxis.y * (1.0f - _Cos);
	_Matrix[1][2] = _RotationAxis.y * _RotationAxis.z * (1.0f - _Cos) - _RotationAxis.x * _Sin;

	_Matrix[2][0] = _RotationAxis.z * _RotationAxis.x * (1.0f - _Cos) - _RotationAxis.y * _Sin;
	_Matrix[2][1] = _RotationAxis.z * _RotationAxis.y * (1.0f - _Cos) + _RotationAxis.x * _Sin;
	_Matrix[2][2] = _Cos + _RotationAxis.z * _RotationAxis.z * (1.0f - _Cos);

	return _Matrix;
}

const AuroraCore::Math::Mat4f AuroraCore::Math::Mat4f::GetTranslation(const Vec3f& _Coords)
{
	Mat4f _Matrix;

	_Matrix[0][3] = _Coords.x;
	_Matrix[1][3] = _Coords.y;
	_Matrix[2][3] = _Coords.z;

	return _Matrix;
}

const AuroraCore::Math::Mat4f AuroraCore::Math::Mat4f::GetOrtho(const float _Left, const float _Right, const float _Bottom, const float _Top, const float _Front, const float _Back)
{
	Mat4f _Matrix;

	_Matrix[0][0] = 2.0f / (_Right - _Left);
	_Matrix[1][1] = 2.0f / (_Top - _Bottom);
	_Matrix[2][2] = 2.0f / (_Back - _Front);

	_Matrix[0][3] = (_Right + _Left) / (_Left - _Right);
	_Matrix[1][3] = (_Top + _Bottom) / (_Bottom - _Top);
	_Matrix[2][3] = (_Back + _Front) / (_Front - _Back);

	return _Matrix;
}

const AuroraCore::Math::Mat4f AuroraCore::Math::Mat4f::GetPerspective(const float _Fov, const float _AspectRatio, const float _ZNear, const float _ZFar)
{
	Mat4f _Matrix;

	float _Tan = tanf(_Fov / 2);

	_Matrix[0][0] = 1.0f / (_AspectRatio * _Tan);
	_Matrix[1][1] = 1.0f / _Tan;
	_Matrix[2][2] = -(_ZFar + _ZNear) / (_ZFar - _ZNear);
	_Matrix[2][3] = -(2.0f * _ZFar * _ZNear) / (_ZFar - _ZNear);
	_Matrix[3][2] = -1.0f;
	_Matrix[3][3] = 0.0f;

	return _Matrix;
}
