#include "Goal.h"


Goal::Goal(std::string name, double initialInsistence, double changeRate)
{
	this->name = name;
	this->insistence = initialInsistence;
	this->changeRate = changeRate;

}

Goal::~Goal()
{
}

double Goal::GetInsistence()
{
	return insistence;
}

void Goal::Update(float dt)
{
	insistence += changeRate * dt;
}
