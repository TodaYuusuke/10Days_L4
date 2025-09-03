#pragma once
#include <Adapter.h>

/// <summary>
/// �W���ꏊ
/// </summary>
class MeetingPlace
{

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	MeetingPlace();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~MeetingPlace();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

public: // �A�N�Z�b�T

	void SetPosition(const LWP::Math::Vector2& position) { position_ = position; }
	LWP::Math::Vector2 GetPosition() const { return position_; }

private:

	// �X�v���C�g
	LWP::Primitive::SequenceSprite sprite_;

	// �A�Ԃ�indexX
	int indexX_;

	// index�ύX�܂ł̃t���[���J�E���g
	int changeIndexFrameCount_;

	// �ʒu
	LWP::Math::Vector2 position_;

};

