#pragma once
namespace SE
{
	namespace SENAME {
		/// <summary>
		/// T�̓^�C�g��,P�͏���,G��Play,R�̓����L���O,C�̓N���A
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
	/// SE�̏�����
	/// </summary>
	void InitSE();

	/// <summary>
	/// SE���Đ�����
	/// </summary>
	/// <param name="_se">�Đ�������SE</param>
	/// <returns>���������� 1 ���s������ 0</returns>
	int PlaySE(SENAME::SEs _se);

	/// <summary>
	/// SE���Đ�����Ă��邩
	/// </summary>
	/// <param name="_se">���ׂ���SE</param>
	/// <returns>�Đ�����Ă����� 1 �Đ�����Ă��Ȃ������� 0</returns>
	int CheckSE(SENAME::SEs _se);

	/// <summary>
	/// SE���~�߂�
	/// </summary>
	/// <param name="_se">�~�߂���SE</param>
	void StopSE(SENAME::SEs _se);

	/// <summary>
	/// SE���~�߂�
	/// </summary>
	void StopSE();

	/// <summary>
	/// SE������������폜
	/// </summary>
	/// <param name="_se">�폜������SE</param>
	void DeleteSE(SENAME::SEs _se);

	/// <summary>
	/// SE������������폜
	/// </summary>
	void DeleteSE();
};

