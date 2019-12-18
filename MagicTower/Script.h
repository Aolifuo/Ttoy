#pragma once
#include <functional>
#include "RealTimeInfo.h"

class Script
{
public:
	using Obj = std::shared_ptr<RealTimeInfo>;
	using Str = std::string;
	Script();
	void playPlot(uint32_t, Obj);

	std::map<std::string, std::function<void(Obj,std::string)>> event;
private:
	std::map<uint32_t, std::stringstream> plot;

};


