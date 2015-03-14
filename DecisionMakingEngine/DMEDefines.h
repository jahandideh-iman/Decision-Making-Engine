#pragma once

#include <functional>

namespace DME
{
	typedef std::function<void(float)> UpdateAction;
	typedef std::function<void()> Action;
	typedef std::function<bool()> Query;
}
