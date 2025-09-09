#include "MinionManager.h"
#include "MinionGlobalData.h"
using namespace LWP::Math;

MinionManager::MinionManager()
	:	minions_{},
		minionNum_(kMinionNumMax_),
		attackMinionNum_(0),
		targetPosition_({ 0.0f,0.0f }),
		meetingPlace_(nullptr),
		stoneManager_(nullptr),
		enemyManager_(nullptr),
		jsonIO_()
{
	Initialize();
}

MinionManager::MinionManager(MeetingPlace* meetingPlace, StoneManager* stoneManager, EnemyManager* enemyManager)
	:	minions_{},
		minionNum_(kMinionNumMax_),
		attackMinionNum_(0),
		targetPosition_({0.0f,0.0f}),
		meetingPlace_(meetingPlace),
		stoneManager_(stoneManager),
		enemyManager_(enemyManager),
		jsonIO_()
{
	Initialize();
}

MinionManager::~MinionManager()
{
}

void MinionManager::Initialize()
{

	jsonIO_.Init("Minion.json");
	MinionGlobalData::JsonDataRegistration(&jsonIO_);
	jsonIO_.CheckJsonFile();

	for (size_t i = 0; i < kMinionNumMax_; ++i) {
		minions_[i].SetMinionManager(this);
	}

}

void MinionManager::Update()
{

	// 目指す場所が変わった
	const Vector2 kMeetingPlacePosition = meetingPlace_->GetPosition();
	if (!(targetPosition_.x == kMeetingPlacePosition.x &&
		targetPosition_.y == kMeetingPlacePosition.y)) {
		
		//数を専用に設定
		attackMinionNum_ = 0;
		for (size_t i = 0; i < kMinionNumMax_; ++i) {
			if ((minions_[i].GetCurrentStateType() == MinionStateType::Attack) 
				&& ((kMeetingPlacePosition - minions_[i].GetPosition()).Length() < MinionGlobalData::GetMeetingPlaceChangeLength())) {
				++attackMinionNum_;
			}
		}
		//場所変更
		targetPosition_ = kMeetingPlacePosition;
	}

	minionNum_ = 0;
	for (size_t i = 0; i < kMinionNumMax_; ++i) {
		minions_[i].Update();

		if (minions_[i].GetHp() > 0) {
			++minionNum_;
		}

	}

	attackMinionNum_ = 0;
	for (size_t i = 0; i < kMinionNumMax_; ++i) {
		if (minions_[i].GetCurrentStateType() == MinionStateType::Attack) {
			++attackMinionNum_;
		}
	}

	// GUI JSON
	ImGui::Begin("Minion");
	jsonIO_.DebugGUI();
	ImGui::End();

}
