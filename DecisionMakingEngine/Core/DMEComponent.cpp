#include "DMEComponent.h"
#include <cassert>
#include "Core/DMEUtilities.h"


DMEComponent::DMEComponent()
{

}

DMEComponent::~DMEComponent()
{
	DELETE_MAP_CONTAINER(interfaces);
}

void DMEComponent::AddEmptyInterface(InterfaceName name)
{
	interfaces.emplace(name, nullptr);
}

void DMEComponent::SetInterface(InterfaceName name, GameInterface *interface)
{
	interfaces[name] = interface;
}

const GameInterface* DMEComponent::GetInterface(InterfaceName name) const
{
	assert(interfaces.find(name) != interfaces.end());
	return interfaces.find(name)->second;
}

