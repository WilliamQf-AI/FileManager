#include "FileColumnHeader.h"
#include <cwchar>

FileColumnHeader::FileColumnHeader(std::wstring&& title, bool isSort):
	title{ title }, isSort{ isSort }
{
}

FileColumnHeader::~FileColumnHeader()
{
}