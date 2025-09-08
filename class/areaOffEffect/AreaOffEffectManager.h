#pragma once
#include <memory>
#include <queue>
#include "AreaOffEffect.h"

// AOEを管理するクラス。シングルトン運用
class AreaOffEffectManager {
public:
	AreaOffEffectManager() = default;
	~AreaOffEffectManager();

	// シングルトンインスタンス
	static AreaOffEffectManager* GetInstance();

private: // 構造体
	// 円での初期化用データ一時保存構造体
	struct CircleInitData {
		Vector2 pos;
		float maxRadius;
		AttackDefaultData data;
	};

public: // 

	// 初期化
	void Initialize();

	// 更新
	void Update();
	
	/// <summary>
	/// 円系エフェクトの生成をリクエストする
	/// </summary>
	/// <param name="pos">中心座標</param>
	/// <param name="maxRadius">最大半径</param>
	/// <param name="data">攻撃に必要な時間データ</param>
	void RequestCreate(const Vector2& pos, const float& maxRadius, const AttackDefaultData& data);

private:
	// データのロード
	void Load();

private:
	// 初期化用データ一時保存用コンテナ
	std::queue<CircleInitData> circleInitDatas_;

	// エフェクトをまとめたコンテナ
	std::vector<std::unique_ptr<AreaOffEffect>> container_;
	// 初期アルファ地
	float firstAlpha_ = 255.0f;

	// json変数
	LWP::Utility::JsonIO json_;
};
