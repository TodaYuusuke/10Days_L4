#include "WallManager.h"

WallManager::WallManager()
	:	walls_{},
		hpMax_(0),
		lifeTimeMax_(0)
{

	Initialize();

}

WallManager::~WallManager()
{
}

void WallManager::Initialize()
{

	hpMax_ = 1;
	lifeTimeMax_ = 5.0f;

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
		Wall* wall = new Wall((*points)[i], (*points)[i + 1], hpMax_, lifeTimeMax_);
		walls_.push_back(wall);
	}

}
