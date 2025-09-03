#pragma once
#include <unordered_map>
#include <memory>
#include "MinionStateType.h"
#include "IMinionState.h"

/// <summary>
/// è‰º‚Ìó‘Ô‚ÌFactory
/// </summary>
class MinionStateFactory
{

public: //ƒƒ“ƒoŠÖ”
	
	/// <summary>
	/// ó‘Ôì¬ŠÖ”
	/// </summary>
	/// <returns>ó‘Ôˆê——</returns>
	static std::unordered_map<MinionStateType, std::unique_ptr<IMinionState>> CreateStates();

};
