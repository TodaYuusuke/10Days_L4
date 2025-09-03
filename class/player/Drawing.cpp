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

	// ドラッグしていない
	if (!isDragging) {
		// アクティブなら止める
		if (isActive_) {

			// 円かどうか
			// 壁を作る

			// 非アクティブ
			isActive_ = false;
			points_.clear();

		}
		
	}
	// ドラッグしている
	else {
		// 線を書き途中
		if (isActive_) {
			recordingTimer_ += LWP::Info::GetDeltaTime();
			// レコーディング時間
			const float kRecordingTime = 0.5f;
			if (recordingTimer_ > kRecordingTime) {
				// 記録
				recordingTimer_ -= kRecordingTime;
				points_.push_back(Mouse::GetPosition());
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
