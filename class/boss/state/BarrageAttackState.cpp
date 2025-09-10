#include "BarrageAttackState.h"
#include "../normalBoss/NormalBossStateManager.h"
#include "../data/NormalBossData.h"
#include "../EnemyBullet.h"
#include "../BaseEnemy.h"

BarrageAttackState::BarrageAttackState(const BaseEnemyData* data, NormalBossStateManager* sManager, std::array<EnemyBullet, NormalBossData::kNormalBossBulletMax>* bullets) {
    const NormalBossData* d = dynamic_cast<const NormalBossData*>(data);
    pBarrage_ = &d->straightBarrage;
	pStateManager_ = sManager;
	pBullets_ = bullets;
}

void BarrageAttackState::Enter(BaseEnemy* enemy) {
    // とりあえず真下に向けて撃つ
    dir_ = { 0.0f,1.0f };
    nowTime_ = 0.0f;
    fireCount_ = 0;
    fireCooldown_ = pBarrage_->fireInterval_;
    enemy->SetAttackPower(pBarrage_->attackData.attackPower);
}

void BarrageAttackState::Update(BaseEnemy* enemy) {
    const float deltaTime = LWP::Info::GetDefaultDeltaTimeF();
    // クールタイムを減らす
    if (fireCount_ < pBarrage_->maxFireCount_) {
        fireCooldown_ -= deltaTime;

        if (fireCooldown_ <= 0.0f) {
            // 発射処理
            FireBullet(enemy->corePosition_, dir_); // 位置と向きは適宜変更
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

void BarrageAttackState::Exit(BaseEnemy* enemy) {

}

void BarrageAttackState::FireBullet(const Vector2& pos, const Vector2& dir) {
    for (auto& bullet : *pBullets_) {
        if (!bullet.GetIsAlive()) {
            bullet.SetBullet(pos, pBarrage_->attackData.attackRange.x);
            break;
        }
    }
}

void BarrageAttackState::BulletUpdate() {

}
