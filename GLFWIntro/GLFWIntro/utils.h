#pragma once

/**
* @brief reads file data into char
*		 NOTE: ensure that fileData initially is empty
* @param char* - relative path of the file
* @param char* - file data read
*/
void readFile(const char* path, char** fileData);