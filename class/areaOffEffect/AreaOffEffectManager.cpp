#include "AreaOffEffectManager.h"

// 静的メンバの定義
std::queue<AreaOffEffectManager::CircleInitData> AreaOffEffectManager::circleInitDatas_;
std::queue<AreaOffEffectManager::RectangleInitData> AreaOffEffectManager::rectangleInitDatas_;

const std::string kFileName = "EffectParameter.json";

AreaOffEffectManager::~AreaOffEffectManager() {
	// 全削除
	circleInitDatas_ = {};
}

void AreaOffEffectManager::Initialize() {
	Load();
}

void AreaOffEffectManager::Update() {
	// リクエストがあれば生成
	while (!circleInitDatas_.empty()) {
		const CircleInitData& req = circleInitDatas_.front();
		// エフェクト生成、コンテナに追加
		container_.push_back(std::make_unique<AreaOffEffect>(&firstAlpha_,&frashCount_,req.pos, req.maxRadius, req.data));
		// リクエストを削除
		circleInitDatas_.pop();
	}
	// リクエストがあれば生成
	while (!rectangleInitDatas_.empty()) {
		const RectangleInitData& req = rectangleInitDatas_.front();
		// エフェクト生成、コンテナに追加
		container_.push_back(std::make_unique<AreaOffEffect>(&firstAlpha_,&frashCount_,req.pos, req.maxSize, req.data));
		// リクエストを削除
		rectangleInitDatas_.pop();
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

void AreaOffEffectManager::RequestCreate(const Vector2& pos, const Vector2& maxSize, const AttackDefaultData& data) {
	// リクエストコンテナに追加
	RectangleInitData req{ pos,maxSize,data };
	rectangleInitDatas_.push(req);
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
			json_.BeginGroup("AreaOffEffect")
				.AddValue("firstAlpha", &firstAlpha_)
				.AddValue("frashCount", &frashCount_)
				.EndGroup();
		}
	}

	json_.Load();
}
