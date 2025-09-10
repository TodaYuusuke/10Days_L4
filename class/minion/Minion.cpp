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
    circle.radius = MinionGlobalData::GetColliderRadius();
    // 親子
    collider_.worldTF.Parent(&(spriteSystem_.GetSprite().worldTF));

    // 関数
    // ヒットした瞬間のとき
    collider_.enterLambda = [this](Collision2D* hitTarget) {
        // 敵
        if (hitTarget->mask.GetBelongFrag() == ColMaskGetter::GetEnemyAttack()) {
            if (!hitTarget->isActive) {
                return;
            }
            if (currentStateType_ != MinionStateType::Down && 
                currentStateType_ != MinionStateType::Absorb) {
                --hp_;
                requestStateType_ = MinionStateType::Down;
            }
        }
        // 壁
        else if(hitTarget->mask.GetBelongFrag() == ColMaskGetter::GetWall()){

            //if (std::holds_alternative<Collider2D::Rectangle>(hitTarget->broad)) {

            //    Collider2D::Rectangle rect = std::get<Collider2D::Rectangle>(hitTarget->broad);

            //    // 矩形中心
            //    Vector2 rectCenter = hitTarget->GetScreenPosition();
            //    // 矩形サイズ — 幅と高さ
            //    Vector2 rectSize = rect.size;
            //    // 回転角度（ラジアン）
            //    float angle = rect.rotation;
            //    //angle -= 1.57f;
            //    // 半径
            //    float radius = MinionGlobalData::GetColliderRadius();

            //    // ローカルの円
            //    Vector2 p = position_ - rectCenter;
            //    float c = std::cosf(-angle);
            //    float s = std::sinf(-angle);
            //    Vector2 localCircleCenter = { c * p.x + s * p.y, -s * p.x + c * p.y };

            //    Vector2 halfSize = rectSize * 0.5f;
            //    Vector2 localClosestPoint =
            //    {   std::clamp(localCircleCenter.x, -halfSize.x, halfSize.x),
            //        std::clamp(localCircleCenter.y, -halfSize.y, halfSize.y)
            //    };

            //    // 距離ベクトル（ローカル）
            //    Vector2 localDiff = localCircleCenter - localClosestPoint;
            //    float localDist = localDiff.Length();

            //    // 衝突チェック
            //    if (localDist < radius) {

            //        if (localDist == 0.0f) {
            //            // 完全に矩形の中心にある場合
            //            localDiff = halfSize;
            //            localDist = 1e-6;
            //        }
            //        // 押し出しベクトル（ローカル空間）
            //        Vector2 localPush = localDiff.Normalize() * (radius - localDist);

            //        // ワールド空間に戻す（回転）
            //        float cReturn = std::cosf(angle);
            //        float sReturn = std::sinf(angle);
            //        Vector2 worldPush = { cReturn * localPush.x + sReturn * localPush.y, -sReturn * localPush.x + cReturn * localPush.y };

            //        // 円の位置を押し出す
            //        position_ += worldPush;
            //    }

            //}

            position_ = prevPosition_;
            requestStateType_ = MinionStateType::Down;
        }
    };

    // マスク、所属
    collider_.mask.SetBelongFrag(ColMaskGetter::GetPlayer());
    // マスク,hit
    collider_.mask.SetHitFrag(ColMaskGetter::GetEnemyAttack() | ColMaskGetter::GetWall());

}

void Minion::Update()
{

    prevPosition_ = position_;

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
