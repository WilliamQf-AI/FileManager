#include "FileColumnSize.h"
#include <format>

FileColumnSize::FileColumnSize(unsigned long long& size) : 
	FileColumn(size==0?std::wstring(L""):std::format(L"{} KB",size)),
	size{size}
{

}

FileColumnSize::~FileColumnSize()
{
}

bool FileColumnSize::operator>(const FileColumn& other) const
{
	const FileColumnSize& temp = static_cast<const FileColumnSize&>(other);
	return size > temp.size;
}
