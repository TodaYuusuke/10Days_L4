#include "UIManager.h"
#include "MinionsNumUI.h"

using namespace LWP::Utility;

UIManager::UIManager()
	:	uis_{},
		jsonIO_()
{
	Initialize(nullptr, nullptr);
}

UIManager::UIManager(Player* player, MinionManager* minionManager)
	: uis_{}
{
	Initialize(player, minionManager);
}

UIManager::~UIManager()
{
}

void UIManager::Initialize(Player* player, MinionManager* minionManager)
{

	// 手下の数
	uis_[static_cast<size_t>(UIList::MinionsNum)] = std::make_unique<MinionsNumUI>();
	dynamic_cast<MinionsNumUI*>(uis_[static_cast<size_t>(UIList::MinionsNum)].get())->SetMinionManager(minionManager);


	jsonIO_.Init("UI.json");

	for (size_t i = 0; i < static_cast<size_t>(UIList::UIListOfCount); ++i) {
		uis_[i]->JsonDataRegistration(&jsonIO_);
	}
	jsonIO_.CheckJsonFile();

}

void UIManager::Update()
{

	for (size_t i = 0; i < static_cast<size_t>(UIList::UIListOfCount); ++i) {
		uis_[i]->Update();
	}

	// GUI JSON
	ImGui::Begin("UIManager");
	jsonIO_.DebugGUI();
	ImGui::End();

}
