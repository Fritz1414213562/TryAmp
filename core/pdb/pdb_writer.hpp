#ifndef TRYAMP_PDB_WRITER_HPP
#define TRYAMP_PDB_WRITER_HPP
#include<TryAmp/core/base/Writer.hpp>
#include<TryAmp/core/pdb/pdb_data_type/pdb_atom_line.hpp>
#include<string>
#include<iostream>
#include<sstream>
#include<iomanip>
#include<vector>
#include<array>


namespace Amp {

class PDBWriter : public FileWriter {


public:
	
	PDBWriter() = default;
	PDBWriter(const std::string& outputfile_name) : FileWriter(outputfile_name) {}
	~PDBWriter() = default;

	void write_AtomLine(const PDB_AtomLine& atom_line);
	void write_TER();
	void write_END();

};



void PDBWriter::write_AtomLine(const PDB_AtomLine& atom_line) {

	if (!output_file)
		throw std::runtime_error("FileOpenError: 'PDBWriter::write_AtomLine' failed.");

	output_file << "ATOM  ";
	output_file << std::right << std::setw(5) << atom_line.atom_id();
	output_file << " ";
	output_file << atom_line.atom_name();
	output_file << atom_line.alt_loc();
	output_file << atom_line.residue_name();
	output_file << " ";
	output_file << atom_line.chain_id();
	output_file << std::right << std::setw(4) << atom_line.residue_seq_id();
	output_file << atom_line.insert_code();
	output_file << "   ";
	output_file << std::right << std::setw(8) << std::fixed << std::setprecision(3) << atom_line.coordinate()[0];
	output_file << std::right << std::setw(8) << std::fixed << std::setprecision(3) << atom_line.coordinate()[1];
	output_file << std::right << std::setw(8) << std::fixed << std::setprecision(3) << atom_line.coordinate()[2];
	output_file << std::right << std::setw(6) << std::fixed << std::setprecision(2) << atom_line.occupancy();
	output_file << std::right << std::setw(6) << std::fixed << std::setprecision(2) << atom_line.temperature();
	output_file << "          ";
	output_file << atom_line.element();
	if (atom_line.charge() == 0.)
		output_file << "  " << std::endl;
	else
		output_file << std::right << std::setw(2) << std::fixed << std::setprecision(1) << atom_line.charge() << std::endl;;
}


void PDBWriter::write_TER() {
	output_file << "TER" << std::endl;
}


void PDBWriter::write_END() {
	output_file << "END" << std::endl;
}


}


#endif /* QAHWA_PDB_WRITER_HPP */
