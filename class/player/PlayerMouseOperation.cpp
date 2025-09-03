#include "PlayerMouseOperation.h"

using namespace LWP::Input;
using namespace LWP::Math;


PlayerMouseOperation::PlayerMouseOperation()
	:	pressedPosition_({0.0f,0.0f}), 
		isDragging_(false), 
		clicked_(false)
{
}

PlayerMouseOperation::~PlayerMouseOperation()
{
}

void PlayerMouseOperation::Initialize()
{
}

void PlayerMouseOperation::Update()
{

	clicked_ = false;

	if (Mouse::GetTrigger(0)) {
		LeftButtonPressed();
	}
	else if(Mouse::GetPress(0)){
		LeftButtonHeldDown();
	}
	else if (Mouse::GetRelease(0)){
		LeftButtonReleased();
	}

}

void PlayerMouseOperation::LeftButtonPressed()
{

	// �����ꂽ�ʒu��ۑ�
	pressedPosition_ = Mouse::GetPosition();

}

void PlayerMouseOperation::LeftButtonHeldDown()
{

	// �h���b�O����Ȃ�
	if (!isDragging_) {
		// �}�E�X�������Ă��Ȃ��m�F
		const Vector2 kNowPosition = Mouse::GetPosition();
		// �������Ƃ��Ƃ̋������m�F
		const float kDistance = (kNowPosition - pressedPosition_).Length();
		// �h���b�O�F�苗��
		const float DragCertifiedDistance = 5.0f;

		if (DragCertifiedDistance < kDistance) {
			//�h���b�O�J�n
			isDragging_ = true;
		}

	}

}

void PlayerMouseOperation::LeftButtonReleased()
{

	// �h���b�O�ł͂Ȃ�
	if (!isDragging_) {
		// �N���b�N���ꂽ
		clicked_ = true;
	}
	else {
		// �h���b�O�I��
		isDragging_ = false;
	}

}
