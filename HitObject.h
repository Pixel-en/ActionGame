#pragma once
#include "Field.h"

/// <summary>
/// �n�`�Ƃ̓����蔻��
/// </summary>
class HitObject
{
	VECTOR Lu_, Ru_, Ld_, Rd_;
	VECTOR size_;
	GameObject* obj_;
	Field* field;

	Transform trans_;
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_Lu">����̓_</param>
	/// <param name="_Ru">�E��̓_</param>
	/// <param name="_Ld">�����̓_</param>
	/// <param name="_Rd">�E���̓_</param>
	/// <param name="_obj">�`�F�b�N�Ώۂ̃I�u�W�F�N�g</param>
	HitObject(VECTOR _Lu, VECTOR _Ru, VECTOR _Ld, VECTOR _Rd, GameObject* _obj);

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_size">�����蔻��̃T�C�Y</param>
	/// <param name="_obj">�I�u�W�F�N�g</param>
	HitObject(SIZE _size, GameObject* _obj);

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_size">�����蔻��̃T�C�Y</param>
	/// <param name="_obj">�I�u�W�F�N�g</param>
	HitObject(VECTOR _size, GameObject* _obj);

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="trans">�����蔻��̃q�b�g�{�b�N�X</param>
	/// <param name="_size">�����蔻��̃T�C�Y</param>
	/// <param name="_obj">�I�u�W�F�N�g</param>
	HitObject(Transform& trans,VECTOR _size, GameObject* _obj);

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="trans">�����蔻��̃q�b�g�{�b�N�X</param>
	/// <param name="_size">�����蔻��̃T�C�Y</param>
	/// <param name="_obj">�I�u�W�F�N�g</param>
	HitObject(Transform& trans, SIZE _size, GameObject* _obj);

	//�f�X�g���N�^
	~HitObject();

	/// <summary>
	/// �����蔻��̃q�b�g�{�b�N�X�̃Z�b�g
	/// </summary>
	/// <param name="trans">�����蔻���Transform</param>
	void SetHitTransform(Transform trans) { trans_ = trans; };

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

	/// <summary>
	/// �I�u�W�F�N�g���m�̓����蔻��
	/// </summary>
	/// <param name="_trans1">�Ώ�1��Transform</param>
	/// <param name="_size1">�Ώ�1�̓����蔻��̃{�b�N�X</param>
	/// <param name="_trans2">�Ώ�2��Transform</param>
	/// <param name="_size2">�Ώ�2�̓����蔻��̃{�b�N�X</param>
	/// <returns>�������Ă��邩�ǂ���</returns>
	bool HitObjectANDObject(XMFLOAT3 _trans1,VECTOR _size1, XMFLOAT3 _trans2, VECTOR _size2);

	/// <summary>
	/// �q�b�g�{�b�N�X���o�͂���
	/// </summary>
	/// <param name="trans">�o�͂���trans</param>
	void DrawHitBox(XMFLOAT3 trans);

	/// <summary>
	/// �q�b�g�{�b�N�X��F�w��ŏo�͂���
	/// </summary>
	/// <param name="trans">�o�͂���trans</param>
	/// <param name="Red">��(���255)</param>
	/// <param name="Green">��(���255)</param>
	/// <param name="Blue">��(���255)</param>
	void DrawHitBox(XMFLOAT3 trans,int Red,int Green,int Blue);

};

