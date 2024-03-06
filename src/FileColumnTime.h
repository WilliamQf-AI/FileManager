#pragma once
#include "FileColumn.h"
#include <Windows.h>

class FileColumnTime:public FileColumn
{
public:
	FileColumnTime(SYSTEMTIME& time);
	~FileColumnTime();
	SYSTEMTIME time;
	bool operator>(const FileColumn& other) const override;
private:
	std::wstring getText(SYSTEMTIME& time);
};