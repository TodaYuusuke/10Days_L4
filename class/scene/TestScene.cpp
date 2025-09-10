#include "TestScene.h"
#include "Title.h"

using namespace LWP;
using namespace LWP::Input;

// 初期化
void TestScene::Initialize() {
	testModel_.LoadCube();				// 立方体と球はデフォルトで用意してある
	testModel_.isActive = false;
	sprite_.LoadTexture("uvChecker.png");	// resources/texture直下のパスを指定する
	sprite_.isActive = false;

	
	player_ = std::make_unique<Player>();
	stoneManager_ = std::make_unique<StoneManager>();

	enemyManager_ = std::make_unique<EnemyManager>();

	minionManager_ = std::make_unique<MinionManager>(player_->GetMeetingPlace(), stoneManager_.get(), enemyManager_.get());
	player_->SetMinionManagerForDrawing(minionManager_.get());
	enemyManager_->SetMinionManagerPtr(minionManager_.get());

	uiManager_ = std::make_unique<UIManager>(player_.get(), minionManager_.get(), enemyManager_.get());

	pAOEManager_.Initialize();

	sceneTransitionBlackOut_.Initialize();
	sceneTransitionBlackOut_.SetIsFadeIn(false);

	backGround_.Initialize();

	nextSprite_.Initialize();
	nextSprite_.SetIsActive(false);

}

// 更新
void TestScene::Update() {

	if (!sceneTransitionBlackOut_.GetStoppingUpdates()) {
		sceneTransitionBlackOut_.Update();
		if (sceneTransitionBlackOut_.GetSwitchScene()) {
			nextSceneFunction = []() { return new Title(); };
		}
	}
	else {
		if (minionManager_->GetMinionNum() == 0 || enemyManager_->GetEnemyHp(nullptr) <= 0u) {
			if (player_->GetDrawing()->GetGameStart()) {
				sceneTransitionBlackOut_.Reset();	// 次のシーンに行くための処理
			}
			else {
				nextSprite_.SetIsActive(true);
				nextSprite_.Update();
				player_->SetMinionManagerForDrawing(nullptr);
			}
		}
	}

	minionManager_->Update();
	player_->Update();
	stoneManager_->Update();
	uiManager_->Update();

	enemyManager_->Update();
	enemyManager_->SecondUpdate();

	pAOEManager_.Update();

	// エンジンの各クラスは大体ImGuiを呼び出す関数がある
	ImGui::Begin("Test");
	if (ImGui::TreeNode("model")) {
		testModel_.DebugGUI();
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("sprite")) {
		sprite_.DebugGUI();
		ImGui::TreePop();
	}
	ImGui::End();
}