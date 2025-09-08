#pragma once
#include <Adapter.h>

/// <summary>
/// 壁
/// </summary>
class Wall
{

public: // メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Wall();

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="start">開始地点</param>
	/// <param name="end">終了地点</param>
	/// <param name="hp">体力</param>
	/// <param name="lifeTime">生存時間</param>
	Wall(const LWP::Math::Vector2& start, const LWP::Math::Vector2 end, int hp, float lifeTime);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Wall();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initilaize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 死んだか
	/// </summary>
	/// <returns></returns>
	bool IsDead() const { return isDead_; }

private: // メンバ変数

	// 開始地点
	LWP::Math::Vector2 start_;
	// 終了地点
	LWP::Math::Vector2 end_;

	// 体力
	int hp_;
	// 生存時間
	float lifeTime_;
	
	// コライダー
	LWP::Object::Collision2D collider_;

	// スプライト
	LWP::Primitive::NormalSprite sprite_;

	// 死んだか
	bool isDead_;

};

