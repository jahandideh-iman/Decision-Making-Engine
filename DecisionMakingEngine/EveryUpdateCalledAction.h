#pragma once
#include "Action.h"
#include <functional>

using std::function;
namespace DME
{

	class EveryUpdateCalledAction :
		public Action
	{
		typedef std::function<void(float)> Method;
	public:
		EveryUpdateCalledAction(Method method = nullptr);
		~EveryUpdateCalledAction();

		void Invoke(float dt) const;
	private:
		Method method = nullptr;
	};

}
