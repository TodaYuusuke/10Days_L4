#pragma once
#include "IMinionState.h"

/// <summary>
/// 泡ステート
/// </summary>
class MinionFoamState :
    public IMinionState
{

public: // メンバ関数

    /// <summary>
    /// この状態になる時の処理
    /// </summary>
    /// <param name="minion">手下のポインタ</param>
    void Enter(Minion* minion) override;

    /// <summary>
    /// 更新処理
    /// </summary>
    /// <param name="minion"></param>
    void Update(Minion* minion) override;

    /// <summary>
    /// この状態でなくなる時の処理
    /// </summary>
    /// <param name="minion"></param>
    void Exit(Minion* minion) override;

};

