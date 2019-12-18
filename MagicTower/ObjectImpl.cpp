#include "Object.h"
#include "RealTimeInfo.h"

void changeFontColor(uint32_t id)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), id);
}

/*------------------------------------ Hero ------------------------------------*/

void Hero::setPosition(std::pair<uint32_t, uint32_t> pos)
{
	position = pos;
}

/*------------------------------------ Map ------------------------------------*/

Map::Map(const std::shared_ptr<std::unordered_map<char, Monster>> & mon)
{
	char label;
	uint32_t color;
	std::string nam;

	std::ifstream file("Reflect.txt");
	while (file >> label)
	{
		file >> color >> nam;
		reflect.insert({ label, {color, nam} });
	}
	reflect.insert({ ' ', {7, "  "} });
	reflect.insert({ '(', {7, "  "} });
	reflect.insert({ ')', {7, "  "} });
	reflect.insert({ '%', {7, "  "} });
	file.close();
	//------------------------------------
	std::string txt_name("Layer ");
	player_up_pos.push_back({ 6, 11 });

	for (int i = 0; i < LayerNums; ++i)
	{
		file.open(txt_name + std::to_string(i + 1) + ".txt");
		std::string line;
		int line_no = 0;
		layer.push_back(std::vector<std::string>());
		monster_manual.push_back(std::set<Monster>());
		while (std::getline(file, line))
		{
			layer[i].push_back(line);
			for (std::size_t j = 0; j < line.size(); ++j)
			{
				if (isalpha(line[j]))
				{
					monster_manual[i].insert(mon->at(line[j])); 
				}
				else if (line[j] == '(')
				{
					player_up_pos.push_back({ j, line_no });
				}
				else if (line[j] == ')')
				{
					player_down_pos.push_back({ j, line_no });
				}
			}
			line_no++;
		}
		file.close();
	}
}



void Map::drawLayer(uint32_t No)
{
	std::vector<std::string>& sense = layer[No];
	for (auto& line : sense)
	{
		for (auto& ch : line)
		{
			changeFontColor(reflect[ch].first);
			std::cout << reflect[ch].second;
		}
		std::cout << std::endl;
	}
}

std::vector<std::string>& Map::getLayer(uint32_t No)
{
	return layer[No];
}

std::pair<uint32_t, uint32_t> Map::getPlayerPos(uint32_t no, bool f)
{
	return f ? player_up_pos[no] : player_down_pos[no];
}

/*------------------------------------ Monster ------------------------------------*/

Monster::Monster(std::string NA, uint32_t HP, uint32_t ATK, uint32_t DEF, uint32_t CO)
	:name(NA), health(HP), attack(ATK), defense(DEF), coins(CO)
{ }


void Monster::showInfo() const
{
	std::cout << std::left << std::setw(20);
	std::cout << name << std::setw(10)<< health << std::setw(10) << attack << std::setw(10) << defense << std::setw(10) << coins << std::endl;
}

std::shared_ptr<std::unordered_map<char, Monster>> getMonsterInfo()
{
	auto monster = std::make_shared<std::unordered_map<char, Monster>>();

	std::ifstream file("Monster.txt");
	std::string line;

	char label;
	std::string name;
	uint32_t hp, atk, def, coin;

	while (std::getline(file, line))
	{
		std::istringstream record(line);
		record >> label >> name
			>> hp >> atk >> def >> coin;
		monster->insert({ label, { name, hp, atk, def, coin } });
	}
	return monster;
}

bool Monster::operator<(const Monster& other) const
{
	return health < other.health;
}