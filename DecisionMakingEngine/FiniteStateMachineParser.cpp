#include "FiniteStateMachineParser.h"


FiniteStateMachineParser::FiniteStateMachineParser()
{
	typeName = "FiniteStateMachine";
}


FiniteStateMachineParser::~FiniteStateMachineParser()
{
}



DMEComponent* FiniteStateMachineParser::CreateWithValidData(XMLNode* rootXMLNode)
{
	FiniteStateMachineComponent* component = new FiniteStateMachineComponent();

	//TODO: change input of prase method from rootXMLNode to their needed xmlNode (i.e. stateXMLNode)
	ParseStates(component, rootXMLNode);
	ParseTransitions(component, rootXMLNode);
	ParseInitialState(component, rootXMLNode);

	return component;
}

void FiniteStateMachineParser::ParseStates(FiniteStateMachineComponent* component, XMLNode* rootXMLNode)
{
	XMLNode* statesXMLNode = rootXMLNode->first_node("States");
	if (statesXMLNode == nullptr)
		return;

	for (XMLNode* stateXMLNode = statesXMLNode->first_node("State"); 
		stateXMLNode; stateXMLNode = stateXMLNode->next_sibling("State"))
		ParseState(component, stateXMLNode);

}


void FiniteStateMachineParser::ParseState(FiniteStateMachineComponent* component, XMLNode * stateXMLNode)
{
	StateName stateName = stateXMLNode->first_node("Name")->value();
	component->AddState(stateName);

	ParseStateEntryAction(component, stateName, stateXMLNode->first_node("EntryAction"));
	ParseStateUpdateAction(component, stateName, stateXMLNode->first_node("UpdateAction"));
	ParseStateExitAction(component, stateName, stateXMLNode->first_node("ExitAction"));
}

void FiniteStateMachineParser::ParseStateEntryAction(FiniteStateMachineComponent* component, StateName stateName, XMLNode* entryActionXMLNode)
{
	if (entryActionXMLNode != nullptr)
	{
		component->AddAction(entryActionXMLNode->value());
		component->SetStateEntryAction(stateName, entryActionXMLNode->value());
	}
}

void FiniteStateMachineParser::ParseStateUpdateAction(FiniteStateMachineComponent* component, StateName stateName, XMLNode* updateActionXMLNode)
{
	if (updateActionXMLNode != nullptr)
	{
		component->AddAction(updateActionXMLNode->value());
		component->SetStateUpdateAction(stateName, updateActionXMLNode->value());
	}
}

void FiniteStateMachineParser::ParseStateExitAction(FiniteStateMachineComponent* component, StateName stateName, XMLNode* exitActionXMLNode)
{
	if (exitActionXMLNode != nullptr)
	{
		component->AddAction(exitActionXMLNode->value());
		component->SetStateExitAction(stateName, exitActionXMLNode->value());
	}
}

void FiniteStateMachineParser::ParseTransitions(FiniteStateMachineComponent* component, XMLNode * rootNode)
{
	XMLNode * transitionsNode = rootNode->first_node("Transitions");
	if (transitionsNode == nullptr)
		return;

	for (XMLNode *transitionNode = transitionsNode->first_node("Transition");
		transitionNode; transitionNode = transitionNode->next_sibling("Transition"))
		ParseTransition(component, transitionNode);
}

void FiniteStateMachineParser::ParseTransition(FiniteStateMachineComponent* component, XMLNode* transitionXMLNode)
{
	XMLNode* fromXMLNode = transitionXMLNode->first_node("From");
	XMLNode* toXMLNode = transitionXMLNode->first_node("To");
	XMLNode* conditionXMLNode = transitionXMLNode->first_node("Condition");

	component->AddTransition(fromXMLNode->value(), toXMLNode->value(), conditionXMLNode->value());
	component->AddCondition(conditionXMLNode->value());
}

void FiniteStateMachineParser::ParseInitialState(FiniteStateMachineComponent* component, XMLNode* rootNode)
{
	XMLNode * initialStateNode = rootNode->first_node("InitialState");
	if (initialStateNode == nullptr)
		return;

	component->SetInitialState(initialStateNode->value());
}


