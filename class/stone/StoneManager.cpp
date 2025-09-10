#include "StoneManager.h"
#include "StoneGlobalData.h"
using namespace LWP::Math;

using namespace LWP::Utility;

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

	isCreate_ = false;

	audio_[0].LoadShortPath("stone1.mp3");
	audio_[1].LoadShortPath("stone2.mp3");
	audio_[2].LoadShortPath("stone3.mp3");

}

void StoneManager::Update()
{

	if (isCreate_) {
		int rand = Random::GenerateInt(0,2);
		audio_[rand].Play();
		audio_[rand].SetVolume(0.5f);
	}

	isCreate_ = false;

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
	Vector2 newDirection = direction;

	float angleRad = Random::GenerateFloat(-0.5f, 0.5f);
	float cosA = std::cos(angleRad);
	float sinA = std::sin(angleRad);

	newDirection.x = direction.x * cosA - direction.y * sinA;
	newDirection.y = direction.x * sinA + direction.y * cosA;

	Stone* stone = new Stone(position, newDirection);
	stones_.push_back(stone);

	isCreate_ = true;

}
