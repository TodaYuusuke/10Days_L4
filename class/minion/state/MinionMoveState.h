#pragma once
#include "IMinionState.h"

/// <summary>
/// 手下の移動状態
/// </summary>
class MinionMoveState :
    public IMinionState
{

public: // メンバ関数

    
    /// <summary>
    /// コンストラクタ
    /// </summary>
    MinionMoveState();

    /// <summary>
    /// この状態になる時の処理
    /// </summary>
    /// <param name="minion">手下のポインタ</param>
    void Enter(Minion* minion) override;

    /// <summary>
    /// 更新処理
    /// </summary>
    /// <param name="minion">手下のポインタ</param>
    void Update(Minion* minion) override;

    /// <summary>
    /// この状態でなくなる時の処理
    /// </summary>
    /// <param name="minion">手下のポインタ</param>
    void Exit(Minion* minion) override;

private:

    // 移動速度
    float speed_;

};

