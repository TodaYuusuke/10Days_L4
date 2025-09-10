#pragma once
#include <Adapter.h>

class NormalBoss;

/// <summary>
/// Stateを管理する敵Aiマネージャー
/// </summary>
class NormalBossStateManager {
public:
	NormalBossStateManager();
	NormalBossStateManager(NormalBoss* boss);
	~NormalBossStateManager() = default;
	
	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="currentType">今のタイプ</param>
	/// <returns>次の状態を返す</returns>
	uint8_t Update(const uint8_t currentType);
	// 状態変化をリクエスト
	const void RequestStateChange() { isStateChange_ = true; }

	const LWP::Math::Vector2& GetTargetPosition() const { return targetPosition_; }

private:
	// 
	LWP::Math::Vector2 targetPosition_ = { 0.0f,0.0f };
	// 状態を変化させるか
	bool isStateChange_ = false;

	NormalBoss* pBoss_ = nullptr;
};

