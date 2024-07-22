#pragma once
#include "Object.h"
#include "Player.h"


class MoveObject :public Object
{
	float sinAngle_;
	float baseY_;
	short ins;
public:

	//コンストラクタ
	//引数：parent  親オブジェクト（ObjectManager）
	MoveObject(GameObject* parent);

	//デストラクタ
	~MoveObject() override;

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	/// <summary>
	/// 足場判定があるかどうが
	/// </summary>
	/// <param name="_Lu">左上の点</param>
	/// <param name="_Ru">右上の点</param>
	/// <param name="_Ld">左下の点</param>
	/// <param name="_Rd">右下の点</param>
	/// <param name="_obj">プレイヤー</param>
	/// <param name="_boxsize">ヒットボックスのサイズ</param>
	/// <returns>当たった4ビット列　左から下、上、左、右</returns>
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

