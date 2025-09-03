#pragma once
#include <Adapter.h>

// 前方宣言
class Minion;

/// <summary>
/// 手下の状態インターフェース
/// </summary>
class IMinionState
{

public: // メンバ関数

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~IMinionState() = default;

	/// <summary>
	/// この状態になる時の処理
	/// </summary>
	/// <param name="minion">手下のポインタ</param>
	virtual void Enter(Minion* minion) = 0;

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="minion"></param>
	virtual void Update(Minion* minion) = 0;

	/// <summary>
	/// この状態でなくなる時の処理
	/// </summary>
	/// <param name="minion"></param>
	virtual void Exit(Minion* minion) = 0;

};


/// <summary>
/// IMinionStateを継承したクラスのみを選択できるテンプレート
/// </summary>
template<class MinionStateT>
concept IsIMinionState = std::is_base_of<IMinionState, MinionStateT>::value;