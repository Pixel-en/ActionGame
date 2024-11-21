#include "Clear.h"
#include "Player.h"
#include "Goal.h"
#include "Material.h"
#include "Enemy.h"
#include "Bullet.h"
#include "CheckPoint.h"
#include "ImGui/imgui.h"
#include "PlaySound.h"
#include "TestOpenObject.h"
#include "OutText.h"
#include "ScoreAndTimeAndMap.h"

namespace {
	const int MATERIALBONUS{ 100 };
	const int ENEMYBONUS{ 100 };
}

void Clear::BonusScore()
{
	if (Mcount_ != 0 && isGetM_&&!isBonusMaterial_) {
		ScoreAndTimeAndMap::AddScore(MATERIALBONUS);
		isBonusMaterial_ = true;
	}
	if (Ecount_ != 0 && isKillE_&&!isBonusEnemy_) {
		ScoreAndTimeAndMap::AddScore(ENEMYBONUS);
		isBonusEnemy_ = true;
	}
}

Clear::Clear(GameObject* parent)
	:GameObject(parent, "Clear")
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
	Mcount_ = 0;
	Ecount_ = 0;
	isFlag_ = false;
	isBonusEnemy_ = false;
	isBonusMaterial_ = false;

}

void Clear::Update()
{
	Player* p = GetParent()->FindGameObject<Player>();
	Goal* g = GetParent()->FindGameObject<Goal>();
	std::list<CheckPoint*> ch = GetParent()->FindGameObjects<CheckPoint>();
	std::list<Material*> m = GetParent()->FindGameObjects<Material>();
	std::list<Enemy*> e = GetParent()->FindGameObjects<Enemy>();
	std::list<Bullet*> b = GetParent()->FindGameObjects<Bullet>();
	std::list<OpenObject*> open = GetParent()->FindGameObjects<OpenObject>();
	if (open.size() <= 0)
		exit(0);
	if (!isgoal_ && p != nullptr) {
		for (CheckPoint* che : ch) {
			if (p->hitobject_->HitObjectANDObject(p->GetHitTrans().position_, p->GetHitBox(), che->GetPosition(), che->GetHitBox())) {
				che->AddScore();
				che->KillMe();
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

		for (OpenObject* o : open) {
			if (p->PlayerAttackHitCheck(o->GetHitTransPos(), o->GetHitBox())) {
				o->Open();
			}
		}

		for (Material* M : m) {
			if (p->hitobject_->HitObjectANDObject(p->GetHitTrans().position_, p->GetHitBox(), M->GetPosition(), M->GetHitBox())) {
				M->Mining(p->GetMiningTime());
			}
		}

		for (Enemy* E : e) {
			//“G‚ÌUŒ‚(ÚG)
			if (p->hitobject_->HitObjectANDObject(p->GetHitTrans().position_, p->GetHitBox(), E->GetHitTransPos(), E->GetHitBox()) && !p->IsAnimState(p->DEATH)) {
				p->HitDamage({ E->GetCenterTransPos().x,E->GetCenterTransPos().y });
			}
			//ƒvƒŒƒCƒ„[‚ÌUŒ‚
			if (p->PlayerAttackHitCheck(E->GetHitTransPos(), E->GetHitBox())) {
				E->HitDamege(p->GetDamege());
			}
			if (E->EnemyAttackHitCheck(p->GetHitTrans().position_, p->GetHitBox())) {
				p->HitDamage({ E->GetCenterTransPos().x,E->GetCenterTransPos().y });
			}

		}

		for (Bullet* B : b) {
			//‚±‚±‚ ‚Æ‚Å’¼‚·
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
						Effect* e = Instantiate<Effect>(GetParent());
						e->Reset(B->GetHitTrans(), e->HIT);
						e->SetEffectObjectName("BHitEffect");
						B->KillMe();
					}
				}
			}
		}
	}

	isFlag_ = isgoal_;

	if (m.empty())
		isGetM_ = true;
	if (e.empty())
		isKillE_ = true;
	BonusScore();

}

void Clear::Draw()
{
}

void Clear::Release()
{
}
