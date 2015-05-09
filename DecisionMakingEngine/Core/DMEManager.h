#pragma once

#include "DMEComponent.h"
#include <vector>
#include "DMEUtilities.h"
#include "DMEComponentParser.h"
#include "FiniteStateMachine/FiniteStateMachineParser.h"
#include "DecisionTree/DecisionTreeParser.h"
#include "BehaviorTree/BehaviorTreeParser.h"


class DMEManager
{
	typedef vector<DMEComponent*> ComponentContainer;
	typedef vector<DMEComponentParser*> ParserContainer;

public:
	static DMEManager* Get();
	static void Destroy();

	void AddComponent(DMEComponent* component);

	DMEComponent* CreateComponentFromFile(std::string fileName);
	//Note: This function is public for testing
	DMEComponent* CreateComponent(std::istream &stream);

	void Update(float dt = 0);

	bool IsEmpty() const;

private:
	DMEManager();
	~DMEManager();
	
	std::string ReadData(std::istream &stream);

	void InitialDefaultParsers();

private:
	static DMEManager* manager;
	ComponentContainer components;
	ParserContainer parsers;
};

