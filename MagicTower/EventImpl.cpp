#include "RealTimeInfo.h"

RealTimeInfo::RealTimeInfo()
	: cur_layer(0),
	god({20, 100, 2, 4}),
	monster (getMonsterInfo()),
	player  (std::make_shared<Hero>()), //≤ªø…”√std::shared_ptr<...>() 
	tower   (std::make_shared<Map>(monster)),
	script  (std::make_shared<Script>())
{ }

uint32_t& RealTimeInfo::getCurLayerNum()
{
	return cur_layer;
}

std::pair<uint32_t, uint32_t>& RealTimeInfo::getPlayerCoord()
{
	return player->position;
}

std::vector<std::vector<std::string>>& RealTimeInfo::getAllLayer()
{
	return tower->layer;
}

std::shared_ptr<std::unordered_map<char, Monster>> RealTimeInfo::getMonsterMap()
{
	return monster;
}

std::shared_ptr<Hero> RealTimeInfo::getPlayer()
{
	return player;
}

void  RealTimeInfo::drawCurLayer()
{
	std::cout << "µ⁄ " << cur_layer + 1 << " ≤„" << '\n'
		<< "…˙√¸:" << player->health << " "
		<< "π•ª˜:" << player->attack << " "
		<< "∑¿”˘:" << player->defense << " "
		<< "Ω±“:" << player->coins << " " << std::endl;
	tower->drawLayer(cur_layer);
	std::cout << "Œ‰∆˜:" << "  "
		<< "∂‹≈∆:" << '\n'
		<< "ª∆‘ø≥◊:" << player->key[0] << " "
		<< "¿∂‘ø≥◊:" << player->key[1] << " "
		<< "∫Ï‘ø≥◊:" << player->key[2] << " " << std::endl;
	std::cout << message << std::endl;
}

void RealTimeInfo::showManual()
{
	system("cls");
	std::cout << std::left << std::setw(20);
	std::cout << "π÷ŒÔ√˚≥∆" <<std::setw(10)<< "…˙√¸" << std::setw(10) << "π•ª˜" << std::setw(10) << "∑¿”˘" << std::setw(10) << "Ω±¿¯" << std::endl;
	for (auto& c : tower->monster_manual[cur_layer])
	{
		c.showInfo();
	}
	system("pause");
	system("cls");
	drawCurLayer();
}

void RealTimeInfo::showGodMenu()
{
	system("cls");
	std::cout << "Ã∞¿∑÷Æ…Ò" << '\n';
	std::cout << "∏¯Œ“" << std::get<0>(god) << "Ω±“æÕø…“‘°≠°≠" << '\n'
		<< "1.…˙√¸+" << std::get<1>(god) << '\n'
		<< "2.π•ª˜+" << std::get<2>(god) << '\n'
		<< "3.∑¿”˘+" << std::get<3>(god) << '\n'
		<< "4.¿Îø™" << std::endl;
	int key = _getch();
	if (player->coins >= std::get<0>(god) && key != 4)
	{
		switch (key)
		{
		case '1':
			addHealth(' ', std::get<1>(god));
			break;
		case '2':
			addATKorDEF('5', std::get<2>(god));
			break;
		case '3':
			addATKorDEF('6', std::get<3>(god));
			break;
		default:
			break;
		}
		player->coins -= std::get<0>(god);
		std::get<0>(god) *= 2;
	}
	else
		std::cout << "Ω±“≤ªπª£¨Œﬁ∑®Ωª“◊" << std::endl;
	system("pause");
	system("cls");
	drawCurLayer();
}

void RealTimeInfo::addKey(uint32_t n)
{
	player->key[n]++;
}

void RealTimeInfo::subKey(uint32_t n)
{
	player->key[n]--;
}

bool RealTimeInfo::haveKey(uint32_t n)
{
	return player->key[n] > 0;
}

void RealTimeInfo::setMessage(const char* ps)
{
	message = ps;
}

void RealTimeInfo::playDialogue()
{
	system("cls");
	std::cout << dialogue.str() << std::endl;
	system("pause");
	system("cls");
	drawCurLayer();
}

bool RealTimeInfo::fightWithResult(const Monster& it)
{
	if (player->attack <= it.defense)
	{
		return false;
	}
	else if (player->defense >= it.attack)
	{
		player->coins += it.coins;
		return true;
	}
	else
	{
		uint32_t myDamage  = player->attack - it.defense;
		uint32_t itsDamage = it.attack - player->defense;
		uint32_t myTimes   = it.health / myDamage + (it.health % myDamage ? 1 : 0);
		uint32_t itsTimes  = player->health / itsDamage + (player->health % itsDamage ? 1 : 0);
		if (myTimes <= itsTimes)
		{
			player->health -= (myTimes - 1) * itsDamage;
			player->coins  += it.coins;
			return true;
		}
		else
		{
			return false;
		}
	}
}

void RealTimeInfo::addHealth(char ch, int32_t _x)
{

	if (ch == '3')
	{
		player->health += 50;
	}
	else if (ch == '4')
	{
		player->health += 200;
	}
	else 
	{
		player->health += _x;
	}
}

void RealTimeInfo::addATKorDEF(char ch, int32_t _x)
{

	if (ch == '5')
	{
		player->attack += _x;
	}
	else
	{
		player->defense += _x;
	}
}

void RealTimeInfo::gotoLayer(uint32_t target)
{
	bool flag = target > cur_layer;
	tower->layer[cur_layer][player->position.second][player->position.first] = ' ';
	cur_layer = target;
	player->setPosition(tower->getPlayerPos(target,flag));
	tower->layer[target][player->position.second][player->position.first] = '@';
	
}

void RealTimeInfo::tpPlayer(uint32_t no, uint32_t _x, uint32_t _y)
{
	removeBlock(cur_layer, player->position.first, player->position.second);
	cur_layer = no;
	player->setPosition({_x, _y});
	tower->layer[no][_y][_x] = '@';
}

void RealTimeInfo::removeBlock(uint32_t no, uint32_t _x, uint32_t _y)
{
	tower->layer[no][_y][_x] = ' ';
}

void RealTimeInfo::executeScript()
{
	script->playPlot(cur_layer, shared_from_this());
}
