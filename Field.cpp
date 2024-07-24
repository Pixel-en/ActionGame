#include "Field.h"
#include "Engine/CsvReader.h"
#include "Camera.h"
#include "Goal.h"
#include "Material.h"
#include "Enemy.h"
#include "Player.h"
#include "Clear.h"
#include "CheckPoint.h"
#include "MoveObject.h"

namespace {
	const int IMAGESIZE{ 48 };	//32*1.5
}


Field::Field(GameObject* parent)
	:GameObject(parent, "Field"), hImage_(-1), Map(nullptr), filename("alphamap.csv")
{
}

Field::~Field()
{
}

void Field::Initialize()
{
}

void Field::Reset()
{
	hImage_ = LoadGraph("Assets\\Image\\MapChip\\SwanpTiles1.5.png");
	assert(hImage_ > 0);

	std::string folder = "Assets\\Map\\";
	CsvReader* csv = new CsvReader(folder + filename);

	height = csv->GetLines();
	width = csv->GetColumns(0);
	Map = new int[height * width];

	Clear* c = GetParent()->FindGameObject<Clear>();
	//c->Reset();

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			Map[i * width + j] = csv->GetInt(i, j);
		}
	}


	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			switch (csv->GetInt(i, j))
			{
			case 102: {
				Goal* g = Instantiate<Goal>(GetParent());
				g->SetPosition(j * IMAGESIZE, i * IMAGESIZE, 0);
				g->Reset();
			}
					break;
			case 103: {
				CheckPoint* ch = Instantiate<CheckPoint>(GetParent());
				ch->SetPosition(j * IMAGESIZE, i * IMAGESIZE, 0);
				ch->Reset();
			}
					break;
			case 104: {
				c->AddEcount();
				Enemy* e = Instantiate<Enemy>(GetParent());
				e->SetPosition(j * IMAGESIZE, i * IMAGESIZE, 0);
				e->Reset();
			}
					break;
			case 105: {
				Player* p = GetParent()->FindGameObject<Player>();
				p->SetPosition(j * IMAGESIZE, i * IMAGESIZE, 0);
			}
					break;
			case 106: {

				c->AddMcount();
				Material* m = Instantiate<Material>(GetParent());
				m->SetPosition(j * IMAGESIZE, i * IMAGESIZE, 0);
				m->Reset();
			}
					break;
			case 107: {
				MoveObject* mo = GetParent()->FindGameObject<MoveObject>();
				mo->InstantL();
				mo->SetLpos(j * IMAGESIZE, i * IMAGESIZE);
				break;
			}
			case 108: {
				MoveObject* mo = GetParent()->FindGameObject<MoveObject>();
				mo->InstantC();
				mo->SetCpos(j * IMAGESIZE, i * IMAGESIZE);
				break;
			}
			case 109: {
				MoveObject* mo = GetParent()->FindGameObject<MoveObject>();
				mo->InstantR();
				mo->SetRpos(j * IMAGESIZE, i * IMAGESIZE);
				break;
			}
			default:
				break;
			}

		}
	}

}

void Field::Update()
{
}

void Field::Draw()
{
	int scroll = 0;
	int scrollY = 0;
	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr) {
		scroll = cam->GetValue();
		scrollY = cam->GetValueY();
	}
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			int chipNum = Map[i * width + j];
			DrawRectGraph(j * IMAGESIZE - scroll, i * IMAGESIZE-scrollY, IMAGESIZE * (chipNum % 10), IMAGESIZE * (chipNum / 10), IMAGESIZE, IMAGESIZE, hImage_, true);
		}
	}
}

void Field::Release()
{
}

int Field::CollisionDownCheck(int x, int y)
{
	if (WhatBlock(x, y) == "Wall")
		return y % IMAGESIZE + 1;	//押し戻すため
	return 0;
}

int Field::CollisionUpCheck(int x, int y)
{
	if (WhatBlock(x, y) == "Wall")
		return IMAGESIZE - (y % IMAGESIZE) - 1;
	return 0;
}

int Field::CollisionLeftCheck(int x, int y)
{
	if (WhatBlock(x, y) == "Wall")
		return IMAGESIZE - (x % IMAGESIZE);
	return 0;
}

int Field::CollisionRightCheck(int x, int y)
{
	if (WhatBlock(x, y) == "Wall")
		return x % IMAGESIZE + 1;
	return 0;
}

bool Field::CollisionObjectCheck(int x, int y)
{
	//何かオブジェクトの当たり判定があったらチェックする用

	if (WhatBlock(x, y) == "Ladder")
		return true;

	return false;
}

std::string Field::WhatBlock(int x, int y)
{
	int chipX = x / IMAGESIZE;	//キャラクターとマップのサイズを合わせるため
	int chipY = y / IMAGESIZE;

	if (Map != nullptr) {


		//壁or床など
		switch (Map[chipY * width + chipX])
		{
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
		case 16:
		case 17:
		case 18:
		case 19:
		case 20:
		case 21:
		case 22:
		case 23:
		case 24:
		case 25:
		case 26:
		case 27:
		case 28:
		case 29:
		case 30:
		case 31:
		case 32:
		case 33:
		case 34:
		case 35:
		case 36:
		case 37:
		case 38:
		case 39:
		case 40:
		case 41:
		case 42:
		case 43:
		case 44:
		case 45:
		case 46:
		case 47:
		case 48:
		case 49:
		case 50:
		case 51:
		case 52:
		case 53:
		case 54:
		case 55:
		case 56:
		case 57:
		case 58:
		case 59:
			return "Wall";
			break;
		case 60:
		case 61:
		case 62:
			return "Ladder";
			break;
		default:
			break;
		}
	}

	return "";
}
