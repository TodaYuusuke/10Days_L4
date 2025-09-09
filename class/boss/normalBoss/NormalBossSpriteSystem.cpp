#include "NormalBossSpriteSystem.h"
#include "NormalBossParts.h"

const uint32_t kMaxParts = 1u;

NormalBossSpriteSystem::NormalBossSpriteSystem() {
	Initialize();
}

void NormalBossSpriteSystem::Initialize() {
	
	sprites_.resize(EnumCast::ToUInt8(EnemyParts::NormalBossParts::kMaxNum));
	sprites_[EnumCast::ToUInt8(EnemyParts::NormalBossParts::Body)].LoadTexture("parts/body.png");
	sprites_[EnumCast::ToUInt8(EnemyParts::NormalBossParts::Head)].LoadTexture("parts/head.png");
	sprites_[EnumCast::ToUInt8(EnemyParts::NormalBossParts::L_Arm)].LoadTexture("parts/arm.png");
	sprites_[EnumCast::ToUInt8(EnemyParts::NormalBossParts::R_Arm)].LoadTexture("parts/arm.png");
	sprites_[EnumCast::ToUInt8(EnemyParts::NormalBossParts::L_Legs)].LoadTexture("parts/legs.png");
	sprites_[EnumCast::ToUInt8(EnemyParts::NormalBossParts::R_Legs)].LoadTexture("parts/legs.png");
	sprites_[EnumCast::ToUInt8(EnemyParts::NormalBossParts::L_Legs)].worldTF.translation.z = -0.1f;
	sprites_[EnumCast::ToUInt8(EnemyParts::NormalBossParts::R_Legs)].worldTF.translation.z = -0.1f;
	animation_.Initialize(&baseTransform_);
	// とりあえずサイズ分に
	for (auto& sprite : sprites_) {
		sprite.SetSplitSize({ 32.0f,32.0f });
	}

	// 親子関係の代入
	for (uint8_t index = 0u; index < EnumCast::ToUInt8(EnemyParts::NormalBossParts::kMaxNum); index++) {
		LWP::Object::TransformQuat* handle = animation_.GetPartsTransformPtr(index);
		sprites_[index].worldTF.Parent(handle);
	}

}

void NormalBossSpriteSystem::Update(const LWP::Math::Vector2& centerPosition) {
	baseTransform_.translation = { centerPosition.x, centerPosition.y, 0.0f };
	baseTransform_.scale = { 3.0f, 3.0f, 0.0f };
	sprites_[0].material.color = LWP::Utility::ColorPattern::WHITE;
	animation_.Update();
}

void NormalBossSpriteSystem::ColorUpdate() {
	sprites_[0].material.color = LWP::Utility::ColorPattern::RED;
}


