#pragma once

#include <string>
class Goal
{
public:
	Goal(std::string name, double initialInsistence = 0, double changeRate = 0);
	~Goal();

	void Update(float dt);

	double GetInsistence();

private:
	std::string name;
	double insistence = 0;
	double changeRate = 0;
};

