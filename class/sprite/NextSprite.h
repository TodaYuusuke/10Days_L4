#pragma once
#include <Adapter.h>

/// <summary>
/// 次へ行くためのスプライト
/// </summary>
class NextSprite
{

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	NextSprite();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~NextSprite();

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

private:
	
	LWP::Primitive::NormalSprite sprite_;

	LWP::Math::Vector2 basePosition_;

	float addValue_;

};

