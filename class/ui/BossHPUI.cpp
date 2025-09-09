#include "BossHPUI.h"

BossHPUI::BossHPUI()
	:	containerSprite_(),
		gaugeSprite_(),
		enemyManager_(nullptr)
{
	Initialize();
}

BossHPUI::~BossHPUI()
{
}

void BossHPUI::Initialize()
{
	// テクスチャ
	containerSprite_.material.color.R = 100;
	containerSprite_.material.color.G = 100;
	containerSprite_.material.color.B = 100;

	gaugeSprite_.material.color.R = 200;
	gaugeSprite_.material.color.G = 0;
	gaugeSprite_.material.color.B = 0;
	gaugeSprite_.material.color.A = 128;

	// 親子関係
	containerSprite_.worldTF.Parent(&baseWorldTF_);
	gaugeSprite_.worldTF.Parent(&baseWorldTF_);

	containerSprite_.worldTF.scale = { 1000.0f,32.0f,1.0f };
	containerSprite_.anchorPoint = { 0.0f, 0.5f };

	gaugeSprite_.worldTF.scale = { 1000.0f,32.0f,1.0f };
	gaugeSprite_.anchorPoint = { 0.0f, 0.5f };

}

void BossHPUI::Update()
{

	if (!enemyManager_) {
		return;
	}

	// 今のHP
	const float kNowHP = 1.0f;
	// HP最大
	const float kMaxHP = 1.0f;
	gaugeSprite_.worldTF.scale.x = 68.0f * (kNowHP / kMaxHP);

}

void BossHPUI::SetIsActive(bool isActive)
{
	containerSprite_.isActive = isActive;
	gaugeSprite_.isActive = isActive;
}

void BossHPUI::JsonDataRegistration(LWP::Utility::JsonIO* jsonIO)
{

	jsonIO->BeginGroup("BossHPUI").

		BeginGroup("Base").
		AddValue("Positon", &baseWorldTF_.translation).
		AddValue("Size", &baseWorldTF_.scale).
		EndGroup().

		BeginGroup("Container").
		AddValue("Positon", &containerSprite_.worldTF.translation).
		AddValue("Size", &containerSprite_.worldTF.scale).
		EndGroup().

		BeginGroup("Gauge").
		AddValue("Positon", &gaugeSprite_.worldTF.translation).
		AddValue("Size", &gaugeSprite_.worldTF.scale).
		EndGroup().

		EndGroup();

}
