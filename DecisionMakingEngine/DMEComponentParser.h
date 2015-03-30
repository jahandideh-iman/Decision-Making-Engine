#pragma once
#include "DMEComponent.h"
#include "DMEUtilities.h"
#include <string>
#include "rapidxml-1.13/rapidxml.hpp"

using namespace rapidxml;

typedef xml_node<> XMLNode;
typedef xml_attribute<> XMLAttribute;

class DMEComponentParser
{
	class CharArrayWrapper
	{
	public:
		CharArrayWrapper(std::string& str)
		{
			unsigned length = str.length() + 1;
			cstr = new char[length];
			strcpy_s(cstr, length, str.c_str());
		}

		~CharArrayWrapper()
		{
			delete[] cstr;
		}

		char* Get()
		{
			return cstr;
		}

	private:
		char *cstr = nullptr;
	};

public:
	DMEComponentParser();
	virtual ~DMEComponentParser();

	virtual DMEComponent* Create(std::string rawData) ;

protected:
	virtual DMEComponent* CreateWithValidData(XMLNode* rootXMLNode) = 0;

	std::string typeName = "";
private:
	XMLNode* GetRootXMLNode(char* rawData);

	bool IsDataValid(XMLNode* rootXMLNode);
	bool IsTypeMatched(XMLNode* rootXMLNode);
};

