#include "NormalBossSpriteSystem.h"
const uint32_t kMaxParts = 1u;

NormalBossSpriteSystem::NormalBossSpriteSystem() {
	Initialize();
}

void NormalBossSpriteSystem::Initialize() {
	sprites_.resize(kMaxParts);
	sprites_[0].LoadTexture("boss.png");
	sprites_[0].SetSplitSize({ 256.0f,256.0f });
}

void NormalBossSpriteSystem::Update(const LWP::Math::Vector2& centerPosition) {
	sprites_[0].worldTF.translation = { centerPosition.x, centerPosition.y, 0.0f };
	sprites_[0].worldTF.scale = { 3.0f / 8.0f, 3.0f / 8.0f, 0.0f };
	sprites_[0].material.color = LWP::Utility::ColorPattern::WHITE;
}

void NormalBossSpriteSystem::ColorUpdate() {
	sprites_[0].material.color = LWP::Utility::ColorPattern::RED;
}


