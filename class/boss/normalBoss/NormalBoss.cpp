#include "NormalBoss.h"
#include "NormalBossStateFactory.h"
#include "NormalBossSpriteSystem.h"

NormalBoss::NormalBoss() {
    Initialize();
}

void NormalBoss::Initialize() {
    name_ = "NormalBoss";
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
