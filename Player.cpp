#include "Player.h"
#include "Camera.h"
#include "Field.h"
#include "ImGui/imgui.h"
#include "Goal.h"
#include "PlayScene.h"
#include "Enemy.h"

namespace {
	const float MOVESPEED{ 100 };			//�����X�s�[�h
	const float GRAVITY{ 9.8f / 60.0f };	//�d��
	const int IMAGESIZE{ 45 };				//�摜�T�C�Y	��44*����44
	const VECTOR LUPOINT{ 15.0f,4.0f };
	const VECTOR LHITBOX{ 15.0f,44.0f };		//�����̍��W
	const VECTOR RHITBOX{ 35.0f,44.0f };	//�E���̍��W
	const SIZE HITBOXSIZE{ 20,40 };			//�����蔻��̃{�b�N�X�̃T�C�Y
	const int SWORDLENGTH{ 50 };
	const float RIGORTIME{ 2.0f };		//�U����̍d��
}

void Player::TestFunc()
{
	if (CheckHitKey(KEY_INPUT_SPACE))
		transform_.position_.y -= 10.0;
}

Player::Player(GameObject* parent)
	:GameObject(parent, "Player"), hImage_(-1), framecnt_(0), attackon_(false), pdir_(1),rigoron_(false)
{
}

Player::~Player()
{
}

void Player::Initialize()
{
	hImage_ = LoadGraph("Assets\\sprite\\sprite\\10.Attack\\resized_dot_img(3).png");
	assert(hImage_ > 0);
}

void Player::Update()
{

	Field* field = GetParent()->FindGameObject<Field>();

	if (transform_.position_.y < 0)
		transform_.position_.y = 0;

	//�d�͉���
	static float Gaccel = 0;
	Gaccel += GRAVITY;
	transform_.position_.y += Gaccel;

	//���������蔻��
	int DLhit = field->CollisionDownCheck(transform_.position_.x + LHITBOX.x, transform_.position_.y + LHITBOX.y + 1);
	int DRhit = field->CollisionDownCheck(transform_.position_.x + RHITBOX.x, transform_.position_.y + RHITBOX.y + 1);
	int push = max(DLhit, DRhit);
	if (push >= 1) {
		transform_.position_.y -= push - 1;
		Gaccel = 0.0f;
	}

	PlayScene* pc = dynamic_cast<PlayScene*>(GetParent());
	
	if (transform_.position_.y > 1000.0f) {
		transform_.position_.y = 1000.0f;
		pc->DeadState();
	}


	if (!pc->CanMove())
		return;

	TestFunc();

	//�E�ړ�
	if (CheckHitKey(KEY_INPUT_D)) {
		if (CheckHitKey(KEY_INPUT_LSHIFT))
			transform_.position_.x += MOVESPEED * Time::DeltaTime() * 2.0;
		else
			transform_.position_.x += MOVESPEED * Time::DeltaTime();

		//�E�������蔻��
		int Rhitx = transform_.position_.x + RHITBOX.x;
		int Rhity = transform_.position_.y + RHITBOX.y;
		int push = field->CollisionRightCheck(Rhitx, Rhity);
		transform_.position_.x -= push;
		pdir_ = 1.0;
	}
	//���ړ�
	if (CheckHitKey(KEY_INPUT_A)) {
		if (CheckHitKey(KEY_INPUT_LSHIFT))
			transform_.position_.x -= MOVESPEED * Time::DeltaTime() * 2.0;
		else
			transform_.position_.x -= MOVESPEED * Time::DeltaTime();

		//���������蔻��
		int Lhitx = transform_.position_.x + LHITBOX.x;
		int Lhity = transform_.position_.y + LHITBOX.y;
		int push = field->CollisionRightCheck(Lhitx, Lhity);
		transform_.position_.x += push;
		pdir_ = -1.0f;
	}

	if (CheckHitKey(KEY_INPUT_J)&&!attackon_&&!rigoron_) {
		attackon_ = true;
		framecnt_ = 0;
	}

	if (attackon_) {
		framecnt_++;
		if (framecnt_ > 5) {
			attackon_ = false;
			rigoron_ = true;
			rigortimer_ = RIGORTIME;
		}
		if (framecnt_ > 1 && framecnt_ < 5) {	//�U������
			VECTOR b1{ transform_.position_.x + LUPOINT.y + HITBOXSIZE.cy / 2,transform_.position_.y + LUPOINT.y + HITBOXSIZE.cy / 2 - 10.0f };	//���S���W���10.0��
			VECTOR b2{ transform_.position_.x + LUPOINT.x + HITBOXSIZE.cx / 2 + (SWORDLENGTH*pdir_), transform_.position_.y + LUPOINT.y + HITBOXSIZE.cy / 2 + 10.0f };	//���S���W���10.0��
			SIZE boxsize{ fabs(b2.x - b1.x),fabs(b2.y - b1.y) };
			VECTOR boxcen{ b1.x + boxsize.cx / 2,b1.y + boxsize.cy / 2 };

			std::list<Enemy*> enemies = GetParent()->FindGameObjects<Enemy>();

			for (auto& Ene : enemies) {
				float Ex = Ene->GetPosition().x + Ene->GetImageSize().cx / 2;
				float Ey = Ene->GetPosition().y + Ene->GetImageSize().cy / 2;
				if (abs(Ex - boxcen.x) < boxsize.cx / 2.0 + Ene->GetImageSize().cx / 2.0 &&
					abs(Ey - boxcen.y) < boxsize.cy / 2.0 + Ene->GetImageSize().cy / 2.0)
					Ene->KillMe();
			}
		}
	}

	if (rigoron_) {
		rigortimer_ -= Time::DeltaTime();
		if (rigortimer_ < 0)
			rigoron_ = false;
	}

	//�E�Œ�J����
	Camera* cam = GetParent()->FindGameObject<Camera>();
	int x = (int)transform_.position_.x - cam->GetValue();
	if (x > 400) {
		x = 400;
		cam->SetValue(transform_.position_.x - x);
	}
	//���Œ�J����
	else if (x < 200) {

		x = 200;
		cam->SetValue(transform_.position_.x - x);
		if (transform_.position_.x < 0)
			transform_.position_.x = 0;
		if (cam->GetValue() < 0)
			cam->SetValue(0);

	}

}

void Player::Draw()
{
	int xpos = transform_.position_.x;
	int ypos = transform_.position_.y;

	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr)
		xpos -= cam->GetValue();

	DrawRectGraph(xpos, ypos, 0, 0, IMAGESIZE, IMAGESIZE, hImage_, true);
	DrawBox(xpos, ypos, xpos + IMAGESIZE, ypos + IMAGESIZE, GetColor(255, 0, 255), false);

	//�����蔻��m�F�p
	DrawBox(xpos + LUPOINT.x, ypos + LUPOINT.y, xpos + RHITBOX.x, ypos + RHITBOX.y, GetColor(255, 255, 255), FALSE);

	DrawCircle(xpos, ypos, 3, GetColor(255, 0, 255), true);
	DrawCircle(xpos + RHITBOX.x, ypos + RHITBOX.y, 3, GetColor(255, 0, 0), true);	//�E
	DrawCircle(xpos + LHITBOX.x, ypos + LHITBOX.y, 3, GetColor(0, 255, 0), true);	//��
	DrawCircle(xpos + RHITBOX.x, ypos + RHITBOX.y + 1, 3, GetColor(0, 0, 255), true);	//�E��
	DrawCircle(xpos + LHITBOX.x, ypos + LHITBOX.y + 1, 3, GetColor(0, 0, 255), true); //����	
	HitCheck(xpos + LUPOINT.x, ypos + LUPOINT.y, HITBOXSIZE);

	if (attackon_) {
		VECTOR b1{ xpos+ LUPOINT.y + HITBOXSIZE.cy / 2,ypos + LUPOINT.y + HITBOXSIZE.cy / 2 - 10.0f };	//���S���W���10.0��
		VECTOR b2{ xpos + LUPOINT.x + HITBOXSIZE.cx / 2 + (SWORDLENGTH * pdir_), ypos + LUPOINT.y + HITBOXSIZE.cy / 2 + 10.0f };	//���S���W���10.0��
		DrawBox(b1.x, b1.y, b2.x, b2.y, GetColor(255, 255, 152), true);	//���̓����蔻��
	}
}

void Player::Release()
{
}

bool Player::HitCheck(int _x, int _y, SIZE _size)
{
	int x = _x + _size.cx / 2;
	int y = _y + _size.cy / 2;

	int px = transform_.position_.x + IMAGESIZE / 2;
	int py = transform_.position_.y + IMAGESIZE / 2;

	DrawCircle(x, y, 3, GetColor(0, 255, 255), false);	//���S

	if (abs(x - px) < _size.cx / 2 + HITBOXSIZE.cx / 2 &&
		abs(y - py) < _size.cy / 2 + HITBOXSIZE.cy / 2)
		return true;



	return false;
}
