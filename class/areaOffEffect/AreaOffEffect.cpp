#include "AreaOffEffect.h"

// textureパスの宣言
const std::string kOuterCirclePath = "outerCircle.png";
const std::string kInnerCirclePath = "innerCircle.png";
const std::string kExclamationPath = "exclamation.png";

// エフェクトの描画優先度 奥行座標
const float kEffectTranslate_Z = 10.0f;

AreaOffEffect::AreaOffEffect(const float* alpha, const Vector2& pos, const float& maxRadius, const AttackDefaultData& data) {
	outerFrame_.LoadTexture(kOuterCirclePath);
	innerFrame_.LoadTexture(kInnerCirclePath);
	exclamation_.LoadTexture(kExclamationPath);
	pFirstAlpha_ = alpha;
	Initialize(pos, maxRadius, data);
}

void AreaOffEffect::Initialize(const Vector2& pos, const float& maxRadius, const AttackDefaultData& data) {
	outerFrame_.worldTF.translation = { pos.x,pos.y,kEffectTranslate_Z };
	outerFrame_.worldTF.scale = { 0.0f,0.0f,0.0f };
	outerFrame_.material.color = LWP::Utility::ColorPattern::YELLOW;
	outerFrame_.material.color.A = static_cast<unsigned char>(*pFirstAlpha_);
	
	innerFrame_.worldTF.translation = { pos.x,pos.y,kEffectTranslate_Z };
	innerFrame_.worldTF.scale = { 0.0f,0.0f,0.0f };
	innerFrame_.material.color = LWP::Utility::ColorPattern::RED;
	innerFrame_.material.color.A = static_cast<unsigned char>(*pFirstAlpha_);
	
	float exSize = exclamation_.GetFitSizeImpl(&exclamation_.material).x * 0.5f;
	exSize = maxRadius / exSize;
	exclamation_.worldTF.translation = { pos.x,pos.y,kEffectTranslate_Z };
	exclamation_.worldTF.scale = { exSize,exSize,0.0f };
	exclamation_.material.color = LWP::Utility::ColorPattern::YELLOW;
	exclamation_.material.color.A = 0u;
	exclamation_.isActive = false;

	// テクスチャの半分の長さを取得
	float size = innerFrame_.GetFitSizeImpl(&innerFrame_.material).x * 0.5f;
	// 尺を合わせる
	maxRadius_ = maxRadius / size;
	data_ = data;
	state_ = State::OuterScaleUp;
	isAlive_ = true;
}

void AreaOffEffect::Update() {
	switch (state_) {
	case AreaOffEffect::OuterScaleUp:
		// 先に外枠を広げる
		OuterScaleUpUpdate();
		break;
	case AreaOffEffect::InnerScaleUp:
		// その後に内枠を広げる
		InnerScaleUpUpdate();
		break;
	case AreaOffEffect::FadeOut:
		// ダメージタイムでどんどん薄くしていく
		FadeOutUpdate();
		break;
	case AreaOffEffect::Delete:
		isAlive_ = false;
		break;
	}
}

void AreaOffEffect::StateInitialize(State type) {
	nowTime_ = 0.0f;
	state_ = type;
}

void AreaOffEffect::OuterScaleUpUpdate() {
	// 前隙の1/nの速度で外枠を広げる
	const float kMaxTime = data_.startupLag / aroundRate_;
	// タイマーの加算
	nowTime_ += LWP::Info::GetDeltaTimeF();
	// イージングでscaleを変更
	float t = LWP::Utility::Easing::CallFunction(LWP::Utility::Easing::Type::OutCubic, nowTime_ / kMaxTime);
	// 終わったら次のstateへ
	if (t >= 1.0f) {
		t = 1.0f;
		StateInitialize(State::InnerScaleUp);
		exclamation_.isActive = true;
	}
	outerFrame_.worldTF.scale =
		LWP::Utility::Interp::Lerp({ 0.0f,0.0f,0.0f }, { maxRadius_ ,maxRadius_ ,0.0f }, t);
}

void AreaOffEffect::InnerScaleUpUpdate() {

	// 前隙の 1/n * (n-1) の速度で内枠を広げる
	const float kMaxTime = (data_.startupLag / aroundRate_) * (aroundRate_ - 1.0f);
	// タイマーの加算
	nowTime_ += LWP::Info::GetDeltaTimeF();
	// イージングでscaleを変更
	float t = LWP::Utility::Easing::CallFunction(LWP::Utility::Easing::Type::OutCubic, nowTime_ / kMaxTime);
	// 終わったら次のstateへ
	if (t >= 1.0f) {
		t = 1.0f;
		StateInitialize(State::FadeOut);
		exclamation_.isActive = false;
	}
	innerFrame_.worldTF.scale =
		LWP::Utility::Interp::Lerp({ 0.0f,0.0f,0.0f }, { maxRadius_ ,maxRadius_ ,0.0f }, t);

	// exclamationの処理 3回点滅させる
	exclamation_.material.color.A = GetAlpha(nowTime_, kMaxTime / 3.0f);
}

void AreaOffEffect::FadeOutUpdate() {
	// ダメージが与えられる時間
	const float kMaxTime = data_.damageTime;
	// タイマーの加算
	nowTime_ += LWP::Info::GetDeltaTimeF();
	// イージングでscaleを変更
	float t = LWP::Utility::Easing::CallFunction(LWP::Utility::Easing::Type::OutCubic, nowTime_ / kMaxTime);
	// 終わったら次のstateへ
	if (t >= 1.0f) {
		t = 1.0f;
		StateInitialize(State::Delete);
	}
	float alpha = LWP::Utility::Interp::LerpF(*pFirstAlpha_, 0.0f, t);
	outerFrame_.material.color.A = static_cast<unsigned char>(alpha);
	innerFrame_.material.color.A = static_cast<unsigned char>(alpha);
}
