#include "DecisionTreeParser.h"


DecisionTreeParser::DecisionTreeParser()
{
	typeName = "DecisionTree";
}


DecisionTreeParser::~DecisionTreeParser()
{
}


DMEComponent* DecisionTreeParser::CreateWithData(xml_node<> * rootNode)
{
	DecisionTreeComponent* component = new DecisionTreeComponent();
	xml_node<>* treeRootNode = rootNode->first_node("Node");

	component->SetRoot(ParseComponentNode(component, treeRootNode));

	return component;
}





DecisionTreeNode* DecisionTreeParser::ParseComponentNode(DecisionTreeComponent* component, xml_node<>* treeNode)
{
	if (treeNode == nullptr)
		return nullptr;

	string nodeType = treeNode->first_attribute("type")->value();
	if (nodeType == "ActionNode")
	{
		ActionNode* node = new ActionNode(component);
		xml_node<>* actionNode = treeNode->first_node("Action");
		if (actionNode != nullptr)
			node->SetActionName(actionNode->value());
		return node;
	}
	if (nodeType == "DecisionNode")
	{
		DecisionNode* root = new DecisionNode(component);
		xml_node<>* conditionNode = treeNode->first_node("Condition");
		if (conditionNode != nullptr)
			root->SetConditionName(conditionNode->value());

		xml_node<>* truePathNode = treeNode->first_node("TruePath");
		if (truePathNode != nullptr)
		{
			root->SetTruePathNode(ParseComponentNode(component, truePathNode->first_node("Node")));
		}

		xml_node<>* falsePathNode = treeNode->first_node("FalsePath");
		if (falsePathNode != nullptr)
		{
			root->SetFalsePathNode(ParseComponentNode(component, falsePathNode->first_node("Node")));
		}

		return root;

	}
	return nullptr;
}
