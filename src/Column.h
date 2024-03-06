#include <string>
#include <Windows.h>

template<typename T>
class Column
{
public:
	Column(T& val) :val{val} {

	}
	~Column() {

	}
	bool operator>(const Column& other) const
	{
		if constexpr (std::is_same_v<T, SYSTEMTIME>) {
			if (val.wYear > other.val.wYear) return true;
			if (val.wYear < other.val.wYear) return false;
			if (val.wMonth > other.val.wMonth) return true;
			if (val.wMonth < other.val.wMonth) return false;
			if (val.wDay > other.val.wDay) return true;
			if (val.wDay < other.val.wDay) return false;
			if (val.wHour > other.val.wHour) return true;
			if (val.wHour < other.val.wHour) return false;
			if (val.wMinute > other.val.wMinute) return true;
			if (val.wMinute < other.val.wMinute) return false;
			if (val.wSecond > other.val.wSecond) return true;
			if (val.wSecond < other.val.wSecond) return false;
			if (val.wMilliseconds > other.val.wMilliseconds) return true;
			return false;
		}
		else {
			return val > other.val;
		}
	}
	std::wstring getText() {
		if constexpr (std::is_same_v<T, unsigned long long>) {
			if (val == 0) {
				return std::wstring();
			}
			else if (val < 1024) {
				return std::format(L"{} KB", T);
			}
			else if (val < 1048576) { //1G
				return std::format(L"{} MB", T / 1024);
			}
			else {
				return std::format(L"{} GB", T / 1048576);
			}
		}
		else if constexpr (std::is_same_v<T, SYSTEMTIME>) {
			return std::format(L"{}-{}-{} {}:{}:{}", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
		}
		else {
			return T;
		}
	}
private:
	T val;
};