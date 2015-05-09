#pragma once
#include "CompoundTask.h"
class SequenceTask :
	public CompoundTask
{
public:
	SequenceTask();
	TaskResult ProcessTask(float dt) override;

};

