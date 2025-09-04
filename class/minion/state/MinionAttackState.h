#pragma once
#include "IMinionState.h"
class MinionAttackState :
    public IMinionState
{

public: // �����o�֐�

    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    MinionAttackState();

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

public:

    // ���C�^�C��
    float motivationTime_;

    // �΂𓊂���܂ł̎���
    float attackCoolTime_;

};

