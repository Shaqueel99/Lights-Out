
#pragma once

namespace MainMenu
{
	void Init(void);
	void Buttons_Init(void);
	void Update(void);

	void Load(void);
	void Unload(void);
	void Render(void);

	void Quit();

	//void EnemyMovement(void);
	//void PlayerMovement(void);

	void SwitchToMainMenu(void);
	void SwitchToLevelSelection(void);
	void SwitchToCreditScreen(void);
	void SwitchToSettings();
	void SwitchToLeaderboard(void);
	void SwitchToUsername(void);
	void SwitchToControl(void);
}

namespace LevelSelection {
	void Init(void);
	void Update(void);
	void Render(void);
	void Unload(void);
}

namespace Options {
	void Init();
	void Update();
	void Render();
	void Unload();
}

namespace Credits {
	void Init();
	void Update();
	void Render();
	void Unload();

	void IncrementOverlay();
	void DecrementOverlay();
}