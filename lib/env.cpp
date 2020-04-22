#include "env.h"

const std::filesystem::path Env::GetExeDirectory()
{
	return this->exeDir;
}

// Source: Karnage
std::filesystem::path Env::findUpwards(const std::filesystem::path& leaf, const PathSearch& paths_to_search, size_t height)
{
	for (const auto& p : paths_to_search)
	{
		auto pth = leaf / p;
		if (std::filesystem::is_directory(pth) || std::filesystem::is_regular_file(pth))
		{
			return pth.parent_path() / pth;
		}
	}

	bool to_stop = height == 0 || leaf.empty() || !leaf.has_parent_path() || leaf == leaf.root_path();
	if (to_stop)
	{
		return {};
	}

	return findUpwards(leaf.parent_path(), paths_to_search, height -= 1);
}