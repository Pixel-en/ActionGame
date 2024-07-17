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
	int Uhit = field->CollisionUpCheck(obj_->GetPosition().x + Ru_.x,
		obj_->GetPosition().y + Ru_.y);
	int Dhit = field->CollisionUpCheck(obj_->GetPosition().x + Rd_.x,
		obj_->GetPosition().y + Rd_.y);
	int push = max(Uhit, Dhit);
	if (push >= 1) {
		float val = obj_->GetPosition().x - push;
		obj_->SetPositionX(val);
		return true;
	}
	return false;
}

bool HitObject::LeftCollisionCheck()
{
	//int Uhit = field->CollisionUpCheck(obj_->GetPosition().x + Lu_.x,
	//	obj_->GetPosition().y + Lu_.y);
	//int Dhit = field->CollisionUpCheck(obj_->GetPosition().x + Ld_.x,
	//	obj_->GetPosition().y + Ld_.y);
	//int push = max(Uhit, Dhit);
	//if (push >= 1) {
	//	float val = obj_->GetPosition().x + push;
	//	obj_->SetPositionX(val);
	//	return true;
	//}
	//return false;

	int push = 0;

	//左側当たり判定
	int Lhitx = obj_->GetPosition().x + Ld_.x;
	int Lhity = obj_->GetPosition().y + Ld_.y;
	push = max(field->CollisionRightCheck(Lhitx, Lhity), push);
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

	if (DownCollisionCheck()) { bit |= 0b1000; }
	if (UpCollisionCheck()) { bit |= 0b0100; }
	if (LeftCollisionCheck()) { bit |= 0b0010; }
	if (RightCollisionCheck()) { bit |= 0b0001; }

	return bit;
}

short HitObject::SelectCollisionCheck(short _bit)
{
	if (_bit & 0b1000)
		DownCollisionCheck();

	if (_bit & 0b0100)
		UpCollisionCheck();

	if (_bit & 0b0010)
		LeftCollisionCheck();

	if (_bit & 0b0001)
		RightCollisionCheck();

	return 0;
}
