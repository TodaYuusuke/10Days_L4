#pragma once

#include <unordered_map>
#include <memory>
#include "state/IMinionState.h"
#include "state/MinionStateType.h"
#include "MinionSpriteSystem.h"

/// <summary>
/// �艺�N���X
/// </summary>
class Minion final
{

public: // �����o�֐�

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Minion();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Minion();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();
	
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �f�o�b�O�pGUI
	/// </summary>
	void DebugGUI();

	/// <summary>
	/// �X�e�[�^�X�ύX
	/// </summary>
	/// <param name="newStateType">�V�������</param>
	void ChangeState(MinionStateType newStateType);

private: // �����o�ϐ�

	// �X�e�[�^�X
	std::unordered_map<MinionStateType, std::unique_ptr<IMinionState>> stateMap_;
	// ���݂̏��
	IMinionState* currentState_ = nullptr;
	// �X�e�[�g�p�^�[��
	LWP::Utility::StatePattern<MinionStateType, static_cast<size_t>(MinionStateType::StateTypeOfCount)> statePattern_;

	// �X�v���C�g�V�X�e��
	std::unique_ptr<MinionSpriteSystem> spriteSystem_;

	// �ʒu
	LWP::Math::Vector2 positon_;
	// ��] ���W�A���p
	float radian_;
	// HP
	int hp_;

};

