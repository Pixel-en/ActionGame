#pragma once
#include "Engine//GameObject.h"
class Item :
    public GameObject
{
protected:
	int GraphSizeX;
	int GraphSizeY_;
	int hGraph_;
public:
	Item(GameObject* parent);
	~Item();

	//‰Šú‰»
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Release() override;
private:
};

