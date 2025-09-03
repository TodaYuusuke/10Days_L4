#pragma once
#include "IMinionState.h"

/// <summary>
/// �艺�̈ړ����
/// </summary>
class MinionMoveState :
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
    /// <param name="minion">�艺�̃|�C���^</param>
    void Update(Minion* minion) override;

    /// <summary>
    /// ���̏�ԂłȂ��Ȃ鎞�̏���
    /// </summary>
    /// <param name="minion">�艺�̃|�C���^</param>
    void Exit(Minion* minion) override;

private:

    // �ړ����x
    float speed_;

    // �ړ��ꏊ

    // 

};

