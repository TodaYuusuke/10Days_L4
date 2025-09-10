#pragma once
#include <Adapter.h>

class EnemyBullet {
public:
	EnemyBullet();
	~EnemyBullet() = default;

	// 初期化 (生成)
	void Initialize();
	// 更新
	void Update();

private:

	LWP::Object::Collision2D coll2D_;
	LWP::Primitive::SequenceSprite sprite_;

	bool isAlive_ = false;
};