#include "DecisionTreeParser.h"


DecisionTreeParser::DecisionTreeParser()
{
}


DecisionTreeParser::~DecisionTreeParser()
{
}

DecisionTreeComponent* DecisionTreeParser::Create(std::istream &stream)
{
	CharArrayWrapper wrapper(ReadData(stream));
	xml_node<>* rootNode = GetRootNode(wrapper);

	if (IsDataValid(rootNode))
		return CreateWithData(rootNode);

	return nullptr;
}

DecisionTreeComponent* DecisionTreeParser::CreateWithData(xml_node<> * rootNode)
{
	DecisionTreeComponent* component = new DecisionTreeComponent();
	xml_node<>* treeRootNode = rootNode->first_node("Node");

	component->SetRoot(ParseComponentNode(component, treeRootNode));

	return component;
}


std::string DecisionTreeParser::ReadData(std::istream &stream)
{
	std::istreambuf_iterator<char> eos;
	return std::string(std::istreambuf_iterator<char>(stream), eos);
}

bool DecisionTreeParser::IsDataValid(xml_node<> * rootNode)
{
	if (rootNode != nullptr)
	{
		xml_attribute<>* typeAttr = rootNode->first_attribute("type");
		if (typeAttr != nullptr && strcmp(typeAttr->value(), "DecisionTree") == 0)
			return true;
	}
	return false;
}


xml_node<>* DecisionTreeParser::GetRootNode(CharArrayWrapper& wrapper)
{
	xml_document<> xmlData;
	xmlData.parse<0>(wrapper.Get());
	return xmlData.first_node("DMEComponent");
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
