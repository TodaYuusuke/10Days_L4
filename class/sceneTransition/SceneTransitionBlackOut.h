#pragma once
#include <Adapter.h>

/// <summary>
/// シーン遷移(暗くなる)
/// </summary>
class SceneTransitionBlackOut
{

public: // メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	SceneTransitionBlackOut();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~SceneTransitionBlackOut();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// リセット
	/// </summary>
	void Reset();

public: // アクセッサ

	/// <summary>
	/// 遷移しているか取得
	/// </summary>
	/// <returns></returns>
	bool GetTransitioning() { return transitioning_; }

	/// <summary>
	/// 遷移しているか設定
	/// </summary>
	/// <returns></returns>
	void SetTransitioning(bool transitioning) { transitioning_ = transitioning; }

	/// <summary>
	/// シーンを切り替えるか取得
	/// </summary>
	/// <returns></returns>
	bool GetSwitchScene() { return switchScene_; }

	/// <summary>
	/// シーンを切り替えるか設定
	/// </summary>
	/// <param name="switchScene"></param>
	void SetSwitchScene(bool switchScene) { switchScene_ = switchScene; }

	/// <summary>
	/// 更新を停止する取得
	/// </summary>
	/// <returns></returns>
	bool GetStoppingUpdates() { return stoppingUpdates_; }

	/// <summary>
	/// 更新を停止する設定
	/// </summary>
	/// <param name="stoppingUpdates"></param>
	void SetStoppingUpdates(bool stoppingUpdates) { stoppingUpdates_ = stoppingUpdates; }

	/// <summary>
	/// フェードインか設定
	/// </summary>
	/// <param name="isFadeIn"></param>
	void SetIsFadeIn(bool isFadeIn) { isFadeIn_ = isFadeIn; }

protected: // メンバ変数

	// フェード時間
	float fadeInTime_; //フェードインタイム
	float fadeOutTime_; //フェードアウトタイム
	float fadeTimer_; // タイマー

	bool transitioning_; //遷移しているか
	bool isFadeIn_; // フェードインか
	bool switchScene_; //シーンを切り替えるか

	bool stoppingUpdates_; // 更新を停止する

	LWP::Primitive::NormalSprite sprite_; // スプライト

};

