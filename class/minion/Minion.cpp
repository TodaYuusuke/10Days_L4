#include "Minion.h"
#include "state/MinionStateFactory.h"

using namespace LWP;

// シリアルナンバー生成用
int Minion::serialNumberCount_ = 0;

Minion::Minion()
    :   stateMap_{},
        currentState_(nullptr),
        currentStateType_(MinionStateType::Idle),
        requestStateType_(MinionStateType::Idle),
        spriteSystem_(nullptr),
        positon_({0.0f,0.0f}),
        direction_({ 0.0f,1.0f }),
        hp_(0),
        serialNumber_(serialNumberCount_),
        minionManager_(nullptr)
{
    Initialize();
}

Minion::Minion(MinionManager* minionManager)
    :   stateMap_{},
        currentState_(nullptr),
        currentStateType_(MinionStateType::Idle),
        requestStateType_(MinionStateType::Idle),
        spriteSystem_(nullptr),
        positon_({ 0.0f,0.0f }),
        direction_({ 0.0f,1.0f }),
        hp_(0),
        serialNumber_(serialNumberCount_),
        minionManager_(minionManager)
{
    Initialize();
}

Minion::~Minion()
{
}

void Minion::Initialize()
{

    // ステータス
    stateMap_ = MinionStateFactory::CreateStates();
    ChangeState(requestStateType_);

    spriteSystem_ = std::make_unique<MinionSpriteSystem>();

    positon_ = { 660.0f,660.0f };

    ++serialNumberCount_;

}

void Minion::Update()
{

    // 状態 リクエストがあったら変更
    if (currentStateType_ != requestStateType_) {
        ChangeState(requestStateType_);
    }

    if (currentState_) {
        currentState_->Update(this);
    }

    // スプライト
    spriteSystem_->Update(MinionStateType::Move, positon_, direction_);

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
