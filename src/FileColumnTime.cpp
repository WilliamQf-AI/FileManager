#include "FileColumnTime.h"

FileColumnTime::FileColumnTime(std::wstring& text, std::filesystem::file_time_type& time) : FileColumn(text),time{time}
{

}

FileColumnTime::~FileColumnTime()
{
}

bool FileColumnTime::operator>(const FileColumn& other) const
{
	const FileColumnTime& temp = static_cast<const FileColumnTime&>(other);
	return time > temp.time;
}
