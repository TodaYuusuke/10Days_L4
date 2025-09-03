#pragma once
#include <Adapter.h>

/// <summary>
/// �v���C���[�̃}�E�X����
/// </summary>
class PlayerMouseOperation
{

public: // �����o�֐�

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	PlayerMouseOperation();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~PlayerMouseOperation();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

private:

	/// <summary>
	/// �����ꂽ
	/// </summary>
	void LeftButtonPressed();

	/// <summary>
	/// �����ꑱ���Ă���
	/// </summary>
	void LeftButtonHeldDown();

	/// <summary>
	/// �����ꂽ
	/// </summary>
	void LeftButtonReleased();

public: // �A�N�Z�b�T

	bool GetIsDragging() const { return isDragging_; }
	bool GetClicked() const { return clicked_; }

private:

	// �����ꂽ�ʒu
	LWP::Math::Vector2 pressedPosition_;

	// �h���b�O��Ԃ�
	bool isDragging_;

	// �N���b�N���ꂽ
	bool clicked_;


};

