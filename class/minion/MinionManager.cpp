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
		minions_[i].Initialize();
		minions_[i].SetMinionManager(this);
	}

	audio_.LoadShortPath("minionDamage.mp3");

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
			const MinionStateType kCurrentStateType = minions_[i].GetCurrentStateType();
			if (kCurrentStateType == MinionStateType::Idle ||
				kCurrentStateType == MinionStateType::Attack) {
				minions_[i].SetRequestStateType(MinionStateType::Move);
			}
		}
		//場所変更
		targetPosition_ = kMeetingPlacePosition;
	}

	minionNum_ = 0;
	bool audioPlay = false;
	for (size_t i = 0; i < kMinionNumMax_; ++i) {
		if (minions_[i].GetCurrentStateType() != MinionStateType::Down &&
			minions_[i].GetRequestStateType() == MinionStateType::Down &&
			minions_[i].GetInvincible()) {
			audioPlay = true;
		}

		minions_[i].Update();

		if (minions_[i].GetHp() > 0) {
			++minionNum_;
			minionsPosition_[i] = minions_[i].GetPosition();	// ミニオンの座標をメモ
		}
	}

	if (audioPlay) {
		audio_.Play();
		audio_.SetVolume(0.1f);
	}

	attackMinionNum_ = 0;
	for (size_t i = 0; i < kMinionNumMax_; ++i) {
		const MinionStateType kCurrentStateType = minions_[i].GetCurrentStateType();
		if (kCurrentStateType == MinionStateType::Idle ||
			kCurrentStateType == MinionStateType::Attack) {
			++attackMinionNum_;
		}
	}

	DebugGUI();

}

void MinionManager::DebugGUI() {}
