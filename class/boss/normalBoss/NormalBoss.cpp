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
    stateMap_ = StateFactory::NormalBoss::CreateStates();
    StateUpdate();
    spriteSystem_ = std::make_unique<NormalBossSpriteSystem>();
}

void NormalBoss::Update() {
    requestStateType_ = static_cast<uint8_t>(NormalBossStateType::Idel);
    // 状態変化更新
    if (StateUpdate()) {
        // 切り替わりがあった場合
        // アニメーション等のリクエストを走らせる
    }

    spriteSystem_->Update(LWP::Math::Vector2(1280.0f, 720.0f));
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
