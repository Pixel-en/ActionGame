#pragma once
#include "Engine/GameObject.h"
#include "HitObject.h"

class Object :public GameObject
{
protected:
	int hImage_;

	int framecnt_;	//�t���[���̃J�E���g
	int FCmax_;	//�t���[���J�E���g�̍ő�l
	int animframe_;	//�A�j���[�V�����̃t���[���J�E���g
	int AFmax_;		//�A�j���[�V�����̃t���[����

	SIZE hitsize_;

	HitObject* hitobj_;

public:

	Object(GameObject* parent);
	Object(GameObject* parent, const std::string& name);

	//�f�X�g���N�^
	virtual ~Object();

	//������
 	virtual void Initialize() override;

	virtual void Reset();

	//�X�V
	virtual void Update() override;

	//�`��
	virtual void Draw() override;

	//�J��
	virtual void Release() override;

	virtual int GetImageHandle() { return hImage_; }
	virtual Transform GetHitTrans();
	virtual SIZE GetSize();

	virtual VECTOR GetHitBox();
};

