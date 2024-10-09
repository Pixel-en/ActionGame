#include"Player.h"
#include "Camera.h"
#include "Engine/CsvReader.h"
#include <algorithm>

namespace {
	const float MOVESPEED{ 100 };			//�����X�s�[�h
	const float GRAVITY{ 9.8f / 60.0f };	//�d��
	const float IMAGESIZE{ 48 * 1.5 };				//�摜�T�C�Y
	const VECTOR LUPOINT{ 11.0f * 1.5f,14.0f * 1.5f };		//����̍��W
	const VECTOR RUPOINT{ 37.0f * 1.5f,14.0f * 1.5f };	//�E��̍��W
	const VECTOR LDPOINT{ 11.0f * 1.5f,46.0f * 1.5f };		//�����̍��W
	const VECTOR RDPOINT{ 37.0f * 1.5f,46.0f * 1.5f };	//�E���̍��W
	const SIZE HITBOXSIZE{ 26 * 1.5f,32 * 1.5f };			//�����蔻��̃{�b�N�X�̃T�C�Y
	const float BUFFER{ 0.5f };		//�U����̍d��
	const float JUMPHEIGHT{ IMAGESIZE * 4.0 };
	const VECTOR PCENTER{ 26.0f * 1.5f,32.0f * 1.5f };

}

void Player::LoadStates()
{
	enum CSVSTATUS
	{
		STRENGTH=1,
		TECHNIC,
		SPEED,
		HP,
	};

	CsvReader* csv = new CsvReader("Assets\\Status\\PlayerStatus.csv");
	status_.strength_= csv->GetInt(1, CSVSTATUS::STRENGTH);
	status_.technic_ = csv->GetInt(1, CSVSTATUS::TECHNIC);
	status_.speed_ = csv->GetInt(1, CSVSTATUS::SPEED);
	status_.hp_ = csv->GetInt(1, CSVSTATUS::HP);

	for (int i = 4; i < csv->GetLines(); i++) {
		StaCorre_[i-4].strength_ = csv->GetInt(i, CSVSTATUS::STRENGTH);
		StaCorre_[i-4].technic_ = csv->GetInt(i, CSVSTATUS::TECHNIC);
		StaCorre_[i-4].speed_ = csv->GetInt(i, CSVSTATUS::SPEED);
		StaCorre_[i-4].hp_ = csv->GetInt(i, CSVSTATUS::HP);
	}


	status_.strength_ = Clamp(status_.strength_, 1, 5);
	status_.technic_ = Clamp(status_.technic_, 1, 5);
	status_.speed_ = Clamp(status_.speed_, 1, 5);
	status_.hp_ = Clamp(status_.hp_, 1, 5);
	
}

Player::Player(GameObject* parent)
	:GameObject(parent,"Player"),hImage_(0), Gaccel_(0)
{
	//�A�j���[�V�����̏�����
	anim_.animtype_ = Animation::IDOL;
	anim_.BEanimtype_ = Animation::NONE;
	anim_.AFmax_ = 0;
	anim_.animframe_ = 0;
	anim_.AFCmax_ = 0;
	anim_.animframecount_ = 0;
	
	transform_.position_ = { 0,0,0 };
	//std::string str = GetParent()->GetParent()->GetObjectName();

	//�����蔻��̏�����
	hitobject_ = new HitObject(LUPOINT, RUPOINT, LDPOINT, RDPOINT, this);

	LoadStates();
}

Player::~Player()
{
}

void Player::Initialize()
{
	hImage_ = LoadGraph("Assets\\Image\\Player1.5.png");
	assert(hImage_ > 0);
}

void Player::Update()
{


	//�d��
	Gaccel_ += GRAVITY;
	transform_.position_.y += Gaccel_;
	//�n�ʂƂ̓����蔻��
	if (hitobject_->DownCollisionCheck()) {
		Gaccel_ = 0;
	}

	MoveControl();

	CameraScroll();
}

void Player::Draw()
{
	int xpos = transform_.position_.x;
	int ypos = transform_.position_.y;

	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr) {
		xpos -= cam->GetValue();
		ypos -= cam->GetValueY();
	}
	////���C���o��
	////if (pRdir_ == true)
	//	DrawRectGraph(xpos, ypos, animframe_ * IMAGESIZE, animtype_ * IMAGESIZE, IMAGESIZE, IMAGESIZE, hImage_, true, false);/*
	//else
	//	DrawRectGraph(xpos, ypos, animframe_ * IMAGESIZE, animtype_ * IMAGESIZE, IMAGESIZE, IMAGESIZE, hImage_, true, true);*/

	DrawRectGraph(xpos, ypos, anim_.animframe_ * IMAGESIZE, anim_.animtype_ * IMAGESIZE, IMAGESIZE, IMAGESIZE, hImage_, true);
}

void Player::Release()
{
}

bool Player::HitCheck(int _x, int _y, SIZE _size)
{
	return false;
}

XMFLOAT3 Player::GetHitBoxPosition()
{
	return { 0,0,0 };
}

void Player::DeadState()
{
}


void Player::CameraScroll()
{
	//�E�Œ�J����
	Camera* cam = GetParent()->FindGameObject<Camera>();
	int x = (int)transform_.position_.x - cam->GetValue();
	int y = (int)transform_.position_.y - cam->GetValueY();



	if (y > 500) {
		y = 500;
		cam->SetValueY(transform_.position_.y - y);
	}
	else if (y < 100) {

		y = 100;
		cam->SetValueY(transform_.position_.y - y);
		if (transform_.position_.y < 0)
			transform_.position_.y = 0;
		if (cam->GetValueY() < 0)
			cam->SetValueY(0);
	}
	else {
		cam->SetValueY(transform_.position_.y - y);
	}
	if (cam->GetValueY() > 300)
		cam->SetValueY(300);


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

void Player::MoveControl()
{
	float Dash = 1.0f;


	if (CheckHitKey(KEY_INPUT_LSHIFT) || CheckHitKey(KEY_INPUT_RSHIFT))
		Dash = 2.0f;

	//���ړ�
	if (CheckHitKey(KEY_INPUT_A)) {
		transform_.position_.x += -MOVESPEED * StaCorre_[status_.speed_ - 1].speed_ * Dash * Time::DeltaTime();
	}

	//�E�ړ�
	if (CheckHitKey(KEY_INPUT_D)) {
		transform_.position_.x += MOVESPEED * StaCorre_[status_.speed_ - 1].speed_ * Dash * Time::DeltaTime();

	}

	////��ړ�
	//if (CheckHitKey(KEY_INPUT_W)) {

	//	transform_.position_.y = -MOVESPEED * Time::DeltaTime();
	//}

	//if (CheckHitKey(KEY_INPUT_SPACE)) {

	//	transform_.position_.x = -MOVESPEED * Time::DeltaTime();
	//}

}


