#pragma once
#include <Adapter.h>
#include <stdexcept>

using namespace LWP::Math;

// EnemyTypeのenum
#define Enemy_TYPE_LIST \
    E(NormalBoss)

// ベースとなる引数構造体
struct BaseEnemyData {
public:
	BaseEnemyData() = default;
	virtual ~BaseEnemyData() = default;

	// 安全性のための型チェック
	enum class Type {
#define E(name) name,
		Enemy_TYPE_LIST
#undef E
		kMaxNum
	};
	Type type = Type::kMaxNum;

#pragma region EnumからStringに変換するためだけの関数
public:
	// enumからstringに変換
	static inline const char* ToString(Type type) {
		static const char* names[] = {
	#define E(name) #name,
			Enemy_TYPE_LIST
	#undef E
		};

		size_t index = static_cast<size_t>(type);
		if (index < static_cast<size_t>(Type::kMaxNum)) {
			return names[index];
		}
		return "Unknown";
	}
	// stringからenumに変換
	static inline Type ToType(const std::string& str) {
#define E(name) if (str == #name) return Type::name;
		Enemy_TYPE_LIST
#undef E
			return Type::kMaxNum;
	}

#pragma endregion

	// タイプの確認 絶対にこの関数内で実行を止めたいのでvoid型にしている
	inline void CheckType(Type checkType) const {
		if (type != checkType) {
			// 違った場合エラーを出す
			std::string log = "Type mismatch: Expected " + std::string(ToString(checkType)) + "but got " + std::string(ToString(type));
			throw std::runtime_error(log.c_str());
		}
	};

	// dataの型キャスト
	template <typename T>
	T& Cast() const {
		// 型チェック
		if (this->type != T::kType) {
			std::string log = "Type mismatch: Expected " + std::string(BaseEnemyData::ToString(T::kType)) +
				" but got " + std::string(BaseEnemyData::ToString(this->type));
			throw std::runtime_error(log);
		}

		// 安全にキャスト
		return dynamic_cast<T&>(*this);
	}


	// 共通のパラメータデータ
	void CommonValue(LWP::Utility::JsonIO json) {
		json.AddValue("RespawnPoint", &respawnPoint);
	}

	// 純粋仮想関数
	virtual void AddValue(LWP::Utility::JsonIO json) { json; }

public: // 共通部分変数
	// 構成されているパーツの数
	uint8_t partsNumber = 0u;
	// 初期スポーン
	Vector2 respawnPoint = { 0.0f,0.0f };
};

// 攻撃用構造体 基本的にtimeはsecondとなる
struct AttackDefaultData {
	float startupLag = 0.0f;// 前隙  (予測線から攻撃準備動作が終わるまでの時間)
	float damageTime = 0.0f;// ダメージ時間 (ダメージが与えられる時間)
	float endingLag = 0.0f;// 後隙　(状態が変化するまでの時間)
	// 共通のパラメータデータ
	void AddValue(const std::string& name, LWP::Utility::JsonIO json) {
		json.BeginGroup(name)
			.AddValue("StartUpLag", &startupLag)
			.AddValue("DamageTime", &damageTime)
			.AddValue("EndingLag", &endingLag)
			.EndGroup();
	}
};

// NormalBossのデータ
struct NormalBossData : public BaseEnemyData {
	static constexpr Type kType = Type::NormalBoss;
	NormalBossData() {
		type = kType;
	}
	NormalBossData(const NormalBossData&) = default;
	// 初期生成
	NormalBossData(const Vector2& resP) { 
		type = kType;
		respawnPoint = resP;
	}

	Vector2 idleTime = { 0.0f,0.0f }; // idle時間 { min,max }
	float moveSpeed = 0.0f; // 移動速度
	AttackDefaultData slam; // 叩きつけ攻撃

	void AddValue(LWP::Utility::JsonIO json) override {
		json.BeginGroup("NormalBossData");
		BaseEnemyData::CommonValue(json);
		json.AddValue("idleTime", &idleTime)
			.AddValue("moveSpeed", &moveSpeed);
		slam.AddValue("Slam", json);
		json.EndGroup();
	}

};