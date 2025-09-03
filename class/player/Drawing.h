#pragma once
#include <vector>
#include <Adapter.h>

/// <summary>
/// 書き途中
/// </summary>
class Drawing
{

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

	// 動いてる
	bool isActive_;

	// 記録タイミングタイマー
	float recordingTimer_;

};

