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
		return CreateWithData(rootXMLNode);

	return nullptr;
}

xml_node<>* DMEComponentParser::GetRootXMLNode(char* rawData)
{
	xml_document<> xmlData;
	xmlData.parse<0>(rawData);
	return xmlData.first_node(ROOT_XML_NODE);
}


bool DMEComponentParser::IsDataValid(xml_node<> * rootXMLNode)
{
	if (rootXMLNode != nullptr)
	{
		xml_attribute<>* typeAttr = rootXMLNode->first_attribute("type");
		if (typeAttr != nullptr && strcmp(typeAttr->value(), typeName.c_str()) == 0)
			return true;
	}
	return false;
}