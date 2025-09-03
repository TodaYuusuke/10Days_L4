#include "MinionSpriteSystem.h"

using namespace LWP::Math;

MinionSpriteSystem::MinionSpriteSystem()
	:	sprite_(),
		indexX_(0),
		preType_(MinionStateType::Idle),
		changeIndexFrameCount_(0)
{

	Initialize();

}

MinionSpriteSystem::~MinionSpriteSystem()
{
}

void MinionSpriteSystem::Initialize()
{

	// �e�N�X�`���̖��O
	const std::string kTextureName = "L4_10Days_Demo.png";
	sprite_.LoadTexture(kTextureName);
	// �e�N�X�`���T�C�Y
	const Vector2& kSize = { 64.0f, 64.0f };
	sprite_.SetSplitSize(kSize);

}

void MinionSpriteSystem::Update(MinionStateType type, const LWP::Math::Vector2& position)
{

	// indexX�̍ő�l
	const int kIndexMaxX = 6;
	// �A�Ԃ̐؂�ւ��t���[����
	const int kChangeIndexFrame = 20;
	
	// �O�̏�Ԃ̂܂܂Ȃ�
	if (preType_ == type) {
		// �t���[���J�E���g�_�E��
		--changeIndexFrameCount_;
		if (0 >= changeIndexFrameCount_) {
			// x���ړ������鏈��
			indexX_ = (++indexX_) % kIndexMaxX;
			// �t���[���J�E���g��߂�
			changeIndexFrameCount_ = kChangeIndexFrame;
		}
	}
	else {
		// x�����������鏈��
		indexX_ = 0;
		// �t���[���J�E���g��߂�
		changeIndexFrameCount_ = kChangeIndexFrame;
	}

	// ���݂̃^�C�v����y��index������
	const int kIndexY = static_cast<int>(type);
	// ���݂�index�̊m��
	sprite_.index = kIndexY * kIndexMaxX + indexX_;

	// Z���W�i�`�揇�j
	const float kPositionZ = 0.0f;
	// �ʒu�̈ړ�
	sprite_.worldTF.translation = { position.x, position.y, kPositionZ };

}
