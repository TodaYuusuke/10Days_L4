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
		recordingTimer_(0.0f),
		wallCreation_(false),
		minionManager_(nullptr)
{
	Initialize();
}

Drawing::Drawing(MinionManager* minionManager)
	:	points_{},
		sprites_{},
		isActive_(false),
		recordingTimer_(0.0f),
		wallCreation_(false),
		minionManager_(minionManager)
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

	wallCreation_ = false;

	// ドラッグしていない
	if (!isDragging) {
		// アクティブなら止める
		if (isActive_) {

			// 非アクティブ
			isActive_ = false;
			sprieIndex_ = 0;
			for (size_t i = 0; i < kSpriteNum_; ++i) {
				sprites_[i].isActive = false;
			}
			lineLength_ = 0.0f;

			// 壁作成フラグ
			wallCreation_ = true;

		}
		
	}
	// ドラッグしている
	else {
		// 線を書き途中
		if (isActive_) {
			recordingTimer_ += static_cast<float>(LWP::Info::GetDeltaTime());
			// レコーディング時間
			const float kRecordingTime = 0.01f;
			if (recordingTimer_ > kRecordingTime) {
				// 記録
				recordingTimer_ -= kRecordingTime;
				const Vector2 mousePosition = Mouse::GetPosition();
				const Vector2 preMousePosition = points_[points_.size() - 1];
				const float kLength = (mousePosition - preMousePosition).Length();

				// 長さ10未満なのでリターン
				if (kLength < 10.0f) {
					return;
				}

				// 現在の位置を保存
				points_.push_back(mousePosition);
				// スプライト
				SpriteActive(preMousePosition, mousePosition);

				// 線の長さ
				lineLength_ += kLength;
				// 線の長さ最大
				const float kLengthMax = 5000.0f;
				// 差分
				float difference = lineLength_ - kLengthMax;

				while (difference > 0.0f) {

					lineLength_ = kLengthMax;

					// 線は一つ
					if (points_.size() <= 2) {
						points_[0] = (points_[1] - points_[0]).Normalize() * kLengthMax + points_[1];
						difference = 0.0f;
					}
					else {
						difference = difference - (points_[0] - points_[1]).Length();

						// 0より小さい
						if (difference < 0.0f) {
							points_[0] = (points_[1] - points_[0]).Normalize() * difference + points_[1];
						}
						else {
							for (size_t i = 0; i < points_.size() - 1; ++i) {
								points_[i] = points_[i + 1];
							}
							points_.pop_back();
						}
					}

					// スプライト
					sprieIndex_ = 0;
					for (size_t i = 0; i < points_.size() - 1; ++i) {
						// スプライト
						SpriteActive(points_[i], points_[i + 1]);
					}
					for (size_t i = sprieIndex_; i < kSpriteNum_; ++i) {
						sprites_[i].isActive = false;
					}

				}

				// ここで線が生成され終わるのでおそらくここで円確認
				if (IsCircleCreated()) {
					// 囲まれた手下の更新
					SurroundedMinionsUpdate();
				}
			
			}

		}
		// これから線を書く
		else {
			points_.clear();
			// 現在の位置を保存
			points_.push_back(Mouse::GetPosition());
			// アクティブ
			isActive_ = true;
		}
	}

}

void Drawing::SpriteActive(const LWP::Math::Vector2& point0, const LWP::Math::Vector2& point1)
{

	// 位置
	const Vector2 spritePosition = (point1 + point0) / 2.0f;
	// Z座標（描画順）
	const float kPositionZ = 0.0f;
	sprites_[sprieIndex_].worldTF.translation = { spritePosition.x, spritePosition.y, kPositionZ };
	// 回転
	const Vector2 kDir2D = (point1 - point0).Normalize();
	const Vector3 kDir3D = { kDir2D.x, kDir2D.y, 0.0f };
	sprites_[sprieIndex_].worldTF.rotation = Quaternion::ConvertFromTo(Vector3{ 0.0f,1.0f,0.0f }, kDir3D);
	// 大きさ
	const float kLength = (point1 - point0).Length();
	sprites_[sprieIndex_].worldTF.scale.y = (kLength / kSpriteSize_.y) + 0.1f;

	// アクティブに
	sprites_[sprieIndex_].isActive = true;
	++sprieIndex_;
	if (sprieIndex_ == kSpriteNum_) {
		sprieIndex_ = 0;
		assert(0);
	}

}

bool Drawing::IsCircleCreated()
{
	return false;
}

void Drawing::SurroundedMinionsUpdate()
{
	// 手下の管理クラスのポインタがあるか
	if (!minionManager_) {
		assert(0);
		return;
	}

}
