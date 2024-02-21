#include "FileColumn.h"

FileColumn::FileColumn(std::wstring& text) :text{ text } {

}
FileColumn::FileColumn(std::wstring&& text) :text{ text } {

}
FileColumn::~FileColumn() {

}

bool FileColumn::operator>(const FileColumn& other) const
{
	return text>other.text;
}
