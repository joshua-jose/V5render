#include "FastPix3D.h"
#include <sstream>


sbyte Convert::ToSByte(string value)
{
	return sbyte(atol(value.c_str()));
}
int16 Convert::ToInt16(string value)
{
	return int16(atol(value.c_str()));
}
int32 Convert::ToInt32(string value)
{
	return atol(value.c_str());
}
int64 Convert::ToInt64(string value)
{
	//return _atoi64((value.c_str()));
	throw std::runtime_error(""); // 32 bit system
}
std::byte Convert::ToByte(string value)
{
	return byte(atol(value.c_str()));
}
float Convert::ToFloat(string value)
{
	return float(atof(value.c_str()));
}
double Convert::ToDouble(string value)
{
	return atof(value.c_str());
}

string Convert::ToString(sbyte value)
{
	return ToString(int64(value));
}
string Convert::ToString(int16 value)
{
	return ToString(int64(value));
}
string Convert::ToString(int32 value)
{
	return ToString(int64(value));
}
string Convert::ToString(int64 value)
{
	std::ostringstream oss;
	uint64 i;
	oss << i;
	std:string ret(oss.str());
	return ret;
}
string Convert::ToString(byte value)
{
	return ToString(int64(value));
}
string Convert::ToString(uint16 value)
{
	return ToString(uint64(value));
}
string Convert::ToString(uint32 value)
{
	return ToString(uint64(value));
}
string Convert::ToString(uint64 value)
{
	std::ostringstream oss;
	uint64 i;
	oss << i;
	std:string ret(oss.str());
	return ret;
}
string Convert::ToString(wstring value)
{
	return string(value.begin(), value.end());
}
