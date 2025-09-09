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
}

PlayerMouseOperation::~PlayerMouseOperation()
{
}

void PlayerMouseOperation::Initialize()
{

	// マウスカーソルを消す
	ShowCursor(false);

#ifdef _DEBUG
	ShowCursor(true);
#endif // _DEBUG

	sprite_.LoadTexture("Pen.png");
	sprite_.anchorPoint = { 0.0f,1.0f }; 
	sprite_.worldTF.scale = PlayerGlobalData::GetMouseSpriteScale();

}

void PlayerMouseOperation::Update()
{

	clicked_ = false;

	const bool kIsTrigger = (Mouse::GetTrigger(0) && !Keyboard::GetPress(DIK_SPACE)) || (Keyboard::GetTrigger(DIK_SPACE) && !Mouse::GetPress(0));
	const bool kIsPress = (Mouse::GetPress(0) || Keyboard::GetPress(DIK_SPACE));
	const bool kIsRelease = (Mouse::GetRelease(0) && !Keyboard::GetPress(DIK_SPACE)) || (Keyboard::GetRelease(DIK_SPACE) && !Mouse::GetPress(0));

	if (kIsTrigger) {
		LeftButtonPressed();
	}
	else if(kIsPress){
		LeftButtonHeldDown();
	}
	else if (kIsRelease){
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
