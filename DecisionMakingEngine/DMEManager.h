#pragma once

#include "DMEComponent.h"
#include <vector>
#include "rapidxml-1.13/rapidxml.hpp"
#include "DMEUtilities.h"
#include "DMEComponentParser.h"
#include "FiniteStateMachineParser.h"
#include "DecisionTreeParser.h"


using namespace rapidxml;
using namespace std;

class DMEManager
{
	typedef vector<DMEComponent*> ComponentContainer;

	typedef vector<DMEComponentParser*> ParserContainer;

public:
	static DMEManager* Get();
	static void Destroy();

	void AddComponent(DMEComponent* component);

	DMEComponent* CreateComponent(std::istream &stream);

	void Update(float dt = 0);

	bool isEmpty();

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

