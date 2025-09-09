#pragma once
#include <Adapter.h>

/// <summary>
/// 石
/// </summary>
class Stone
{

public: // メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Stone();

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="position">位置</param>
	/// <param name="direction">方向</param>
	Stone(const LWP::Math::Vector2& position, const LWP::Math::Vector2& direction);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Stone();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// リセット
	/// </summary>
	/// <param name="position">位置</param>
	/// <param name="direction">方向</param>
	void Reset(const LWP::Math::Vector2& position, const LWP::Math::Vector2& direction);
	
public: // アクセッサ

	bool IsDead() const { return isDead_; }

private: // メンバ変数

	// 位置
	LWP::Math::Vector2 position_;
	// 方向
	LWP::Math::Vector2 direction_;
	// 速さ
	float speed_;
	// スプライト
	LWP::Primitive::NormalSprite sprite_;
	// 死んだか
	bool isDead_;

	// コライダー
	LWP::Object::Collision2D collider_;

};

