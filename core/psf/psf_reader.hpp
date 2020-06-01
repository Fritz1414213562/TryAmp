#ifndef TRYAMP_PSF_READER_HPP
#define TRYAMP_PSF_READER_HPP
#include<TryAmp/core/psf/psf_parser.hpp>
#include<TryAmp/core/psf/psf_data_type/psf_topology.hpp>
#include<string>
#include<vector>
#include<algorithm>
#include<iostream>
#include<tuple>


namespace Amp {


class PSFReader : public PSFParser {

public:

	PSFReader() : PSFParser() {}
	PSFReader(const std::string& filename) : PSFParser(filename) {}
	~PSFReader() = default; 


	PSF_Topology read_Topology(const std::string& filename) {
		open(filename);
		return read_Topology();
	}


	 PSF_Topology read_Topology() {
		open();
		
		std::string buffer;
		constexpr std::size_t min_line_size = 15;
		bool isAtomBlock = false;
		bool isBondBlock = false;

		std::size_t block_atom_num = 0;
		std::size_t block_bond_num = 0;

		PSF_Topology result;

		while (std::getline(input_file, buffer)) {
			if (buffer.size() < min_line_size) continue;
			else if (read_BlockKind(buffer) == "!NATOM") {
				isBondBlock = false;
				isAtomBlock = true;
				block_atom_num = read_BlockNum(buffer);
				continue;
			}
			else if (read_BlockKind(buffer) == "!NBOND") {
				isAtomBlock = false;
				isBondBlock = true;
				block_bond_num = read_BlockNum(buffer);
				continue;
			}
			
			if (isAtomBlock) {
				const PSF_AtomLine& atom_line = PSF_AtomLine(
					read_AtomID(buffer),
					read_SegmentName(buffer),
					read_ResidueID(buffer),
					read_ResidueName(buffer),
					read_AtomName(buffer),
					read_AtomType(buffer),
					read_Charge(buffer),
					read_Mass(buffer),
					read_UnusedZero(buffer)
				);
				result.add_AtomLines(atom_line);
			}

			else if (isBondBlock) {
				const std::vector<std::array<int, 2>>& bond_line = read_BondLine(buffer);
				for (std::size_t i_pair = 0; i_pair < bond_line.size(); ++i_pair) {
					result.add_BondPairs(PSF_BondPair(bond_line[i_pair][0], bond_line[i_pair][1]));
				}
			}
		}

		close();
		if (block_atom_num != result.atom_size()) {
			std::cerr << "The Atom Number is not consistent. Check !NATOM block" << std::endl;
			std::exit(1);
		}
		else if (block_bond_num != result.bond_pair_size()) {
			std::cerr << "The Bond Number is not consistent. Check !NBOND block" << std::endl;
			std::exit(1);
		}

		std::cout << "atom_num = " << block_atom_num << std::endl;
		std::cout << "bond_num = " << block_bond_num << std::endl;

		return result;

	}

};
}

#endif /* TRYAMP_PSF_READER_HPP */
