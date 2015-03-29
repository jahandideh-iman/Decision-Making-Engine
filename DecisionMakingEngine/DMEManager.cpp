#include "DMEManager.h"

DMEManager* DMEManager::manager = nullptr;

DMEManager::DMEManager()
{
	InitialDefaultParsers();
}

DMEManager::~DMEManager()
{
	for (auto parser : parsers)
		delete parser;
}

void DMEManager::AddComponent(DMEComponent* component)
{
	components.push_back(component);
}

void DMEManager::Update(float dt)
{
	for (DMEComponent* c : components)
		c->Update(dt);
}

DMEManager* DMEManager::Get()
{
	if (manager == nullptr)
		manager = new DMEManager();
	return manager;
}

void DMEManager::Destroy()
{
	delete manager;
	manager = nullptr;
}

bool DMEManager::isEmpty()
{
	return components.empty();
}

DMEComponent* DMEManager::CreateComponent(std::istream &stream)
{
	string data = ReadData(stream);
	
	for (auto parser : parsers)
	{
		DMEComponent* comp;
		comp = parser->Create(data);
		if (comp != nullptr)
			return comp;
	}
	return nullptr;
}

std::string DMEManager::ReadData(std::istream &stream)
{
	std::istreambuf_iterator<char> eos;
	return std::string(std::istreambuf_iterator<char>(stream), eos);
}

void DMEManager::InitialDefaultParsers()
{
	parsers.push_back(new DecisionTreeParser());
	parsers.push_back(new FiniteStateMachineParser());
}
