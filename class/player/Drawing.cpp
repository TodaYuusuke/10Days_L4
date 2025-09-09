#include "Drawing.h"
#include "PlayerGlobalData.h"
#include "../minion/MinionManager.h"

using namespace LWP::Math;
using namespace LWP::Input;
using namespace LWP::Info;
using namespace LWP::Utility;

Drawing::Drawing()
	:	points_{},
		sprites_{},
		isActive_(false),
		recordingTimer_(0.0f),
		wallCreation_(false),
		startWriting_({ 0.0f,0.0f }),
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
		startWriting_({0.0f,0.0f}),
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
		sprites_[i].worldTF.scale.x = PlayerGlobalData::GetLineSpriteScale().x;
		sprites_[i].isActive = false;
	}

}

void Drawing::Update(bool isDragging)
{
	ImGui::Begin("Drawing");
	ImGui::Text("Points Count : %d", points_.size());
	ImGui::End();

	wallCreation_ = false;

	// ドラッグしていない
	if (!isDragging) {
		// アクティブなら止める
		if (isActive_) {
			// スプライトとポイントをリセット
			ResetSprites();
			isActive_ = false;	// ラクガキしゅうりょ～う！

			// 壁作成フラグ
			wallCreation_ = true;

		}
		else {
			if ((Mouse::GetTrigger(0) && !Keyboard::GetPress(DIK_SPACE)) || (Keyboard::GetTrigger(DIK_SPACE) && !Mouse::GetPress(0))) {
				startWriting_ = Mouse::GetPosition();
			}
		}
		
	}
	// ドラッグしている
	else {
		// 線を書き途中
		if (isActive_) {
			recordingTimer_ += static_cast<float>(LWP::Info::GetDeltaTime());
			// レコーディング時間
			const float kRecordingTime = PlayerGlobalData::GetLineRecordingTime();
			if (recordingTimer_ > kRecordingTime) {
				// 記録
				recordingTimer_ -= kRecordingTime;
				const Vector2 mousePosition = Mouse::GetPosition();
				const Vector2 preMousePosition = points_[points_.size() - 1];
				const float kLength = (mousePosition - preMousePosition).Length();

				// 長さ30未満なのでリターン
				// ドラッグ認定距離
				if (kLength < PlayerGlobalData::GetDragCertifiedDistance()) {
					return;
				}

				// 現在の位置を保存
				points_.push_back(mousePosition);
				// スプライト
				SpriteActive(preMousePosition, mousePosition);

				// 線の長さ
				lineLength_ += kLength;
				// 線の長さ最大
				const float kLengthMax = PlayerGlobalData::GetLineLengthMax();
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

				for (int i = 0; i < kSpriteNum_; ++i) {
					sprites_[i].material.color = ColorPattern::WHITE;
				}
				// ここで線が生成され終わるのでおそらくここで円確認
				IsCircleCreated();
			
			}

		}
		// これから線を書く
		else {
			points_.clear();
			// 書き始めの位置を保存
			points_.push_back(startWriting_);
			// 現在の位置を保存
			//points_.push_back(Mouse::GetPosition());
			// アクティブ
			isActive_ = true;
		}
	}

}
void Drawing::ResetSprites() {
	sprieIndex_ = 0;
	for (size_t i = 0; i < kSpriteNum_; ++i) {
		sprites_[i].isActive = false;
	}
	lineLength_ = 0.0f;
}

void Drawing::SpriteActive(const LWP::Math::Vector2& point0, const LWP::Math::Vector2& point1)
{

	// 位置
	const Vector2 spritePosition = (point1 + point0) / 2.0f;
	// Z座標（描画順）
	sprites_[sprieIndex_].worldTF.translation = { spritePosition.x, spritePosition.y, PlayerGlobalData::GetLinePositionZ()};
	// 回転
	const Vector2 kDir2D = (point1 - point0).Normalize();
	const Vector3 kDir3D = { kDir2D.x, kDir2D.y, 0.0f };
	sprites_[sprieIndex_].worldTF.rotation = Quaternion::ConvertFromTo(Vector3{ 0.0f,1.0f,0.0f }, kDir3D);
	// 大きさ
	const float kLength = (point1 - point0).Length();
	sprites_[sprieIndex_].worldTF.scale.y = (kLength / PlayerGlobalData::GetLineTextureSize().y) + PlayerGlobalData::GetLineSpriteScale().x;

	// アクティブに
	sprites_[sprieIndex_].isActive = true;
	++sprieIndex_;
	if (sprieIndex_ == kSpriteNum_) {
		sprieIndex_ = 0;
		assert(0);
	}

}

// 外積による向き判定
float ccw(const Vector2& A, const Vector2& B, const Vector2& C) {
	return (B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x);
}

// 線分交差判定
std::optional<Vector2> GetIntersection(const Vector2& A1, const Vector2& A2, const Vector2& B1, const Vector2& B2) {
	float d1 = ccw(A1, A2, B1);
	float d2 = ccw(A1, A2, B2);
	float d3 = ccw(B1, B2, A1);
	float d4 = ccw(B1, B2, A2);

	if (d1 * d2 > 0.0f || d3 * d4 > 0.0f) {
		// 交差していない
		return std::nullopt;
	}

	// パラメータ t を求める
	float denom = (A2.x - A1.x) * (B2.y - B1.y) - (A2.y - A1.y) * (B2.x - B1.x);
	if (denom == 0.0f) return std::nullopt; // 平行または重なり

	float t = ((B1.x - A1.x) * (B2.y - B1.y) - (B1.y - A1.y) * (B2.x - B1.x)) / denom;

	Vector2 intersection;
	intersection.x = A1.x + t * (A2.x - A1.x);
	intersection.y = A1.y + t * (A2.y - A1.y);

	return intersection;
}
void Drawing::IsCircleCreated()
{	
	if (points_.size() < 4) { return; }	// 3以下ならば絶対に円は作れないので戻る
	// 線から円が形成されているか判定する

	for (int i = 2; i < points_.size() - 1; i++) {
		// 判定する線分を指定
		Vector2 a1 = points_[i];
		Vector2 a2 = points_[i + 1];
		// これまでの線分と交差しているか判定
		for (int n = 0; n < i-1; n++) {
			Vector2 b1 = points_[n];
			Vector2 b2 = points_[n + 1];
			std::optional<Vector2> opt = GetIntersection(a1, a2, b1, b2);
			if (opt != std::nullopt) {
				// 衝突した線分を、衝突した部分にまで縮小する
				points_[i + 1] = *opt;
				points_[n] = *opt;

				// nより手前の点を削除する
				if (n >= 1) {
					points_.erase(points_.begin(), points_.begin() + n - 1);
				}

				// 囲まれた手下の更新
				SurroundedMinionsUpdate();

				ResetSprites();	// スプライトをリセット
				points_.clear();	// 点をリセット
				points_.push_back(*opt);	// 初期地点は設定する
				break;
			}
		}
	}
}

void Drawing::SurroundedMinionsUpdate()
{
	// 手下の管理クラスのポインタがあるか
	assert(minionManager_);
	
	// 全手下確認
	int index = 0;
	for (Vector2& pos : minionManager_->GetMinionsPosition()) {
		// 各線分を確認
		bool inside = false;
		for (int i = 0; i < points_.size() - 1; i++) {
				const Vector2& pi = points_[i];
				const Vector2& pj = points_[i + 1];
				bool intersect = ((pi.y > pos.y) != (pj.y > pos.y)) &&
					(pos.x < (pj.x - pi.x) * (pos.y - pi.y) / (pj.y - pi.y + 1e-6f) + pi.x);
				if (intersect) inside = !inside;
			}
		
		if (inside) {
			minionManager_->ApplyMinionAttack(index);
		}
		index++;
	}

}
