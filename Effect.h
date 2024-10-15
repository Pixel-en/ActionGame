#pragma once
#include "Object.h"

class Effect
	: public Object
{
	SIZE effectSize;
	bool canLoop_;
public:
	Effect(GameObject* parent);
	~Effect();
	//������
	void Initialize() override;
	//�t�@�C������30�����ȓ�
	void Initialize(Transform pos,std::string _filename, SIZE _size, int _animframe, int _maxframe, bool _canLoop);

	void Reset() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};

