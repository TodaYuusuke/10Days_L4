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

private: // メンバ関数
	
	/// <summary>
	/// スプライト起動
	/// </summary>
	/// <param name="point0">点0</param>
	/// <param name="point1">点1</param>
	void SpriteActive(const LWP::Math::Vector2& point0, const LWP::Math::Vector2& point1);

private: // メンバ変数

	// 点
	std::vector<LWP::Math::Vector2> points_;

	// スプライト
	std::array<LWP::Primitive::NormalSprite, kSpriteNum_> sprites_;

	// スプライト番号
	size_t sprieIndex_;

	// 動いてる
	bool isActive_;

	// 記録タイミングタイマー
	float recordingTimer_;

	// 線の長さ
	float lineLength_;

};

