#include "InterfaceFactory.h"

#include "Core/Interfaces/OneTimeCalledAction.h"
#include "Core/Interfaces/EveryUpdateCalledAction.h"
#include "Core/Interfaces/Condition.h"

using DME::InterfaceFactory;

DME::Action *InterfaceFactory::CreateAction(std::function<void()> function)
{
	return new DME::OneTimeCalledAction(function);
}

DME::Action * DME::InterfaceFactory::CreateUpdateAction(std::function<void(float)> function)
{
	return new DME::EveryUpdateCalledAction(function);
}

DME::Condition * DME::InterfaceFactory::CreateCondition(std::function<bool()> function)
{
	return new DME::Condition(function);
}
