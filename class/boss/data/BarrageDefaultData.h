#pragma once
#include <Adapter.h>
#include <string>
#include "AttackDefaultData.h"

// 攻撃用構造体 基本的にtimeはsecondとなる
struct BarrageDefaultData {
	AttackDefaultData attackData; // 攻撃パラム
	float fireInterval_ = 1.0f; // 何秒ごとに撃つか
	int maxFireCount_ = 0; // 何発撃つか
	float bulletSpeed_ = 0.0f; // 弾速

	// 共通のパラメータデータ
	void AddValue(const std::string& name, LWP::Utility::JsonIO json) {
		json.BeginGroup(name);
		attackData.AddValue("AttackData", json);
		json.AddValue("FireInterval", &fireInterval_);
		json.AddValue("MaxFireCount", &maxFireCount_);
		json.AddValue("BulletSpeed", &bulletSpeed_);
		json.EndGroup();
	}
};