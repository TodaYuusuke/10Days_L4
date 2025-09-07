#include "NormalBossStateManager.h"
#include "../normalBoss/NormalBossStateType.h"

NormalBossStateManager::NormalBossStateManager() {

}

uint8_t NormalBossStateManager::Update(const uint8_t currentType) {
	ImGui::Text("currentType %u", static_cast<unsigned int>(currentType));
	// 変更がなければ何もなし
	if (!isStateChange_) { return currentType; }
	isStateChange_ = false;

	// 以下仮
	if (currentType == static_cast<uint8_t>(NormalBossStateType::Move)) {
		return static_cast<uint8_t>(NormalBossStateType::Idle);
	}
	else if (currentType == static_cast<uint8_t>(NormalBossStateType::Idle)) {
		// 移動する場所を雑に設定
		targetPosition_.x = LWP::Utility::Random::GenerateFloat(0.0f, 1280.0f);
		targetPosition_.y = LWP::Utility::Random::GenerateFloat(0.0f, 720.0f);
		return static_cast<uint8_t>(NormalBossStateType::Move);
	}
}
