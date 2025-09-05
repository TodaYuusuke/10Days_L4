#include "WallManager.h"
#include "../PlayerGlobalData.h"

WallManager::WallManager()
	:	walls_{}
{
	Initialize();
}

WallManager::~WallManager()
{
	// 削除
	for (auto it = walls_.begin(); it != walls_.end();) {
		Wall* wall = *it;
		it = walls_.erase(it);
		delete wall;
	}
}

void WallManager::Initialize()
{

}

void WallManager::Update()
{
	
	// 削除
	for (auto it = walls_.begin(); it != walls_.end();) {
		Wall* wall = *it;
		if (wall->IsDead()) {
			it = walls_.erase(it);
			delete wall;
		}
		else {
			++it;
		}
	}

	// 更新
	for (auto it = walls_.begin(); it != walls_.end(); ++it) {
		Wall* wall = *it;
		wall->Update();
	}

}

void WallManager::CreateWalls(const std::vector<LWP::Math::Vector2>* points)
{

	// 作成、登録
	for (size_t i = 0; i < points->size() - 1; ++i) {
		Wall* wall = new Wall((*points)[i], (*points)[i + 1], PlayerGlobalData::GetWallHpMax(), PlayerGlobalData::GetWallLifeTimeMax());
		walls_.push_back(wall);
	}

}
