#pragma once

#include <functional>
#include "GameInterface.h"

namespace DME
{
	class Condition : public GameInterface
	{
		typedef std::function<bool()> Method;

	public:
		Condition(Method method);
		~Condition();

		bool GetResult() const;

	private:
		Method method = nullptr;
	};
}

