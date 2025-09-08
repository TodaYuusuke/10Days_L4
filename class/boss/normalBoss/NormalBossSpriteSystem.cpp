#include "NormalBossSpriteSystem.h"
const uint32_t kMaxParts = 1u;

NormalBossSpriteSystem::NormalBossSpriteSystem() {
	Initialize();
}

void NormalBossSpriteSystem::Initialize() {
	sprites_.resize(kMaxParts);
	sprites_.at(0).LoadTexture("boss.png");
	sprites_.at(0).SetSplitSize({ 32.0f,32.0f });
}

void NormalBossSpriteSystem::Update(const LWP::Math::Vector2& centerPosition) {
	sprites_.at(0).worldTF.translation = { centerPosition.x, centerPosition.y, 0.0f };
	sprites_.at(0).worldTF.scale = { 3.0f, 3.0f, 0.0f };
}
