#include "AreaOffEffect.h"
#undef min

AreaOffEffect::AreaOffEffect() {
	outerFrame_.LoadTexture("outerCircle.png");
	innerFrame_.LoadTexture("innerCircle.png");
}

void AreaOffEffect::Intiialize(const Vector2& pos, const float& maxRadius, const AttackDefaultData& data) {
	outerFrame_.worldTF.translation = { pos.x,pos.y,0.0f };
	outerFrame_.worldTF.scale = { 0.0f,0.0f,0.0f };
	innerFrame_.worldTF.translation = { pos.x,pos.y,0.0f };
	innerFrame_.worldTF.scale = { 0.0f,0.0f,0.0f };
	maxRadius_ = maxRadius;
	data_ = data;
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
	}
	innerFrame_.worldTF.scale =
		LWP::Utility::Interp::Lerp({ 0.0f,0.0f,0.0f }, { maxRadius_ ,maxRadius_ ,0.0f }, t);
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
	float alpha = LWP::Utility::Interp::LerpF(255.0f, 0.0f, t);
	outerFrame_.material.color.A = static_cast<unsigned char>(alpha);
}
