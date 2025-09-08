#include "AreaOffEffectManager.h"

AreaOffEffectManager* AreaOffEffectManager::GetInstance() {
	static AreaOffEffectManager instance;
	return &instance;
}

void AreaOffEffectManager::Initialize() {
	// 仮生成
	pFirstAlpha_ = new float(155.0f);
}

void AreaOffEffectManager::Update() {
	// リクエストがあれば生成
	while (!circleInitDatas_.empty()) {
		const CircleInitData& req = circleInitDatas_.front();
		// エフェクト生成、コンテナに追加
		container_.push_back(std::make_unique<AreaOffEffect>(pFirstAlpha_,req.pos, req.maxRadius, req.data));
		// リクエストを削除
		circleInitDatas_.pop();
	}

	// エフェクトの更新
	for (auto& effect : container_) {
		effect->Update();
	}

	// 死んだエフェクトを削除
	container_.erase(
		std::remove_if(container_.begin(), container_.end(),[](const std::unique_ptr<AreaOffEffect>& e) { return !e->IsAlive(); }),
		container_.end());

}

void AreaOffEffectManager::RequestCreate(const Vector2& pos, const float& maxRadius, const AttackDefaultData& data) {
	// リクエストコンテナに追加
	CircleInitData req{ pos,maxRadius,data };
	circleInitDatas_.push(req);
}
