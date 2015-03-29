#pragma once

#include <iostream>
#include "rapidxml-1.13/rapidxml.hpp"
#include "DecisionTreeComponent.h"
#include "ActionNode.h"
#include "DecisionNode.h"
#include "DMEUtilities.h"
#include "DMEComponentParser.h"

using namespace rapidxml;
using namespace std;

class DecisionTreeParser : public DMEComponentParser
{
public:
	DecisionTreeParser();
	~DecisionTreeParser();

protected:
	DMEComponent* CreateWithData(xml_node<> * rootNode) override;

private:
	static DecisionTreeNode* ParseComponentNode(DecisionTreeComponent* component, xml_node<>* treeNode);

};

