#include "CppUTest/TestHarness.h"
#include "FiniteStateMachine/FiniteStateMachineComponent.h"
#include "FiniteStateMachine/FiniteStateMachineParser.h"
#include <sstream>


TEST_GROUP(FiniteStateMachineParser)
{
	FiniteStateMachineComponent* comp;
	FiniteStateMachineParser parser;


	void teardown()
	{
		SAFE_DELETE(comp);
	}

	void CheckHasTransition(string from, string to, string condition)
	{
		bool hasTransition = false;
		const FiniteStateMachineComponent::State* sourceState = comp->GetState(from);
		for (const FiniteStateMachineComponent::StateTransition& t : sourceState->transitions)
		{
			if (t.destinationState->name == to && t.conditionName == condition)
			{
				hasTransition = true;
				break;
			}
		}
		CHECK_TRUE(hasTransition);
	}
};

TEST(FiniteStateMachineParser, CreateNullOnEmptyInput)
{
	comp = (FiniteStateMachineComponent*)parser.Create("");

	POINTERS_EQUAL(nullptr, comp);
}

TEST(FiniteStateMachineParser, CreateEmptyComponentWithNoData)
{
	comp = (FiniteStateMachineComponent*)parser.Create(
		"<DMEComponent  type=\"FiniteStateMachine\" >"
		"</DMEComponent>");

	CHECK_TRUE(comp->HasNoState());
}

TEST(FiniteStateMachineParser, ComponentHasTheProvidedStates)
{
	comp = (FiniteStateMachineComponent*)parser.Create(
		"<DMEComponent  type=\"FiniteStateMachine\" >"
		"    <States>"
		"        <State><Name>StateOne</Name></State>"
		"        <State><Name>StateTwo</Name></State>"
		"        <State><Name>StateThree</Name></State>"
		"    </States>"
		"</DMEComponent>");

	CHECK_TRUE(comp->HasState("StateOne"));
	CHECK_TRUE(comp->HasState("StateTwo"));
	CHECK_TRUE(comp->HasState("StateThree"));
}

TEST(FiniteStateMachineParser, ComponentHasTheProvidedInitialState)
{
	comp = (FiniteStateMachineComponent*)parser.Create(
		"<DMEComponent  type=\"FiniteStateMachine\" >"
		"    <States>"
		"        <State><Name>StateOne</Name></State>"
		"        <State><Name>StateTwo</Name></State>"
		"    </States>"
		"    <InitialState>StateTwo</InitialState>"
		"</DMEComponent>");

	CHECK_EQUAL("StateTwo", comp->GetInitialStateName());
}

TEST(FiniteStateMachineParser, ComponentHasTheProvidedStateActions)
{
	comp = (FiniteStateMachineComponent*)parser.Create(
		"<DMEComponent  type=\"FiniteStateMachine\" >"
		"    <States>"
		"        <State>"
		"               <Name>StateOne</Name>"
		"               <UpdateAction>StateOneUpdateAction</UpdateAction>"
		"               <EntryAction>StateOneEntryAction</EntryAction>"
		"               <ExitAction>StateOneExitAction</ExitAction>"
		"        </State>"
		"    </States>"
		"</DMEComponent>");

	CHECK_EQUAL("StateOneUpdateAction", comp->GetState("StateOne")->updateActionName);
	CHECK_EQUAL("StateOneEntryAction", comp->GetState("StateOne")->entryActionName);
	CHECK_EQUAL("StateOneExitAction", comp->GetState("StateOne")->exitActionName);
}

TEST(FiniteStateMachineParser, ComponentHasTheProvidedTransitions)
{
	comp = (FiniteStateMachineComponent*)parser.Create(
		"<DMEComponent  type=\"FiniteStateMachine\" >"
		"    <States>"
		"        <State>"
		"               <Name>StateOne</Name>"
		"        </State>"
		"        <State>"
		"               <Name>StateTwo</Name>"
		"        </State>"
		"    </States>"
		"    <Transitions>"
		"        <Transition>"
		"            <From>StateOne</From>"
		"            <To>StateTwo</To>"
		"            <Condition>TransitionOneCondition</Condition>"
		"        </Transition>"
		"        <Transition>"
		"            <From>StateTwo</From>"
		"            <To>StateOne</To>"
		"            <Condition>TransitionTwoCondition</Condition>"
		"        </Transition>"
		"    </Transitions>"
		"</DMEComponent>");

	CheckHasTransition("StateOne", "StateTwo", "TransitionOneCondition");
	CheckHasTransition("StateTwo", "StateOne", "TransitionTwoCondition");
}
