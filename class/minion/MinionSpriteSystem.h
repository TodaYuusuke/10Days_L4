#pragma once
#include <Adapter.h>
#include "state/MinionStateType.h"

/// <summary>
/// �艺�̃X�v���C�g�@�\
/// </summary>
class MinionSpriteSystem
{

public:  // �����o�֐�

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	MinionSpriteSystem();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~MinionSpriteSystem();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="type">���</param>
	/// <param name="position">�ʒu</param>
	void Update(MinionStateType type, const LWP::Math::Vector2& position);

private: // �����o�ϐ�

	// �X�v���C�g
	LWP::Primitive::SequenceSprite sprite_;

	// �A�Ԃ�indexX
	int indexX_;

	// �O�̏��
	MinionStateType preType_;

	// index�ύX�܂ł̃t���[���J�E���g
	int changeIndexFrameCount_;

};

