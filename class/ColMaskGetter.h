#pragma once

/// <summary>
/// マスク確認
/// </summary>
class ColMaskGetter
{

public: // メンバ関数

	/// <summary>
	/// プレイヤー
	/// </summary>
	static int GetPlayer();

	/// <summary>
	/// エネミー
	/// </summary>
	static int GetEnemy();

	/// <summary>
	/// 壁
	/// </summary>
	/// <returns></returns>
	static int GetWall();

	/// <summary>
	/// 弾
	/// </summary>
	/// <returns></returns>
	static int GetBullet();

};

