#pragma once
#include "../BaseEnemy.h"

enum class NormalBossStateType : uint8_t {
	Idel, // 待機
	Move, // 移動

	StateTypeOfCount // 最大数
};