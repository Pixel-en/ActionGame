#include "Clear.h"
#include "Player.h"
#include "Goal.h"
#include "Material.h"
#include "Enemy.h"
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

	if (!isgoal_&&!isGetM_ && !isKillE_&&p!=nullptr) {
		if (ch != nullptr) {
			if (ch->IsHitting() || ischeck_) {
				if (!ischeck_){
					Playsound* ps = GetParent()->FindGameObject<Playsound>();
					ps->SoundON("Rune");
				}
				ischeck_ = true;
				ch->SetPosition(-100, 100, 0);
				if (g != nullptr) {
					if (g->IsHitting())
					{
						Playsound* ps = GetParent()->FindGameObject<Playsound>();
						ps->SoundON("Flag");
						isgoal_ = true;
						g->KillMe();
					}
				}
			}
		}
		for (Material* M : m) {
			if (M->IsHitting()) {
				Playsound* ps = GetParent()->FindGameObject<Playsound>();
				ps->SoundON("Mine");
				M->KillMe();
			}
		}
		for (Enemy* E : e) {
			//‚±‚±‚ ‚Æ‚Å’¼‚·
			if (E->IsHitting() && !p->IsAnimState(p->DEATH)) {
				
				p->HitDamage(E->GetCenter());
			}

		}

		if (m.empty() && Mcount_!=0)
			isGetM_ = true;
		if (e.empty() && Ecount_ != 0)
			isKillE_ = true;
	}

	isFlag_ = isgoal_ || isGetM_ || isKillE_;

}

void Clear::Draw()
{
}

void Clear::Release()
{
}
