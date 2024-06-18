#include "Field.h"
#include "Engine/CsvReader.h"
#include "Camera.h"
#include "Goal.h"
#include "Material.h"
#include "Enemy.h"
#include "Player.h"

namespace {
	const int IMAGESIZE{ 32 };
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
	hImage_ = LoadGraph("Assets\\Image\\Ground_test.png");
	assert(hImage_ > 0);

	std::string folder = "Assets\\Map\\";
	CsvReader* csv = new CsvReader(folder + filename);

	height = csv->GetLines();
	width = csv->GetColumns(0);
	Map = new int[height * width];

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			Map[i * width + j] = csv->GetInt(i, j);
		}
	}

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			switch (csv->GetInt(i, j))
			{
			case 2:{
				Goal* g = Instantiate<Goal>(GetParent());
				g->SetPosition(j * 32, i * 32, 0);
				g->Reset();
			}
				break;
			case 3: {
				Material* m = Instantiate<Material>(GetParent());
				m->SetPosition(j * 32, i * 32, 0);
				m->Reset();
			}
				break;
			case 4: {
				Enemy* e = Instantiate<Enemy>(GetParent());
				e->SetPosition(j * 32, i * 32, 0);
				e->Reset();
			}
				break;
			case 5: {
				Player* p = GetParent()->FindGameObject<Player>();
				p->SetPosition(j * 32, i * 32, 0);
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
	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr)
		scroll = cam->GetValue();

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (Map[i * width + j] == 1)
				DrawRectGraph(j * IMAGESIZE-scroll, i * IMAGESIZE, 0, 0, 32, 32, hImage_, true);
		}
	}

}

void Field::Release()
{
}

int Field::CollisionDownCheck(int x, int y)
{
	if (IsWallBlock(x, y))
		return y % 32 + 1;	//押し戻すため
	return 0;
}

int Field::CollisionLeftCheck(int x, int y)
{
	if (IsWallBlock(x, y))
		return x % 32 - 1;
	return 0;
}

int Field::CollisionRightCheck(int x, int y)
{
	if (IsWallBlock(x, y))
		return x % 32 + 1;
	return 0;
}

bool Field::IsWallBlock(int x, int y)
{
	int chipX = x / IMAGESIZE;	//キャラクターとマップのサイズを合わせるため
	int chipY = y / IMAGESIZE;

	if (Map != nullptr) {


		//壁or床など
		switch (Map[chipY * width + chipX])
		{
		case 1:
			return true;
		default:
			break;
		}
	}

	return false;
}
