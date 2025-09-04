#include "BaseEnemy.h"
#include <limits>
#undef max

BaseEnemy::BaseEnemy()
    : currentStateType_(std::numeric_limits<uint8_t>::max()),
    requestStateType_(0u)
{
    
}

bool BaseEnemy::StateUpdate() {
    bool isChangeState = false;
    // 状態 リクエストがあったら変更
    if (currentStateType_ != requestStateType_) {
        ChangeState(requestStateType_);
        currentStateType_ = requestStateType_;
        isChangeState = true;
    }
    // 更新
    if (currentState_) {
        currentState_->Update(this);
    }
    return isChangeState;
}

void BaseEnemy::ChangeState(const uint8_t& newStateTypeNumber) {
    // 前のステートがあればExit処理
    if (currentState_) {
        currentState_->Exit(this);
    }

    // 次のステートを見つける
    auto it = stateMap_.find(newStateTypeNumber);

    // 次のステートにしてEnter処理
    if (it != stateMap_.end()) {
        currentState_ = it->second.get();
        currentState_->Enter(this);
    }
}
