#include "CppUTest/TestHarness.h"
#include "FiniteStateMachineComponent.h"
#include "FiniteStateMachineParser.h"
#include <sstream>

#define SAFE_DELETE(pointer) {if (pointer) delete pointer; pointer = nullptr; }



TEST_GROUP(FiniteStateMachineParser)
{
	FiniteStateMachineComponent* comp;

	std::stringbuf* tempBuf = nullptr;
	std::istream* tempIStream = nullptr;

	void teardown()
	{
		SAFE_DELETE(comp);
		SAFE_DELETE(tempBuf);
		SAFE_DELETE(tempIStream);
	}

	std::istream& CreateStream(string input)
	{
		tempBuf = new std::stringbuf(input);
		tempIStream = new std::istream(tempBuf);
		return  *(tempIStream);
	}

	void CheckHasTransition(string from, string to, string condition)
	{
		bool hasTransition = false;
		FiniteStateMachineComponent::State* sourceState = comp->GetState(from);
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
	comp = FiniteStateMachineParser::Create(CreateStream(""));

	POINTERS_EQUAL(nullptr, comp);
}

TEST(FiniteStateMachineParser, CreateEmptyComponentWithNoData)
{
	comp = FiniteStateMachineParser::Create(CreateStream(
		"<DMEComponent  type=\"FiniteStateMachine\" >"
		"</DMEComponent>"));

	CHECK_TRUE(comp->HasNoState());
}

TEST(FiniteStateMachineParser, ComponentHasTheProvidedStates)
{

	comp = FiniteStateMachineParser::Create(CreateStream(
		"<DMEComponent  type=\"FiniteStateMachine\" >"
		"    <States>"
		"        <State><Name>StateOne</Name></State>"
		"        <State><Name>StateTwo</Name></State>"
		"        <State><Name>StateThree</Name></State>"
		"    </States>"
		"</DMEComponent>"));

	CHECK_TRUE(comp->HasState("StateOne"));
	CHECK_TRUE(comp->HasState("StateTwo"));
	CHECK_TRUE(comp->HasState("StateThree"));
}

TEST(FiniteStateMachineParser, ComponentHasTheProvidedInitialState)
{

	comp = FiniteStateMachineParser::Create(CreateStream(
		"<DMEComponent  type=\"FiniteStateMachine\" >"
		"    <States>"
		"        <State><Name>StateOne</Name></State>"
		"        <State><Name>StateTwo</Name></State>"
		"    </States>"
		"    <InitialState>StateTwo</InitialState>"
		"</DMEComponent>"));

	CHECK_EQUAL("StateTwo", comp->GetInitialStateName());
}

TEST(FiniteStateMachineParser, ComponentHasTheProvidedStateActions)
{
	comp = FiniteStateMachineParser::Create(CreateStream(
		"<DMEComponent  type=\"FiniteStateMachine\" >"
		"    <States>"
		"        <State>"
		"               <Name>StateOne</Name>"
		"               <UpdateAction>StateOneUpdateAction</UpdateAction>"
		"               <EntryAction>StateOneEntryAction</EntryAction>"
		"               <ExitAction>StateOneExitAction</ExitAction>"
		"        </State>"
		"    </States>"
		"</DMEComponent>"));

	CHECK_EQUAL("StateOneUpdateAction", comp->GetState("StateOne")->updateAction);
	CHECK_EQUAL("StateOneEntryAction", comp->GetState("StateOne")->entryAction);
	CHECK_EQUAL("StateOneExitAction", comp->GetState("StateOne")->exitAction);
}

TEST(FiniteStateMachineParser, ComponentHasTheProvidedTransitions)
{
	comp = FiniteStateMachineParser::Create(CreateStream(
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
		"</DMEComponent>"));

	CheckHasTransition("StateOne", "StateTwo", "TransitionOneCondition");
	CheckHasTransition("StateTwo", "StateOne", "TransitionTwoCondition");
}
