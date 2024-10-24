#pragma once
#include"Item.h"
class Crystal_Black :
	public Item
{
public:
	Crystal_Black(GameObject* parent);
	~Crystal_Black();

	//‰Šú‰»
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Release() override;
private:
};