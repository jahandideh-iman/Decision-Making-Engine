#include "EveryUpdateCalledAction.h"

using namespace DME;

EveryUpdateCalledAction::EveryUpdateCalledAction(Method method)
{
	this->method = method;
}


EveryUpdateCalledAction::~EveryUpdateCalledAction()
{
}

void EveryUpdateCalledAction::Invoke(float dt) const
{
	if (method != nullptr)
		method(dt);
}
