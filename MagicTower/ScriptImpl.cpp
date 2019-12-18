#include "RealTimeInfo.h"

Script::Script()
	:event{
	{"addHP", [](Obj obj, Str op) {
		obj->addHealth(' ', atoi(op.c_str()));
	}},

	{"addATK", [](Obj obj, Str op) {
		obj->addATKorDEF('5', atoi(op.c_str()));
	}},

	{"addDEF", [](Obj obj, Str op) {
		obj->addATKorDEF('6', atoi(op.c_str()));
	}},

	{"TP", [](Obj obj, Str op) {
		std::stringstream strm(op);
		uint32_t no, _x, _y;
		strm >> no >> _x >> _y;
		obj->tpPlayer(no, _x, _y);
	}},

	{"remove", [](Obj obj, Str op) {
		std::stringstream strm(op);
		uint32_t no, _x, _y;
		strm >> no >> _x >> _y;
		obj->removeBlock(no, _x, _y);
	}}
}

{ 
	std::ifstream file("Plot.txt");
	uint32_t no;
	std::string line;
	while (file >> no)
	{
		file.get();
		plot.insert({ no, std::stringstream() });
		std::getline(file, line);
		while (line[0] != '#')
		{
			plot[no] << line << '\n';
			std::getline(file, line);
		}
	}
}

void Script::playPlot(uint32_t no, Obj obj)
{
	std::string foo;
	std::string temp;
	std::string line;
	obj->dialogue.str("");
	while (plot[no] >> foo)
	{
		if (foo == "dialogue")
		{

			plot[no] >> line;
			while (line != "end")
			{
				obj->dialogue << line << '\n';
				plot[no] >> line;
			}
			obj->playDialogue();
		}
		else
		{
			std::getline(plot[no], temp);
			event[foo](obj, temp);
		}
	}
}
