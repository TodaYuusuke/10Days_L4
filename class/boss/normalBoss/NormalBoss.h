#pragma once
#include "../BaseEnemy.h"
#include <memory>
#include "NormalBossStateManager.h"
#include "../data/NormalBossData.h"

class MinionManager;
class Minion;

class NormalBoss : public BaseEnemy{
public:
	NormalBoss() = delete;
	NormalBoss(BaseEnemyData& data);
	~NormalBoss() = default;

	void Initialize(BaseEnemyData& data) override;
	void Update() override;

	void SetMinionManagerPtr(MinionManager* mManager);

private:
	// データのセット
	void SetData(BaseEnemyData& data) override;
	// 当たった際の処理
	void OnCollision();

	// 吸収処理
	void UpdateAbsorbMinions();

	// データ
	NormalBossData& data_;
	// state管理クラス
	std::unique_ptr<NormalBossStateManager> stateManager_;

	// 衝突判定
	LWP::Object::Collision2D collider_;
	// 当たったかのフラグ
	bool isHit_ = false;

	MinionManager* pMinionManager_ = nullptr;
	std::vector<Minion*> absorbMinions_;

};
