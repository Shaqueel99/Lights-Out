

#pragma once
namespace Gameplay {

	enum GameLevel {
		TUTORIAL = 0
	};

	void Init();
	void Update();
	void Load();
	void Render();
	void Restart();
	void Unload();

	// For player, tiles, enemy
	void EntitiesUpdate(void);
}