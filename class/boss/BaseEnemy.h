#pragma once
#include <Adapter.h>
#include <memory>
#include <unordered_map>

#include "BaseEnemySpriteSystem.h"
#include "state/IEnemyState.h"


// 敵キャラクターの基底クラス
class BaseEnemy {
public:
	BaseEnemy();
	virtual ~BaseEnemy() = default;

	/*	初期化処理 かならず継承先でstateの初期化を行う
		stateMap_ = Mapの生成;
		StateUpdate();
		spriteSystem_ = 生成;
	*/ 
	virtual void Initialize() = 0;
	// 更新処理
	virtual void Update() = 0;

	/// <summary>
	/// 状態更新処理
	/// </summary>
	/// <returns>状態が切り替わった際、trueを返す</returns>
	bool StateUpdate();

private:

	/// <summary>
	/// 状態変化
	/// </summary>
	/// <param name="newStateTypeNumber">新しい状態 enumからcastして使用</param>
	void ChangeState(const uint8_t& newStateTypeNumber);

protected:
	// キャラクターの名前 のちに使う（と思う）
	std::string name_ = "unknown";

	// スプライト管理クラス
	std::unique_ptr<BaseEnemySpriteSystem> spriteSystem_;

	// ステータス
	std::unordered_map<uint8_t, std::unique_ptr<IEnemyState>> stateMap_;
	// 現在の状態
	IEnemyState* currentState_ = nullptr;
	// 現在の状態
	uint8_t currentStateType_ = 0u;
	// リクエストされた状態
	uint8_t requestStateType_ = 0u;

};
