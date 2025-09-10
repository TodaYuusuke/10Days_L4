#pragma once
#include <Adapter.h>

/// <summary>
/// �I��鎞�̃X�v���C�g
/// </summary>
class GameSprite
{


public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	GameSprite();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~GameSprite();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �A�N�e�B�u�؂�ւ�
	/// </summary>
	/// <param name="isActive"></param>
	void SetIsActive(bool isActive);

	/// <summary>
	/// �A�N�e�B�u�؂�ւ�
	/// </summary>
	bool GetIsActive();

	/// <summary>
	/// index�擾
	/// </summary>
	/// <param name="index">�C���f�b�N�X</param>
	void SetIndex(int index);

private:

	LWP::Primitive::SequenceSprite sprite_;

};

