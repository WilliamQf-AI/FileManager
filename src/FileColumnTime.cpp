#include "FileColumnTime.h"
#include <format>

FileColumnTime::FileColumnTime(SYSTEMTIME& time) : FileColumn(getText(time)),time{time}
{

}

FileColumnTime::~FileColumnTime()
{
}

bool FileColumnTime::operator>(const FileColumn& other) const
{
	const FileColumnTime& temp = static_cast<const FileColumnTime&>(other);
    if (time.wYear > temp.time.wYear) return true;
    if (time.wYear < temp.time.wYear) return false;
    if (time.wMonth > temp.time.wMonth) return true;
    if (time.wMonth < temp.time.wMonth) return false;
    if (time.wDay > temp.time.wDay) return true;
    if (time.wDay < temp.time.wDay) return false;
    if (time.wHour > temp.time.wHour) return true;
    if (time.wHour < temp.time.wHour) return false;
    if (time.wMinute > temp.time.wMinute) return true;
    if (time.wMinute < temp.time.wMinute) return false;
    if (time.wSecond > temp.time.wSecond) return true;
    if (time.wSecond < temp.time.wSecond) return false;
    if (time.wMilliseconds > temp.time.wMilliseconds) return true;
    return false;
}

std::wstring FileColumnTime::getText(SYSTEMTIME& time)
{
    return std::format(L"{}-{}-{} {}:{}:{}",time.wYear,time.wMonth,time.wDay,time.wHour,time.wMinute,time.wSecond);
}
