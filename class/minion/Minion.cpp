#include "Minion.h"
#include "state/MinionStateFactory.h"
#include "MinionManager.h"
#include "MinionGlobalData.h"
#include "../ColMaskGetter.h"
using namespace LWP::Math;
using namespace LWP::Utility;
using namespace LWP::Object;

using namespace LWP;

// シリアルナンバー生成用
int Minion::serialNumberCount_ = 0;

Minion::Minion()
    :   stateMap_{},
        currentState_(nullptr),
        currentStateType_(MinionStateType::Idle),
        requestStateType_(MinionStateType::Move),
        spriteSystem_(),
        position_({0.0f,0.0f}),
        direction_({ 0.0f,1.0f }),
        hp_(MinionGlobalData::GetInitialHp()),
        serialNumber_(serialNumberCount_),
        motivationTime_(0.0f),
        collider_(),
        minionManager_(nullptr)
{
}

Minion::Minion(MinionManager* minionManager)
    :   stateMap_{},
        currentState_(nullptr),
        currentStateType_(MinionStateType::Idle),
        requestStateType_(MinionStateType::Move),
        spriteSystem_(),
        position_({ 0.0f,0.0f }),
        direction_({ 0.0f,1.0f }),
        hp_(MinionGlobalData::GetInitialHp()),
        serialNumber_(serialNumberCount_),
        motivationTime_(0.0f),
        collider_(),
        minionManager_(minionManager)
{
}

Minion::~Minion()
{
}

void Minion::Initialize()
{

    // ステータス
    stateMap_ = MinionStateFactory::CreateStates();
    ChangeState(requestStateType_);

    serialNumber_ = serialNumberCount_;
    ++serialNumberCount_;

    const Vector2 kBasePosition = MinionGlobalData::GetInitialPosition();
    const Vector2 kRadomWidth = MinionGlobalData::GetInitialPositionWidth();
    position_ = {
        kBasePosition.x + Random::GenerateFloat(-kRadomWidth.x, kRadomWidth.x),
        kBasePosition.y + Random::GenerateFloat(-kRadomWidth.y, kRadomWidth.y) };

    spriteSystem_.Initialize();
    spriteSystem_.ColorChange(serialNumber_);

    // サークル
    Collider2D::Circle& circle = collider_.SetBroadShape<Collider2D::Circle>();
    circle.radius = 30.0f;
    // 親子
    collider_.worldTF.Parent(&(spriteSystem_.GetSprite().worldTF));

    // 関数
    // ヒットした瞬間のとき
    collider_.enterLambda = [this](Collision2D* hitTarget) {
        // 敵
        if (hitTarget->mask.GetBelongFrag() == ColMaskGetter::GetEnemy()) {
            if (currentStateType_ != MinionStateType::Down && 
                currentStateType_ != MinionStateType::Absorb) {
                --hp_;
                requestStateType_ = MinionStateType::Down;
            }
        }
        // 壁
        else if(hitTarget->mask.GetBelongFrag() == ColMaskGetter::GetWall()){
            hitTarget->GetScreenPosition();


            }
        };

    // マスク、所属
    collider_.mask.SetBelongFrag(ColMaskGetter::GetPlayer());
    // マスク,hit
    collider_.mask.SetHitFrag(ColMaskGetter::GetEnemy() | ColMaskGetter::GetWall());

}

void Minion::Update()
{

    // 状態 リクエストがあったら変更
    if (currentStateType_ != requestStateType_) {
        ChangeState(requestStateType_);
        currentStateType_ = requestStateType_;
    }

    if (currentState_) {
        currentState_->Update(this);
    }

    // スプライト
    spriteSystem_.Update(currentStateType_, position_, direction_);

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
