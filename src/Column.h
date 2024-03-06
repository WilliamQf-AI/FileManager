#include <string>
#include <Windows.h>


class ColumnBase
{
public:
	ColumnBase() {};
	~ColumnBase() {};
	virtual bool operator>(const ColumnBase& other) const { return false; };
	virtual std::wstring getText() { return std::wstring(); };
private:

};

/// <summary>
/// todo 这个类没用上
/// 因为：循环显示列内容的时候，会有太多类型判断了
/// 
/// </summary>
/// <typeparam name="T"></typeparam>
template<typename T>
class Column:public ColumnBase
{
public:
	Column(T& val) :val{val} {

	}
	~Column() {

	}
	virtual bool operator>(const ColumnBase& other) const override
	{
		const Column<T>& temp = static_cast<const Column<T>&>(other);
		if constexpr (std::is_same_v<T, SYSTEMTIME>) {
			if (val.wYear > temp.val.wYear) return true;
			if (val.wYear < temp.val.wYear) return false;
			if (val.wMonth > temp.val.wMonth) return true;
			if (val.wMonth < temp.val.wMonth) return false;
			if (val.wDay > temp.val.wDay) return true;
			if (val.wDay < temp.val.wDay) return false;
			if (val.wHour > temp.val.wHour) return true;
			if (val.wHour < temp.val.wHour) return false;
			if (val.wMinute > temp.val.wMinute) return true;
			if (val.wMinute < temp.val.wMinute) return false;
			if (val.wSecond > temp.val.wSecond) return true;
			if (val.wSecond < temp.val.wSecond) return false;
			if (val.wMilliseconds > temp.val.wMilliseconds) return true;
			return false;
		}
		else {
			return val > temp.val;
		}
	}
	virtual std::wstring getText() override {
		if constexpr (std::is_same_v<T, unsigned long long>) {
			if (val == 0) {
				return std::wstring();
			}
			else if (val < 1024) {
				return std::format(L"{} KB", val);
			}
			else if (val < 1048576) { //1G
				return std::format(L"{} MB", val / 1024);
			}
			else {
				return std::format(L"{} GB", val / 1048576);
			}
		}
		else if constexpr (std::is_same_v<T, SYSTEMTIME>) {
			return std::format(L"{}-{}-{} {}:{}:{}", val.wYear, val.wMonth, val.wDay, val.wHour, val.wMinute, val.wSecond);
		}
		else {
			return val;
		}
	}
private:
	T val;
};