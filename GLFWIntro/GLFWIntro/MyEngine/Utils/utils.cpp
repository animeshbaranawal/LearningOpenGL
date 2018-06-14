#include "utils.h"

#include <fstream>
#include <array>
#include <cstdarg>
#include <ctime>
#include <sstream>

/// default filename for error logging file
#define ERRLOG_FILENAME     "error_log.txt"
#define TEMPWHY_MAXALLOC    1024

void log(const char *ppFile, int ppLine, const std::string &what, const std::string &why, ...)
{
	const std::time_t rawTime_ = std::time(nullptr); /// seconds since 01-01-1970
	std::string what_ = "(TOP SECRET)";
	std::string why_ = "(The programmer decided you don't need to know more.)";
	std::string ppFile_ = "(Unknown file)";

	/// did the programmer specify the bugged unit?
	if (!what.empty())
		what_ = what;

	if (ppFile != nullptr && *ppFile != '\0')
		ppFile_ = ppFile;

	// TODO: use std::to_string() when available
	what_ = what_ + ", " + ppFile_ + " @ " 
			+ static_cast<std::ostringstream *> (&(std::ostringstream() << ppLine))->str();

	if (!why.empty())
	{
		/// build message from parameters
		std::va_list args_;
		std::array<char, TEMPWHY_MAXALLOC> tempWhy_;

		va_start(args_, why);
		std::vsnprintf(&tempWhy_.front(), tempWhy_.size(), why.c_str(), args_);
		va_end(args_);

		why_ = tempWhy_.data();
	}

	std::ofstream errorLogFile_(ERRLOG_FILENAME, std::ofstream::app);

	if (errorLogFile_.is_open())
	{
		char timeStr[26];
		ctime_s(timeStr, sizeof timeStr, &rawTime_);

		// TODO: check for exceptions
		errorLogFile_
			<< " WHEN --- " << timeStr
			<< " WHAT --- " << what_ << '\n'
			<< "  WHY --- " << why_ << "\n\n";

		errorLogFile_.close();
	}
}

void readFile(const char* path, char** fileData)
{
	/// source : https://stackoverflow.com/questions/2602013/read-whole-ascii-file-into-c-stdstring
	std::ifstream t;
	int length;
	t.open(path);
	t.seekg(0, std::ios::end);
	length = t.tellg();
	t.seekg(0, std::ios::beg);

	if (*fileData)
		delete *fileData;
	*fileData = new char[length];
	t.read(*fileData, length);
	t.close();
}