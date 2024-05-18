#pragma once
#include "MyFunc.h"

class Camera2D {
	Camera2D();
	~Camera2D();
	static void Init();
	static void Update();
	static void Fin();


private:
	static Vec2 pos_;
	static Vec2 scale_;
	static Vec2 theta_;
	static Vector2<int> shake_;

public:
	static Vec2 GetPos() { return pos_; }
	static void SetPos(const Vec2& pos){ pos_ = pos; }

	static Vec2 GetScale() { return scale_; }
	static void SetScale(const Vec2& scale) { scale_ = scale; }

	static Vec2 GetTheta() { return theta_; }
	static void SetTheta(const Vec2& theta) { theta_ = theta; }

	static Vector2<int> GetShake() { return shake_; }
	static void SetShake(const Vector2<int>& shake) { shake_ = shake; }
};

class Camera3D {
public:
	Camera3D();
	~Camera3D();
	static void Init();
	static void Update();
	static void Fin();

private:
	static Vec3 pos_;
	static Vec3 scale_;
	static Vec3 theta_;
	static Vector3<int> shake_;

public:
	static Vec3 GetPos() { return pos_; }
	static void SetPos(const Vec3& pos) { pos_ = pos; }

	static Vec3 GetScale() { return scale_; }
	static void SetScale(const Vec3& scale) { scale_ = scale; }

	static Vec3 GetTheta() { return theta_; }
	static void SetTheta(const Vec3& theta) { theta_ = theta; }

	static Vector3<int> GetShake() { return shake_; }
	static void SetShake(const Vector3<int>& shake) { shake_ = shake; }
};
