#pragma once

#include <functional>
using std::placeholders::_1;
#define BIND_MEMBER_ACTION(MEMBER_FUNCTION, OBJECT) std::bind(&MEMBER_FUNCTION, OBJECT)
#define BIND_MEMBER_UPDATE_ACTION(MEMBER_FUNCTION, OBJECT) std::bind(&MEMBER_FUNCTION, OBJECT, _1 )

#define SAFE_DELETE(pointer) {if (pointer) delete pointer; pointer = nullptr; }

class CharArrayWrapper
{
public:
	CharArrayWrapper(std::string& str)
	{
		cstr = new char[str.length() + 1];
		strcpy_s(cstr, str.length() + 1, str.c_str());
	}

	~CharArrayWrapper()
	{
		delete[] cstr;
	}

	char* Get()
	{
		return cstr;
	}

private:
	char *cstr = nullptr;
};