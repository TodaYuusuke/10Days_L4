#pragma once
#include <Adapter.h>
#include <string>

// 攻撃用構造体 基本的にtimeはsecondとなる
struct AttackDefaultData {
	float startupLag = 0.0f;// 前隙  (予測線から攻撃準備動作が終わるまでの時間)
	float damageTime = 0.0f;// ダメージ時間 (ダメージが与えられる時間)
	float endingLag = 0.0f;	// 後隙　(状態が変化するまでの時間)
	int attackPower = 0;	// 攻撃力
	// 共通のパラメータデータ
	void AddValue(const std::string& name, LWP::Utility::JsonIO json) {
		json.BeginGroup(name)
			.AddValue("StartUpLag", &startupLag)
			.AddValue("DamageTime", &damageTime)
			.AddValue("EndingLag", &endingLag)
			.AddValue("AttackPower", &attackPower)
			.EndGroup();
	}
};