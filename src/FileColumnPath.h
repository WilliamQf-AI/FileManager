#pragma once
#include "FileColumn.h"
#include <filesystem>
#include <Windows.h>

class FileColumnPath :public FileColumn
{
public:
	FileColumnPath(std::wstring& text, std::wstring& path);
	~FileColumnPath();
	std::wstring path;
private:

};