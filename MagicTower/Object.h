#pragma once
#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>
#include<array>
#include<map>
#include<set>
#include<unordered_map>
#include<unordered_set>
#include<utility>
#include<memory>
#include<algorithm>
#include<cctype>
#include<conio.h>
#include<Windows.h>

class Hero;
class Monster;
class Map;
class RealTimeInfo;

#include "RealTimeInfo.h"

constexpr uint32_t LayerNums = 4;
constexpr uint32_t Length = 11;
constexpr uint32_t Width = 11;

enum class Weapons : uint32_t { calibur };
enum class Shields : uint32_t { argos };

/*------------------------------------ Hero ------------------------------------*/

class Hero
{
	friend class RealTimeInfo;
	friend class Script;

public:
	Hero() = default;
	void setPosition(std::pair<uint32_t, uint32_t>);

private:
	int32_t                       health = 1000;
	uint32_t                      attack = 100;
	uint32_t                      defense = 100;
	int32_t                       coins = 1000;
	Weapons                       weapon = Weapons::calibur;
	Shields                       shield = Shields::argos;
	std::array<uint32_t, 3>       key = { 0, 0, 0 };
	std::pair<uint32_t, uint32_t> position = { 6, 11 }; //x,y
};

/*------------------------------------ Monster ------------------------------------*/

class Monster
{
	friend class RealTimeInfo;
	friend class Script;

public:
	Monster(std::string, uint32_t, uint32_t, uint32_t, uint32_t);
	void showInfo() const;
	bool operator<(const Monster&) const;

private:
	std::string name;
	uint32_t  health;
	uint32_t attack;
	uint32_t defense;
	uint32_t coins;
};

/*------------------------------------ NPC ------------------------------------*/

class NPC
{
	friend Map;

public:
	
private:
	std::stringstream dialogue;
};


/*------------------------------------ Map ------------------------------------*/

class Map
{
	friend class RealTimeInfo;
	friend class Script;

public:
	Map(const std::shared_ptr<std::unordered_map<char, Monster>> &);
	void drawLayer(uint32_t);
	std::vector<std::string>& getLayer(uint32_t);
	std::pair<uint32_t, uint32_t> getPlayerPos(uint32_t,bool);

private:
	std::unordered_map<char, std::pair<uint32_t, std::string>> reflect; //地图翻译
	std::vector<std::vector<std::string>> layer; //层信息
	std::vector<std::pair<uint32_t, uint32_t>> player_up_pos; //上塔初始
	std::vector<std::pair<uint32_t, uint32_t>> player_down_pos;
	std::vector<std::set<Monster>> monster_manual; //层怪物图鉴
};

std::shared_ptr<std::unordered_map<char, Monster>> getMonsterInfo();
