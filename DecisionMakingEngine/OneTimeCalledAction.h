#pragma once
#include "Action.h"
#include <functional>

using std::function;

namespace DME
{
	class OneTimeCalledAction :
		public Action
	{
		typedef std::function<void()> Method;
	public:
		OneTimeCalledAction(Method method);
		~OneTimeCalledAction();

		void Invoke();
	private:
		Method method = nullptr;
	};
}