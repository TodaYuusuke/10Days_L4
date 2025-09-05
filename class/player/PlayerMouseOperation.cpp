#include "PlayerMouseOperation.h"
#include "PlayerGlobalData.h"

using namespace LWP::Input;
using namespace LWP::Math;


PlayerMouseOperation::PlayerMouseOperation()
	:	pressedPosition_({0.0f,0.0f}), 
		isDragging_(false), 
		clicked_(false),
		sprite_()
{
	Initialize();
}

PlayerMouseOperation::~PlayerMouseOperation()
{
}

void PlayerMouseOperation::Initialize()
{

	// マウスカーソルを消す
	ShowCursor(false);

	sprite_.LoadTexture("Pen.png");
	sprite_.anchorPoint = { 0.0f,1.0f };

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

	const Vector2 kNowPosition = Mouse::GetPosition();
	// 先頭
	sprite_.worldTF.translation = { kNowPosition.x, kNowPosition.y, -1000.0f };

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
		if (PlayerGlobalData::GetDragCertifiedDistance() < kDistance) {
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
