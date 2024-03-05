#pragma once
#include "FileColumn.h"
#include <filesystem>

class FileColumnSize:public FileColumn
{
public:
	FileColumnSize(unsigned long long& size);
	~FileColumnSize();
	unsigned long long size;
	bool operator>(const FileColumn& other) const override;
private:
	std::wstring getText(unsigned long long& size);
};