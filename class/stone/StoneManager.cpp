#include "StoneManager.h"
#include "StoneGlobalData.h"

StoneManager::StoneManager()
	:	stones_{},
		jsonIO_()
{
	Initialize();
}

StoneManager::~StoneManager()
{
	// 削除
	for (auto it = stones_.begin(); it != stones_.end();) {
		Stone* stone = *it;
		it = stones_.erase(it);
		delete stone;
	}
}

void StoneManager::Initialize()
{

	jsonIO_.Init("Stone.json");
	StoneGlobalData::JsonDataRegistration(&jsonIO_);
	jsonIO_.CheckJsonFile();

}

void StoneManager::Update()
{

	// 削除
	for (auto it = stones_.begin(); it != stones_.end();) {
		Stone* stone = *it;
		if (stone->IsDead()) {
			it = stones_.erase(it);
			delete stone;
		}
		else {
			++it;
		}
	}

	// 更新
	for (auto it = stones_.begin(); it != stones_.end(); ++it) {
		Stone* stone = *it;
		stone->Update();
	}

	// GUI JSON
	ImGui::Begin("Stone");
	jsonIO_.DebugGUI();
	ImGui::End();

}

void StoneManager::CreateStone(const LWP::Math::Vector2& position, const LWP::Math::Vector2& direction)
{

	// 作成、登録
	Stone* stone = new Stone(position, direction);
	stones_.push_back(stone);

}
