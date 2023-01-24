
#pragma once
#include "AEEngine.h"

namespace GAMEPLAY_MISC {
	extern bool PAUSED;
	extern bool DEV_MODE;
	extern bool DEBUG_MODE;
	extern bool FULLSCREEN;
	extern bool DISPLAY_QUIT_UI;
	extern bool DISABLE_COLLISION;
	extern bool WASD_KEYS;
	extern bool ARROW_KEYS;

	extern float app_time, TimeAttack_remaining;
	extern int app_max_time;
	extern int app_score;
	extern int player_score;
	extern int previous_player_score;
	// Level tracker
	extern unsigned short Level;
}
namespace fontID {
	extern char Roboto;
}
namespace Mesh { // Base Meshes
	extern AEGfxVertexList* Rect;
	extern AEGfxVertexList* Circle;
	extern AEGfxVertexList* Anim;
	extern AEGfxVertexList* Anim2;
	extern AEGfxVertexList* BatAnim;
	extern AEGfxVertexList* SlimeAnim;
	extern AEGfxVertexList* SquirrelAnim;
	extern AEGfxVertexList* PlayerCurr;
}
extern unsigned short DialogueID;
// Miscallenous
extern float g_dt;

extern const float bat_anim_offset_x;
extern const float slime_anim_offset_x;
extern const float squirrel_anim_offset_x;
extern float player_objtexX;
extern float bat_objtexX;
extern float slime_objtexX;
extern float squirrel_objtexX;