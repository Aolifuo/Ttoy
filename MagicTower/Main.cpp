#include "RealTimeInfo.h"

std::pair<uint32_t, uint32_t>& operator+=(std::pair<uint32_t, uint32_t>& _a,  std::pair<uint32_t, uint32_t>& _b)
{
	_a.first += _b.first;
	_a.second += _b.second;
	return _a;
}

int main()
{

	int   key;
	char  block;
	std::string movekey("wsad");

	auto  infoEvent     = std::make_shared<RealTimeInfo>();

	auto& current       = infoEvent->getCurLayerNum();
	auto& playerCoord   = infoEvent->getPlayerCoord();
	auto& layer         = infoEvent->getAllLayer();
	auto  player        = infoEvent->getPlayer();
	auto  enemies       = infoEvent->getMonsterMap();
	auto  pos           = playerCoord;
	auto& _x            = pos.first;
	auto& _y            = pos.second;

	std::map<char, std::pair<uint32_t, uint32_t>> _move{
		{'w', {0, -1}},		{'s', {0, 1}},
		{'a', {-1, 0}},		{'d', {1, 0}} };

	std::set<char> keyhit{ 
		'w', 's', 'a', 'd', 'm'
	};

	auto getBlock = [&]()->char {
		return layer[current][_y][_x];
	};

	auto movePlayer = [&]() {
		layer[current][playerCoord.second][playerCoord.first] = ' ';
		layer[current][_y][_x] = '@';
		playerCoord = pos;
	};

	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);

	infoEvent->drawCurLayer();

	while (true)
	{
		while (true)
		{
			key = _getch();
			if (keyhit.find(key) !=keyhit.end())
				break;
		}

		if (movekey.find(key) != std::string::npos)
		{
			pos += _move[key];
			block = getBlock();

			if (block == ' ' || block == '(' || block == ')') //空地
			{
				movePlayer();
			}
			else if (block == '#' || block == '|') //墙或铁门
			{
				pos = playerCoord;
			}
			else if (isalpha(block)) //怪物
			{
				if (infoEvent->fightWithResult(enemies->at(block))) //战胜
				{
					movePlayer();
				}
				else //打不过
				{
					pos = playerCoord;
				}
			}
			else if (block >= '0' && block <= '2') //钥匙
			{
				infoEvent->addKey(block - '0');
				movePlayer();
			}
			else if (block >= '7' && block <= '9') //门
			{
				if (infoEvent->haveKey(block - '7'))
				{
					infoEvent->subKey(block - '7');
					movePlayer();
				}
				else
				{
					pos = playerCoord;
				}
			}
			else if (block >= '3' && block <= '4') //药
			{
				infoEvent->addHealth(block);
				movePlayer();
			}
			else if (block >= '5' && block <= '6') //
			{
				infoEvent->addATKorDEF(block);
				movePlayer();
			}
			else if (block == '<' || block == '>') //上下楼
			{
				infoEvent->gotoLayer(current + (block == '<' ? 1 : -1));
				pos = playerCoord;
			}
			else if (block == '%') //事件
			{
				movePlayer();
				infoEvent->executeScript();
				pos = playerCoord;
			}
			else if (block == ':' || block == ';')
			{
				pos = playerCoord;
			}
			else if (block == '$')
			{
				infoEvent->showGodMenu();
				pos = playerCoord;
			}
	
		}

		else
		{
			if (key == 'm')
			{
				infoEvent->showManual();
			}

		}

		system("cls");
		infoEvent->drawCurLayer();
	}
	return 0;
}

