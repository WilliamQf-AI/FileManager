#pragma once

#include <string>

class FileColumn
{
public:
	FileColumn(std::wstring& text);
	FileColumn(std::wstring&& text);
	~FileColumn();
	std::wstring text;
	virtual bool operator>(const FileColumn& other) const;
private:

};