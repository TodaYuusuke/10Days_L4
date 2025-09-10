#pragma once
#include "IEnemyState.h"
#include "../data/NormalBossData.h"

class EnemyBullet;
class NormalBossStateManager;

// 弾幕攻撃stateクラス
class RainBarrageState : public IEnemyState {
public:
	RainBarrageState() = delete;
	RainBarrageState(const BaseEnemyData* data, NormalBossStateManager* sManager, std::array<EnemyBullet, NormalBossData::kNormalBossBulletMax>* bullets);
	~RainBarrageState() = default;
	void Init(const float* moveSpeed, NormalBossStateManager* sManager, std::array<EnemyBullet, NormalBossData::kNormalBossBulletMax>* bullets) {};

	// 初期化処理
	void Enter(BaseEnemy* enemy) override;
	// 更新処理
	void Update(BaseEnemy* enemy) override;
	// 終了処理
	void Exit(BaseEnemy* enemy) override;

private:
	// 弾の発射
	void FireBullet(const Vector2& pos, const Vector2& dir);
	// 弾の座標更新
	void BulletUpdate();

	const float* pMoveSpeed_ = nullptr;
	NormalBossStateManager* pStateManager_ = nullptr;
	std::array<EnemyBullet, NormalBossData::kNormalBossBulletMax>* pBullets_;
	std::vector<LWP::Math::Vector2> bulletPositions_; // 弾の座標

	// 発射管理
	float fireCooldown_ = 0.0f;   // クールタイム残り時間
	int fireCount_ = 0;           // 発射した弾数
	LWP::Math::Vector2 dir_;
	float nowTime_ = 0.0f;
	const BarrageDefaultData* pBarrage_ = nullptr;

	std::array<Vector2, 3u> respawnPos_;
	bool isBullet_ = false; // 弾が発射

};
