#pragma once
#include <unordered_map>
#include <memory>
#include "MinionStateType.h"
#include "IMinionState.h"

/// <summary>
/// �艺�̏�Ԃ�Factory
/// </summary>
class MinionStateFactory
{

public: //�����o�֐�
	
	/// <summary>
	/// ��ԍ쐬�֐�
	/// </summary>
	/// <returns>��Ԉꗗ</returns>
	static std::unordered_map<MinionStateType, std::unique_ptr<IMinionState>> CreateStates();

};
