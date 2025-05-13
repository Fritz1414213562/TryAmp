#ifndef TRYAMP_STARTS_WITH_HPP
#define TRYAMP_STARTS_WITH_HPP
#include<string>
#include<algorithm>

namespace Amp {
namespace strmanage{
	bool startswith(const std::string& s, const std::string& prefix) {
		if (s.size() < prefix.size()) return false;
		return std::equal(std::begin(prefix), std::end(prefix), std::begin(s));
	}
}
}


#endif // TRYAMP_STARTS_WITH_HPP
