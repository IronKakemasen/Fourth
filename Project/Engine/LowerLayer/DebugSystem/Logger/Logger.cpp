
#include "Logger.h"
#include <filesystem>

void Logger::Init()
{
	static int onlyOnce{ };
	if (onlyOnce++ > 0) return;

	std::filesystem::create_directory("DebugLog");

	//現在時刻を取得
	auto now = std::chrono::system_clock::now();
	std::time_t time_t_now = std::chrono::system_clock::to_time_t(now);

	std::tm localTime{};
	localtime_s(&localTime, &time_t_now);

	//バッファに "YYYYMMDD_HHMMSS" を書き込む
	char buffer[32];
	std::strftime(buffer, sizeof(buffer), "%Y%m%d_%H%M%S", &localTime);

	std::string dateString(buffer);
	std::string logFilePath = std::string("DebugLog/") + dateString + ".log";

	logFIle.open(logFilePath);
}

///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Logger::Log(std::string const& message_, const std::string& fileName_)
{
#ifdef _DEBUG

	Init();

	std::string output = message_;

	if (fileName_.size() > 0)
	{
		static std::string space = " ";
		static std::string colon = ": ";
		static int const numSpace = 88;
		int numSpaceRequired = numSpace - (int)message_.size();

		for (int i = 0;i < numSpaceRequired;++i)
		{
			output += space;
		}

		output += colon + fileName_;
	}

	logFIle << output << std::endl;
	OutputDebugStringA((output + "\n").c_str());

#endif
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Logger::Entry(const std::string& message_)
{
#ifdef _DEBUG

	Init();

	std::string output = "\n[ Entry ]=======----[ " + message_ + " ]----";

	static std::string const lineBreak = "\n";
	static std::string const doubleLine = "=";

	static int const numEnd = 90;
	int numCharRequired = numEnd - (int)output.size();
	for (int i = 0;i < numCharRequired;++i)
	{
		output += doubleLine;
	}

	output += lineBreak;

	logFIle << output << std::endl;
	OutputDebugStringA(output.c_str());
#endif

}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Logger::End(const std::string& message_)
{
#ifdef _DEBUG

	std::string output = "\n[ End ]=========----[ " + message_ + " ]----";

	std::string const lineBreak = "\n";
	std::string const doubleLine = "=";

	int const numEnd = 90;
	int numCharRequired = numEnd - (int)output.size();
	for (int i = 0;i < numCharRequired;++i)
	{
		output += doubleLine;
	}

	output += lineBreak;

	logFIle << output << std::endl;
	OutputDebugStringA(output.c_str());

#endif
}
