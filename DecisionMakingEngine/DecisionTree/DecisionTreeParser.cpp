#include "DecisionTreeParser.h"


DecisionTreeParser::DecisionTreeParser()
{
	typeName = "DecisionTree";
}


DecisionTreeParser::~DecisionTreeParser()
{
}


DMEComponent* DecisionTreeParser::CreateWithValidData(XMLNode* rootXMLNode)
{
	DecisionTreeComponent* component = new DecisionTreeComponent();

	XMLNode* treeRootXMLNode = rootXMLNode->first_node("Node");
	component->SetRoot(ExtractNode(component, treeRootXMLNode));

	return component;
}

DecisionTreeNode* DecisionTreeParser::ExtractNode(DecisionTreeComponent* component, XMLNode* xmlNode)
{
	if (xmlNode == nullptr)
		return nullptr;

	std::string nodeType = GetNodeType(xmlNode);

	if (nodeType == "ActionNode")
		return ExtractActionNode(component, xmlNode);
	else if (nodeType == "DecisionNode")
		return ExtractDecisionNode(component, xmlNode);

	return nullptr;
}

std::string DecisionTreeParser::GetNodeType(XMLNode* xmlNode)
{
	return xmlNode->first_attribute("type")->value();
}

DecisionTreeNode* DecisionTreeParser::ExtractActionNode(DecisionTreeComponent* component, XMLNode* xmlNode)
{
	ActionNode* actionNode = new ActionNode(component);
	XMLNode* actionXMLNode = xmlNode->first_node("Action");
	if (actionXMLNode != nullptr)
		actionNode->SetActionName(actionXMLNode->value());
	return actionNode;
}

DecisionTreeNode* DecisionTreeParser::ExtractDecisionNode(DecisionTreeComponent* component, XMLNode* xmlNode)
{
	DecisionNode* decisionNode = new DecisionNode(component);

	ParseDecisionNodeCondition(decisionNode, xmlNode);
	ParseDecisionNodeTruePathNode(decisionNode, component, xmlNode);
	ParseDecisionNodeFalsePathNode(decisionNode, component, xmlNode);

	return decisionNode;
}

void DecisionTreeParser::ParseDecisionNodeCondition(DecisionNode* decisionNode, XMLNode* xmlNode)
{
	XMLNode* conditionXMLNode = xmlNode->first_node("Condition");
	if (conditionXMLNode != nullptr)
		decisionNode->SetConditionName(conditionXMLNode->value());
}

void DecisionTreeParser::ParseDecisionNodeTruePathNode(DecisionNode* decisionNode, DecisionTreeComponent* component, XMLNode* xmlNode)
{
	XMLNode* truePathNode = xmlNode->first_node("TruePath");
	if (truePathNode != nullptr)
		decisionNode->SetTruePathNode(ExtractNode(component, truePathNode->first_node("Node")));
}

void DecisionTreeParser::ParseDecisionNodeFalsePathNode(DecisionNode* decisionNode, DecisionTreeComponent* component, XMLNode* xmlNode)
{
	XMLNode* falsePathNode = xmlNode->first_node("FalsePath");
	if (falsePathNode != nullptr)
		decisionNode->SetFalsePathNode(ExtractNode(component, falsePathNode->first_node("Node")));
}


