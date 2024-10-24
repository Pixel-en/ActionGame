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

	SIZE bulletSize_{ 48,48 };
	SIZE bulletHitBoxSize_{ 32,32 };

	int dir_;
	float speed_;
	int bulletType_;
	
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iObjectManager�j
	Bullet(GameObject* parent);

	//�f�X�g���N�^
	~Bullet();


	//������
	void Initialize() override;
	void Initialize(int _dir, int _type);

	void Reset() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	SIZE GetSize() override;

	VECTOR GetCenter() { return VECTOR{ transform_.position_.x + bulletSize_.cx / 2, transform_.position_.y + bulletSize_.cy / 2 }; };

};

