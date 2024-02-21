#pragma once

#include <string>

class FileColumnHeader
{
public:
	FileColumnHeader(std::wstring&& title,bool isSort);
	~FileColumnHeader();
	std::wstring title;
	float left;
	float right;
	bool isSort;
private:

};