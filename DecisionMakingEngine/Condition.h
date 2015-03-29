#pragma once

#include <functional>

namespace DME
{

	class Condition
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

