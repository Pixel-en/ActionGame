#include "Player.h"
#include "Camera.h"
#include "Field.h"
#include "ImGui/imgui.h"
#include "Goal.h"
#include "PlayScene.h"
#include "Enemy.h"
#include "Clear.h"
#include "bitset"
#include <string>

namespace {
	const float MOVESPEED{ 100 };			//�����X�s�[�h
	const float GRAVITY{ 9.8f / 60.0f };	//�d��
	const int IMAGESIZE{ 48 };				//�摜�T�C�Y
	//const VECTOR LUPOINT{ 1.0f,14.0f };
	//const VECTOR RUPOINT{ 27.0f,14.0f };
	//const VECTOR LDPOINT{ 1.0f,46.0f };
	//const VECTOR RDPOINT{ 27.0f,46.0f };
	const VECTOR LUPOINT{ 11.0f,14.0f };		//����̍��W
	const VECTOR RUPOINT{ 37.0f,14.0f };	//�E��̍��W
	const VECTOR LDPOINT{ 11.0f,46.0f };		//�����̍��W
	const VECTOR RDPOINT{ 37.0f,46.0f };	//�E���̍��W
	const SIZE HITBOXSIZE{ 26,32 };			//�����蔻��̃{�b�N�X�̃T�C�Y
	const float BUFFER{ 0.5f };		//�U����̍d��
	const float JUMPHEIGHT{ IMAGESIZE * 4.0 };
	const VECTOR PCENTER{ 26.0f,32.0f };
}

bool Player::HitAttack(int _x, int _y, SIZE _size)
{
	int x = _x + _size.cx / 2;
	int y = _y + _size.cy / 2;
	
	SIZE BOXSIZE{ 30,30 };
	if (!pRdir_)
		BOXSIZE = { -30,30 };

	int px = transform_.position_.x + PCENTER.x + BOXSIZE.cx / 2;
	int py = transform_.position_.y + PCENTER.y;

	

	//if (pdir_ < 0)
	//	px += IMAGESIZE / 2;
#if 1
	DrawCircle(x, y, 3, GetColor(0, 255, 255), false);	//���S
	DrawBox(_x, _y, _x + _size.cx, _y + _size.cy, GetColor(111, 111, 255), false);
	DrawBox(px - BOXSIZE.cx / 2, py - BOXSIZE.cy / 2, px + BOXSIZE.cx / 2, py + BOXSIZE.cy / 2, GetColor(255, 111, 111), false);
#endif

	if (abs(x - px) < _size.cx / 2 + abs(BOXSIZE.cx) / 2 &&
		abs(y - py) < _size.cy / 2 + BOXSIZE.cy / 2)
		return true;

	return false;
}

Player::Player(GameObject* parent)
	:GameObject(parent, "Player"), hImage_(-1), attackon_(false), pRdir_(true), framecnt_(0), animframe_(0),attackbuffer_(false),bufferTime_(BUFFER),
	onjump_(false), flagon_(false), animtype_(IDOL),FCmax_(0),AFmax_(0),BEanimtype_(NONE),Gaccel_(0.0f)
{
	hitobj_ = new HitObject(LUPOINT, RUPOINT, LDPOINT, RDPOINT, this);
}

Player::~Player()
{
	if (hitobj_ == nullptr)
		delete hitobj_;
}

void Player::Initialize()
{
	hImage_ = LoadGraph("Assets\\Image\\Player.png");
	assert(hImage_ > 0);
}

void Player::Update()
{


	PlayScene* pc = dynamic_cast<PlayScene*>(GetParent());

	if (animtype_ == Animation::DEATH) {
		if (animframe_ == 5) {
			FCmax_ = 120;
			if (framecnt_ == 120) {
				pc->DeadState();
				KillMe();
			}
		}
		//MessageBox(NULL, "test", NULL, MB_OK);
	}
	else {
		//------�A�C�h����Ԃ̃A�j���[�V����-----
		animtype_ = Animation::IDOL;
		FCmax_ = 20;
		AFmax_ = 4;
		onjump_ = true;
	}

	Field* field = GetParent()->FindGameObject<Field>();
	Clear* clear = GetParent()->FindGameObject<Clear>();

	if (clear->GetFlag())
		flagon_ = false;

	if (transform_.position_.y < 0)
		transform_.position_.y = 0;

	//�d�͉���
	Gaccel_ += GRAVITY;
	transform_.position_.y += Gaccel_;


	if (hitobj_->DownCollisionCheck()) {
		Gaccel_ = 0.0f;
		onjump_ = false;
	}



	if (transform_.position_.y > 1000.0f) {
		transform_.position_.y = 1000.0f;
		pc->DeadState();
	}

	if (!pc->CanMove())
		return;


	if (!flagon_&&!attackon_&&animtype_!=Animation::DEATH) {
		//�E�ړ�
		if (CheckHitKey(KEY_INPUT_D)) {
			AFmax_ = 6;
			if (CheckHitKey(KEY_INPUT_LSHIFT)) {
				transform_.position_.x += MOVESPEED * 2 * Time::DeltaTime();
				animtype_ = Animation::RUN;
				FCmax_ = 11;
			}
			else {
				transform_.position_.x += MOVESPEED * Time::DeltaTime();
				animtype_ = Animation::WALK;
				FCmax_ = 17;
			}
			//�E�������蔻��
			hitobj_->RightCollisionCheck();
			pRdir_ = true;

		}

		//���ړ�
		if (CheckHitKey(KEY_INPUT_A)) {
			AFmax_ = 6;

			if (CheckHitKey(KEY_INPUT_LSHIFT)) {
				transform_.position_.x -= MOVESPEED * Time::DeltaTime() * 2.0;
				animtype_ = RUN;
				FCmax_ = 11;
			}
			else {
				transform_.position_.x -= MOVESPEED * Time::DeltaTime();
				
				animtype_ = WALK;
				FCmax_ = 17;
			}

			//���������蔻��
			hitobj_->LeftCollisionCheck();
			pRdir_ = false;
			
		}

		if (CheckHitKey(KEY_INPUT_W)) {
			if (field->CollisionObjectCheck(transform_.position_.x + PCENTER.x, transform_.position_.y + 46.0f)) {
				animtype_ = Animation::CLIMB;
				FCmax_ = 17;
				AFmax_ = 6;
				
				Gaccel_ = 0.0;

				transform_.position_.y -= MOVESPEED * Time::DeltaTime();
				onjump_ = true;
			}
		}

		//�W�����v(���������킩���)
		if (CheckHitKey(KEY_INPUT_SPACE) && !onjump_) {
			onjump_ = true;
			Gaccel_ = -sqrtf(2 * GRAVITY * JUMPHEIGHT);
		}

		if (onjump_) {
			short cflag = hitobj_->SelectCollisionCheck(0b0111);
			//���������ƓV��X���C�h���ł���
			if (cflag & 0b0100)
				Gaccel_ = 0;
		}

		if (CheckHitKey(KEY_INPUT_J) && !attackbuffer_&&!attackon_) {
			attackon_ = true;
		}
	}

	//�U����
	if (attackon_) {
		animtype_ = Animation::ATTACK;
		FCmax_ = 8;
		AFmax_ = 6;

		//�R�t���[������T�t���[���܂ōU������
		std::list<Enemy*> enemies = GetParent()->FindGameObjects<Enemy>();
		if (animframe_ >= 2 && animframe_ <= 4) {
			for (auto& E : enemies) {
				if (HitAttack(E->GetPosition().x, E->GetPosition().y, E->GetImageSize()))
					E->DeadState();
			}
		}

		if (animframe_ >= 5) {
			attackbuffer_ = true;
			attackon_ = false;
		}
	}

	if (attackbuffer_) {
		bufferTime_ -= Time::DeltaTime();
		if (bufferTime_ < 0) {
			attackbuffer_ = false;
			bufferTime_ = BUFFER;
		}
	}


	//�A�j���[�V�����̓���
	if (true) {
		//�O�t���[���ƈႤ�A�j���[�V�����Ȃ�J�E���g���[���ɂ���
		if (BEanimtype_ != animtype_) {
			framecnt_ = 0;
			animframe_ = 0;
		}

		framecnt_++;
		if (framecnt_ > FCmax_) {
			framecnt_ = 0;
			animframe_ = (animframe_ + 1) % AFmax_;
		}
		BEanimtype_ = animtype_;
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

	//���C���o��
	if (pRdir_==true)
		DrawRectGraph(xpos, ypos, 1 * animframe_ * IMAGESIZE, animtype_ * IMAGESIZE, IMAGESIZE, IMAGESIZE, hImage_, true, false);
	else
		DrawRectGraph(xpos, ypos, 1 * animframe_ * IMAGESIZE, animtype_ * IMAGESIZE, IMAGESIZE, IMAGESIZE, hImage_, true, true);

#if 1
	//�f�o�b�O�p�o��

	//�摜�T�C�Y
	DrawBox(xpos, ypos, xpos + IMAGESIZE, ypos + IMAGESIZE, GetColor(255, 0, 255), false);

	//�����蔻��m�F�p
	DrawBox(xpos + LUPOINT.x, ypos + LUPOINT.y, xpos + RDPOINT.x, ypos + RDPOINT.y, GetColor(255, 255, 255), FALSE);


	DrawCircle(xpos, ypos, 3, GetColor(255, 0, 255), true);
	DrawCircle(xpos + RDPOINT.x , ypos + RDPOINT.y, 3, GetColor(255, 0, 0), true);	//�E�@��
	DrawCircle(xpos + LDPOINT.x , ypos + LDPOINT.y, 3, GetColor(0, 255, 0), true);	//���@��
	DrawCircle(xpos + RUPOINT.x, ypos + RUPOINT.y, 3, GetColor(255, 0, 0), true);	//�E�@��
	DrawCircle(xpos + LUPOINT.x, ypos + LUPOINT.y, 3, GetColor(0, 255, 0), true);	//���@��
	//DrawCircle(xpos + RDPOINT.x+pFieldBuffer.x, ypos + RDPOINT.y+pFieldBuffer.y + 1, 3, GetColor(0, 0, 255), true);	//�E���@��
	//DrawCircle(xpos + LDPOINT.x+pFieldBuffer.x, ypos + LDPOINT.y+pFieldBuffer.y + 1, 3, GetColor(0, 0, 255), true); //����	��
	HitCheck(xpos + LUPOINT.x, ypos + LUPOINT.y, HITBOXSIZE);

	DrawCircle(xpos + RDPOINT.x, ypos + LUPOINT.y, 1, GetColor(145, 214, 75), false);

	DrawCircle(xpos + IMAGESIZE / 2+20, ypos + IMAGESIZE / 2, 1, GetColor(148, 241, 111), false);
	DrawCircle(xpos + IMAGESIZE / 2+20, ypos + IMAGESIZE / 2, 10, GetColor(148, 241, 111), false);
	DrawCircle(xpos + PCENTER.x, ypos + 46.0f, 5, GetColor(147, 54, 84), false);
	DrawCircle(transform_.position_.x + PCENTER.x, transform_.position_.y + 45.0f, 5, GetColor(145, 48, 241), true);
	HitAttack(xpos, ypos, HITBOXSIZE);
#endif
}

void Player::Release()
{
}

bool Player::HitCheck(int _x, int _y, SIZE _size)
{
	int x = _x + _size.cx / 2;
	int y = _y + _size.cy / 2;


	int px = transform_.position_.x + LUPOINT.x + HITBOXSIZE.cx / 2;
	int py = transform_.position_.y + LUPOINT.y + HITBOXSIZE.cy / 2;

	DrawCircle(x, y, 3, GetColor(0, 255, 255), false);	//���S

	if (abs(x - px) < _size.cx / 2 + HITBOXSIZE.cx / 2 &&
		abs(y - py) < _size.cy / 2 + HITBOXSIZE.cy / 2)
		return true;



	return false;
}

XMFLOAT3 Player::GetHitBoxPosition()
{
	return { transform_.position_.x + LUPOINT.x, transform_.position_.y + LUPOINT.y, 0 };
}

void Player::DeadState()
{
	animtype_ = Animation::DEATH;
	FCmax_ = 20;
	AFmax_ = 6;
	framecnt_ = 0;
	animframe_ = 0;
}
