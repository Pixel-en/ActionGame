#pragma once
#include "Object.h"

enum EffectType
{
	KILL, GRASS, JUMP,SLASH,MINE, END
};

class Effect
	: public Object
{
	int frame;

	int Image;
	std::string fileName;
	SIZE imageSize;
	int animFrame;
	int maxFrame;
	bool canLoop;

	XMFLOAT3 cameraPos_;
public:
	bool isStart;
	bool isEnd;

	Effect(GameObject* parent);
	~Effect();
	//初期化
	void Initialize() override;
	//ファイル名は30文字以内
	void Initialize(Transform pos, int _effectNumber);

	void Reset() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;
	void Draw(XMFLOAT3 _cameraPos);
	void Draw(int _camX, int _camY);

	//開放
	void Release() override;

	void SetPosition(XMFLOAT3 pos) { transform_.position_ = pos; }

	void SetCameraPos(XMFLOAT3 _cameraPos);
};

