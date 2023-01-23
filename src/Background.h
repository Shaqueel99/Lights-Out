
#pragma once

class Player;

namespace Background {
	void Load();
	void Init();
	void Update();
	void Render(const Player& player);

	// Render loop for the different Gamemode
	void RenderCasual();
	void RenderTimeAttack();

	void Unload();
	void LerpBackgroundColor(void);

	void ObjectsInit();
	void ObjectsLoad();
	void ObjectsUpdate();
	void ObjectsRender();
	void ObjectsUnload();
}