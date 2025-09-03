#pragma once
#include <Adapter.h>

/// <summary>
/// ��
/// </summary>
class Wall
{

public:

	// �X�v���C�g�̑傫��
	static const LWP::Math::Vector2 kSpriteSize_;

public: // �����o�֐�

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Wall();

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="start">�J�n�n�_</param>
	/// <param name="end">�I���n�_</param>
	/// <param name="hp">�̗�</param>
	/// <param name="lifeTime">��������</param>
	Wall(const LWP::Math::Vector2& start, const LWP::Math::Vector2 end, float hp, float lifeTime);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Wall();

	/// <summary>
	/// ������
	/// </summary>
	void Initilaize();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// ���񂾂�
	/// </summary>
	/// <returns></returns>
	bool IsDead() const { return isDead_; }

private: // �����o�ϐ�

	// �J�n�n�_
	LWP::Math::Vector2 start_;
	// �I���n�_
	LWP::Math::Vector2 end_;

	// �̗�
	int hp_;
	// ��������
	float lifeTime_;
	
	// �R���C�_�[
	//LWP::Object::Collider:: lineCollider;

	// �X�v���C�g
	LWP::Primitive::NormalSprite sprite_;

	// ���񂾂�
	bool isDead_;

};

