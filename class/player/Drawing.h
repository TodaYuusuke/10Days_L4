#pragma once
#include <vector>
#include <Adapter.h>

/// <summary>
/// �����r��
/// </summary>
class Drawing
{

public: // �����o�֐�

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Drawing(); 

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Drawing();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="isDragging">�h���b�O����</param>
	void Update(bool isDragging);

private: // �����o�ϐ�

	// �_
	std::vector<LWP::Math::Vector2> points_;

	// �����Ă�
	bool isActive_;

	// �L�^�^�C�~���O�^�C�}�[
	float recordingTimer_;

};

