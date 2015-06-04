#include "OneTimeCalledAction.h"

using namespace DME;

OneTimeCalledAction::OneTimeCalledAction(Method method)
{
	this->method = method;
}


OneTimeCalledAction::~OneTimeCalledAction()
{
}

void OneTimeCalledAction::Invoke(float /*dt*/) const
{
	if (method != nullptr)
		method();
}
