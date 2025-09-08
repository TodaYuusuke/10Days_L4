#include "Minion.h"
#include "state/MinionStateFactory.h"
#include "MinionManager.h"
#include "MinionGlobalData.h"
using namespace LWP::Math;
using namespace LWP::Utility;

using namespace LWP;

// シリアルナンバー生成用
int Minion::serialNumberCount_ = 0;

Minion::Minion()
    :   stateMap_{},
        currentState_(nullptr),
        currentStateType_(MinionStateType::Idle),
        requestStateType_(MinionStateType::Idle),
        spriteSystem_(nullptr),
        position_({0.0f,0.0f}),
        direction_({ 0.0f,1.0f }),
        hp_(MinionGlobalData::GetInitialHp()),
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
        position_({ 0.0f,0.0f }),
        direction_({ 0.0f,1.0f }),
        hp_(MinionGlobalData::GetInitialHp()),
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

    ++serialNumberCount_;

    const Vector2 kBasePosition = { 960.0f, 800.0f };
    const Vector2 kRadomWidth = { 80.0f, 45.0f };
    position_ = {
        kBasePosition.x + Random::GenerateFloat(-kRadomWidth.x, kRadomWidth.x),
        kBasePosition.y + Random::GenerateFloat(-kRadomWidth.y, kRadomWidth.y) };

}

void Minion::Update()
{
    // ダウン状態ならリクエストは変わらない
    if (requestStateType_ != MinionStateType::Down) {
        // リクエスト
        Vector2 sub = (minionManager_->GetTargetPosition() - position_);
        //倍率
        const float kDistanceMagnification = static_cast<float>(minionManager_->GetAttackMinionNum()) / static_cast<float>(minionManager_->kMinionNumMax_);
        // リクエスト決定
        if (sub.Length() <= (MinionGlobalData::GetAttackStateChangesDistance() * Easing::CallFunction(Easing::Type::OutExpo, kDistanceMagnification)) + 20.0f) {
            requestStateType_ = MinionStateType::Attack;
        }
        else {
            requestStateType_ = MinionStateType::Move;
        }
    }

    // 状態 リクエストがあったら変更
    if (currentStateType_ != requestStateType_) {
        ChangeState(requestStateType_);
        currentStateType_ = requestStateType_;
    }

    if (currentState_) {
        currentState_->Update(this);
    }

    // スプライト
    spriteSystem_->Update(currentStateType_, position_, direction_);

}

void Minion::DebugGUI()
{
}

void Minion::ThrowStone()
{
    minionManager_->GetStoneManager()->CreateStone(position_, direction_);
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
