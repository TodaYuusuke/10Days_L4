#include "CircleBarrageState.h"
#include "../normalBoss/NormalBossStateManager.h"
#include "../data/NormalBossData.h"
#include "../EnemyBullet.h"
#include "../BaseEnemy.h"
#include "../../areaOffEffect/AreaOffEffectManager.h"
#include <numbers>

CircleBarrageState::CircleBarrageState(const BaseEnemyData* data, NormalBossStateManager* sManager, std::array<EnemyBullet, NormalBossData::kNormalBossBulletMax>* bullets) {
	const NormalBossData* d = dynamic_cast<const NormalBossData*>(data);
	pBarrage_ = &d->rainBarrage;
	pStateManager_ = sManager;
	pBullets_ = bullets;
}

void CircleBarrageState::Enter(BaseEnemy* enemy) {
    dirs_.resize(NormalBossData::kBulletDivisionCount);
    nowTime_ = 0.0f;
    fireCount_ = 0;
    fireCooldown_ = pBarrage_->fireInterval_;
    enemy->SetAttackPower(pBarrage_->attackData.attackPower);
    BulletUpdate();
    //AreaOffEffectManager::RequestCreate(pos, pBarrage_->attackData.attackRange, pBarrage_->attackData);
    isBullet_ = false;
}

void CircleBarrageState::Update(BaseEnemy* enemy) {
    const float kDeltaTime = LWP::Info::GetDefaultDeltaTimeF();
    const float totalTime = pBarrage_->attackData.startupLag + pBarrage_->attackData.damageTime + pBarrage_->attackData.endingLag;

    // 時間の加算
    nowTime_ += kDeltaTime;
    // ダメージが入る時間ならば
    if (pBarrage_->attackData.startupLag < nowTime_) {
        isBullet_ = true;
    }

    // クールタイムを減らす
    if (fireCount_ < pBarrage_->maxFireCount_ && isBullet_) {
        fireCooldown_ -= kDeltaTime;
        if (fireCooldown_ <= 0.0f) {
            // 発射処理
            FireBullet(enemy->corePosition_); // 位置と向きは適宜変更
            fireCount_++;
            // クールタイムをリセット
            fireCooldown_ = pBarrage_->fireInterval_;
        }
    }

    // 弾の更新
    uint8_t index = 0u;
    for (auto& bullet : *pBullets_) {
        if (bullet.GetIsAlive()) {
            bullet.Update(LWP::Math::Vector2());
        }
        if (index >= NormalBossData::kBulletDivisionCount) {
            index = 0u;
        }
    }

    // 攻撃の一連の動作がおわったらstateを変更
    if (totalTime < nowTime_) {
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

void CircleBarrageState::Exit(BaseEnemy* enemy) {

}

void CircleBarrageState::FireBullet(const Vector2& pos) {
    for (auto& bullet : *pBullets_) {
        if (!bullet.GetIsAlive()) {
            bullet.SetBullet(pos, pBarrage_->attackData.attackRange.x,dirs_[divisionCount_++] * pBarrage_->bulletSpeed_);
            if (divisionCount_ >= NormalBossData::kBulletDivisionCount) { divisionCount_ = 0u; }
            break;
        }
    }
}

void CircleBarrageState::BulletUpdate() {
    for (uint8_t i = 0; i < NormalBossData::kBulletDivisionCount; i++) {
        float angle = (2.0f * std::numbers::pi_v<float> / static_cast<float>(NormalBossData::kBulletDivisionCount)) * (float)i;
        Quaternion rot = Quaternion::CreateFromAxisAngle(Vector3(0.0f, 0.0f, 1.0f), angle);

        Vector3 dir = Vector3(1.0f, 0.0f, 0.0f) * rot; // X軸基準
        dir = dir.Normalize();
        dirs_[i] = { dir.x,dir.y };
    }

}
