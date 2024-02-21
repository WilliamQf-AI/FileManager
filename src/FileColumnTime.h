#pragma once
#include "FileColumn.h"
#include <filesystem>

class FileColumnTime:public FileColumn
{
public:
	FileColumnTime(std::wstring& text, std::filesystem::file_time_type& time);
	~FileColumnTime();
	std::filesystem::file_time_type time;
	bool operator>(const FileColumn& other) const override;
private:

};