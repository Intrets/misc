#pragma once

namespace misc
{
	auto filter_unique(auto& x) {
		std::ranges::sort(x);
		auto range = std::ranges::unique(x);
		x.erase(range.begin(), range.end());
	}
}