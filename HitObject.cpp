#include "HitObject.h"

HitObject::HitObject(VECTOR _Lu, VECTOR _Ru, VECTOR _Ld, VECTOR _Rd, GameObject* _obj)
	:Lu_(_Lu), Ru_(_Ru), Ld_(_Ld), Rd_(_Rd), obj_(nullptr)
{
	obj_ = _obj;
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
	//int Uhit = field->CollisionRightCheck(trns.position_.x + Ru_.x,
	//	trns.position_.y + Ru_.y);
	//int Dhit = field->CollisionRightCheck(trns.position_.x + Rd_.x,
	//	trns.position_.y + Rd_.y);
	//int push = max(Uhit, Dhit);
	//if (push >= 1) {
	//	float val = trns.position_.x - push;
	//	obj_->SetPositionX(val);
	//	return true;
	//}
	//return false;

	Transform trns;
	trns.position_ = obj_->GetPosition();

	int push = field->CollisionRightCheck(trns.position_.x + Rd_.x, trns.position_.y + Rd_.y);
	if (push >= 1) {

		trns.position_.x -= push;
		obj_->SetPosition(trns.position_);
		return true;
	}
	return false;
}

bool HitObject::LeftCollisionCheck()
{
	//int Uhit = field->CollisionLeftCheck(trns.position_.x + Lu_.x,
	//	trns.position_.y + Lu_.y);
	//int Dhit = field->CollisionLeftCheck(trns.position_.x + Ld_.x,
	//	trns.position_.y + Ld_.y);
	//int push = max(Uhit, Dhit);
	//if (push >= 1) {
	//	float val = trns.position_.x + push;
	//	obj_->SetPositionX(val);
	//	return true;
	//}
	//return false;

	Transform trns;
	trns.position_ = obj_->GetPosition();
	
	int push = field->CollisionLeftCheck(trns.position_.x + Ld_.x, trns.position_.y + Ld_.y);
	if (push >= 1) {
		trns.position_.x += push;
		obj_->SetPosition(trns.position_);
		return true;
	}
	return false;
}

bool HitObject::UpCollisionCheck()
{	
	Transform trns;
	trns.position_ = obj_->GetPosition();

	int Lhit = field->CollisionUpCheck(trns.position_.x + Lu_.x,
		trns.position_.y + Lu_.y - 1);
	int Rhit = field->CollisionUpCheck(trns.position_.x + Ru_.x,
		trns.position_.y + Ru_.y - 1);
	int push = max(Lhit, Rhit);
	if (push >= 1) {

		trns.position_.y += push + 1;
		obj_->SetPosition(trns.position_);
		return true;
	}
	return false;
}

bool HitObject::DownCollisionCheck()
{
	Transform trns;
	trns.position_ = obj_->GetPosition();

	int Lhit = field->CollisionDownCheck(trns.position_.x + Ld_.x,
		trns.position_.y + Ld_.y + 1);
	int Rhit = field->CollisionDownCheck(trns.position_.x + Rd_.x,
		trns.position_.y + Rd_.y + 1);
	int push = max(Lhit, Rhit);
	if (push >= 1) {

		trns.position_.y -= push - 1;
		obj_->SetPosition(trns.position_);
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
