#include "CppUTest/TestHarness.h"
#include "DMEManager.h"
#include "DecisionTreeComponent.h"
#include "FiniteStateMachineComponent.h"
#include "DMEComponent.h"


class DMEComponentUpdateCounterMock : public DMEComponent
{
public:
	void Update(float dt)
	{
		++updateCount;
	};

	int updateCount = 0;
};

class DMEComponentDeltaTimeSpy : public DMEComponent
{
public:
	void Update(float dt) override
	{
		lastDeltaTime = dt;
	};

	float lastDeltaTime = 0;
};

TEST_GROUP(DMEManager)
{
	DMEManager * manager;

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
	}
};

TEST(DMEManager, IsSingleton)
{
	POINTERS_EQUAL(manager, DMEManager::Get());
}

TEST(DMEManager, IsEmptyOnCreation)
{
	CHECK_TRUE(manager->isEmpty());
}

TEST(DMEManager, IsNotEmptyOnAddComponent)
{
	DecisionTreeComponent component;
	manager->AddComponent(&component);

	CHECK_FALSE(manager->isEmpty());
}

TEST(DMEManager, ComponentIsUpdatedOnEachUpdate)
{
	DMEComponentUpdateCounterMock componentMock;
	manager->AddComponent(&componentMock);

	CallMultipleUpdate(5);

	CHECK_EQUAL(5, componentMock.updateCount);
}

TEST(DMEManager, MultipleComponentsIsUpdateOnEachUpdate)
{
	DMEComponentUpdateCounterMock componentMock1;
	DMEComponentUpdateCounterMock componentMock2;
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

