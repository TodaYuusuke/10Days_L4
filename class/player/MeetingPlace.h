#pragma once
#include <Adapter.h>

/// <summary>
/// 集合場所
/// </summary>
class MeetingPlace
{

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	MeetingPlace();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~MeetingPlace();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

public: // アクセッサ

	void SetPosition(const LWP::Math::Vector2& position) { position_ = position; }
	LWP::Math::Vector2 GetPosition() const { return position_; }

private:

	// スプライト
	LWP::Primitive::SequenceSprite sprite_;

	// 連番のindexX
	int indexX_;

	// index変更までのフレームカウント
	int changeIndexFrameCount_;

	// 位置
	LWP::Math::Vector2 position_;

};

