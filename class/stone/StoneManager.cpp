#include "StoneManager.h"

StoneManager::StoneManager()
	:	stones_{}
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
}

void StoneManager::Update()
{

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

}

void StoneManager::CreateStone(const LWP::Math::Vector2& position, const LWP::Math::Vector2& direction)
{

	// 作成、登録
	Stone* stone = new Stone(position, direction);
	stones_.push_back(stone);

}
