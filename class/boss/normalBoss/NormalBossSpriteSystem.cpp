#include "NormalBossSpriteSystem.h"
const uint32_t kMaxParts = 1u;

NormalBossSpriteSystem::NormalBossSpriteSystem() {
	Initialize();
}

void NormalBossSpriteSystem::Initialize() {
	sprites_.resize(kMaxParts);

}

void NormalBossSpriteSystem::Update(const LWP::Math::Vector2& centerPosition) {
	sprites_.at(0).worldTF.translation = { centerPosition.x, centerPosition.y, 0.0f };
}
