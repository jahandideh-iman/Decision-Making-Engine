#include "Task.h"


Task::Task(Method method)
{
	this->method = method;
}


Task::~Task()
{
}

auto Task::Invoke(float dt) const -> TaskResult
{
	if (method != nullptr)
		return method(dt);
	return TaskResult::None;
}
