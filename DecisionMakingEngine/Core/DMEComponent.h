#pragma once
class DMEComponent
{
public:
	DMEComponent(){};
	virtual ~DMEComponent() {};

	virtual void Update(float dt) = 0;
};

