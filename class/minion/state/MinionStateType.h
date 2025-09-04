#pragma once

/// <summary>
/// 手下の状態一覧
/// </summary>
enum class MinionStateType {
	Idle,				// 通常
	Move,				// 移動
	//Attack,			// 攻撃
	//Down,				// ダウン
	//Absorb,			// 吸収
	StateTypeOfCount,	// 数数える用
};