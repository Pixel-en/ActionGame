#pragma once
#include "Engine/GameObject.h"

//アルファベットと数字とカタカナと!?が使えるよ
class TitleText :public GameObject
{
	int hImage_;
	int hImageW_;
	int hImageUI_;

	char CharNum(char c);

	std::string fontarr;

public:
	/// <summary>
	/// 文字表示
	/// </summary>
	/// <param name="_text">表示したいテキスト</param>
	/// <param name="_posx">表示する場所のx座標</param>
	/// <param name="_posy">表示する場所のy座標</param>
	void DrawString(std::string _text, float _posx, float _posy);

	/// <summary>
	/// 文字表示
	/// </summary>
	/// <param name="_text">表示したいテキスト</param>
	/// <param name="_posx">表示する場所のx座標</param>
	/// <param name="_posy">表示する場所のy座標</param>
	/// <param name="black">文字の色が黒でいいか falseは白</param>
	void DrawString(std::string _text, float _posx, float _posy,bool black);

	//コンストラクタ
	//引数：parent  親オブジェクト（ObjectManager）
	TitleText(GameObject* parent);

	//デストラクタ
	~TitleText();

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

};

