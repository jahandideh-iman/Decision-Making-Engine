#include "FiniteStateMachineParser.h"


FiniteStateMachineParser::FiniteStateMachineParser()
{
	typeName = "FiniteStateMachine";
}


FiniteStateMachineParser::~FiniteStateMachineParser()
{
}



DMEComponent* FiniteStateMachineParser::CreateWithData(xml_node<> * rootNode)
{
	FiniteStateMachineComponent* component = new FiniteStateMachineComponent();

	ParseComponentStates(component, rootNode);
	ParseComponentTransitions(component, rootNode);
	ParseComponentInitialState(component, rootNode);

	return component;
}

void FiniteStateMachineParser::ParseComponentStates(FiniteStateMachineComponent* component, xml_node<> * rootNode)
{
	xml_node<> * statesNode = rootNode->first_node(STATES_ELEMENT);
	if (statesNode == nullptr)
		return;

	for (xml_node<> *stateNode = statesNode->first_node(STATE_ELEMENT);
		stateNode; stateNode = stateNode->next_sibling(STATE_ELEMENT))
	{
		xml_node<>* nameNode = stateNode->first_node(STATE_NAME_ELEMENT);
		xml_node<>* entryActionNode = stateNode->first_node("EntryAction");
		xml_node<>* updateActionNode = stateNode->first_node("UpdateAction");
		xml_node<>* exitActionNode = stateNode->first_node("ExitAction");

		

		component->AddState(nameNode->value());
		if (entryActionNode != nullptr)
		{
			component->AddAction(entryActionNode->value());
			component->SetStateEntryAction(nameNode->value(), entryActionNode->value());
		}

		if (updateActionNode != nullptr)
		{
			component->AddAction(updateActionNode->value());
			component->SetStateUpdateAction(nameNode->value(), updateActionNode->value());
		}

		if (exitActionNode != nullptr)
		{
			component->AddAction(exitActionNode->value());
			component->SetStateExitAction(nameNode->value(), exitActionNode->value());
		}

	}
}

void FiniteStateMachineParser::ParseComponentTransitions(FiniteStateMachineComponent* component, xml_node<> * rootNode)
{
	xml_node<> * transitionsNode = rootNode->first_node("Transitions");
	if (transitionsNode == nullptr)
		return;

	for (xml_node<> *transitionNode = transitionsNode->first_node("Transition");
		transitionNode; transitionNode = transitionNode->next_sibling("Transition"))
	{
		xml_node<>* fromNode = transitionNode->first_node("From");
		xml_node<>* toNode = transitionNode->first_node("To");
		xml_node<>* conditionNode = transitionNode->first_node("Condition");

		component->AddTransition(fromNode->value(), toNode->value(), conditionNode->value());
		component->AddCondition(conditionNode->value());
	}
}


void FiniteStateMachineParser::ParseComponentInitialState(FiniteStateMachineComponent* component, xml_node<>* rootNode)
{
	xml_node<> * initialStateNode = rootNode->first_node("InitialState");
	if (initialStateNode == nullptr)
		return;

	component->SetInitialState(initialStateNode->value());
}


