#pragma once

#include "Core/DMEDefines.h"
#include "Core/Interfaces/GameInterface.h"
#include <map>

using DME::InterfaceName;

class DMEComponent
{
	typedef std::map<InterfaceName, GameInterface*> InterfaceContainer;

public:
	DMEComponent();
	virtual ~DMEComponent();

	virtual void Update(float dt) = 0;

protected:
	void AddEmptyInterface(InterfaceName name);
	void SetInterface(InterfaceName name, GameInterface *_interface);
	const GameInterface* GetInterface(InterfaceName name) const;

private:

	InterfaceContainer interfaces;
};

