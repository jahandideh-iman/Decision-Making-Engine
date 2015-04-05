#pragma once

#include <functional>
#include <fstream>
using std::placeholders::_1;
#define BIND_MEMBER_ACTION(MEMBER_FUNCTION, OBJECT) std::bind(&MEMBER_FUNCTION, OBJECT)
#define BIND_MEMBER_UPDATE_ACTION(MEMBER_FUNCTION, OBJECT) std::bind(&MEMBER_FUNCTION, OBJECT, _1 )

#define SAFE_DELETE(pointer) {if (pointer) delete pointer; pointer = nullptr; }


#define DELETE_MAP_CONTAINER(container) { for(auto c: container) delete c.second;}


class FileGuard
{
public:
	FileGuard(std::ifstream &f)
	{
		this->file = &f;
	}

	~FileGuard()
	{
		file->close();
	}

	std::ifstream& Get()
	{
		return *file;
	}

private:
	std::ifstream* file = nullptr;
};