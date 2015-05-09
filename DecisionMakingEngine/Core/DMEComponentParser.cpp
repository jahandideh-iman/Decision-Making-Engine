#include "DMEComponentParser.h"


DMEComponentParser::DMEComponentParser()
{
}


DMEComponentParser::~DMEComponentParser()
{
}

DMEComponent* DMEComponentParser::Create(std::string rawData)
{
	CharArrayWrapper wrapper(rawData);
	XMLNode* rootXMLNode = GetRootXMLNode(wrapper.Get());

	if (IsDataValid(rootXMLNode))
		return CreateWithValidData(rootXMLNode);

	return nullptr;
}

xml_node<>* DMEComponentParser::GetRootXMLNode(char* rawData)
{
	xml_document<> xmlData;
	xmlData.parse<0>(rawData);
	return xmlData.first_node("DMEComponent");
}

bool DMEComponentParser::IsDataValid(XMLNode* rootXMLNode)
{
	if (rootXMLNode != nullptr)
		return IsTypeMatched(rootXMLNode);

	return false;
}

bool DMEComponentParser::IsTypeMatched(XMLNode* rootXMLNode)
{
	XMLAttribute* typeAttr = rootXMLNode->first_attribute("type");
	if (typeAttr != nullptr && strcmp(typeAttr->value(), typeName.c_str()) == 0)
		return true;

	return false;
}
