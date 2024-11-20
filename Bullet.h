#pragma once
#include "Object.h"

enum BULLET_TYPE
{
	FIRE,
};

class Bullet
	: public Object
{
	const int BULLET_ANIMATION{ 4 };
	//int framecnt_{ 0 };

	VECTOR bulletSize_{ 48,48 };
	VECTOR bulletHitBoxSize_{ 32,32 };

	int dir_;
	float speed_;
	int bulletType_;
	XMFLOAT3 originpos_;
	float range_;

	std::string targetName_;

	int damege_;

public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iObjectManager�j
	Bullet(GameObject* parent);

	//�f�X�g���N�^
	~Bullet();


	//������
	void Initialize() override;
	void Set(int _dir, int _type, XMFLOAT3 pos, float range,std::string Name);

	void Reset() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	SIZE GetSize() override;

	VECTOR GetCenter() { return VECTOR{ transform_.position_.x + bulletSize_.x / 2, transform_.position_.y + bulletSize_.y / 2 }; };

	std::string GetTargetName() { return targetName_; };
	Transform GetHitTrans() override;
	void SetDamege(int _damege) {
		if (_damege > 0)
			damege_ = _damege;
		else
			damege_ = 1;
	};
	int GetDamege() { return damege_; };
	VECTOR GetHitBox() override;

	void SetBulletObjectName(std::string Name) { objectName_ = Name; };

};

