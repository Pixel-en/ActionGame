#pragma once
#include "Item.h"
#include"Engine/GameObject.h"
class CrystalBlack :
    public Item
{
public:
	CrystalBlack(GameObject* parent);
	~CrystalBlack();

	//èâä˙âª
	void Initialize() override;
	void Update() override;
	void Draw() override;

	/*float GetfGraphSizeX() { return fGraphSizeX_; }
	float GetfGraphSizeY() { return fGraphSizeY_; }*/
private:
	/*int graphSizeX_;
	int graphSizeY_;

	float fGraphSizeX_;
	float fGraphSizeY_;

	int hImage_;*/
};

