#include "FileColumnSize.h"
#include <format>

FileColumnSize::FileColumnSize(unsigned long long& size) : 
	FileColumn(getText(size)),
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

std::wstring FileColumnSize::getText(unsigned long long& size)
{
	if (size == 0) {
		return std::wstring();
	}
	else if(size < 1024) {
		return std::format(L"{} KB", size);
	}
	else if (size < 1048576) { //1G
		return std::format(L"{} MB", size/1024);
	}
	else{
		return std::format(L"{} GB", size / 1048576);
	}
}
