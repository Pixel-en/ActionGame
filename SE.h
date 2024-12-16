#pragma once
namespace SE
{
	namespace SENAME {
		/// <summary>
		/// Tはタイトル,Pは準備,GはPlay,Rはランキング,Cはクリア
		/// </summary>
		enum SEs
		{
			T_Choise,
			G_P_Attack,
			G_P_Death,
			G_E_Attack,
			G_E_Death,
			G_Flag,
			G_Ladder,
			G_Mine,
			G_Rune,
			G_Clear,

		};
	};

	/// <summary>
	/// SEの初期化
	/// </summary>
	void InitSE();

	/// <summary>
	/// SEを再生する
	/// </summary>
	/// <param name="_se">再生したいSE</param>
	/// <returns>成功したら 1 失敗したら 0</returns>
	int PlaySE(SENAME::SEs _se);

	/// <summary>
	/// SEが再生されているか
	/// </summary>
	/// <param name="_se">調べたいSE</param>
	/// <returns>再生されていたら 1 再生されていなかったら 0</returns>
	int CheckSE(SENAME::SEs _se);

	/// <summary>
	/// SEを止める
	/// </summary>
	/// <param name="_se">止めたいSE</param>
	void StopSE(SENAME::SEs _se);

	/// <summary>
	/// SEを止める
	/// </summary>
	void StopSE();

	/// <summary>
	/// SEをメモリから削除
	/// </summary>
	/// <param name="_se">削除したいSE</param>
	void DeleteSE(SENAME::SEs _se);

	/// <summary>
	/// SEをメモリから削除
	/// </summary>
	void DeleteSE();
};

