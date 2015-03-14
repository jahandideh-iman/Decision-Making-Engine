#pragma once
class DMEComponent
{
public:
	DMEComponent(){};
	~DMEComponent(){};

	virtual void Update(float dt) = 0;
};

