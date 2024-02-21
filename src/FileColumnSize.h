#pragma once
#include "FileColumn.h"
#include <filesystem>

class FileColumnSize:public FileColumn
{
public:
	FileColumnSize(int& size);
	~FileColumnSize();
	int size;
	bool operator>(const FileColumn& other) const override;
private:

};