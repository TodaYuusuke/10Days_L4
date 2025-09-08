#include "NormalBoss.h"
#include "NormalBossStateFactory.h"
#include "NormalBossSpriteSystem.h"

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
    stateMap_ = StateFactory::NormalBoss::CreateStates(&data_, stateManager_.get());
    StateUpdate();

    spriteSystem_ = std::make_unique<NormalBossSpriteSystem>();

    corePosition_ = data_.respawnPoint;

    collider_.mask.SetHitFrag(ColMask0);
    collider_.mask.SetBelongFrag(ColMask0);

    // 衝突時
    collider_.stayLambda = [this](LWP::Object::Collision2D* hit) {
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

    collider_.worldTF.translation = { corePosition_.x,corePosition_.y,0.0f };
    
    if (isHit_) {
        OnCollision();
    }

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
    NormalBossSpriteSystem& handle = dynamic_cast<NormalBossSpriteSystem&>(*spriteSystem_);
    handle.ColorUpdate();
    isHit_ = false;
}
