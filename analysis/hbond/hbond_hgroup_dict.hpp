#ifndef TRYAMP_HYDROGEN_BOND_HEAVYGROUP_DICTIONARY_HPP
#define TRYAMP_HYDROGEN_BOND_HEAVYGROUP_DICTIONARY_HPP
#include<TryAmp/analysis/hbond/hbond_heavygroup.hpp>
#include<unordered_map>

namespace Amp::analysis {

struct HBond_HeavyDonorDict {


/*	=========== ==============
	group       donor         
	=========== ==============
	main chain  N             
	                          
	water       OH2, OW       
	
	ARG         NE, NH1, NH2
	ASN         ND2           
	ASP                       
	CYS         SG
	CYH                       
	GLN         NE2           
	GLU                       
	HIS         ND1, NE2      
	HSD         ND1           
	HSE         NE2           
	HSP         ND1, NE2
	LYS         NZ
	MET                       
	SER         OG            
	THR         OG1           
	TRP         NE1
	TYR         OH            
	=========== ==============
*/


	HBond_HeavyDonorDict() {
		_dict["ALA"] = HBond_HeavyDonor();
		_dict["ARG"] = HBond_HeavyDonor(" NE ", " NH1", " NH2");
		_dict["ASN"] = HBond_HeavyDonor(" ND2");
		_dict["ASP"] = HBond_HeavyDonor();
		_dict["CYS"] = HBond_HeavyDonor(" SG ");
		_dict["CYH"] = HBond_HeavyDonor();
		_dict["GLN"] = HBond_HeavyDonor(" NE2");
		_dict["GLU"] = HBond_HeavyDonor();
		_dict["GLY"] = HBond_HeavyDonor();
		_dict["HIS"] = HBond_HeavyDonor(" ND1", " NE2");
		_dict["HSD"] = HBond_HeavyDonor(" ND1");
		_dict["HSE"] = HBond_HeavyDonor(" NE2");
		_dict["HSP"] = HBond_HeavyDonor(" ND1", " NE2");
		_dict["ILE"] = HBond_HeavyDonor();
		_dict["LEU"] = HBond_HeavyDonor();
		_dict["LYS"] = HBond_HeavyDonor(" NZ ");
		_dict["MET"] = HBond_HeavyDonor();
		_dict["PHE"] = HBond_HeavyDonor();
		_dict["PRO"] = HBond_HeavyDonor();
		_dict["SER"] = HBond_HeavyDonor(" OG ");
		_dict["THR"] = HBond_HeavyDonor(" OG1");
		_dict["TRP"] = HBond_HeavyDonor(" NE1");
		_dict["TYR"] = HBond_HeavyDonor(" OH ");
		_dict["VAL"] = HBond_HeavyDonor();
	}

	HBond_HeavyDonorDict(
		const std::vector<std::string>& aa_keys, const std::vector<HBond_HeavyDonor>& donor_values) {
		if (aa_keys.size() != donor_values.size())
			throw std::invalid_argument(
			"The number of keys is not consistent with that of values");

		_dict["ALA"] = HBond_HeavyDonor();
		_dict["ARG"] = HBond_HeavyDonor(" NE ", " NH1", " NH2");
		_dict["ASN"] = HBond_HeavyDonor(" ND2");
		_dict["ASP"] = HBond_HeavyDonor();
		_dict["CYS"] = HBond_HeavyDonor(" SG ");
		_dict["CYH"] = HBond_HeavyDonor();
		_dict["GLN"] = HBond_HeavyDonor(" NE2");
		_dict["GLU"] = HBond_HeavyDonor();
		_dict["GLY"] = HBond_HeavyDonor();
		_dict["HIS"] = HBond_HeavyDonor(" ND1", " NE2");
		_dict["HSD"] = HBond_HeavyDonor(" ND1");
		_dict["HSE"] = HBond_HeavyDonor(" NE2");
		_dict["HSP"] = HBond_HeavyDonor(" ND1", " NE2");
		_dict["ILE"] = HBond_HeavyDonor();
		_dict["LEU"] = HBond_HeavyDonor();
		_dict["LYS"] = HBond_HeavyDonor(" NZ ");
		_dict["MET"] = HBond_HeavyDonor();
		_dict["PHE"] = HBond_HeavyDonor();
		_dict["PRO"] = HBond_HeavyDonor();
		_dict["SER"] = HBond_HeavyDonor(" OG ");
		_dict["THR"] = HBond_HeavyDonor(" OG1");
		_dict["TRP"] = HBond_HeavyDonor(" NE1");
		_dict["TYR"] = HBond_HeavyDonor(" OH ");
		_dict["VAL"] = HBond_HeavyDonor();

		for (std::size_t idx = 0; idx < aa_keys.size(); ++idx)
			_dict[aa_keys[idx]] = donor_values[idx];
	}



	HBond_HeavyDonor operator[](const std::string& key) {return _dict[key];}
	HBond_HeavyDonor at(const std::string& key) const {return _dict.at(key);}
	std::size_t size() const {return _dict.size();}


private:

	std::unordered_map<std::string, HBond_HeavyDonor> _dict;

};



struct HBond_HeavyAcceptorDict {


/*	===========  =========== 
	group        acceptor    
	===========  =========== 
	main chain   O, OC1, OC2 
	                         
	water        OH2, OW     
	
	ARG         
	ASN          OD1
	ASP          OD1, OD2
	CYS         
	CYH          SG          
	GLN          OE1
	GLU          OE1, OE2
	HIS          ND1, NE2    
	HSD          NE2
	HSE          ND1
	HSP         
	LYS         
	MET          SD          
	SER          OG
	THR          OG1
	TRP         
	TYR          OH
	===========  =========== 
*/

	HBond_HeavyAcceptorDict() {
		_dict["ALA"] = HBond_HeavyAcceptor();
		_dict["ARG"] = HBond_HeavyAcceptor();
		_dict["ASN"] = HBond_HeavyAcceptor(" OD1");
		_dict["ASP"] = HBond_HeavyAcceptor(" OD1", " OD2");
		_dict["CYS"] = HBond_HeavyAcceptor();
		_dict["CYH"] = HBond_HeavyAcceptor(" SG ");
		_dict["GLN"] = HBond_HeavyAcceptor(" OE1");
		_dict["GLU"] = HBond_HeavyAcceptor(" OE1", " OE2");
		_dict["GLY"] = HBond_HeavyAcceptor();
		_dict["HIS"] = HBond_HeavyAcceptor(" ND1", " NE2");
		_dict["HSD"] = HBond_HeavyAcceptor(" NE2");
		_dict["HSE"] = HBond_HeavyAcceptor(" ND1");
		_dict["HSP"] = HBond_HeavyAcceptor();
		_dict["ILE"] = HBond_HeavyAcceptor();
		_dict["LEU"] = HBond_HeavyAcceptor();
		_dict["LYS"] = HBond_HeavyAcceptor();
		_dict["MET"] = HBond_HeavyAcceptor(" SD ");
		_dict["PHE"] = HBond_HeavyAcceptor();
		_dict["PRO"] = HBond_HeavyAcceptor();
		_dict["SER"] = HBond_HeavyAcceptor(" OG ");
		_dict["THR"] = HBond_HeavyAcceptor(" OG1");
		_dict["TRP"] = HBond_HeavyAcceptor();
		_dict["TYR"] = HBond_HeavyAcceptor(" OH ");
		_dict["VAL"] = HBond_HeavyAcceptor();
	}


	HBond_HeavyAcceptorDict(
		const std::vector<std::string>& aa_keys,
		const std::vector<HBond_HeavyAcceptor>& acceptor_values) {

		if (aa_keys.size() != acceptor_values.size())
			throw std::invalid_argument(
			"The number of keys is not consistent with that of values.");

		_dict["ALA"] = HBond_HeavyAcceptor();
		_dict["ARG"] = HBond_HeavyAcceptor();
		_dict["ASN"] = HBond_HeavyAcceptor(" OD1");
		_dict["ASP"] = HBond_HeavyAcceptor(" OD1", " OD2");
		_dict["CYS"] = HBond_HeavyAcceptor();
		_dict["CYH"] = HBond_HeavyAcceptor(" SG ");
		_dict["GLN"] = HBond_HeavyAcceptor(" OE1");
		_dict["GLU"] = HBond_HeavyAcceptor(" OE1", " OE2");
		_dict["GLY"] = HBond_HeavyAcceptor();
		_dict["HIS"] = HBond_HeavyAcceptor(" ND1", " NE2");
		_dict["HSD"] = HBond_HeavyAcceptor(" NE2");
		_dict["HSE"] = HBond_HeavyAcceptor(" ND1");
		_dict["HSP"] = HBond_HeavyAcceptor();
		_dict["ILE"] = HBond_HeavyAcceptor();
		_dict["LEU"] = HBond_HeavyAcceptor();
		_dict["LYS"] = HBond_HeavyAcceptor();
		_dict["MET"] = HBond_HeavyAcceptor(" SD ");
		_dict["PHE"] = HBond_HeavyAcceptor();
		_dict["PRO"] = HBond_HeavyAcceptor();
		_dict["SER"] = HBond_HeavyAcceptor(" OG ");
		_dict["THR"] = HBond_HeavyAcceptor(" OG1");
		_dict["TRP"] = HBond_HeavyAcceptor();
		_dict["TYR"] = HBond_HeavyAcceptor(" OH ");
		_dict["VAL"] = HBond_HeavyAcceptor();

		for (std::size_t idx = 0; idx < aa_keys.size(); ++idx)
			_dict[aa_keys[idx]] = acceptor_values[idx];
	}


	HBond_HeavyAcceptor operator[](const std::string& key) {return _dict[key];}
	HBond_HeavyAcceptor at(const std::string& key) const {return _dict.at(key);}
	std::size_t size() const {return _dict.size();}


private:

	std::unordered_map<std::string, HBond_HeavyAcceptor> _dict;

};

}


#endif // TRYAMP_HYDROGEN_BOND_HEAVYGROUP_DICTIONARY_HPP
