#include "UIManager.h"
#include "MinionsNumUI.h"
#include "LineGaugeUI.h"
#include "BossHPUI.h"

using namespace LWP::Utility;

UIManager::UIManager()
	:	uis_{},
		jsonIO_()
{
	Initialize(nullptr, nullptr, nullptr);
}

UIManager::UIManager(Player* player, MinionManager* minionManager, EnemyManager* enemyManager)
	:	uis_{},
		jsonIO_()
{
	Initialize(player, minionManager, enemyManager);
}

UIManager::~UIManager()
{
}

void UIManager::Initialize(Player* player, MinionManager* minionManager, EnemyManager* enemyManager)
{

	// 手下の数
	uis_[static_cast<size_t>(UIList::MinionsNum)] = std::make_unique<MinionsNumUI>();
	dynamic_cast<MinionsNumUI*>(uis_[static_cast<size_t>(UIList::MinionsNum)].get())->SetMinionManager(minionManager);
	// ゲージ
	uis_[static_cast<size_t>(UIList::LineGauge)] = std::make_unique<LineGaugeUI>();
	dynamic_cast<LineGaugeUI*>(uis_[static_cast<size_t>(UIList::LineGauge)].get())->SetPlayer(player);
	// ボスHP
	uis_[static_cast<size_t>(UIList::BossHP)] = std::make_unique<BossHPUI>();
	dynamic_cast<BossHPUI*>(uis_[static_cast<size_t>(UIList::BossHP)].get())->SetEnemyManager(enemyManager);


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
}
