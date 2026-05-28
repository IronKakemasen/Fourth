#pragma once


class Logger
{
	static inline std::ofstream logFIle;

public:
	Logger();

	void Log(std::string const& str_);
	void Log(std::ostream& os, std::string const& message);

};

