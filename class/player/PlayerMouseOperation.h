#pragma once
#include <Adapter.h>

/// <summary>
/// プレイヤーのマウス操作
/// </summary>
class PlayerMouseOperation
{

public: // メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	PlayerMouseOperation();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerMouseOperation();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

private:

	/// <summary>
	/// 押された
	/// </summary>
	void LeftButtonPressed();

	/// <summary>
	/// 押され続けている
	/// </summary>
	void LeftButtonHeldDown();

	/// <summary>
	/// 離された
	/// </summary>
	void LeftButtonReleased();

public: // アクセッサ

	bool GetIsDragging() const { return isDragging_; }
	bool GetClicked() const { return clicked_; }

private:

	// 押された位置
	LWP::Math::Vector2 pressedPosition_;

	// ドラッグ状態か
	bool isDragging_;

	// クリックされた
	bool clicked_;

	// スプライト
	LWP::Primitive::NormalSprite sprite_;

};

