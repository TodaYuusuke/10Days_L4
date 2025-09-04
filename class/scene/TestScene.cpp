#include "TestScene.h"
#include "Title.h"

using namespace LWP;
using namespace LWP::Input;

// 初期化
void TestScene::Initialize() {
	testModel_.LoadCube();				// 立方体と球はデフォルトで用意してある
	sprite_.LoadTexture("uvChecker.png");	// resources/texture直下のパスを指定する

	enemyManager_ = std::make_unique<EnemyManager>();
	enemyManager_->Initialize();
}

// 更新
void TestScene::Update() {
	if (Keyboard::GetTrigger(DIK_P)) {
		nextSceneFunction = []() { return new Title(); };	// 次のシーンに行くための処理
	}

	enemyManager_->Update();
	enemyManager_->SecondUpdate();

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