#pragma once
#include <Adapter.h>
#include "BaseEnemyData.h"
#include <memory>
#include <unordered_map>

// 敵のデータ管理クラス
class EnemyDataManager {
private:
	EnemyDataManager() = default;
	~EnemyDataManager();
public:
	// シングルトン
	static EnemyDataManager* GetInstance();
	// 初期化処理 ここでjsonからすべてのdataを取得
	void Initialize();

	void ImGuiProc();

	BaseEnemyData* GetData(BaseEnemyData::Type type);

private:
	void Save(const std::string& fileName);
	void Load(const std::string& fileName);

private:
	// json変数
	LWP::Utility::JsonIO json_;
	// data格納用コンテナ
	std::unordered_map<std::string, std::unique_ptr<BaseEnemyData>> dataMap_;

};

