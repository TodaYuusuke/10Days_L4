#pragma once
#include <Adapter.h>
#include "BaseEnemySpriteSystem.h"
#include <memory>

// 敵キャラクターの基底クラス
class BaseEnemy {
public:
	BaseEnemy();
	virtual ~BaseEnemy() = default;

	// 初期化処理
	virtual void Initialize();
	// 更新処理
	virtual void Update();


private:
	
	// スプライト管理クラス
	std::unique_ptr<BaseEnemySpriteSystem> spriteSystem_;
	


};
