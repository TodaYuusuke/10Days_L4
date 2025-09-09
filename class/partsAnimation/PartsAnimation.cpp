#include "PartsAnimation.h"
#include "../boss/normalBoss/NormalBossParts.h"
#include "../boss/data/BaseEnemyData.h"

using namespace LWP::Math;

PartsAnimation::PartsAnimation() {

}

void PartsAnimation::Initialize(LWP::Object::TransformQuat* base) {
    transforms_.resize(EnumCast::ToUInt8(EnemyParts::NormalBossParts::kMaxNum));
    Load();
    transforms_[EnumCast::ToUInt8(EnemyParts::NormalBossParts::Body)].Parent(base);
    // 体を除く
    for (uint8_t index = 1u; index < EnumCast::ToUInt8(EnemyParts::NormalBossParts::kMaxNum); index++) {
        transforms_[index].Parent(&transforms_[EnumCast::ToUInt8(EnemyParts::NormalBossParts::Body)]);
    }
}

void PartsAnimation::Update() {
	// デルタタイム
	float deltaTime = LWP::Info::GetDeltaTimeF();

    ImGui::Begin("Parts");
    json_.DebugGUI();
    ImGui::End();

    // 更新で、Animationのnameをriquestされたらそのデータにのっとってアニメーションさせていく

}

void PartsAnimation::Load() {
    const std::string fileName = "PartsAnimation.json";
    // 初期化とロード
    json_.Init(fileName);
    json_.CheckJsonFile();

    // グループ名の取得
    LWP::Utility::NestedList nameList = LWP::Utility::JsonIO::LoadGroupNames(fileName);

    // グループ名リストが空の場合早期リターン
    if (nameList.empty()) {
        return;
    }

    for (auto itr = nameList.begin(); itr != nameList.end(); ++itr) {
        // NormalBossDataと書かれている場合
        if (itr->name == "NormalBossPartsDefault") {
            // 生成
            json_.BeginGroup("NormalBossPartsDefault")
                .AddValue("Body", &transforms_[EnumCast::ToUInt8(EnemyParts::NormalBossParts::Body)])
                .AddValue("Head", &transforms_[EnumCast::ToUInt8(EnemyParts::NormalBossParts::Head)])
                .AddValue("L_Arm", &transforms_[EnumCast::ToUInt8(EnemyParts::NormalBossParts::L_Arm)])
                .AddValue("R_Arm", &transforms_[EnumCast::ToUInt8(EnemyParts::NormalBossParts::R_Arm)])
                .AddValue("L_Legs", &transforms_[EnumCast::ToUInt8(EnemyParts::NormalBossParts::L_Legs)])
                .AddValue("R_Legs", &transforms_[EnumCast::ToUInt8(EnemyParts::NormalBossParts::R_Legs)])
                .EndGroup();
        }
        // 別の場合
        else if (itr->name == "Unknown") {
            continue;
        }
    }

    json_.Load();
}
