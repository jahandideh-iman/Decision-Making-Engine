#pragma once
#include <functional>
#include "BehaviorTask.h"

class TaskMethod
{
	typedef std::function<TaskResult(float)> Method;
public:
	TaskMethod(Method method);
	~TaskMethod();

	TaskResult Invoke(float dt) const;
private:
	Method method = nullptr;

};

