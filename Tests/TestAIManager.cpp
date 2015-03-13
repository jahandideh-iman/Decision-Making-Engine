#include "CppUTest/TestHarness.h"
#include "AIManager.h"
#include "DecisionTreeComponent.h"
#include "FiniteStateComponent.h"


class AIComponentMock : public AIComponent
{
public:
	void Update(float dt)
	{
		++updateCount;
	};

	int GetUpdateCount()
	{
		return updateCount;
	}

private:
	int updateCount = 0;
};


TEST_GROUP(AIManager)
{
	AIManager * manager;

	void CallMultipleUpdate(unsigned numberOfTimes)
	{
		for (unsigned i = 0; i < numberOfTimes; ++i)
			manager->Update();
	}

	void setup()
	{
		manager = AIManager::Get();
	}

	void teardown()
	{
		AIManager::Destroy();
	}
};

TEST(AIManager, IsSingleton)
{
	POINTERS_EQUAL(manager, AIManager::Get());
}

TEST(AIManager, IsEmptyOnCreation)
{
	CHECK_TRUE(manager->isEmpty());
}

TEST(AIManager, IsNotEmptyOnAddComponent)
{
	DecisionTreeComponent component;
	manager->AddComponent(&component);

	CHECK_FALSE(manager->isEmpty());
}

TEST(AIManager, ComponentIsUpdatedOnEachUpdate)
{
	AIComponentMock componentMock;
	manager->AddComponent(&componentMock);

	CallMultipleUpdate(5);

	CHECK_EQUAL(5, componentMock.GetUpdateCount());
}

TEST(AIManager, MultipleComponentsIsUpdateOnEachUpdate)
{
	AIComponentMock componentMock1;
	AIComponentMock componentMock2;
	manager->AddComponent(&componentMock1);
	manager->AddComponent(&componentMock2);

	CallMultipleUpdate(5);

	CHECK_EQUAL(5, componentMock1.GetUpdateCount());
	CHECK_EQUAL(5, componentMock2.GetUpdateCount());
}

