#pragma once
#include <Adapter.h>
#include <vector>

// 敵の描画システム基底クラス
class BaseEnemySpriteSystem {
public:
	BaseEnemySpriteSystem() = default;
	virtual ~BaseEnemySpriteSystem() = default;

	// 初期化処理
	virtual void Initialize() {};
	
	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="centerPosition">描画用中心座標,いうなれば親</param>
	virtual void Update(const LWP::Math::Vector2& centerPosition) {};


protected:
	// スプライト用コンテナ。パーツのenumを別途作成しその数に合わせて生成する
	std::vector<LWP::Primitive::SequenceSprite> sprites_;

};
