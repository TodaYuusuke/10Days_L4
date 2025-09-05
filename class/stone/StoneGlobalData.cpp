#include "StoneGlobalData.h"

// 加速度
float StoneGlobalData::acceleration_ = -0.2f;
// 初速
float StoneGlobalData::initialSpeed_ = 10.0f;
// Z座標
float StoneGlobalData::positionZ_ = 0.0f;
// スプライトの大きさ	
LWP::Math::Vector3 StoneGlobalData::spriteScale_ = { 1.0f,1.0f,1.0f };

void StoneGlobalData::JsonDataRegistration(LWP::Utility::JsonIO* jsonIO)
{

		// 加速度
	jsonIO->AddValue("Acceleration", &acceleration_).
		// 初速
		AddValue("InitialSpeed", &initialSpeed_).
		// Z座標
		AddValue("PositionZ", &positionZ_).
		// スプライトの大きさ
		AddValue("SpriteScale", &spriteScale_);

}
