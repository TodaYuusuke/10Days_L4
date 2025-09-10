#pragma once
#include <Adapter.h>

/// <summary>
/// 終わる時のスプライト
/// </summary>
class GameSprite
{


public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameSprite();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameSprite();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// アクティブ切り替え
	/// </summary>
	/// <param name="isActive"></param>
	void SetIsActive(bool isActive);

	/// <summary>
	/// アクティブ切り替え
	/// </summary>
	bool GetIsActive();

	/// <summary>
	/// index取得
	/// </summary>
	/// <param name="index">インデックス</param>
	void SetIndex(int index);

private:

	LWP::Primitive::SequenceSprite sprite_;

};

