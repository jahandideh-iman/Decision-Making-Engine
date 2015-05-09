#pragma once

#include "Core/DMEComponentParser.h"

class BehaviorTreeComponent;
class BehaviorTask;
class CompoundTask;

class BehaviorTreeParser : public DMEComponentParser
{
public:
	BehaviorTreeParser();
	~BehaviorTreeParser();

protected:
	DMEComponent* CreateWithValidData(XMLNode* rootXMLNode);

	std::string GetTypeName() override;

private:
	BehaviorTask* ExtractTask(BehaviorTreeComponent* component, XMLNode* xmlNode);
	std::string GetNodeType(XMLNode* xmlNode);

	BehaviorTask* ExtractActionTask(BehaviorTreeComponent* component, XMLNode* xmlNode);
	BehaviorTask* ExtractSequenceTask(BehaviorTreeComponent* component, XMLNode* xmlNode);
	BehaviorTask* ExtractSelectorTask(BehaviorTreeComponent* component, XMLNode* xmlNode);

	void ParseCompundTaskChildren(BehaviorTreeComponent* component, CompoundTask * task, XMLNode* xmlNode);

};