#include "Player.h"

using namespace LWP::Input;

Player::Player()
	:	playerMouseOperation_(nullptr),
		meetingPlace_(nullptr)
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

}

void Player::Update()
{

	playerMouseOperation_->Update();
	if (playerMouseOperation_->GetClicked()) {
		meetingPlace_->SetPosition(Mouse::GetPosition());
	}

	meetingPlace_->Update();

}
