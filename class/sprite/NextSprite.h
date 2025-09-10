#pragma once
#include <Adapter.h>

/// <summary>
/// ���֍s�����߂̃X�v���C�g
/// </summary>
class NextSprite
{

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	NextSprite();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~NextSprite();

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

private:
	
	LWP::Primitive::NormalSprite sprite_;

	LWP::Math::Vector2 basePosition_;

	float addValue_;

};

