#pragma once
#include "scene/IScene.h"
#include "../boss/EnemyManager.h"

class TestScene final
	: public IScene {
public:
	TestScene() = default;
	~TestScene() = default;

	//*** 純粋仮想関数の実体宣言 ***//

	// 初期化
	void Initialize() override;
	// 更新
	void Update() override;


private: //*** これより先に必要な処理や変数を記述 ***//

	LWP::Resource::RigidModel testModel_;
	LWP::Primitive::NormalSprite sprite_;
	
	// 敵統括クラス
	std::unique_ptr<EnemyManager> enemyManager_;
};