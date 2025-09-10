#pragma once
#include "../BaseEnemy.h"
#include <memory>
#include <array>
#include "NormalBossStateManager.h"
#include "../data/NormalBossData.h"
#include "../EnemyBullet.h"

class MinionManager;
class Minion;

class NormalBoss : public BaseEnemy {
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

private:

	// データ
	NormalBossData& data_;
	// state管理クラス
	std::unique_ptr<NormalBossStateManager> stateManager_;

	// 衝突判定
	LWP::Object::Collision2D collider_;
	// 当たったかのフラグ
	bool isHit_ = false;

	// ミニオン用
	MinionManager* pMinionManager_ = nullptr;
	std::vector<Minion*> absorbMinions_;

	// 弾のコンテナ
	std::array<EnemyBullet, NormalBossData::kNormalBossBulletMax> bullets_;

};
