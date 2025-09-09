#pragma once
#include <Adapter.h>

// 2Dのパーツアニメーション
class PartsAnimation {
public:
	PartsAnimation();
	~PartsAnimation() = default;

	void Initialize(LWP::Object::TransformQuat* base);

	void Update();

	inline LWP::Object::TransformQuat* GetPartsTransformPtr(uint8_t num) {
		return &transforms_[num];
	}

private:

	void Load();

private:

	std::vector<LWP::Object::TransformQuat> transforms_;

	// json変数
	LWP::Utility::JsonIO json_;

};
