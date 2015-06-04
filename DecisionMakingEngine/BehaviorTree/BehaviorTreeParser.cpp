#include "BehaviorTreeParser.h"
#include "BehaviorTreeComponent.h"
#include "ActionTask.h"
#include "SequenceTask.h"
#include "SelectorTask.h"

BehaviorTreeParser::BehaviorTreeParser()
{

}

BehaviorTreeParser::~BehaviorTreeParser()
{

}

std::string BehaviorTreeParser::GetTypeName()
{
	return "BehaviorTree";
}

DMEComponent* BehaviorTreeParser::CreateWithValidData(XMLNode* rootXMLNode)
{
	auto component =  new BehaviorTreeComponent();
	XMLNode* treeRootXMLNode = rootXMLNode->first_node("Task");
	component->SetRoot(ExtractTask(component, treeRootXMLNode));

	return component;
}

BehaviorTask* BehaviorTreeParser::ExtractTask(BehaviorTreeComponent* component, XMLNode* xmlNode)
{
	if (xmlNode == nullptr)
		return nullptr;

	std::string nodeType = GetNodeType(xmlNode);

	if (nodeType == "ActionTask")
		return ExtractActionTask(component, xmlNode);
	else if (nodeType == "SequenceTask")
		return ExtractSequenceTask(component, xmlNode);
	else if (nodeType == "SelectorTask")
		return ExtractSelectorTask(component, xmlNode);

	return nullptr;
}

std::string BehaviorTreeParser::GetNodeType(XMLNode* xmlNode)
{
	return xmlNode->first_attribute("type")->value();
}

BehaviorTask* BehaviorTreeParser::ExtractActionTask(BehaviorTreeComponent* component, XMLNode* xmlNode)
{
	auto actionTask = new ActionTask(component);
	XMLNode* actionXMLNode = xmlNode->first_node("Action");
	if (actionXMLNode != nullptr)
		actionTask->SetTaskName(actionXMLNode->value());
	return actionTask;
}

BehaviorTask* BehaviorTreeParser::ExtractSequenceTask(BehaviorTreeComponent* component, XMLNode* xmlNode)
{
	auto sequenceTask = new SequenceTask();

	ParseCompundTaskChildren(component, sequenceTask, xmlNode);
	return sequenceTask;
}

BehaviorTask* BehaviorTreeParser::ExtractSelectorTask(BehaviorTreeComponent* component, XMLNode* xmlNode)
{
	auto selectoraTask = new SelectorTask();

	ParseCompundTaskChildren(component, selectoraTask, xmlNode);
	return selectoraTask;
}

void BehaviorTreeParser::ParseCompundTaskChildren(BehaviorTreeComponent* component, CompoundTask * task, XMLNode* xmlNode)
{
	auto childXMLNode = xmlNode->first_node("Child");
	while (childXMLNode != nullptr)
	{
		task->AddTask(ExtractTask(component, childXMLNode->first_node("Task")));
		childXMLNode = childXMLNode->next_sibling("Child");
	}
}
