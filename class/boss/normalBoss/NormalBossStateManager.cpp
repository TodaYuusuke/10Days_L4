#include "NormalBossStateManager.h"
#include "../normalBoss/NormalBossStateType.h"

NormalBossStateManager::NormalBossStateManager() {

}

NormalBossStateManager::NormalBossStateManager(NormalBoss* boss) {
	pBoss_ = boss;
}

uint8_t NormalBossStateManager::Update(const uint8_t currentType) {
	//ImGui::Text("currentType %u", static_cast<unsigned int>(currentType));
	// 変更がなければ何もなし
	if (!isStateChange_) { return currentType; }
	isStateChange_ = false;

	// 以下仮
	if (currentType == StateType::ToUInt8(NormalBossStateType::Move)) {
		//return StateType::ToUInt8(NormalBossStateType::Rain);
		return LWP::Utility::Random::GenerateInt(StateType::ToUInt8(NormalBossStateType::Slam), StateType::ToUInt8(NormalBossStateType::StateTypeOfCount) -1u);
	}
	else if (currentType == StateType::ToUInt8(NormalBossStateType::Idle)) {
		// 移動する場所を雑に設定
		targetPosition_.x = LWP::Utility::Random::GenerateFloat(0.0f, 1280.0f);
		targetPosition_.y = LWP::Utility::Random::GenerateFloat(0.0f, 720.0f);
		return StateType::ToUInt8(NormalBossStateType::Move);
	}
	// 以下攻撃
	else if (currentType == StateType::ToUInt8(NormalBossStateType::Slam)) {
		return StateType::ToUInt8(NormalBossStateType::Idle);
	}
	else if (currentType == StateType::ToUInt8(NormalBossStateType::Barrage)) {
		return StateType::ToUInt8(NormalBossStateType::Idle);
	}
	else if (currentType == StateType::ToUInt8(NormalBossStateType::Rain)) {
		return StateType::ToUInt8(NormalBossStateType::Idle);
	}
	return currentType;
}
