#pragma once

#include <iostream>
#include "rapidxml-1.13/rapidxml.hpp"
#include "FiniteStateMachineComponent.h"
#include "DMEUtilities.h"
#include "DMEComponentParser.h"
using namespace rapidxml;
using namespace std;


#define TYPE_ATTRIBUTE "type"
#define TYPE_NAME "FiniteStateMachine"
#define STATES_ELEMENT "States"
#define STATE_ELEMENT "State"
#define STATE_NAME_ELEMENT "Name"

class FiniteStateMachineParser: public DMEComponentParser
{
public:
	FiniteStateMachineParser();
	~FiniteStateMachineParser();

protected:

	DMEComponent* CreateWithData(xml_node<> * rootNode) override;

private:



	void ParseComponentStates(FiniteStateMachineComponent* component, xml_node<> * rootNode);
	void ParseComponentTransitions(FiniteStateMachineComponent* component, xml_node<> * rootNode);
	void ParseComponentInitialState(FiniteStateMachineComponent* component, xml_node<>* rootNode);

};

