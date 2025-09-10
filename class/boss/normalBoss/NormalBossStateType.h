#pragma once

enum class NormalBossStateType : uint8_t {
	Idle, // 待機
	Move, // 移動
	Slam, // たたきつけ攻撃
	Barrage, // 弾幕

	StateTypeOfCount // 最大数
};

namespace StateType {

	// enum を uint8_t に変更
	template <typename EnumType>
	constexpr uint8_t ToUInt8(EnumType e) noexcept {
		return static_cast<uint8_t>(e);
	}

	// uint8_t を enum に変更
	template <typename EnumType>
	EnumType FromUInt8(uint8_t value) {
		static_assert(std::is_enum_v<EnumType>, "EnumType must be an enum");
		EnumType e = static_cast<EnumType>(value);
		return e;
	}

}