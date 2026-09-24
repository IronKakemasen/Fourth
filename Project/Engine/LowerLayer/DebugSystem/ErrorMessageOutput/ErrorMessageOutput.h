#pragma once


namespace ErrorMessageOutput
{
	namespace Abort
	{
		void OutputError(const std::string& message_, const std::string& fileName_);
		void DetectError(bool positiveResult_, const std::string& message_, const std::string& fileName_);
	}

	namespace Assert
	{
		void OutputError(const std::string& message_, const std::string& fileName_);
		void DetectError(bool positiveResult_, const std::string& message_, const std::string& fileName_);
	}

}


