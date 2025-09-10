#pragma once
#include "scene/IScene.h"
#include "../minion/MinionManager.h"
#include "../player/Player.h"
#include "../stone/StoneManager.h"
#include "../ui/UIManager.h"
#include "../boss/EnemyManager.h"
#include "../areaOffEffect/AreaOffEffectManager.h"
#include "../sceneTransition/SceneTransitionBlackOut.h"

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

	std::unique_ptr<MinionManager> minionManager_;
	std::unique_ptr<Player> player_;
	std::unique_ptr<StoneManager> stoneManager_;

	std::unique_ptr<UIManager> uiManager_;

	
	// 敵統括クラス
	std::unique_ptr<EnemyManager> enemyManager_;
	// AOEマネージャー
	AreaOffEffectManager pAOEManager_;

	// シーン遷移
	SceneTransitionBlackOut sceneTransitionBlackOut_;

};