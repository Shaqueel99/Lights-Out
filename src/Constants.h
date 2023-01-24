
#pragma once
#include "AEEngine.h"


namespace FILE_PATHS {
	namespace LOGOS {
		extern const char* FMod;
		extern const char* DigipenRed;
		extern const char* DigipenWhite;
	}
	namespace BACKGROUND {
		extern const char* Pause;
		extern const char* Victory;
		extern const char* Gameover;
		extern const char* Moon;
		extern const char* Cloud;
		extern const char* BG;
	}
	namespace ENEMY {
		extern const char* BatSprite;
		extern const char* SquirrelSprite;
		extern const char* BatSpriteSheet;
		extern const char* WaterSlimeSprite;
		extern const char* SlimeSpriteSheet;
		extern const char* SquirrelSpriteSheet;
	}
	namespace PLAYER {
		extern const char* Sprite;
		extern const char* SpriteSheetRun;
		extern const char* SpriteSheetIdle;
	}
	namespace TILE {
		extern const char* Goal;
		extern const char* Grey;
		extern const char* Grass;
		extern const char* Special;
		extern const char* Dialogue;

		extern const char* Guide1;
		extern const char* Guide2;
		extern const char* Guide3;
		extern const char* Guide4;
		extern const char* Guide5;
		extern const char* Guide6;
		extern const char* Guide7;
	}
	namespace BUTTONS {
		extern const char* Btn;
	}
	namespace FONT {
		extern const char* Roboto;
	}
	

	namespace UI {
		extern const char* HeartSprite;
	}
	extern const char* Black;
}
namespace FP = FILE_PATHS; // Short hand 

namespace PLAYER_CONST {
	extern const float SPEED;
	extern const float DEBUGSPEED;
	extern const float JUMPVEL;
	extern const float CHARGED_JUMPVEL;
	extern const short CASUAL_MODE_HP_MAX;
	extern const short TIMEATK_MODE_HP_MAX;
	extern const float CHARGEDJUMP_COUNTER;
	extern const float COLLIDER_BTM_OFFSET_X;
	extern const float COLLIDER_SIDE_OFFSET_X;
	extern const float PLAYER_IDLE_OFFSET_X;
	extern const float PLAYER_RUN_OFFSET_X;
}
namespace TILE_CONST {
	extern const float COLLAPSE_DELAY;
	extern const float COLLAPSE_SPEED;
	extern const float GRASS_SPRITE_HEIGHT;
}
namespace GAMEPLAY_CONST {
	extern const float BASE_GRAVITY_MULTIPLIER;
}

// Key bindings.

#define DEBUG_KEY AEVK_F1
#define PAUSE_KEY AEVK_TAB 
#define RESTART_KEY AEVK_R
#define NEXT_LEVEL_KEY AEVK_N
#define PREV_LEVEL_KEY AEVK_B
#define COLLISION_OFF_KEY AEVK_F2
#define FULLSCREEN_KEY1 AEVK_LALT
#define FASTFOWARD_TIME_KEY AEVK_F
#define FULLSCREEN_KEY2 AEVK_RETURN
