#pragma once
class AIComponent
{
public:
	AIComponent();
	~AIComponent();

	virtual void Update(float dt) = 0;
};

