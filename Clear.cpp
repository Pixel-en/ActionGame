#include "Clear.h"
#include "Player.h"
#include "Goal.h"
#include "Material.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Explosion.h"
#include "CheckPoint.h"
#include "ImGui/imgui.h"
#include "PlaySound.h"

Clear::Clear(GameObject* parent)
	:GameObject(parent,"Clear")
{
	Reset();
}

Clear::~Clear()
{
}

void Clear::Initialize()
{
	Reset();
}

void Clear::Reset()
{
	isgoal_ = false;
	isGetM_ = false;
	isKillE_ = false;
	ischeck_ = false;
	Mcount_ = 0;
	Ecount_ = 0;
	isFlag_ = false;
	
	
}

void Clear::Update()
{
	Player* p = GetParent()->FindGameObject<Player>();
	Goal* g = GetParent()->FindGameObject<Goal>();
	CheckPoint* ch = GetParent()->FindGameObject<CheckPoint>();
	std::list<Material*> m = GetParent()->FindGameObjects<Material>();
	std::list<Enemy*> e = GetParent()->FindGameObjects<Enemy>();
	std::list<Bullet*> b = GetParent()->FindGameObjects<Bullet>();
	std::list<Explosion*> ex = GetParent()->FindGameObjects<Explosion>();

	if (!isgoal_&&p!=nullptr) {
		if (ch != nullptr) {
			if (p->hitobject_->HitObjectANDObject(p->GetHitTrans().position_, p->GetHitBox(), ch->GetPosition(), ch->GetHitBox()) || ischeck_) {
				if (!ischeck_) {
					Playsound* ps = GetParent()->FindGameObject<Playsound>();
					ps->SoundON("Rune");
				}
				ischeck_ = true;
				ch->SetPosition(-100, 100, 0);
			}
		}

		if (g != nullptr) {
			if (p->hitobject_->HitObjectANDObject(p->GetHitTrans().position_, p->GetHitBox(), g->GetPosition(), g->GetHitBox()))
			{
				isgoal_ = true;
				g->KillMe();
			}
		}
		else
			assert(false);

		for (Material* M : m) {
			if (p->hitobject_->HitObjectANDObject(p->GetHitTrans().position_,p->GetHitBox(),M->GetPosition(),M->GetHitBox() )) {
				M->Mining(p->GetMiningTime());
			}
		}

		for (Enemy* E : e) {
			//�G�̍U��(�ڐG)
			if (p->hitobject_->HitObjectANDObject(p->GetHitTrans().position_,p->GetHitBox(),E->GetHitTransPos(), E->GetHitBox()) && !p->IsAnimState(p->DEATH)) {
				p->HitDamage({ E->GetCenterTransPos().x,E->GetCenterTransPos().y });
			}
			//�v���C���[�̍U��
			if (p->PlayerAttackHitCheck(E->GetHitTransPos(),E->GetHitBox())) {
				E->HitDamege(p->GetDamege());
			}
			if (E->EnemyAttackHitCheck(p->GetHitTrans().position_, p->GetHitBox())) {
				p->HitDamage({ E->GetCenterTransPos().x,E->GetCenterTransPos().y });
			}

		}

		for (Bullet* B : b) {
			//�������ƂŒ���
			if (p->hitobject_->HitObjectANDObject(p->GetHitTrans().position_, p->GetHitBox(), B->GetHitTrans().position_, B->GetHitBox()) && !p->IsAnimState(p->DEATH)) {
				if (B->GetTargetName() == "Player") {
					p->HitDamage(B->GetCenter());
					B->KillMe();
				}
			}
			for (Enemy* E : e) {
				if (E->hitobj_->HitObjectANDObject(E->GetHitTransPos(), E->GetHitBox(), B->GetHitTrans().position_, B->GetHitBox())) {
					if (B->GetTargetName() == "Enemy") {
						E->HitDamege(B->GetDamege());
						B->KillMe();
					}
				}
			}
		}
	}

	isFlag_ = isgoal_;

}

void Clear::Draw()
{
}

void Clear::Release()
{
}
