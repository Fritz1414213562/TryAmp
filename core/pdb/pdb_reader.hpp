#ifndef TRYAMP_PDB_READER_HPP
#define TRYAMP_PDB_READER_HPP
#include<TryAmp/core/pdb/pdb_parser.hpp>
#include<TryAmp/core/pdb/pdb_data_type/pdb_atom_line.hpp>
#include<vector>
#include<array>


namespace Amp {


class PDBReader : public PDBParser {

public:

	PDBReader() : PDBParser() {}
	PDBReader(const std::string& input_filename) : PDBParser(input_filename) {}

	~PDBReader() = default;

	std::vector<PDB_AtomLine> read();

	std::vector<std::vector<PDB_AtomLine>>
		divide_residues(const std::vector<PDB_AtomLine>& topo) const;
	std::vector<std::vector<PDB_AtomLine>>
		divide_chains(const std::vector<PDB_AtomLine>& topo) const;

};



std::vector<PDB_AtomLine> PDBReader::read() {

	open();
	std::string buffer;

	std::vector<PDB_AtomLine> retval;

	while (std::getline(input_file, buffer)) {

		if (buffer.empty()) continue;

		const std::string& record_name = read_RecordName(buffer);

		if (record_name != "ATOM  ") continue;

		const PDB_AtomLine& atom_line = (buffer.size() > 54) ? ((buffer.size() > 78)
			? PDB_AtomLine(
				read_SerialNum(buffer),
				read_AtomName(buffer),
				read_AltLoc(buffer),
				read_ResidueName(buffer),
				read_ChainID(buffer),
				read_ResiSeqNum(buffer),
				read_InsertCode(buffer),
				read_Coordinate(buffer),
				read_Occupancy(buffer),
				read_TemperatureFactor(buffer),
				read_Element(buffer),
				read_Charge(buffer))
			: PDB_AtomLine(
				read_SerialNum(buffer),
				read_AtomName(buffer),
				read_AltLoc(buffer),
				read_ResidueName(buffer),
				read_ChainID(buffer),
				read_ResiSeqNum(buffer),
				read_InsertCode(buffer),
				read_Coordinate(buffer),
				read_Occupancy(buffer),
				read_TemperatureFactor(buffer),
				read_Element(buffer),
				0.))
			: PDB_AtomLine(
				read_SerialNum(buffer),
				read_AtomName(buffer),
				read_AltLoc(buffer),
				read_ResidueName(buffer),
				read_ChainID(buffer),
				read_ResiSeqNum(buffer),
				read_InsertCode(buffer),
				read_Coordinate(buffer),
				1.00,
				0.00,
				" ",
				0.);

		retval.push_back(atom_line);
	}

	return retval;
}

std::vector<std::vector<PDB_AtomLine>>
	PDBReader::divide_residues(const std::vector<PDB_AtomLine>& topo) const {

	std::vector<std::vector<PDB_AtomLine>> result;

	bool is_1st_read = false;
	int current_resi_id;

	std::vector<PDB_AtomLine> residue_topo;

	for (const PDB_AtomLine& atom_line : topo) {
		if (not is_1st_read) {
			current_resi_id = atom_line.residue_seq_id();
			residue_topo.push_back(atom_line);
			is_1st_read = true;
			continue;
		}
		if (current_resi_id != atom_line.residue_seq_id()) {
			current_resi_id = atom_line.residue_seq_id();
			result.push_back(residue_topo);
			residue_topo.clear();
		}
		residue_topo.push_back(atom_line);
	}
	if (!residue_topo.empty())
		result.push_back(residue_topo);
	

	return result;
}

std::vector<std::vector<PDB_AtomLine>>
	PDBReader::divide_chains(const std::vector<PDB_AtomLine>& topo) const {

	std::vector<std::vector<PDB_AtomLine>> result;

	bool is_1st_read = false;
	char current_chain_id;

	std::vector<PDB_AtomLine> chain_topo;

	for (const PDB_AtomLine& atom_line : topo) {
		if (not is_1st_read) {
			current_chain_id = atom_line.chain_id();
			chain_topo.push_back(atom_line);
			is_1st_read = true;
			continue;
		}
		if (current_chain_id != atom_line.chain_id()) {
			current_chain_id = atom_line.chain_id();
			result.push_back(chain_topo);
			chain_topo.clear();
		}
		chain_topo.push_back(atom_line);
	}
	if (!chain_topo.empty())
		result.push_back(chain_topo);
	

	return result;
}


}




#endif /* TRYAMP_PDB_READER_HPP */
