#pragma once
#include <vector>
#include <Adapter.h>
#include "../particle/DirtSplash.h"
#include "../particle/TracesofDirt.h"

// 前方宣言
class MinionManager;

/// <summary>
/// 書き途中線
/// </summary>
class Drawing
{

public:

	// スプライトの数
	static const size_t kSpriteNum_ = 256;

public: // メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Drawing(); 

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="minionManager">手下のマネージャー</param>
	Drawing(MinionManager* minionManager);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Drawing();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="isDragging">ドラッグ中か</param>
	void Update(bool isDragging);
	/// <summary>
	/// 点の集合をリセットする関数（円判定が計測された後に呼び出される）
	/// </summary>
	void ResetSprites();

public: // アクセッサ

	std::vector<LWP::Math::Vector2>* GetPoints() { return &points_; }
	bool GetWallCreation() const { return wallCreation_; }
	float GetLineLength() const { return lineLength_; }

	void SetMinionManager(MinionManager* minionManager) { minionManager_ = minionManager; }

	void SetStartCheck(bool startCheck) { startCheck_ = startCheck; }

private: // メンバ関数
	
	/// <summary>
	/// スプライト起動
	/// </summary>
	/// <param name="point0">点0</param>
	/// <param name="point1">点1</param>
	void SpriteActive(const LWP::Math::Vector2& point0, const LWP::Math::Vector2& point1);

	/// <summary>
	/// 円が作成されたか
	/// </summary>
	/// <returns>作成されたかどうか</returns>
	void IsCircleCreated();
	/// <summary>
	/// 囲まれた手下の更新
	/// </summary>
	void SurroundedMinionsUpdate();

private: // メンバ変数

	// 点
	std::vector<LWP::Math::Vector2> points_;
	// スプライト
	std::array<LWP::Primitive::NormalSprite, kSpriteNum_> sprites_;
	// スプライト番号
	size_t sprieIndex_;
	// 動いてる
	bool isActive_;
	// 記録タイミングタイマー
	float recordingTimer_;
	// 線の長さ
	float lineLength_;
	// 壁作成フラグ
	bool wallCreation_;
	// 書き始め点
	LWP::Math::Vector2 startWriting_;
	// スタート時フラグ
	bool startCheck_;

	LWP::Resource::Audio audio_[8];

	int audioCount_;

	DirtSplash dirtSplash_;

private: // ポインタ

	// 手下のマネージャー
	MinionManager* minionManager_;

private:

	bool gameStart = false;

public: 

	bool GetGameStart() { return gameStart; }

};

