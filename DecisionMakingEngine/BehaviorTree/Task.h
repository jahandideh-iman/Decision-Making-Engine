#pragma once
#include <functional>

#include "Core/Interfaces/GameInterface.h"


class Task : public GameInterface
{
	
public:
	enum TaskResult
	{
		None, Unfinished, Success, Failure,
	};

	typedef std::function<TaskResult(float)> Method;

public:
	Task(Method method);
	~Task();

	TaskResult Invoke(float dt) const;
private:
	Method method = nullptr;

};

