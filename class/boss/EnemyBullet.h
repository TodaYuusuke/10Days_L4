#pragma once
#include <Adapter.h>

class EnemyBullet {
public:
	EnemyBullet();
	~EnemyBullet() = default;

	// 初期化 (生成)
	void Initialize();
	// 更新
	void Update(const LWP::Math::Vector2& dir);

	// 弾の生成
	void SetBullet(const LWP::Math::Vector2& pos, const float& radius);
	void SetBullet(const LWP::Math::Vector2& pos, const float& radius, const LWP::Math::Vector2& dir);
	// 生死フラグの取得
	const bool& GetIsAlive() const { return isAlive_; }
private:
	// 画面制限の設定
	void Limit();
private:

	LWP::Object::TransformQuat transform_;
	LWP::Object::Collision2D coll2D_;
	LWP::Primitive::NormalSprite sprite_;
	LWP::Math::Vector2 dir_;
	bool isAlive_ = false;
};