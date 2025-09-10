#include "RainBarrage.h"
#include "../normalBoss/NormalBossStateManager.h"
#include "../data/NormalBossData.h"
#include "../EnemyBullet.h"
#include "../BaseEnemy.h"

RainBarrageState::RainBarrageState(const BaseEnemyData* data, NormalBossStateManager* sManager, 
	std::array<EnemyBullet, NormalBossData::kNormalBossBulletMax>* bullets) {
	const NormalBossData* d = dynamic_cast<const NormalBossData*>(data);
	pBarrage_ = &d->rainBarrage;
	pStateManager_ = sManager;
	pBullets_ = bullets;
    for (auto& a : respawnPos_) {
        a = { 0.0f,0.0f };
    }
}

void RainBarrageState::Enter(BaseEnemy* enemy) {
	// とりあえず真下に向けて撃つ
	dir_ = { 0.0f,1.0f };
	nowTime_ = 0.0f;
	fireCount_ = 0;
	fireCooldown_ = pBarrage_->fireInterval_;
	enemy->SetAttackPower(pBarrage_->attackData.attackPower);
    BulletUpdate();
}

void RainBarrageState::Update(BaseEnemy* enemy) {
    const float deltaTime = LWP::Info::GetDefaultDeltaTimeF();
    // クールタイムを減らす
    if (fireCount_ < pBarrage_->maxFireCount_) {
        fireCooldown_ -= deltaTime;

        if (fireCooldown_ <= 0.0f) {
            // 発射処理
            for (auto& a : respawnPos_) {
                FireBullet(a, dir_); // 位置と向きは適宜変更
            }
            fireCount_++;

            // クールタイムをリセット
            fireCooldown_ = pBarrage_->fireInterval_;
        }
    }
    else {
        nowTime_ += deltaTime;
    }

    // 弾の更新
    int index = 0;
    for (auto& bullet : *pBullets_) {
        if (bullet.GetIsAlive()) {
            bullet.Update(dir_ * pBarrage_->bulletSpeed_);
        }
    }

    // 攻撃の一連の動作がおわったらstateを変更
    if (pBarrage_->attackData.endingLag < nowTime_) {
        bool isAlive = false;
        for (auto& bullet : *pBullets_) {
            if (bullet.GetIsAlive()) {
                isAlive = true;
            }
        }
        if (!isAlive) {
            pStateManager_->RequestStateChange();
        }
    }
}

void RainBarrageState::Exit(BaseEnemy* enemy) {

}

void RainBarrageState::FireBullet(const Vector2& pos, const Vector2& dir) {
    for (auto& bullet : *pBullets_) {
        if (!bullet.GetIsAlive()) {
            bullet.SetBullet(pos, pBarrage_->attackData.attackRange.x);
            break;
        }
    }
}

void RainBarrageState::BulletUpdate() {
    float width = LWP::Info::GetWindowWidthF();
    width = width / 3.0f;

    respawnPos_[0].x = LWP::Utility::Random::GenerateFloat(0.0f, width);
    respawnPos_[1].x = LWP::Utility::Random::GenerateFloat(width, width * 2.0f);
    respawnPos_[2].x = LWP::Utility::Random::GenerateFloat(width * 2.0f, width * 3.0f);
}
