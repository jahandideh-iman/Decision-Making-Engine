#pragma once

#include <functional>
using std::placeholders::_1;
#define BIND_MEMBER_ACTION(MEMBER_FUNCTION, OBJECT) std::bind(&MEMBER_FUNCTION, OBJECT)
#define BIND_MEMBER_UPDATE_ACTION(MEMBER_FUNCTION, OBJECT) std::bind(&MEMBER_FUNCTION, OBJECT, _1 )

