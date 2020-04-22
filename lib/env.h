#include <iostream>
#include <vector>
#include <string>
#include <filesystem>

#ifndef ENV_H
#define ENV_H

using PathSearch = std::vector<std::filesystem::path>;

class Env
{
public:
	Env(const std::filesystem::path& pathToExeDir) : exeDir(pathToExeDir){};

	const std::filesystem::path GetExeDirectory();
	std::filesystem::path findUpwards(const std::filesystem::path& leaf, const PathSearch& paths_to_search, size_t height);

private:
	const std::filesystem::path exeDir;
};

#endif /* ENV_H */