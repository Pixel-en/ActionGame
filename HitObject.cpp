#include "HitObject.h"
#include "MoveObject.h"

HitObject::HitObject(VECTOR _Lu, VECTOR _Ru, VECTOR _Ld, VECTOR _Rd, GameObject* _obj)
	:Lu_(_Lu), Ru_(_Ru), Ld_(_Ld), Rd_(_Rd), obj_(nullptr)
{
	trans_.position_ = { -1,-1,-1 };
	obj_ = _obj;
	field = obj_->GetParent()->FindGameObject<Field>();
	size_ = { -1,-1 };
	if (field == nullptr) {
		MessageBox(NULL, "Fieldオブジェクトが見つかりません", "HitObjectより", MB_OK);
		assert(false);
	}
}

HitObject::HitObject(SIZE _size, GameObject* _obj)
	:obj_(nullptr), Lu_({ -1,-1 }), Ru_({ -1,-1 }), Ld_({ -1,-1 }), Rd_({ -1,-1 })
{
	trans_.position_ = {-1,-1,-1};
	size_.x = _size.cx;
	size_.y = _size.cy;
	obj_ = _obj;
	field = obj_->GetParent()->FindGameObject<Field>();
	if (field == nullptr) {
		MessageBox(NULL, "Fieldオブジェクトが見つかりません", "HitObjectより", MB_OK);
		assert(false);
	}
}

HitObject::HitObject(VECTOR _size, GameObject* _obj)
	:obj_(nullptr), Lu_({ -1,-1 }), Ru_({ -1,-1 }), Ld_({ -1,-1 }), Rd_({ -1,-1 })
{
	trans_.position_ = { -1,-1,-1 };
	size_.x = _size.x;
	size_.y = _size.y;
	obj_ = _obj;
	field = obj_->GetParent()->FindGameObject<Field>();
	if (field == nullptr) {
		MessageBox(NULL, "Fieldオブジェクトが見つかりません", "HitObjectより", MB_OK);
		assert(false);
	}
}

HitObject::HitObject(Transform trans,VECTOR _size, GameObject* _obj)
	:size_(_size), obj_(nullptr), Lu_({ -1,-1 }), Ru_({ -1,-1 }), Ld_({ -1,-1 }), Rd_({ -1,-1 })
{
	obj_ = _obj;
	trans_ = trans;
	field = obj_->GetParent()->FindGameObject<Field>();
	if (field == nullptr) {
		MessageBox(NULL, "Fieldオブジェクトが見つかりません", "HitObjectより", MB_OK);
		assert(false);
	}
}

HitObject::HitObject(Transform trans, SIZE _size, GameObject* _obj)
	: obj_(nullptr), Lu_({ -1,-1 }), Ru_({ -1,-1 }), Ld_({ -1,-1 }), Rd_({ -1,-1 })
{
	obj_ = _obj;
	size_.x = _size.cx;
	size_.y = _size.cy;
	trans_ = trans;
	field = obj_->GetParent()->FindGameObject<Field>();
	if (field == nullptr) {
		MessageBox(NULL, "Fieldオブジェクトが見つかりません", "HitObjectより", MB_OK);
		assert(false);
	}
}


HitObject::~HitObject()
{
}

bool HitObject::RightCollisionCheck()
{

	Transform trns;

	if (trans_.position_.x < 0)
		trns.position_ = obj_->GetPosition();
	else
		trns = trans_;
	int push;
	if (size_.x > 0)
		push = field->CollisionRightCheck(trns.position_.x + size_.x, trns.position_.y + size_.y);
	else
		push = field->CollisionRightCheck(trns.position_.x + Rd_.x, trns.position_.y + Rd_.y);

	if (push >= 1) {

		trns.position_.x -= push;
		if (trans_.position_.x < 0)
			obj_->SetPosition(trns.position_);
		else
			trans_ = trns;
		return true;
	}
	return false;
}

bool HitObject::LeftCollisionCheck()
{

	Transform trns;
	if (trans_.position_.x < 0)
		trns.position_ = obj_->GetPosition();
	else
		trns = trans_;

	int push;
	if (size_.x > 0)
		push = field->CollisionLeftCheck(trns.position_.x - size_.x, trns.position_.y + size_.y);
	else
		push = field->CollisionLeftCheck(trns.position_.x + Ld_.x, trns.position_.y + Ld_.y);

	if (push >= 1) {
		trns.position_.x += push;
		if (trans_.position_.x < 0)
			obj_->SetPosition(trns.position_);
		else
			trans_ = trns;
		return true;
	}
	return false;
}

bool HitObject::UpCollisionCheck()
{
	Transform trns;
	if (trans_.position_.x < 0)
		trns.position_ = obj_->GetPosition();
	else
		trns = trans_;

	int push;

	if (size_.x > 0) {
		int Lhit = field->CollisionUpCheck(trns.position_.x - size_.x,
			trns.position_.y - size_.y - 1);
		int Rhit = field->CollisionUpCheck(trns.position_.x + size_.x,
			trns.position_.y - size_.y - 1);
		push = max(Lhit, Rhit);
	}
	else {
		int Lhit = field->CollisionUpCheck(trns.position_.x + Lu_.x,
			trns.position_.y + Lu_.y - 1);
		int Rhit = field->CollisionUpCheck(trns.position_.x + Ru_.x,
			trns.position_.y + Ru_.y - 1);
		push = max(Lhit, Rhit);
	}

	if (push >= 1) {

		trns.position_.y += push + 1;
		if (trans_.position_.x < 0)
			obj_->SetPosition(trns.position_);
		else
			trans_ = trns;
		return true;
	}
	return false;
}

bool HitObject::DownCollisionCheck()
{
	Transform trns;
	if (trans_.position_.x < 0)
		trns.position_ = obj_->GetPosition();
	else
		trns = trans_;

	int push;
	if (size_.x > 0) {

		int Lhit = field->CollisionDownCheck(trns.position_.x - size_.x,
			trns.position_.y + size_.y + 1);
		int Rhit = field->CollisionDownCheck(trns.position_.x + size_.x,
			trns.position_.y + size_.y + 1);
		push = max(Lhit, Rhit);
	}
	else {
		int Lhit = field->CollisionDownCheck(trns.position_.x + Ld_.x,
			trns.position_.y + Ld_.y + 1);
		int Rhit = field->CollisionDownCheck(trns.position_.x + Rd_.x,
			trns.position_.y + Rd_.y + 1);
		push = max(Lhit, Rhit);
	}

	if (push >= 1) {

		trns.position_.y -= push - 1;
		if (trans_.position_.x < 0)
			obj_->SetPosition(trns.position_);
		else
			trans_ = trns;
		return true;
	}
	return false;
}

short HitObject::AllCollisionCheck()
{
	short bit = 0b0000;
	if (DownCollisionCheck()) { bit |= 0b1000; }
	if (UpCollisionCheck()) { bit |= 0b0100; }
	if (LeftCollisionCheck()) { bit |= 0b0010; }
	if (RightCollisionCheck()) { bit |= 0b0001; }

	return bit;
}

short HitObject::SelectCollisionCheck(short _bit)
{
	short bit = 0b0000;

	if (_bit & 0b1000)
		if (DownCollisionCheck()) { bit |= 0b1000; }

	if (_bit & 0b0100)
		if (UpCollisionCheck()) { bit |= 0b0100; }

	if (_bit & 0b0010)
		if (LeftCollisionCheck()) { bit |= 0b0010; }

	if (_bit & 0b0001)
		if (RightCollisionCheck()) { bit |= 0b0001; }

	return bit;
}

bool HitObject::HitObjectANDObject(XMFLOAT3 _trans1, VECTOR _size1, XMFLOAT3 _trans2, VECTOR _size2)
{

	Transform trans1, trans2;
	trans1.position_ = { _trans1.x + _size1.x / 2.0f,_trans1.y + _size1.y / 2.0f,_trans1.z };
	trans2.position_ = { _trans2.x + _size2.x / 2.0f,_trans2.y + _size2.y / 2.0f,_trans2.z };

	if (fabs(trans1.position_.x - trans2.position_.x) < _size1.x / 2.0f + _size2.x / 2.0f &&
		fabs(trans1.position_.y - trans2.position_.y) < _size1.y / 2.0f + _size2.y / 2.0f)
		return true;

	return false;

}

void HitObject::DrawHitBox(XMFLOAT3 trans)
{
	DrawHitBox(trans,255, 255, 255);
}

void HitObject::DrawHitBox(XMFLOAT3 trans,int Red, int Green, int Blue)
{
	if (size_.x > 0)
		DrawBox(trans.x, trans.y, trans.x + size_.x, trans.y + size_.y, GetColor(Red, Green, Blue), false);
	else
		DrawBox(trans.x + Lu_.x, trans.y + Lu_.y, trans.x + Rd_.x, trans.y + Rd_.y, GetColor(Red, Green, Blue), false);
}