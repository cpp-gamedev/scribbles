#include "env.hpp"

AssetsManagr::env::env(const std::filesystem::path& pathToExeDir)
{
	this->exeDir = pathToExeDir;
}

const std::filesystem::path AssetsManagr::env::GetExeDirectory()
{
	return this->exeDir;
}

// Source: Karnage
std::filesystem::path AssetsManagr::env::findUpwards(const std::filesystem::path& leaf, const PathSearch& paths_to_search, size_t height)
{
	for (const auto& p : paths_to_search)
	{
		auto path = leaf / p;
		if (std::filesystem::is_directory(path) || std::filesystem::is_regular_file(path))
		{
			std::filesystem::path name = leaf.filename() == "." ? leaf.parent_path() : leaf;
			return name / p;
		}
	}

	bool to_stop = height == 0 || leaf.empty() || !leaf.has_parent_path() || leaf == leaf.root_path();
	if (to_stop)
	{
		return {};
	}

	return findUpwards(leaf.parent_path(), paths_to_search, height -= 1);
}