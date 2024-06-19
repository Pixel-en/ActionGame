#include "Clear.h"
#include "Player.h"
#include "Goal.h"
#include "Material.h"
#include "Enemy.h"
#include "ImGui/imgui.h"

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
	Mcount_ = 0;
	Ecount_ = 0;
	isFlag_ = false;
}

void Clear::Update()
{
	Player* p = GetParent()->FindGameObject<Player>();
	Goal* g = GetParent()->FindGameObject<Goal>();
	std::list<Material*> m = GetParent()->FindGameObjects<Material>();
	std::list<Enemy*> e = GetParent()->FindGameObjects<Enemy>();

	if (!isgoal_&&!isGetM_ && !isKillE_) {

		if (g != nullptr) {
			if (g->IsHitting())
			{
				isgoal_ = true;
				g->KillMe();
			}
		}
		for (Material* M : m) {
			if (M->IsHitting()) {
				M->KillMe();
			}
		}
		if (m.empty() && Mcount_!=0)
			isGetM_ = true;
		if (e.empty() && Ecount_ != 0)
			isKillE_ = true;
	}

	isFlag_ = isgoal_ || isGetM_ || isKillE_;

	ImGui::Begin("flag");
	int a = isFlag_;
	ImGui::InputInt("flag", &a);
	ImGui::End();

}

void Clear::Draw()
{
}

void Clear::Release()
{
}
