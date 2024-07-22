#pragma once
#include "Object.h"
#include "Player.h"


class MoveObject :public Object
{
	float sinAngle_;
	float baseY_;
	short ins;
public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iObjectManager�j
	MoveObject(GameObject* parent);

	//�f�X�g���N�^
	~MoveObject() override;

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	/// <summary>
	/// ���ꔻ�肪���邩�ǂ���
	/// </summary>
	/// <param name="_Lu">����̓_</param>
	/// <param name="_Ru">�E��̓_</param>
	/// <param name="_Ld">�����̓_</param>
	/// <param name="_Rd">�E���̓_</param>
	/// <param name="_obj">�v���C���[</param>
	/// <param name="_boxsize">�q�b�g�{�b�N�X�̃T�C�Y</param>
	/// <returns>��������4�r�b�g��@�����牺�A��A���A�E</returns>
	short CollisionCheck(VECTOR _Lu, VECTOR _Ru, VECTOR _Ld, VECTOR _Rd, Player* _obj,SIZE _boxsize);

	void InstantL() { left = Instantiate<Left>(GetParent()); ins |= 0b001; }
	void InstantR() { right = Instantiate<Right>(GetParent()); ins |= 0b010;}
	void InstantC() { center = Instantiate<Center>(GetParent()); ins |= 0b100;}

	void SetLpos(float x, float y) { left->SetPosition(x, y, 0); baseY_ = y; }
	void SetRpos(float x, float y) { right->SetPosition(x, y, 0); baseY_ = y; }
	void SetCpos(float x, float y) { center->SetPosition(x, y, 0);  baseY_ = y; }

private:
	class Left:public Object
	{
	public:
		Left(GameObject* parent);
		~Left();
		void Initialize() override;
		void Update() override;
		void Draw();
		void SetPosY(float y) { transform_.position_.y = y; }
	private:
	};

	class Right :public Object
	{
	public:
		Right(GameObject* parent);
		~Right();
		void Initialize() override;
		void Update() override;
		void Draw();
		void SetPosY(float y) { transform_.position_.y = y; }
	private:

	};

	class Center :public Object
	{
	public:
		Center(GameObject* parent);
		~Center();
		void Initialize() override;
		void Update() override;
		void Draw();
		void SetPosY(float y) { transform_.position_.y = y; }
	private:

	};


	Left* left;
	Right* right;
	Center* center;
};

