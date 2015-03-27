#pragma once

#include <functional>
#include <string>


namespace DME
{
	typedef std::function<void(float)> UpdateAction;
	typedef std::function<void()> Action;
	typedef std::function<bool()> Condition;

	typedef std::string StateName;
	typedef std::string ActionName;
	typedef std::string ConditionName;
}
