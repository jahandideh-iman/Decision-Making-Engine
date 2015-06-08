#include "CppUTest/TestHarness.h"
#include "Core/DMEManager.h"
#include "DecisionTree/DecisionTreeComponent.h"
#include "FiniteStateMachine/FiniteStateMachineComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Core/DMEComponent.h"
#include <sstream>
#include "Core/DMEUtilities.h"

#define CHECK_COMPONENT_TYPE(comp, CType) CHECK_TRUE(dynamic_cast<CType*>(comp)!= nullptr);

class DMEComponentUpdateCounterSpy : public DMEComponent
{
public:

	~DMEComponentUpdateCounterSpy()
	{
	}

	void Update(float dt)
	{
		++updateCount;
	}

	int updateCount = 0;
};

class DMEComponentDeltaTimeSpy : public DMEComponent
{
public:

	~DMEComponentDeltaTimeSpy()
	{
	}

	void Update(float dt) override
	{
		lastDeltaTime = dt;
	}

	float lastDeltaTime = 0;
};

TEST_GROUP(DMEManager)
{
	DMEManager * manager;

	std::stringbuf* tempBuf = nullptr;
	std::istream* tempIStream = nullptr;

	DMEComponent* parsedComponent = nullptr;

	void CallMultipleUpdate(unsigned numberOfTimes)
	{
		for (unsigned i = 0; i < numberOfTimes; ++i)
			manager->Update();
	}

	void setup()
	{
		manager = DMEManager::Get();
	}

	void teardown()
	{
		DMEManager::Destroy();
		SAFE_DELETE(tempBuf);
		SAFE_DELETE(tempIStream);
		SAFE_DELETE(parsedComponent);
	}

	std::istream& CreateStream(std::string input)
	{
		tempBuf = new std::stringbuf(input);
		tempIStream = new std::istream(tempBuf);
		return  *(tempIStream);
	}
};

TEST(DMEManager, IsSingleton)
{
	POINTERS_EQUAL(manager, DMEManager::Get());
}

TEST(DMEManager, IsEmptyOnCreation)
{
	CHECK_TRUE(manager->IsEmpty());
}

TEST(DMEManager, IsNotEmptyOnAddComponent)
{
	DecisionTreeComponent component;
	manager->AddComponent(&component);

	CHECK_FALSE(manager->IsEmpty());
}

TEST(DMEManager, ComponentIsUpdatedOnEachUpdate)
{
	DMEComponentUpdateCounterSpy componentMock;
	manager->AddComponent(&componentMock);

	CallMultipleUpdate(5);

	CHECK_EQUAL(5, componentMock.updateCount);
}

TEST(DMEManager, MultipleComponentsAreUpdatedOnEachUpdate)
{
	DMEComponentUpdateCounterSpy componentMock1;
	DMEComponentUpdateCounterSpy componentMock2;
	manager->AddComponent(&componentMock1);
	manager->AddComponent(&componentMock2);

	CallMultipleUpdate(5);

	CHECK_EQUAL(5, componentMock1.updateCount);
	CHECK_EQUAL(5, componentMock2.updateCount);
}

TEST(DMEManager, DeltaTimeIsPropagatedToComponent)
{
	DMEComponentDeltaTimeSpy componentSpy;
	manager->AddComponent(&componentSpy);

	manager->Update(0.5);

	CHECK_EQUAL(0.5, componentSpy.lastDeltaTime);
}

TEST(DMEManager, CreateNullComponentOnEmptyInput)
{
	DMEComponent* comp = DMEManager::Get()->CreateComponent(CreateStream(""));

	POINTERS_EQUAL(nullptr, comp);
}

TEST(DMEManager, CreateDecisionTreeComponentOnValidInput)
{
	parsedComponent = DMEManager::Get()->CreateComponent(CreateStream(
		"<DMEComponent  type=\"DecisionTree\" >"
		"</DMEComponent>"));

	CHECK_COMPONENT_TYPE(parsedComponent, DecisionTreeComponent);
}

TEST(DMEManager, CreateFiniteStateMachineComponentOnValidInput)
{
	parsedComponent = DMEManager::Get()->CreateComponent(CreateStream(
		"<DMEComponent  type=\"FiniteStateMachine\" >"
		"</DMEComponent>"));

	CHECK_COMPONENT_TYPE(parsedComponent, FiniteStateMachineComponent);
}

TEST(DMEManager, CreateBehaviorTreeComponentOnValidInput)
{
	parsedComponent = DMEManager::Get()->CreateComponent(CreateStream(
		"<DMEComponent  type=\"BehaviorTree\" >"
		"</DMEComponent>"));

	CHECK_COMPONENT_TYPE(parsedComponent, BehaviorTreeComponent);
}

