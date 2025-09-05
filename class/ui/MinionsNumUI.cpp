#include "MinionsNumUI.h"
#include "../minion/MinionManager.h"

using namespace LWP::Math;
using namespace LWP::Utility;

MinionsNumUI::MinionsNumUI()
	:	spriteLeftNum_(),
		spriteCenterNum_(),
		spriteRightNum_(),
		spriteMark_(),
		minionManager_()
{
	Initialize();
}

MinionsNumUI::~MinionsNumUI()
{
}

void MinionsNumUI::Initialize()
{

	// テクスチャ
	spriteLeftNum_.LoadTexture("Num.png");
	spriteCenterNum_.LoadTexture("Num.png");
	spriteRightNum_.LoadTexture("Num.png");
	spriteMark_.LoadTexture("MinionNumBack.png");

	// サイズ
	const Vector2 kNumSize = {64.0f,64.0f};
	spriteLeftNum_.SetSplitSize(kNumSize);
	spriteCenterNum_.SetSplitSize(kNumSize);
	spriteRightNum_.SetSplitSize(kNumSize);

	// 色
	spriteLeftNum_.material.color = LWP::Utility::BLACK;
	spriteLeftNum_.material.color.A = 200;
	spriteCenterNum_.material.color = LWP::Utility::BLACK;
	spriteCenterNum_.material.color.A = 200;
	spriteRightNum_.material.color = LWP::Utility::BLACK;
	spriteRightNum_.material.color.A = 200;
	spriteMark_.material.color.A = 200;

	// 親子関係
	spriteLeftNum_.worldTF.Parent(&baseWorldTF_);
	spriteCenterNum_.worldTF.Parent(&baseWorldTF_);
	spriteRightNum_.worldTF.Parent(&baseWorldTF_);
	spriteMark_.worldTF.Parent(&baseWorldTF_);

}

void MinionsNumUI::Update()
{

	if (!minionManager_) {
		return;
	}

	// 数
	const int num = static_cast<int>(minionManager_->GetMinionNum());
	// 数字の設定
	spriteLeftNum_.index = num / 100;
	spriteCenterNum_.index = num / 10;
	spriteRightNum_.index = num;

}

void MinionsNumUI::SetIsActive(bool isActive)
{

	// スプライト 百の位
	spriteLeftNum_.isActive = isActive;
	// スプライト 十の位
	spriteCenterNum_.isActive = isActive;
	// スプライト 一の位
	spriteRightNum_.isActive = isActive;
	// スプライト 手下マーク
	spriteMark_.isActive = isActive;

}

void MinionsNumUI::JsonDataRegistration(LWP::Utility::JsonIO* jsonIO)
{

	jsonIO->BeginGroup("MinionsNum").

		BeginGroup("Base").
		AddValue("Positon", &baseWorldTF_.translation).
		AddValue("Size", &baseWorldTF_.scale).
		EndGroup().

		BeginGroup("LeftNum").
		AddValue("Positon", &spriteLeftNum_.worldTF.translation).
		AddValue("Size", &spriteLeftNum_.worldTF.scale).
		EndGroup().

		BeginGroup("CenterNum").
		AddValue("Positon", &spriteCenterNum_.worldTF.translation).
		AddValue("Size", &spriteCenterNum_.worldTF.scale).
		EndGroup().

		BeginGroup("RightNum").
		AddValue("Positon", &spriteRightNum_.worldTF.translation).
		AddValue("Size", &spriteRightNum_.worldTF.scale).
		EndGroup().

		BeginGroup("Mark").
		AddValue("Positon", &spriteMark_.worldTF.translation).
		AddValue("Size", &spriteMark_.worldTF.scale).
		EndGroup().

		EndGroup();

}

