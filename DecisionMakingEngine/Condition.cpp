#include "Condition.h"

namespace DME
{

	Condition::Condition(Method method)
	{
		this->method = method;
	}


	Condition::~Condition()
	{
	}

	bool Condition::GetResult() const
	{
		if (method != nullptr)
			return method();
	}

}
