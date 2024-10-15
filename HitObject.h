#pragma once
#include "Field.h"

/// <summary>
/// �n�`�Ƃ̓����蔻��
/// </summary>
class HitObject
{
	//VECTOR Lu_, Ru_, Ld_, Rd_;
	SIZE size_;
	GameObject* obj_;
	Field* field;
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_Lu">����̓_</param>
	/// <param name="_Ru">�E��̓_</param>
	/// <param name="_Ld">�����̓_</param>
	/// <param name="_Rd">�E���̓_</param>
	/// <param name="_obj">�`�F�b�N�Ώۂ̃I�u�W�F�N�g</param>
	//HitObject(VECTOR _Lu, VECTOR _Ru, VECTOR _Ld, VECTOR _Rd, GameObject* _obj);

	HitObject(SIZE _size, GameObject* _obj);

	//�f�X�g���N�^
	~HitObject();

	/// <summary>
	/// �E���̓����蔻��Ɖ����o��
	/// </summary>
	/// <returns>�������Ă��邩</returns>
	bool RightCollisionCheck();

	/// <summary>
	/// �����̓����蔻��Ɖ����o��
	/// </summary>
	/// <returns>�������Ă��邩</returns>
	bool LeftCollisionCheck();
	
	/// <summary>
	/// �㑤�̓����蔻��Ɖ����o��
	/// </summary>
	/// <returns>�������Ă��邩</returns>
	bool UpCollisionCheck();

	/// <summary>
	/// �����̓����蔻��Ɖ����o��
	/// </summary>
	/// <returns>�������Ă��邩</returns>
	bool DownCollisionCheck();

	/// <summary>
	/// ���ׂĂ̓����蔻��̃`�F�b�N�Ɖ����o���@�����と�����E�̏���
	/// </summary>
	/// <returns>�������Ă��邩��4�r�b�g��</returns>
	short AllCollisionCheck();

	/// <summary>
	/// �r�b�g��Ŏw�肵�������蔻��̃`�F�b�N�Ɖ����o��
	/// </summary>
	/// <param name="_bit">���삵����4�r�b�g��@�����牺�A��A���A�E</param>
	/// <returns>�������Ă��邩��4�r�b�g��</returns>
	short SelectCollisionCheck(short _bit);

};

