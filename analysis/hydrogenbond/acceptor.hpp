#ifndef TRYAMP_ANALYSIS_HYDROGEN_BOND_ACCEPTOR_DICTIONARY_HPP
#define TRYAMP_ANALYSIS_HYDROGEN_BOND_ACCEPTOR_DICTIONARY_HPP
#include<vector>
#include<string>
#include<unordered_map>

namespace Amp::analysis {

struct AcceptorDict {


	AcceptorDict(
		const std::vector<std::string>& aa_keys,
		const std::vector<std::vector<std::string>>& acceptor_atom_names) {
		if (aa_keys.size() != acceptor_atom_names.size())
			throw std::invalid_argument(
			"The number of keys is not consistent with that of values");

		for (std::size_t idx = 0; idx < aa_keys.size(); ++idx)
			_dict[aa_keys[idx]] = acceptor_atom_names[idx];
	}



	std::vector<std::string> operator[](const std::string& key) {return _dict[key];}
	std::vector<std::string> at(const std::string& key) const {return _dict.at(key);}
	std::size_t size() const {return _dict.size();}


private:

	std::unordered_map<std::string, std::vector<std::string>> _dict;

};


}


#endif // TRYAMP_ANALYSIS_HYDROGEN_BOND_ACCEPTOR_DICTIONARY_HPP
