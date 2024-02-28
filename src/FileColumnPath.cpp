#include "FileColumnPath.h"

FileColumnPath::FileColumnPath(std::wstring& text, std::wstring& path)
	: FileColumn(text), path{path}
{
}

FileColumnPath::~FileColumnPath()
{
}
