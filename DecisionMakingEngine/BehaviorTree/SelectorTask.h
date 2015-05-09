#pragma once
#include "CompoundTask.h"


class SelectorTask :
	public CompoundTask
{
public:
	SelectorTask();

	TaskResult ProcessTask(float dt) override;
};

