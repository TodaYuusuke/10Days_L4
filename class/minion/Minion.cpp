#include "Minion.h"
#include "state/MinionStateFactory.h"

using namespace LWP;

Minion::Minion()
    :   stateMap_{},
        currentState_(nullptr),
        statePattern_(),
        spriteSystem_(nullptr)
{
}

Minion::~Minion()
{
}

void Minion::Initialize()
{

    // ステータス
    stateMap_ = MinionStateFactory::CreateStates();
    ChangeState(MinionStateType::Idle);
    statePattern_.Init();

    spriteSystem_ = std::make_unique<MinionSpriteSystem>();

}

void Minion::Update()
{

    // ステータス
    statePattern_.Update();
    if (currentState_) {
        currentState_->Update(this);
    }

    // スプライト
    spriteSystem_->Update(statePattern_.GetCurrentBehavior(), {640.0f, 360.0f});

}

void Minion::DebugGUI()
{
}

void Minion::ChangeState(MinionStateType newStateType)
{

    // 前のステートがあればExit処理
    if (currentState_) {
        currentState_->Exit(this);
    }

    // 次のステートを見つける
    auto it = stateMap_.find(newStateType);

    // 次のステートにしてEnter処理
    if (it != stateMap_.end()) {
        currentState_ = it->second.get();
        currentState_->Enter(this);
    }

}
