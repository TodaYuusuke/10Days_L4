#pragma once
#include "../BaseEnemySpriteSystem.h"

// normalBoss用sprite管理クラス
class NormalBossSpriteSystem : public BaseEnemySpriteSystem {
public:
	~NormalBossSpriteSystem() override = default;

	void Initialize() override;
	void Update(const LWP::Math::Vector2& centerPosition) override;

private:

};

