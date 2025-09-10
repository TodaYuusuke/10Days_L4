#pragma once
#include <Adapter.h>
#include "../boss/data/AttackDefaultData.h"

using namespace LWP::Math;

// 攻撃予兆エフェクト
class AreaOffEffect {
public:
	AreaOffEffect() = delete;
	AreaOffEffect(const float* alpha, const Vector2& pos, const float& maxRadius, const AttackDefaultData& data);
	~AreaOffEffect() = default;


private: // 構造体やenum
	// 状態
	enum State {
		OuterScaleUp,	// 外枠の移動
		InnerScaleUp,	// 内枠の移動
		FadeOut,		// フェードアウト
		Delete			// 削除
	};

public:
	// 初期化
	void Initialize(const Vector2& pos, const float& maxRadius, const AttackDefaultData& data);
	// 更新
	void Update();

	bool IsAlive() const { return isAlive_; }

private: // ローカル関数
	// stateを変える時の初期化
	void StateInitialize(State type);
	// 外枠の更新
	void OuterScaleUpUpdate();
	// 内枠の更新
	void InnerScaleUpUpdate();
	// フェードアウトの更新
	void FadeOutUpdate();

	/// <summary>
	/// アルファ値を 0～255 の範囲で往復させる 点滅
	/// </summary>
	/// <param name="time">経過時間[秒]</param>
	/// <param name="period">往復にかかる時間（秒）</param>
	/// <returns>アルファ値（0～255）</returns>
	static inline uint8_t GetAlpha(float time, float period) {
		if (period <= 0.0f) return 255u;

		// 周期で正規化 [0,1)
		float t = fmodf(time, period) / period;

		// 三角波: 0 → 1 → 0
		float tri = t < 0.5f ? (t * 2.0f) : (2.0f - t * 2.0f);

		// 0～255 にマッピング
		return static_cast<uint8_t>(tri * 255.0f);
	}

private:
	
	// 外枠
	LWP::Primitive::NormalSprite outerFrame_;
	// 内枠
	LWP::Primitive::NormalSprite innerFrame_;
	// !
	LWP::Primitive::NormalSprite exclamation_;
	// 現在時間のタイマー
	float nowTime_ = 0.0f;
	// 現在の状態
	State state_ = State::OuterScaleUp;
	// 攻撃時間データ
	AttackDefaultData data_;
	// 最大半径
	float maxRadius_ = 0.0f;
	// 外枠の移動から内枠の移動までの比率 (4だった場合 外1:内3) n = 外(n):内(n-1)
	float aroundRate_ = 4.0f;
	// エフェクトが生きているか
	bool isAlive_ = false;
	// 最初のアルファ地
	const float* pFirstAlpha_ = nullptr;
};

