#pragma once

template<typename T>
struct Vector2 final {
	T x = 0;
	T y = 0;

	// ADD-----------------------------------
	Vector2 operator+(const Vector2& obj) {
		Vector2 result;
		result.x = x + obj.x;
		result.y = y + obj.y;

		return result;
	}
	void operator+=(const Vector2& obj) {
		x += obj.x;
		y += obj.y;
	}
	Vector2 operator+(float obj) {
		Vector2 result;
		result.x = x + obj;
		result.y = y + obj;

		return result;
	}
	void operator+=(float obj) {
		x += obj;
		y += obj;
	}

	// SUB---------------------------------
	Vector2 operator-(const Vector2& obj) {
		Vector2 result;
		result.x = x - obj.x;
		result.y = y - obj.y;

		return result;
	}
	void operator-=(const Vector2& obj) {
		x -= obj.x;
		y -= obj.y;
	}
	Vector2 operator-(float obj) {
		Vector2 result;
		result.x = x - obj;
		result.y = y - obj;

		return result;
	}
	void operator-=(float obj) {
		x -= obj;
		y -= obj;
	}

	// MULTIPLY-----------------------
	Vector2 operator*(const Vector2& obj) {
		Vector2 result;
		result.x = x * obj.x;
		result.y = y * obj.y;

		return result;
	}
	void operator*=(const Vector2& obj) {
		x *= obj.x;
		y *= obj.y;
	}
	Vector2 operator*(float obj) {
		Vector2 result;
		result.x = x * obj;
		result.y = y * obj;

		return result;
	}
	void operator*=(float obj) {
		x *= obj;
		y *= obj;
	}
};
using Vec2 = Vector2<float>;

template<typename T>
struct Vector3 final {
	T x = 0;
	T y = 0;
	T z = 0;

	// ADD----------------------------------
	Vector3 operator+(const Vector3& obj) {
		Vector3 result;
		result.x = x + obj.x;
		result.y = y + obj.y;
		result.z = z + obj.z;

		return result;
	}
	void operator+=(const Vector3& obj) {
		x += obj.x;
		y += obj.y;
		z += obj.z;
	}
	Vector3 operator+(float obj) {
		Vector3 result;
		result.x = x + obj;
		result.y = y + obj;
		result.z = z + obj;

		return result;
	}
	void operator+=(float obj) {
		x += obj;
		y += obj;
		z += obj;
	}


	// SUB--------------------------
	Vector3 operator-(const Vector3& obj) {
		Vector3 result;
		result.x = x - obj.x;
		result.y = y - obj.y;
		result.z = z - obj.z;

		return result;
	}
	void operator-=(const Vector3& obj) {
		x -= obj.x;
		y -= obj.y;
		z -= obj.z;
	}
	Vector3 operator-(float obj) {
		Vector3 result;
		result.x = x - obj;
		result.y = y - obj;
		result.z = z - obj;

		return result;
	}
	void operator-=(float obj) {
		x -= obj;
		y -= obj;
		z -= obj;
	}

	// MULTIPLY-----------------------------
	Vector3 operator*(const Vector3& obj) {
		Vector3 result;
		result.x = x * obj.x;
		result.y = y * obj.y;
		result.z = z * obj.z;

		return result;
	}
	void operator*=(const Vector3& obj) {
		x *= obj.x;
		y *= obj.y;
		z *= obj.z;
	}
	Vector3 operator*(float obj) {
		Vector3 result;
		result.x = x * obj;
		result.y = y * obj;
		result.z = z * obj;

		return result;
	}
	void operator*=(float obj) {
		x *= obj;
		y *= obj;
		z *= obj;
	}
};
using Vec3 = Vector3<float>;

template<typename T>
struct Vector4 final {
	T x = 0;
	T y = 0;
	T z = 0;
	T w = 0;

	// ADD----------------------------------
	Vector4 operator+(const Vector4& obj) {
		Vector4 result;
		result.x = x + obj.x;
		result.y = y + obj.y;
		result.z = z + obj.z;
		result.w = w + obj.w;

		return result;
	}
	void operator+=(const Vector4& obj) {
		x += obj.x;
		z += obj.z;
		y += obj.y;
		w += obj.w;
	}
	Vector4 operator+(float obj) {
		Vector4 result;
		result.x = x + obj;
		result.y = y + obj;
		result.z = z + obj;
		result.w = w + obj;

		return result;
	}
	void operator+=(float obj) {
		x += obj;
		y += obj;
		z += obj;
		w += obj;
	}


	// SUB----------------------------------
	Vector4 operator-(const Vector4& obj) {
		Vector4 result;
		result.x = x - obj.x;
		result.y = y - obj.y;
		result.z = z - obj.z;
		result.w = w - obj.w;

		return result;
	}
	void operator-=(const Vector4& obj) {
		x -= obj.x;
		y -= obj.y;
		z -= obj.z;
		w -= obj.w;
	}
	Vector4 operator-(float obj) {
		Vector4 result;
		result.x = x - obj;
		result.y = y - obj;
		result.z = z - obj;
		result.w = w - obj;

		return result;
	}
	void operator-=(float obj) {
		x -= obj;
		y -= obj;
		z -= obj;
		w -= obj;
	}

	// MULTIPLY-----------------------------
	Vector4 operator*(const Vector4& obj) {
		Vector4 result;
		result.x = x * obj.x;
		result.y = y * obj.y;
		result.z = z * obj.z;
		result.w = w * obj.w;

		return result;
	}
	void operator*=(const Vector4& obj) {
		x *= obj.x;
		y *= obj.y;
		z *= obj.z;
		w *= obj.w;
	}
	Vector4 operator*(float obj) {
		Vector4 result;
		result.x = x * obj;
		result.y = y * obj;
		result.z = z * obj;
		result.w = w * obj;

		return result;
	}
	void operator*=(float obj) {
		x *= obj;
		y *= obj;
		z *= obj;
		w *= obj;
	}
};
using Vec4 = Vector4<float>;