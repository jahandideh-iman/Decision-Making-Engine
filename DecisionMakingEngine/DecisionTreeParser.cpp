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
	if (treeRootNode != nullptr)
	{
		string nodeType = treeRootNode->first_attribute("type")->value();
		if (nodeType == "ActionNode")
		{
			ActionNode* root = new ActionNode(component);
			xml_node<>* actionNode = treeRootNode->first_node("Action");
			if (actionNode != nullptr)
				root->SetActionName(actionNode->value());
			component->SetRoot(root);
		}
		if (nodeType == "DecisionNode")
		{
			DecisionNode* root = new DecisionNode(component);
			xml_node<>* conditionNode = treeRootNode->first_node("Condition");
			if (conditionNode != nullptr)
				root->SetConditionName(conditionNode->value());
			component->SetRoot(root);
		}
	}

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
