#include "Drawing.h"
using namespace LWP::Math;
using namespace LWP::Input;
using namespace LWP::Info;
using namespace LWP::Utility;

// スプライトの大きさ
const Vector2 Drawing::kSpriteSize_ = {100.0f, 100.0f};

Drawing::Drawing()
	:	points_{},
		sprites_{},
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

	for (size_t i = 0; i < kSpriteNum_; ++i) {
		sprites_[i].LoadTexture("Line.png");
		sprites_[i].worldTF.scale.x = 0.1f;
		sprites_[i].isActive = false;
	}

}

void Drawing::Update(bool isDragging)
{

	// ドラッグしていない
	if (!isDragging) {
		// アクティブなら止める
		if (isActive_) {

			// 円かどうか
			// 壁を作る

			// 非アクティブ
			isActive_ = false;
			points_.clear();
			sprieIndex_ = 0;
			for (size_t i = 0; i < kSpriteNum_; ++i) {
				sprites_[i].isActive = false;
			}

		}
		
	}
	// ドラッグしている
	else {
		// 線を書き途中
		if (isActive_) {
			recordingTimer_ += LWP::Info::GetDeltaTime();
			// レコーディング時間
			const float kRecordingTime = 0.01f;
			if (recordingTimer_ > kRecordingTime) {
				// 記録
				recordingTimer_ -= kRecordingTime;
				const Vector2 mousePosition = Mouse::GetPosition();
				const Vector2 preMousePosition = points_[points_.size() - 1];

				// スプライト
				// 位置
				const Vector2 spritePosition = (mousePosition + preMousePosition) / 2.0f;
				// Z座標（描画順）
				const float kPositionZ = 0.0f;
				sprites_[sprieIndex_].worldTF.translation = { spritePosition.x, spritePosition .y, kPositionZ };
				// 回転
				const Vector2 kDir2D = (mousePosition - preMousePosition).Normalize();
				const Vector3 kDir3D = { kDir2D.x, kDir2D.y, 0.0f};
				sprites_[sprieIndex_].worldTF.rotation = Quaternion::ConvertFromTo(Vector3{0.0f,1.0f,0.0f}, kDir3D);
				// 大きさ
				const float kLength = (mousePosition - preMousePosition).Length();
				sprites_[sprieIndex_].worldTF.scale.y = (kLength / kSpriteSize_.y) + 0.1f;

				// アクティブに
				sprites_[sprieIndex_].isActive = true;
				++sprieIndex_;
				if (sprieIndex_ == kSpriteNum_) {
					sprieIndex_ = 0;
				}

				// 現在の位置を保存
				points_.push_back(mousePosition);
			}
		}
		// これから線を書く
		else {
			// 現在の位置を保存
			points_.push_back(Mouse::GetPosition());
			// アクティブ
			isActive_ = true;
		}
	}

}
