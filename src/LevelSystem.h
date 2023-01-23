
#pragma once

// Locking / unlocking system for the level selection. Currently called from GameStateMgr.cpp
class LevelSystem {

private:
	const char* keyPath{ "./Assets/Level_System/Key.txt" };
	unsigned short key, maxLevel;

public:
	LevelSystem();
	~LevelSystem();
	void Init();
	void UnlockNext();
	void SaveKeyToFile(void);
	unsigned short GetUnlockedLevels();

	inline void UpdateKey(unsigned short newKey) { key = newKey; }
	inline unsigned short GetKey() const { return key; }
	inline unsigned short GetMaxLevel() { return maxLevel; }

	static void SetLevel(unsigned short level);
	static void SetNextLevel();
};
