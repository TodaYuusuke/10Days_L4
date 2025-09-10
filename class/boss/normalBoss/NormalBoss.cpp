#include "NormalBoss.h"
#include "NormalBossStateFactory.h"
#include "NormalBossSpriteSystem.h"
#include "../../ColMaskGetter.h"
#include "../../minion/MinionManager.h"

// data_に関してはとりあえずの初期化 のちに再設定している
NormalBoss::NormalBoss(BaseEnemyData& data) : data_(dynamic_cast<NormalBossData&>(data)) {
    Initialize(data);
}

void NormalBoss::Initialize(BaseEnemyData& data) {
    name_ = "NormalBoss";
    SetData(data);

    // stateの初期化
    requestStateType_ = static_cast<uint8_t>(NormalBossStateType::Idle);
    stateManager_ = std::make_unique<NormalBossStateManager>();
    
    stateMap_ = StateFactory::NormalBoss::CreateStates(&data_, stateManager_.get(), &bullets_, pMinionManager_);
    StateUpdate();

    spriteSystem_ = std::make_unique<NormalBossSpriteSystem>();

    // データの代入
    corePosition_ = data_.respawnPoint;
    hp_ = data_.hp_;
    maxHp_ = data_.hp_;

    isAlive_ = true;

    collider_.mask.SetBelongFrag(ColMaskGetter::GetEnemy());
    collider_.mask.SetHitFrag(ColMaskGetter::GetBullet());
    
    // 衝突時
    collider_.enterLambda = [this](LWP::Object::Collision2D* hit) {
        isHit_ = true;
        };

}

void NormalBoss::Update() {
    // debug
    ImGui::Begin("Enemy");
    collider_.DebugGUI();
    ImGui::End();

    // 状態変化更新
    if (StateUpdate()) {
        // 切り替わりがあった場合
        // アニメーション等のリクエストを走らせる
    }
    // リクエストがあれば次の状態を決める
    requestStateType_ = stateManager_->Update(currentStateType_);
    // 描画用更新
    spriteSystem_->Update(corePosition_);

    // collision座標の更新 SetFollowに切り替えた方がいいけど作り的にめんどい
    collider_.worldTF.translation = { corePosition_.x,corePosition_.y,0.0f };

    // 衝突時の処理
    if (isHit_) {
        OnCollision();
    }

}

void NormalBoss::SetMinionManagerPtr(MinionManager* mManager) {
    pMinionManager_ = mManager;
}

void NormalBoss::SetData(BaseEnemyData& data) {
    // タイプを確認
    data.CheckType(BaseEnemyData::Type::NormalBoss);
    // Dataを代入
    try {
        data_ = dynamic_cast<NormalBossData&>(data);
    }
    catch (const std::bad_cast& e) {
        // castエラー
        throw std::runtime_error(e.what());
    }
}

void NormalBoss::OnCollision() {
    // とりあえず色を赤くしている
    NormalBossSpriteSystem& handle = dynamic_cast<NormalBossSpriteSystem&>(*spriteSystem_);
    handle.ColorUpdate();
    isHit_ = false;
    // ダメージ
    hp_--;
    if (hp_ <= 0u) {
        isAlive_ = false;
    }
}

void NormalBoss::UpdateAbsorbMinions() {
    // 給される状態に切り替わったタイミングが取れないので、毎回空に
    absorbMinions_.clear();
    
    if (pMinionManager_) {
        for (auto& minion : pMinionManager_->GetMinions()) {
            // もし、吸収される状態なら
            if (minion.GetCurrentStateType() == MinionStateType::Absorb) {
                // コンテナに追加
                absorbMinions_.push_back(&minion);
            }
        }
    }
    // 画面外に座標を固定
    for (auto minion : absorbMinions_) {
        minion->SetPosition({ -100.0f,-100.0f });
    }
}
