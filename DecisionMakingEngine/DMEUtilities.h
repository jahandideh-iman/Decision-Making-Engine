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
		length = str.length() + 1;
		cstr = new char[length];
		strcpy_s(cstr,length, str.c_str());
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
	unsigned length = 0;
};