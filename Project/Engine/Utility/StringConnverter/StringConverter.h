#pragma once

namespace StringConverter
{
	std::wstring ConvertString(const std::string& str);
	std::string ConvertString(const std::wstring& str);
	std::string ToUTF8(const std::wstring& value);
}

