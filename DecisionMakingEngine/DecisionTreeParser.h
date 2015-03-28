#pragma once

#include <iostream>
#include "rapidxml-1.13/rapidxml.hpp"
#include "DecisionTreeComponent.h"
#include "ActionNode.h"
#include "DecisionNode.h"
#include "DMEUtilities.h"

using namespace rapidxml;
using namespace std;

class DecisionTreeParser
{
public:
	static DecisionTreeComponent* Create(std::istream &stream);
private:
	static DecisionTreeComponent* CreateWithData(xml_node<> * rootNode);
	static bool IsDataValid(xml_node<> * rootNode);
	static std::string ReadData(std::istream &stream);

	static xml_node<>* GetRootNode(CharArrayWrapper& wrapper);

	DecisionTreeParser();
	~DecisionTreeParser();
	static DecisionTreeNode* ParseComponentNode(DecisionTreeComponent* component, xml_node<>* treeNode);

};

