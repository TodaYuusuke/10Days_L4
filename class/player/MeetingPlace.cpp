#include "MeetingPlace.h"
using namespace LWP::Math;

MeetingPlace::MeetingPlace()
	:	sprite_(),
		indexX_(0),
		changeIndexFrameCount_(0),
		position_({ 0.0f,0.0f })
{
	Initialize();
}

MeetingPlace::~MeetingPlace()
{
}

void MeetingPlace::Initialize()
{

	// �e�N�X�`���̖��O
	const std::string kTextureName = "MeetingPlace.png";
	sprite_.LoadTexture(kTextureName);
	// �e�N�X�`���T�C�Y
	const Vector2& kSize = { 64.0f, 64.0f };
	sprite_.SetSplitSize(kSize);

}

void MeetingPlace::Update()
{

	// indexX�̍ő�l
	const int kIndexMaxX = 6;
	// �A�Ԃ̐؂�ւ��t���[����
	const int kChangeIndexFrame = 4;

	// �t���[���J�E���g�_�E��
	--changeIndexFrameCount_;
	if (0 >= changeIndexFrameCount_) {
		// x���ړ������鏈��
		indexX_ = (++indexX_) % kIndexMaxX;
		// �t���[���J�E���g��߂�
		changeIndexFrameCount_ = kChangeIndexFrame;
	}

	// ���݂�index�̊m��
	sprite_.index = indexX_;

	// Z���W�i�`�揇�j
	const float kPositionZ = 0.0f;
	// �ʒu�̈ړ�
	sprite_.worldTF.translation = { position_.x, position_.y, kPositionZ };

}
