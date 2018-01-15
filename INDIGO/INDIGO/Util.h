#pragma once
#include "SDK\SDK.h"
#include <chrono>

	std::string ReplaceString(std::string subject, const std::string& search, const std::string& replace);
	void StdReplaceStr(std::string&, const std::string&, const std::string&);
	const char* PadStringRight(std::string text, size_t value);
	void ProtectAddr(void* address, int prot);
	bool Contains(const std::string &word, const std::string &sentence);