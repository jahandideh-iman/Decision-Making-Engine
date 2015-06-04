#pragma once
#include <functional>

namespace DME
{
	class Condition;
	class Action;

	class InterfaceFactory
	{
	public:
		InterfaceFactory() = delete;

		static DME::Action *CreateAction(std::function<void()> function);

		static DME::Action *CreateUpdateAction(std::function<void(float)> function);

		static DME::Condition *CreateCondition(std::function<bool()> function);

	};

}