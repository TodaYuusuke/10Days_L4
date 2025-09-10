#pragma once
#include "scene/IScene.h"
#include "../player/Drawing.h"
#include "../player/PlayerMouseOperation.h"
#include "../title/TitleMinion.h"
#include "../sceneTransition/SceneTransitionBlackOut.h"

class Title final
	: public IScene {
public:
	Title() = default;
	~Title() = default;

	//*** 純粋仮想関数の実体宣言 ***//

	// 初期化
	void Initialize() override;
	// 更新
	void Update() override;


private: //*** これより先に必要な処理や変数を記述 ***//

	// タイトルスプライト
	LWP::Primitive::NormalSprite titleSprite_;

	// 線を書く
	Drawing drawing_;

	// マウスの操作
	PlayerMouseOperation playerMouseOperation_;

	// 手下
	TitleMinion minion_;

	SceneTransitionBlackOut sceneTransitionBlackOut_;

};