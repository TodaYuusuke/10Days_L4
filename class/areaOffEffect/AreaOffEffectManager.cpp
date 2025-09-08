#include "AreaOffEffectManager.h"

const std::string kFileName = "EffectParameter.json";


AreaOffEffectManager::~AreaOffEffectManager() {
	// 全削除
	circleInitDatas_ = {};
}

AreaOffEffectManager* AreaOffEffectManager::GetInstance() {
	static AreaOffEffectManager instance;
	return &instance;
}

void AreaOffEffectManager::Initialize() {
	Load();
}

void AreaOffEffectManager::Update() {
	ImGui::Begin("Effect");
	json_.DebugGUI();
	ImGui::End();
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

void AreaOffEffectManager::Load() {
	json_.Init(kFileName);
	json_.CheckJsonFile();

	// グループ名の取得
	LWP::Utility::NestedList nameList = LWP::Utility::JsonIO::LoadGroupNames(kFileName);

	// グループ名リストが空の場合早期リターン
	if (nameList.empty()) {
		return;
	}

	for (auto itr = nameList.begin(); itr != nameList.end(); ++itr) {
		// NormalBossDataと書かれている場合
		if (itr->name == "AreaOffEffect") {
			// 生成
			json_.BeginGroup("AreaOffEffect").AddValue("firstAlpha", &firstAlpha_).EndGroup();
		}
	}

	json_.Load();
}
