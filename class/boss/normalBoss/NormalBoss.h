#pragma once
#include "../BaseEnemy.h"
#include <memory>
#include "NormalBossStateType.h"
#include "../state/IEnemyState.h"

class NormalBoss : public BaseEnemy{
public:
	NormalBoss() = default;
	~NormalBoss() = default;

	void Initialize() override;
	void Update() override;

private:
	// ステータス
	std::unordered_map<NormalBossStateType, std::unique_ptr<IEnemyState>> stateMap_;
	// 現在の状態
	IEnemyState* currentState_ = nullptr;
	// ステートパターン
	LWP::Utility::StatePattern<enum class BaseEnemyStateType, static_cast<size_t>(NormalBossStateType::StateTypeOfCount)> statePattern_;

};
