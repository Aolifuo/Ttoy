#pragma once
#include "Object.h"
#include "Script.h"

class RealTimeInfo : public std::enable_shared_from_this <RealTimeInfo>
{
	friend class Script;

public:
	RealTimeInfo();
	uint32_t&                                          getCurLayerNum();
	std::pair<uint32_t, uint32_t>&                     getPlayerCoord();
	std::vector<std::vector<std::string>>&             getAllLayer();
	std::shared_ptr<std::unordered_map<char, Monster>> getMonsterMap();
	std::shared_ptr<Hero>                              getPlayer();

	void drawCurLayer();
	void addKey(uint32_t);
	void subKey(uint32_t);
	bool haveKey(uint32_t);
	void addHealth(char, int32_t _x = 0);
	void addATKorDEF(char, int32_t _x = 1);
	void showManual();
	void showGodMenu();
	void gotoLayer(uint32_t);
	void tpPlayer(uint32_t, uint32_t, uint32_t);
	void removeBlock(uint32_t, uint32_t, uint32_t);
	bool fightWithResult(const Monster&);
	void setMessage(const char *);
	void playDialogue();
	void executeScript();

private:
	uint32_t cur_layer;
	std::tuple<uint32_t, uint32_t, uint32_t, uint32_t> god;
	std::shared_ptr<std::unordered_map<char, Monster>> monster;
	std::shared_ptr<Hero> player;
	std::shared_ptr<Map> tower;
	std::shared_ptr<Script> script;
	std::stringstream dialogue;
	std::string message;

};
