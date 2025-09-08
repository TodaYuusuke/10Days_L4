#include "Player.h"
#include "PlayerGlobalData.h"

using namespace LWP::Input;

Player::Player()
	:	playerMouseOperation_(),
		meetingPlace_(),
		drawing_(),
		wallManager_(),
		jsonIO_()
{
	Initialize();
}

Player::~Player()
{
}

void Player::Initialize()
{

	jsonIO_.Init("Player.json");
	PlayerGlobalData::JsonDataRegistration(&jsonIO_);
	jsonIO_.CheckJsonFile();

}

void Player::Update()
{

	playerMouseOperation_.Update();
	if (playerMouseOperation_.GetClicked()) {
		meetingPlace_.SetPosition(Mouse::GetPosition());
	}

	meetingPlace_.Update();

	drawing_.Update(playerMouseOperation_.GetIsDragging());

	if (drawing_.GetWallCreation()) {
		wallManager_.CreateWalls(drawing_.GetPoints());
	}
	wallManager_.Update();

	// GUI JSON
	ImGui::Begin("Player");
	jsonIO_.DebugGUI();
	ImGui::End();

}

void Player::SetMinionManagerForDrawing(MinionManager* minionManager)
{

	drawing_.SetMinionManager(minionManager);

}
