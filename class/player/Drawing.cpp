#include "Drawing.h"

using namespace LWP::Input;
using namespace LWP::Info;

Drawing::Drawing()
	:	points_{},
		isActive_(false),
		recordingTimer_(0.0f)
{
	Initialize();
}

Drawing::~Drawing()
{
}

void Drawing::Initialize()
{
}

void Drawing::Update(bool isDragging)
{

	// �h���b�O���Ă��Ȃ�
	if (!isDragging) {
		// �A�N�e�B�u�Ȃ�~�߂�
		if (isActive_) {

			// �~���ǂ���
			// �ǂ����

			// ��A�N�e�B�u
			isActive_ = false;
			points_.clear();

		}
		
	}
	// �h���b�O���Ă���
	else {
		// ���������r��
		if (isActive_) {
			recordingTimer_ += LWP::Info::GetDeltaTime();
			// ���R�[�f�B���O����
			const float kRecordingTime = 0.5f;
			if (recordingTimer_ > kRecordingTime) {
				// �L�^
				recordingTimer_ -= kRecordingTime;
				points_.push_back(Mouse::GetPosition());
			}
		}
		// ���ꂩ���������
		else {
			// ���݂̈ʒu��ۑ�
			points_.push_back(Mouse::GetPosition());
			// �A�N�e�B�u
			isActive_ = true;
		}
	}

}
