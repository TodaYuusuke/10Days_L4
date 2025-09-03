#pragma once
#include <unordered_map>
#include <memory>
#include "MinionStateType.h"
#include "IMinionState.h"

/// <summary>
/// 手下の状態のFactory
/// </summary>
class MinionStateFactory
{

public: //メンバ関数
	
	/// <summary>
	/// 状態作成関数
	/// </summary>
	/// <returns>状態一覧</returns>
	static std::unordered_map<MinionStateType, std::unique_ptr<IMinionState>> CreateStates();

};
