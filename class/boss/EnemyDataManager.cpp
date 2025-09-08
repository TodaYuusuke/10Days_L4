#include "EnemyDataManager.h"

const std::string kFileName = "EnemyParameterData.json";

EnemyDataManager::~EnemyDataManager() {
#ifdef _DEBUG // 普段は邪魔なのでレベルデザインの時に解禁
	/*int result = MessageBoxA(nullptr, "EnemyDataはセーブされていません。セーブしますか？","確認",MB_YESNO | MB_ICONQUESTION);
	if (result == IDYES) {
		Save(kFileName);
	}*/
#endif // _DEBUG
}

EnemyDataManager* EnemyDataManager::GetInstance() {
	static EnemyDataManager instance;
	return &instance;
}

void EnemyDataManager::Initialize() {

	json_.Init(kFileName);

	// データの登録
	dataMap_["NormalBoss"] = std::make_unique<NormalBossData>();

	Load(kFileName);
}

void EnemyDataManager::ImGuiProc() {
	ImGui::Begin("EnemyDataManager");
	json_.DebugGUI();
	ImGui::End();
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
			// 生成
			dataMap_["NormalBoss"] = std::make_unique<NormalBossData>();
			dataMap_["NormalBoss"]->AddValue(json_);
		}
		// 別の場合
		else if (itr->name == "Unknown") {
			continue;
		}
	}

	json_.Load();

}
