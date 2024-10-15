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
	//初期化
	void Initialize() override;
	//ファイル名は30文字以内
	void Initialize(Transform pos,std::string _filename, SIZE _size, int _animframe, int _maxframe, bool _canLoop);

	void Reset() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};

