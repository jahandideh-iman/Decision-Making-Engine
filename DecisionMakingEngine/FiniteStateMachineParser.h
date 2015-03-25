#pragma once

#include <iostream>
#include "rapidxml-1.13/rapidxml.hpp"
#include "FiniteStateMachineComponent.h"

using namespace rapidxml;
using namespace std;

#define ROOT_ELEMENT "DMEComponent"
#define TYPE_ATTRIBUTE "type"
#define TYPE_NAME "FiniteStateMachine"
#define STATES_ELEMENT "States"
#define STATE_ELEMENT "State"
#define STATE_NAME_ELEMENT "Name"

class FiniteStateMachineParser
{
public:
	class CharArrayWrapper
	{
	public:
		CharArrayWrapper(std::string& str)
		{
			cstr = new char[str.length() + 1];
			strcpy_s(cstr, str.length() + 1, str.c_str());
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

	static FiniteStateMachineComponent* Create(std::istream &stream);




private:
	FiniteStateMachineParser();
	~FiniteStateMachineParser();

	static FiniteStateMachineComponent* CreateWithData(xml_node<> * rootNode);
	static bool IsDataValid(xml_node<> * rootNode);
	static std::string ReadData(std::istream &stream);
	static void ParseComponentStates(FiniteStateMachineComponent* component, xml_node<> * rootNode);
	static xml_node<>* GetRootNode(CharArrayWrapper& wrapper);

};

