

#pragma once
#include "AEEngine.h"

enum class TYPE_OBJECT
{
	EMPTY,						//0
	COLLAPSIBLE,				//1
	NON_COLLAPSIBLE,			//2
	SPECIAL,					//3
	GOAL,						//4
	MAN,					//5
	SLIME,						//6
	BAT,						//7	
	SQUIRREL,					//8
	DIALOGUE,					//9
	MAX							//10
};

enum class EntitySizes {
	SLIME = 0,
	BAT,
	SQUIRREL,
	PLAYER,
	MAX
};

EntitySizes& operator++(EntitySizes& rhs);

extern int** MapData;
extern int Map_Width;
extern int Map_Height;

int		ImportMapDataFromFile(const char* FileName);
void	FreeMapData(void);