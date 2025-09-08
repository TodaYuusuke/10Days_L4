#pragma once
#include <Adapter.h>

using namespace LWP::Math;
class BaseEnemy;
class NormalBossStateManager;

/// <summary>
/// 敵の状態インターフェース
/// </summary>
class IEnemyState{
public:
	virtual ~IEnemyState() = default;

	// 初期化処理
	virtual void Enter(BaseEnemy* enemy) = 0;
	// 更新処理
	virtual void Update(BaseEnemy* enemy) = 0;
	// 終了処理
	virtual void Exit(BaseEnemy* enemy) = 0;

private:

};
