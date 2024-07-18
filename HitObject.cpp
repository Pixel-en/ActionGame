#include "HitObject.h"

HitObject::HitObject(VECTOR _Lu, VECTOR _Ru, VECTOR _Ld, VECTOR _Rd, GameObject* _obj)
	:Lu_(_Lu),Ru_(_Ru),Ld_(_Ld),Rd_(_Rd),obj_(nullptr)
{
	obj_ = _obj;
	objectName_ = "HitObject";
	field = obj_->GetParent()->FindGameObject<Field>();
	if (field == nullptr)
		MessageBox(NULL, "Fieldオブジェクトが見つかりません", NULL, MB_OK);
}

HitObject::~HitObject()
{
	if (obj_ != nullptr)
		delete obj_;
}

bool HitObject::RightCollisionCheck()
{
	//int Uhit = field->CollisionRightCheck(obj_->GetPosition().x + Ru_.x,
	//	obj_->GetPosition().y + Ru_.y);
	//int Dhit = field->CollisionRightCheck(obj_->GetPosition().x + Rd_.x,
	//	obj_->GetPosition().y + Rd_.y);
	//int push = max(Uhit, Dhit);
	//if (push >= 1) {
	//	float val = obj_->GetPosition().x - push;
	//	obj_->SetPositionX(val);
	//	return true;
	//}
	//return false;

	int push = field->CollisionRightCheck(obj_->GetPosition().x + Rd_.x, obj_->GetPosition().y + Rd_.y);
	if (push >= 1) {
		float val = obj_->GetPosition().x - push;
		obj_->SetPositionX(val);
		return true;
	}
	return false;
}

bool HitObject::LeftCollisionCheck()
{
	//int Uhit = field->CollisionLeftCheck(obj_->GetPosition().x + Lu_.x,
	//	obj_->GetPosition().y + Lu_.y);
	//int Dhit = field->CollisionLeftCheck(obj_->GetPosition().x + Ld_.x,
	//	obj_->GetPosition().y + Ld_.y);
	//int push = max(Uhit, Dhit);
	//if (push >= 1) {
	//	float val = obj_->GetPosition().x + push;
	//	obj_->SetPositionX(val);
	//	return true;
	//}
	//return false;

	int push = field->CollisionLeftCheck(obj_->GetPosition().x + Ld_.x, obj_->GetPosition().y + Ld_.y);
	if (push >= 1) {
		float val = obj_->GetPosition().x + push;
		obj_->SetPositionX(val);
		return true;
	}
	return false;
}

bool HitObject::UpCollisionCheck()
{	
	
	int Lhit = field->CollisionUpCheck(obj_->GetPosition().x + Lu_.x,
		obj_->GetPosition().y + Lu_.y - 1);
	int Rhit = field->CollisionUpCheck(obj_->GetPosition().x + Ru_.x,
		obj_->GetPosition().y + Ru_.y - 1);
	int push = max(Lhit, Rhit);
	if (push >= 1) {
		float val = obj_->GetPosition().y + push + 1;
		obj_->SetPositionY(val);
		return true;
	}
	return false;
}

bool HitObject::DownCollisionCheck()
{

	int Lhit = field->CollisionDownCheck(obj_->GetPosition().x + Ld_.x,
		obj_->GetPosition().y + Ld_.y + 1);
	int Rhit = field->CollisionDownCheck(obj_->GetPosition().x + Rd_.x,
		obj_->GetPosition().y + Rd_.y + 1);
	int push = max(Lhit, Rhit);
	if (push >= 1) {
		float val = obj_->GetPosition().y - push - 1;
		obj_->SetPositionY(val);
		return true;
	}
	return false;
}

short HitObject::AllCollisionCheck()
{
	short bit = 0b0000;
	if (LeftCollisionCheck()) { bit |= 0b0010; }
	if (RightCollisionCheck()) { bit |= 0b0001; }
	if (DownCollisionCheck()) { bit |= 0b1000; }
	if (UpCollisionCheck()) { bit |= 0b0100; }


	return bit;
}

short HitObject::SelectCollisionCheck(short _bit)
{
	short bit=0b0000;

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
