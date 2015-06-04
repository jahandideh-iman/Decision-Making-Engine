#pragma once

#include "GameInterface.h"

namespace DME
{
	class Action : public GameInterface
	{
	public:
		Action();
		virtual ~Action();

		virtual void Invoke(float dt) const = 0;
	};
}
