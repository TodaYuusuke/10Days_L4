#pragma once
#include <Adapter.h>

/// <summary>
/// ベースUI
/// </summary>
class BaseUI
{

public: // メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	BaseUI() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~BaseUI() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Initialize() = 0;

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update() = 0;

	/// <summary>
	/// 全部のisActiveを変更する関数
	/// </summary>
	/// <param name="isActive"></param>
	virtual void SetIsActive(bool isActive) = 0;

	/// <summary>
	/// JSON登録
	/// </summary>
	/// <param name="jsonIO">json</param>
	virtual void JsonDataRegistration(LWP::Utility::JsonIO* jsonIO) = 0;

protected: // メンバ変数

	// 親
	LWP::Object::TransformQuat baseWorldTF_;

};

