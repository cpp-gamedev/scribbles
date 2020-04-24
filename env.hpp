#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <filesystem>

namespace AssetsManagr
{
using PathSearch = std::vector<std::filesystem::path>;

class env
{
public:
	env(const std::filesystem::path& pathToExeDir);

	const std::filesystem::path GetExeDirectory();
	std::filesystem::path findUpwards(const std::filesystem::path& leaf, const PathSearch& paths_to_search, size_t height);

private:
	std::filesystem::path exeDir;
};
} // namespace Env
