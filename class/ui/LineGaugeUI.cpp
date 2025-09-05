#include "LineGaugeUI.h"
#include "../player/Player.h"

using namespace LWP::Math;
using namespace LWP::Input;

LineGaugeUI::LineGaugeUI()
	:	containerSprite_(),
		gaugeSprite_(),
		player_(nullptr)
{
	Initialize();
}

LineGaugeUI::~LineGaugeUI()
{
}

void LineGaugeUI::Initialize()
{

	// テクスチャ
	containerSprite_.LoadTexture("container.png");
	gaugeSprite_.LoadTexture("gauge.png");

	// 親子関係
	containerSprite_.worldTF.Parent(&baseWorldTF_);
	gaugeSprite_.worldTF.Parent(&baseWorldTF_);

	gaugeSprite_.clipRect.min = { 0.0f,0.0f};
	gaugeSprite_.clipRect.max = { 32.0f,32.0f };

}

void LineGaugeUI::Update()
{

	if (!player_) {
		return;
	}

	const Vector2 kMousePosition = Mouse::GetPosition();
	baseWorldTF_.translation = { kMousePosition.x, kMousePosition.y, baseWorldTF_.translation.z };

}

void LineGaugeUI::SetIsActive(bool isActive)
{
	containerSprite_.isActive = isActive;
	gaugeSprite_.isActive = isActive;
}

void LineGaugeUI::JsonDataRegistration(LWP::Utility::JsonIO* jsonIO)
{

	jsonIO->BeginGroup("LineGauge").

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
