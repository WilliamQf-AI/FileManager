#pragma once

#include <string>

class FileColumnHeader
{
public:
	FileColumnHeader(std::wstring&& title,bool isSort,float minWidth);
	~FileColumnHeader();
	std::wstring title;
	float left;
	float right;
	bool isSort;
	float minWidth;
private:

};