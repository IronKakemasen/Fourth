#pragma once


class Logger
{
	static inline std::ofstream logFIle;
	static void Init();

public:

	static void Log(std::string const& message_, const std::string& fileName_ = "");
	static void Entry(const std::string& message_);
	static void End(const std::string& message_);

};


