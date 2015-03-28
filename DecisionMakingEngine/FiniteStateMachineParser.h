#pragma once

#include <iostream>
#include "rapidxml-1.13/rapidxml.hpp"
#include "FiniteStateMachineComponent.h"
#include "DMEUtilities.h"

using namespace rapidxml;
using namespace std;

#define ROOT_ELEMENT "DMEComponent"
#define TYPE_ATTRIBUTE "type"
#define TYPE_NAME "FiniteStateMachine"
#define STATES_ELEMENT "States"
#define STATE_ELEMENT "State"
#define STATE_NAME_ELEMENT "Name"

class FiniteStateMachineParser
{
public:

	static FiniteStateMachineComponent* Create(std::istream &stream);

private:
	FiniteStateMachineParser();
	~FiniteStateMachineParser();

	static FiniteStateMachineComponent* CreateWithData(xml_node<> * rootNode);
	static bool IsDataValid(xml_node<> * rootNode);
	static std::string ReadData(std::istream &stream);


	static void ParseComponentStates(FiniteStateMachineComponent* component, xml_node<> * rootNode);
	static void ParseComponentTransitions(FiniteStateMachineComponent* component, xml_node<> * rootNode);
	static void ParseComponentInitialState(FiniteStateMachineComponent* component, xml_node<>* rootNode);


	static xml_node<>* GetRootNode(CharArrayWrapper& wrapper);
};

