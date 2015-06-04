#pragma once

#include <iostream>
#include "rapidxml-1.13/rapidxml.hpp"
#include "FiniteStateMachineComponent.h"
#include "Core/DMEUtilities.h"
#include "Core/DMEComponentParser.h"
using namespace rapidxml;
using namespace std;


class FiniteStateMachineParser: public DMEComponentParser
{
	using StateName = DME::StateName;
public:
	FiniteStateMachineParser();
	~FiniteStateMachineParser();

protected:

	DMEComponent* CreateWithValidData(XMLNode* rootXMLNode) override;

	std::string GetTypeName() override;

private:

	void ParseStates(FiniteStateMachineComponent* component, XMLNode* rootXMLNode);
	void ParseState(FiniteStateMachineComponent* component, XMLNode * stateNode);
	void ParseStateEntryAction(FiniteStateMachineComponent* component, StateName stateName, XMLNode* entryActionXMLNode);
	void ParseStateUpdateAction(FiniteStateMachineComponent* component, StateName stateName, XMLNode* updateActionXMLNode);
	void ParseStateExitAction(FiniteStateMachineComponent* component, StateName stateName, XMLNode* exitActionXMLNode);

	void ParseTransitions(FiniteStateMachineComponent* component, XMLNode* rootXMLNode);
	void ParseTransition(FiniteStateMachineComponent* component, XMLNode * transitionNode);

	void ParseInitialState(FiniteStateMachineComponent* component, XMLNode* rootXMLNode);
};

