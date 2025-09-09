#pragma once
#include "scene/IScene.h"
#include "../player/Drawing.h"
#include "../player/PlayerMouseOperation.h"
#include "../title/TitleMinion.h"

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
	std::unique_ptr<Drawing> drawing_;

	// マウスの操作
	std::unique_ptr<PlayerMouseOperation> playerMouseOperation_;

	// 手下
	std::unique_ptr<TitleMinion> minion_;

};