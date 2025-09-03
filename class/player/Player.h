#pragma once
#include <Adapter.h>
#include "MeetingPlace.h"
#include "PlayerMouseOperation.h"

/// <summary>
/// �v���C���[
/// </summary>
class Player
{

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Player();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Player();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

private:
	
	// �}�E�X�̑���
	std::unique_ptr<PlayerMouseOperation> playerMouseOperation_;

	// �W���ꏊ
	std::unique_ptr<MeetingPlace> meetingPlace_;

};

