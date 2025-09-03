#pragma once
#include <Adapter.h>
#include <vector>

// 敵キャラクターの基底クラス
class BaseEnemy{
public:
	BaseEnemy();
	~BaseEnemy() = default;

	// 初期化処理
	virtual void Initialize();
	// 更新処理
	virtual void Update();


private:
	// スプライト用コンテナ。パーツのenumを別途作成しその数に合わせて生成する
	std::vector<LWP::Primitive::SequenceSprite> sprites_;



};
