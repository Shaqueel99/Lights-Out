
#include "MainMenu.h"

#include "Image.h"
#include "Constants.h"
#include "Graphics.h"
#include "Utilities.h"
#include "GameStateManager.h"
#include "Button.h"
#include "Utilities.h"
#include "Enemy.h"
#include "Tiles.h"
#include "Player.h"
#include "Particles.h"
#include "LevelSystem.h"
#include "Gameplay.h"
#include "Globals.h"
#include "Background.h"
#include "Control.h"

#include <array>
#include <vector>
#include <cmath>
#include <string>
#include <array>


static std::vector <Image> BgOverlayArr;
static std::vector<Button> MenuBtn, LevelBtn, SettingsBtn;
static std::vector<Enemies> enemy;
static std::vector<Tiles> tiles;
static std::vector<Player> player;
static Graphics::Text Title;
static AEVec2 ScreenMid;

static int count = 0; // For checking CreditScreen overlay.
static float WindowWidth, WindowHeight;
static Color background;
extern LevelSystem LevelSys;






void MainMenu::Init(void)
{
	
	ScreenMid = Utils::GetScreenMiddle();
	MainMenu::Buttons_Init();
	LevelSelection::Init();
	Options::Init();
	UI::QuitInit();
	Control::Init();
	Background::ObjectsInit();
	count = 0;

	const float TileWidth{ 80.0f }, TileHeight{ 100.0f },
				EnemyWidth{ 60.0f }, EnemyHeight{ 60.0f },
				playerWidth{ 50.0f }, playerHeight{ 50.0f };

	const int TilesNum = static_cast<int>(WindowWidth / TileWidth);

	Tiles::AddTileRow(tiles, TileType::Grass, TilesNum + 1, TileWidth, TileHeight, AEVec2{ TileWidth / 2.0f, WindowHeight - TileHeight });
	Enemies::AddNew(enemy, EnemyType::Slime,	AEVec2{ 260.0f, tiles[0].image.pos.y - TileHeight / 2.0f }, EnemyWidth, EnemyHeight);
	Enemies::AddNew(enemy, EnemyType::Bat,		AEVec2{ 520.0f, tiles[0].image.pos.y - TileHeight / 2.0f }, EnemyWidth, EnemyHeight);
	Enemies::AddNew(enemy, EnemyType::Squirrel, AEVec2{ 710.0f, tiles[0].image.pos.y - TileHeight / 2.0f }, EnemyWidth, EnemyHeight);


	player.push_back(Player(Player::playerTex, playerWidth, playerHeight));
	player[0].SetPos(AEVec2Set(playerWidth / 2.0f, tiles[0].image.pos.y - TileHeight - 10.0f));

	background.Set(Color{ 51.0f, 215.0f, 255.0f, 255.0f });

	Title.SetText("LIGHTS OUT");
	Title.SetFontID(fontID::Roboto);
	Title.SetTextColor(Color{ 0.0f, 0.0f, 0.0f, 255.0f });
	Title.SetTextScale(1.0f);
}

void MainMenu::Update(void)
{
	if (AEInputCheckTriggered(AEVK_ESCAPE))
		gamestateNext = GS_QUIT;

	Background::ObjectsUpdate();
	Background::LerpBackgroundColor();


	if (GAMEPLAY_MISC::DISPLAY_QUIT_UI) {
		UI::QuitUpdate();
		return;
	}


	for (int i = 0; i < MenuBtn.size(); ++i) {
		MenuBtn[i].Update();
	}
	static const float RotationRate{ 100.0f };
	player[0].sprite.rotation += RotationRate * g_dt;
	Particles::Update();

}

void MainMenu::Render() {
	Background::ObjectsRender();
	for (int i = 0; i < tiles.size(); ++i) {
		tiles[i].image.Draw_Texture(255.0f);
	}



	Title.Draw_Wrapped(AEVec2Set(ScreenMid.x, ScreenMid.y - WindowHeight / 3.0f));
	Particles::Render();

	if (GAMEPLAY_MISC::DISPLAY_QUIT_UI)
		UI::QuitRender();
	else {
		for (size_t i = 0; i < MenuBtn.size(); ++i) {
			MenuBtn[i].Render();
		}
	
	}
}

void MainMenu::Load(void)
{
	Mesh::PlayerCurr = Mesh::Anim;
	Tiles::LoadTex();
	Enemies::LoadTex();
	Player::LoadTex();
	Background::ObjectsLoad();

	WindowWidth = static_cast<float>(AEGetWindowWidth());
	WindowHeight = static_cast<float>(AEGetWindowHeight());
}

void MainMenu::Unload(void)
{
	Enemies::Unload();
	Tiles::Unload();
	Player::Unload();
	Particles::Unload();
	for (size_t i = 0; i < BgOverlayArr.size(); ++i) {
		BgOverlayArr[i].Free();
	}
	BgOverlayArr.clear();
	enemy.clear();
	MenuBtn.clear();
	player.clear();
	tiles.clear();
	Options::Unload();
	LevelSelection::Unload();
	UI::QuitUnload();

	Background::ObjectsUnload();
	Control::Unload();
}

void MainMenu::Quit(void) {
	Utils::ToggleQuitUI();
}

void MainMenu::Buttons_Init() {

	const float BtnCount{ 3 }, BtnWidth{ 200.0f }, BtnHeight{ 50.0f }, BtntextScale{ 0.7f };
	for (int i = 0; i < BtnCount; ++i) {
		MenuBtn.push_back(Button(ButtonType::Color, BtnWidth, BtnHeight, BtntextScale));

		
			MenuBtn[i].Set_Position(AEVec2Set(ScreenMid.x, ScreenMid.y / 1.3f - BtnHeight + (100 * i)));
		
	

	}
	for (int i = 0; i < MenuBtn.size(); ++i) {
	
			MenuBtn[i].SetBtnType(ButtonType::Texture);
			MenuBtn[i].Load_Texture(FP::BUTTONS::Btn);
			MenuBtn[i].ChangeStateColor(ButtonState::Hovered, Color{ 0.0f, 255.0f, 255.0f, 255.0f });
		


	}
	LevelSys.GetKey() == 1 ? MenuBtn[0].Set_Text("Start") : MenuBtn[0].Set_Text("Play");
	MenuBtn[0].Set_Callback(MainMenu::SwitchToLevelSelection);

	MenuBtn[1].Set_Text("Options");
	MenuBtn[1].Set_Callback(MainMenu::SwitchToSettings);

	MenuBtn[2].Set_Text("Quit");
	MenuBtn[2].Set_Callback(Quit);


	for (int i = 0; i < MenuBtn.size(); ++i) {
		MenuBtn[i].SetFontID(fontID::Roboto);
	}



}

const float baseSpeed = 50.0f;



void LevelSelection::Init(void)
{
	const unsigned short LevelBtnCount{ 10 };
	const float BtnWidth{ 150.0f }, BtnHeight{ 75.0f }, BtnTextScale{ 0.5f };
	for (unsigned short i = 0; i < LevelBtnCount; ++i) {
		LevelBtn.push_back(Button(ButtonType::Texture, BtnWidth, BtnHeight, BtnTextScale));
		LevelBtn[i].SetID(i);
		LevelBtn[i].Set_TextColor(Color{ 0.0f, 0.0f, 0.0f, 255.0f });
		LevelBtn[i].SetFontID(fontID::Roboto);
		LevelBtn[i].ChangeStateColor(ButtonState::Hovered, Color{ 247.0f, 161.0f, 187.0f, 255.0f });
	}
	// For Unlocked levels
	for (unsigned short i = 0; i < LevelSys.GetUnlockedLevels(); ++i) {
		LevelBtn[i].Load_Texture(FP::BUTTONS::Btn);
		LevelBtn[i].Set_Callback(LevelSystem::SetLevel);

		std::string LevelCount{ "Level " + std::to_string(i) };
		LevelBtn[i].Set_Text(LevelCount.c_str());
	}

	LevelBtn[0].Set_Text("Tutorial");


	for (unsigned short i = LevelSys.GetUnlockedLevels(); i < LevelBtnCount - 1; ++i) {
		LevelBtn[i].Load_Texture(FP::BUTTONS::Btn);
		LevelBtn[i].ChangeStateColor(ButtonState::Idle, Color(255.0f, 255.0f, 255.0f, 150.0f));
	}
	// Assigning position
	for (unsigned short i = 0; i < 3; ++i) {
		for (unsigned short j = 0; j < 3; ++j) {
			unsigned short BtnIndex{ i * 3U + j };
			static const float BtnPosX{ 175.0f }, PerOffsetX{ 225.0f }, BtnPosY{ 162.5f }, PerOffsetY{ 150.0f };
			LevelBtn[BtnIndex].Set_Position(AEVec2Set(BtnPosX + PerOffsetX * j,
													  BtnPosY + PerOffsetY * i));
		}
	}
	if(LevelSys.GetKey() < LevelSys.GetMaxLevel())
		LevelBtn[LevelSys.GetKey()].ChangeStateColor(ButtonState::Idle, Color{ 200.0f, 0.0f, 0.0f, 255.0f });

	LevelBtn[9].Load_Texture(FP::BUTTONS::Btn);
	LevelBtn[9].Set_Position(AEVec2Set(ScreenMid.x, WindowHeight - LevelBtn[9].GetHeight() / 2.0f));
	LevelBtn[9].Set_Text("Back");
	LevelBtn[9].Set_Callback(MainMenu::SwitchToMainMenu);
}
void MainMenu::SwitchToLevelSelection(void)
{
	GameStateUpdate = LevelSelection::Update;
	GameStateDraw = LevelSelection::Render;
}

void MainMenu::SwitchToSettings()
{
	GameStateUpdate = Options::Update;
	GameStateDraw = Options::Render;
}
void MainMenu::SwitchToControl(void)
{
	GameStateUpdate = Control::Update;
	GameStateDraw = Control::Render;
}
void MainMenu::SwitchToMainMenu(void)
{
	count = 0;
	GameStateUpdate = MainMenu::Update;
	GameStateDraw = MainMenu::Render;
}
void LevelSelection::Update(void)
{
	for (int i = 0; i < LevelBtn.size(); ++i) {
		LevelBtn[i].Update();
	}
	if (AEInputCheckReleased(AEVK_ESCAPE))
		MainMenu::SwitchToMainMenu();
}
void LevelSelection::Render(void)
{
	static Graphics::Text LevelSelectionText;
	LevelSelectionText.SetText("Level Selection");
	LevelSelectionText.SetTextColor(Color{ 0.0f, 0.0f, 0.0f, 255.0f });
	LevelSelectionText.SetTextScale(1.0f);

	for (int i = 0; i < LevelBtn.size(); ++i) {
		LevelBtn[i].Render();
	}
	LevelSelectionText.Draw_Wrapped(AEVec2Set(ScreenMid.x, WindowHeight / 10.0f));
}

void LevelSelection::Unload(void)
{
	LevelBtn.clear();
}

void Options::Init()
{
	const size_t btnCount{ 2 };
	const float BtnWidth{ 200.0f }, BtnHeight{ 50.0f }, BtnTextScale{ 0.6f };
	const float BtnYOffset{ 150.0f };
	for (size_t i = 0; i < btnCount; ++i) {
		SettingsBtn.push_back(Button(ButtonType::Texture, BtnWidth, BtnHeight, BtnTextScale));
		SettingsBtn[i].Set_Position(AEVec2Set(ScreenMid.x, ScreenMid.y / 2.0f - BtnHeight / 2.0f + i * BtnYOffset));
		SettingsBtn[i].SetFontID(fontID::Roboto);
	
		
	}

	SettingsBtn[0].Set_Callback(Utils::ToggleFullscreen);
	SettingsBtn[1].Set_Text("Back");
	SettingsBtn[1].Set_Callback(MainMenu::SwitchToMainMenu);

}

void Options::Update()
{
	Utils::GetFullscreenStatus() == true ? SettingsBtn[0].Set_Text("Windows Mode") 
										 : SettingsBtn[0].Set_Text("Fullscreen");

	for (size_t i = 0; i < SettingsBtn.size(); ++i) {
		SettingsBtn[i].Update();
	}
	if (AEInputCheckReleased(AEVK_ESCAPE) && gamestateCurr == GS_MAINMENU)
		MainMenu::SwitchToMainMenu();
}

void Options::Render()
{
	static Graphics::Text SettingsPageText;
	SettingsPageText.SetFontID(fontID::Roboto);
	SettingsPageText.SetText("Settings");
	SettingsPageText.SetTextColor(Color{ 0.0f, 0.0f, 0.0f, 255.0f });
	SettingsPageText.SetTextScale(1.0f);

	for (size_t i = 0; i < SettingsBtn.size(); ++i) {
		SettingsBtn[i].Render();
		SettingsBtn[i].Load_Texture(FP::BUTTONS::Btn);
	}
	SettingsPageText.Draw_Wrapped(AEVec2Set(ScreenMid.x, WindowHeight / 10.0f));
}

void Options::Unload()
{
	SettingsBtn.clear();
}

