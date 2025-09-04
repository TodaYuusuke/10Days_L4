#pragma once
#include "IMinionState.h"

/// <summary>
/// 手下の攻撃状態
/// </summary>
class MinionAttackState :
    public IMinionState
{

public: // メンバ関数

    /// <summary>
    /// コンストラクタ
    /// </summary>
    MinionAttackState();

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

public:

    // やる気タイム
    float motivationTime_;

    // 石を投げるまでの時間
    float attackCoolTime_;

};

