#pragma once
#include <vector>
#include <Adapter.h>

/// <summary>
/// 書き途中
/// </summary>
class Drawing
{

public:

	// スプライトの数
	static const size_t kSpriteNum_ = 128;
	// スプライトの大きさ
	static const LWP::Math::Vector2 kSpriteSize_;

public: // メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Drawing(); 

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Drawing();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="isDragging">ドラッグ中か</param>
	void Update(bool isDragging);

private: // メンバ変数

	// 点
	std::vector<LWP::Math::Vector2> points_;

	// スプライト
	std::array<LWP::Primitive::NormalSprite, kSpriteNum_> sprites_;

	size_t sprieIndex_;

	// 動いてる
	bool isActive_;

	// 記録タイミングタイマー
	float recordingTimer_;

};

