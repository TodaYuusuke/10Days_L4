#include "MinionManager.h"

MinionManager::MinionManager()
	:	minions_{},
		minionNum_(kMinionNumMax_),
		meetingPlace_(nullptr),
		stoneManager_(nullptr)
{
	Initialize();
}

MinionManager::MinionManager(MeetingPlace* meetingPlace, StoneManager* stoneManager)
	:	minions_{},
		minionNum_(kMinionNumMax_),
		meetingPlace_(meetingPlace),
		stoneManager_(stoneManager)
{
	Initialize();
}

MinionManager::~MinionManager()
{
}

void MinionManager::Initialize()
{

	for (size_t i = 0; i < kMinionNumMax_; ++i) {
		minions_[i] = std::make_unique<Minion>(this);
	}

}

void MinionManager::Update()
{

	minionNum_ = 0;
	for (size_t i = 0; i < kMinionNumMax_; ++i) {
		minions_[i]->Update();

		if (minions_[i]->GetHp() > 0) {
			++minionNum_;
		}

	}

}
