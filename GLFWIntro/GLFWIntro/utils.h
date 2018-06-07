#pragma once
#include <string>

#define ERROR_LOG(fmt, ...)     log(__FILE__, __LINE__, fmt, __VA_ARGS__)

/**
* @brief utility to log errors
*		 NOTE: http://www.cplusplus.com/articles/Dj2z3TCk/
* @param const char* - file where error occurred
* @param int - line number where error occurred
* @param const std::string& - what of the error
* @param const std::string& - why of the error
*/
void log(const char *ppFile, int ppLine, const std::string &what, const std::string &why, ...);

/**
* @brief reads file data into char
*		 NOTE: ensure that fileData initially is empty
* @param char* - relative path of the file
* @param char* - file data read
*/
void readFile(const char* path, char** fileData);