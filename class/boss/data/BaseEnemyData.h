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
	T& Cast() {
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
		json.AddValue("TargetPosition", &targetPosition);
	}

	// 純粋仮想関数
	virtual void AddValue(LWP::Utility::JsonIO json) { json; }

public: // 共通部分変数
	// 構成されているパーツの数
	uint8_t partsNumber = 0u;
	// 初期スポーン
	Vector2 respawnPoint = { 0.0f,0.0f };
	// ターゲットとなる座標や向き
	Vector2 targetPosition = { 0.0f,0.0f };
};
