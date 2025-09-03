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

	// 押された位置を保存
	pressedPosition_ = Mouse::GetPosition();

}

void PlayerMouseOperation::LeftButtonHeldDown()
{

	// ドラッグじゃない
	if (!isDragging_) {
		// マウスが動いていない確認
		const Vector2 kNowPosition = Mouse::GetPosition();
		// 推したときとの距離を確認
		const float kDistance = (kNowPosition - pressedPosition_).Length();
		// ドラッグ認定距離
		const float DragCertifiedDistance = 5.0f;

		if (DragCertifiedDistance < kDistance) {
			//ドラッグ開始
			isDragging_ = true;
		}

	}

}

void PlayerMouseOperation::LeftButtonReleased()
{

	// ドラッグではない
	if (!isDragging_) {
		// クリックされた
		clicked_ = true;
	}
	else {
		// ドラッグ終了
		isDragging_ = false;
	}

}
