#pragma once
#include "Engine/GameObject.h"

class TitleText :public GameObject
{
	int hImage_;
	int hImageUI_;

	int CharNum(char c);

public:
	/// <summary>
	/// 文字表示
	/// </summary>
	/// <param name="_text">表示したいテキスト</param>
	/// <param name="_posx">表示する場所のx座標</param>
	/// <param name="_posy">表示する場所のy座標</param>
	void DrawString(std::string _text, float _posx, float _posy);

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

