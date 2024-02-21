#include "FileColumnSize.h"

FileColumnSize::FileColumnSize(int& size) : FileColumn(std::to_wstring(size)),size{size}
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
