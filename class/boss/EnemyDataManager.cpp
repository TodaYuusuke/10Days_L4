#include "EnemyDataManager.h"

EnemyDataManager* EnemyDataManager::GetInstance() {
	static EnemyDataManager instance;
	return &instance;
}

void EnemyDataManager::Initialize() {

	json_.Init("EnemyParameterData.json");

	// データの登録
	NormalBossData data;
	dataMap_["NormalBoss"] = std::make_unique<NormalBossData>(data);

	Load("EnemyParameterData.json");
}

void EnemyDataManager::ImGuiProc() {
#ifdef _DEBUG
	json_.DebugGUI();
	ImGui::Begin("Parameter", nullptr, ImGuiWindowFlags_MenuBar);
	ImGui::BeginMenuBar();

	for (size_t i = 0; i < static_cast<size_t>(BaseEnemyData::Type::kMaxNum); ++i) {
		BaseEnemyData::Type type = static_cast<BaseEnemyData::Type>(i);
		const char* name = BaseEnemyData::ToString(type);
		auto it = dataMap_.find(name);
		if (it == dataMap_.end()) continue;

		if (ImGui::BeginMenu(name)) {
			it->second->ImGuiProc(); // 継承先のImGuiProc() が呼ばれる
			ImGui::EndMenu();
		}
	}

	ImGui::EndMenuBar();
	ImGui::End();
#endif // _DEBUG
}

BaseEnemyData* EnemyDataManager::GetData(BaseEnemyData::Type type) {
	auto it = dataMap_.find(BaseEnemyData::ToString(type));
	if (it != dataMap_.end() && it->second) {
		return it->second.get();
	}
	return nullptr; // 見つからなければnullptrを返す
}

void EnemyDataManager::Save(const std::string& fileName) {
	json_.Init(fileName);
	for (auto& data : dataMap_) {
		data.second->AddValue(json_);
	}
	json_.Save();
	MessageBoxA(nullptr, "SaveComplete ", "EnemyData - Save", 0);
}

void EnemyDataManager::Load(const std::string& fileName) {
	// 初期化とロード
	json_.Init(fileName);
	json_.CheckJsonFile();

	// グループ名の取得
	LWP::Utility::NestedList nameList = LWP::Utility::JsonIO::LoadGroupNames(fileName);

	// グループ名リストが空の場合早期リターン
	if (nameList.empty()) {
		return;
	}

	for (auto itr = nameList.begin(); itr != nameList.end(); ++itr) {
		// NormalBossDataと書かれている場合
		if (itr->name == "NormalBossData") {
			// 入れ子
			NormalBossData handle;
			handle.AddValue(json_);
			// 生成
			dataMap_["NormalBoss"] = std::make_unique<NormalBossData>(handle);
		}
		// 別の場合
		else if (itr->name == "Unknown") {
			continue;
		}
	}

	json_.Load();

}
