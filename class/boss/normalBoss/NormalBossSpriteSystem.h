#pragma once
#include "../BaseEnemySpriteSystem.h"
#include "../../partsAnimation/PartsAnimation.h"

// normalBoss用sprite管理クラス
class NormalBossSpriteSystem : public BaseEnemySpriteSystem {
public:
	NormalBossSpriteSystem();
	~NormalBossSpriteSystem() override = default;

	void Initialize() override;
	void Update(const LWP::Math::Vector2& centerPosition) override;

	void ColorUpdate();

private:
	LWP::Object::TransformQuat baseTransform_;
	PartsAnimation animation_;

};

