#pragma once
#include <Adapter.h>

// �O���錾
class Minion;

/// <summary>
/// �艺�̏�ԃC���^�[�t�F�[�X
/// </summary>
class IMinionState
{

public: // �����o�֐�

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~IMinionState() = default;

	/// <summary>
	/// ���̏�ԂɂȂ鎞�̏���
	/// </summary>
	/// <param name="minion">�艺�̃|�C���^</param>
	virtual void Enter(Minion* minion) = 0;

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="minion"></param>
	virtual void Update(Minion* minion) = 0;

	/// <summary>
	/// ���̏�ԂłȂ��Ȃ鎞�̏���
	/// </summary>
	/// <param name="minion"></param>
	virtual void Exit(Minion* minion) = 0;

};


/// <summary>
/// IMinionState���p�������N���X�݂̂�I���ł���e���v���[�g
/// </summary>
template<class MinionStateT>
concept IsIMinionState = std::is_base_of<IMinionState, MinionStateT>::value;