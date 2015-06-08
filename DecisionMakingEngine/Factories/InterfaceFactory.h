#pragma once
#include <functional>

#include "BehaviorTree/Task.h"

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

		static Task *CreateTask(std::function<Task::TaskResult(float)> function);

	};

}