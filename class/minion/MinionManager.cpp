#include "MinionManager.h"
#include "MinionGlobalData.h"

MinionManager::MinionManager()
	:	minions_{},
		minionNum_(kMinionNumMax_),
		attackMinionNum_(0),
		meetingPlace_(nullptr),
		stoneManager_(nullptr),
		jsonIO_()
{
	Initialize();
}

MinionManager::MinionManager(MeetingPlace* meetingPlace, StoneManager* stoneManager)
	:	minions_{},
		minionNum_(kMinionNumMax_),
		attackMinionNum_(0),
		meetingPlace_(meetingPlace),
		stoneManager_(stoneManager),
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

	attackMinionNum_ = 0;
	for (size_t i = 0; i < kMinionNumMax_; ++i) {
		if (minions_[i]->GetCurrentStateType() == MinionStateType::Attack) {
			++attackMinionNum_;
		}
	}

	// GUI JSON
	ImGui::Begin("Minion");
	jsonIO_.DebugGUI();
	ImGui::End();

}
