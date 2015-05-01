#pragma once

#include <iostream>
#include "rapidxml-1.13/rapidxml.hpp"
#include "DecisionTreeComponent.h"
#include "ActionNode.h"
#include "DecisionNode.h"
#include "DMEUtilities.h"
#include "DMEComponentParser.h"

using namespace rapidxml;


class DecisionTreeParser : public DMEComponentParser
{
public:
	DecisionTreeParser();
	~DecisionTreeParser();

protected:
	DMEComponent* CreateWithValidData(XMLNode* rootXMLNode) override;

private:
	DecisionTreeNode* ExtractNode(DecisionTreeComponent* component, XMLNode* xmlNode);
	std::string GetNodeType(XMLNode* xmlNode);

	DecisionTreeNode* ExtractActionNode(DecisionTreeComponent* component, XMLNode* xmlNode);
	DecisionTreeNode* ExtractDecisionNode(DecisionTreeComponent* component, XMLNode* xmlNode);

	void ParseDecisionNodeFalsePathNode(DecisionNode* decisionNode, DecisionTreeComponent* component, XMLNode* xmlNode);
	void ParseDecisionNodeTruePathNode(DecisionNode* decisionNode, DecisionTreeComponent* component, XMLNode* xmlNode);
	void ParseDecisionNodeCondition(DecisionNode* decisionNode, XMLNode* xmlNode);

};

