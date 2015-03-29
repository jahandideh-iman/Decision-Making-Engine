#pragma once
#include "DMEComponent.h"
#include "DMEUtilities.h"
#include <string>
#include "rapidxml-1.13/rapidxml.hpp"

using namespace rapidxml;

#define ROOT_XML_NODE "DMEComponent"


typedef xml_node<> XMLNode;

class DMEComponentParser
{
public:
	DMEComponentParser();
	virtual ~DMEComponentParser();

	virtual DMEComponent* Create(std::string rawData) ;

protected:
	virtual DMEComponent* CreateWithData(XMLNode* rootXMLNode) = 0;

	std::string typeName = "";
private:
	XMLNode* GetRootXMLNode(char* rawData);
	bool IsDataValid(XMLNode* rootXMLNode);



};

