#pragma once
#include "BaseEnemyData.h"
#include "AttackDefaultData.h"
#include "BarrageDefaultData.h"

// NormalBossのデータ
struct NormalBossData : public BaseEnemyData {

	// 弾の最大数 とりあえず100個生成
	static const uint8_t kNormalBossBulletMax = 100;

	static constexpr Type kType = Type::NormalBoss;
	NormalBossData() {
		type = kType;
	}
	NormalBossData(const NormalBossData&) = default;
	// 初期生成
	NormalBossData(const Vector2& resP) {
		type = kType;
		respawnPoint = resP;
	}

	Vector2 idleTime = { 0.0f,0.0f }; // idle時間 { min,max }
	float moveSpeed = 0.0f; // 移動速度
	AttackDefaultData slam; // 叩きつけ攻撃
	BarrageDefaultData straightBarrage; // 弾幕
	BarrageDefaultData rainBarrage; // 弾幕

	void AddValue(LWP::Utility::JsonIO json) override {
		json.BeginGroup("NormalBossData");
		BaseEnemyData::CommonValue(json);
		json.AddValue("idleTime", &idleTime)
			.AddValue("moveSpeed", &moveSpeed);
		slam.AddValue("Slam", json);
		straightBarrage.AddValue("StraightBarrage", json);
		rainBarrage.AddValue("RainBarrage", json);
		json.EndGroup();
	}

};