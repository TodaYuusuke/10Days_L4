#include "Player.h"

using namespace LWP::Input;

Player::Player()
	:	playerMouseOperation_(nullptr),
		meetingPlace_(nullptr),
		drawing_(nullptr),
		wallManager_(nullptr)
{
	Initialize();
}

Player::~Player()
{
}

void Player::Initialize()
{

	playerMouseOperation_ = std::make_unique<PlayerMouseOperation>();

	meetingPlace_ = std::make_unique<MeetingPlace>();

	drawing_ = std::make_unique<Drawing>();

	wallManager_ = std::make_unique<WallManager>();

}

void Player::Update()
{

	playerMouseOperation_->Update();
	if (playerMouseOperation_->GetClicked()) {
		meetingPlace_->SetPosition(Mouse::GetPosition());
	}

	meetingPlace_->Update();

	drawing_->Update(playerMouseOperation_->GetIsDragging());


	if (drawing_->GetWallCreation()) {
		wallManager_->CreateWalls(drawing_->GetPoints());
	}
	wallManager_->Update();

}
