#pragma once
#include "IMinionState.h"

/// <summary>
/// �~�j�I���̑ҋ@���
/// </summary>
class MinionIdleState :
    public IMinionState
{

public: // �����o�֐�
    
    /// <summary>
    /// ���̏�ԂɂȂ鎞�̏���
    /// </summary>
    /// <param name="minion">�艺�̃|�C���^</param>
    void Enter(Minion* minion) override;

    /// <summary>
    /// �X�V����
    /// </summary>
    /// <param name="minion"></param>
    void Update(Minion* minion) override;

    /// <summary>
    /// ���̏�ԂłȂ��Ȃ鎞�̏���
    /// </summary>
    /// <param name="minion"></param>
    void Exit(Minion* minion) override;

};

