#include "FileColumnHeader.h"
#include <cwchar>

FileColumnHeader::FileColumnHeader(std::wstring&& title, bool isSort, float minWidth):
	title{ title }, isSort{ isSort },minWidth{minWidth}
{
}

FileColumnHeader::~FileColumnHeader()
{
}