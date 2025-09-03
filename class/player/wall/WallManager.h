#pragma once
#include <list>
#include "Wall.h"

/// <summary>
/// �ǂ̊Ǘ���
/// </summary>
class WallManager
{

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	WallManager();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~WallManager();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �ǂ��쐬
	/// </summary>
	/// <param name="points">�_</param>
	void CreateWalls(const std::vector<LWP::Math::Vector2>* points);

private:

	// ��
	std::list<Wall*> walls_;

	// �ǂ�HP�ő�l
	int hpMax_;

	// �ǂ̐������ԍő�l
	float lifeTimeMax_;

};

