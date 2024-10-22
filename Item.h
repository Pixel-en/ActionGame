#pragma once
#include "Engine//GameObject.h"
class Item :
    public GameObject
{
protected:
    int graphSizeX_;
    int graphSizeY_;

	float fGraphSizeX_;
	float fGraphSizeY_;

	int hImage_;
public:
	Item(GameObject* parent);
	~Item();

	//èâä˙âª
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Draw() override;

	float GetfGraphSizeX() { return fGraphSizeX_; }
	float GetfGraphSizeY() { return fGraphSizeY_; }

private:
};

