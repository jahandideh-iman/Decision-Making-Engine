#include "TaskMethod.h"


TaskMethod::TaskMethod(Method method)
{
	this->method = method;
}


TaskMethod::~TaskMethod()
{
}

TaskResult TaskMethod::Invoke(float dt) const
{
	if (method != nullptr)
		return method(dt);
}
