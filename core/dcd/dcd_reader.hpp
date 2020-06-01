// This class can read the coordinates in a snapshot.
#ifndef TRYAMP_DCD_READER_HPP
#define TRYAMP_DCD_READER_HPP

#include<TryAmp/core/dcd/dcd_parser.hpp>
#include<TryAmp/core/snapshot.hpp>
#include<iostream>
#include<fstream>
#include<vector>
#include<array>

namespace Amp {

class DCDReader : public DCDParser {

public :
	DCDReader(const std::string& input_file_name) : DCDParser(input_file_name) {}
	DCDReader() : DCDParser() {}
	~DCDReader() = default;

	Snapshot<float, 3> read_SnapShot_at(const std::size_t& frame_in_snapshot) {

		read_num_frame_and_atom();
		Snapshot<float, 3> result(atom_num);

		if (frame_in_snapshot > frame_num) {
			std::cerr << "The frame " << frame_in_snapshot << " is out of range." << std::endl;
			std::exit(1);
		}

		for (std::size_t iframe = 0; iframe < frame_in_snapshot; ++iframe) {
			result = Snapshot<float, 3>(read_xyz());
		}

		close();

		return result;
	}


	std::vector<Snapshot<float, 3>> read_Trajectory() {

		read_num_frame_and_atom();
		std::vector<Snapshot<float, 3>> result(frame_num, Snapshot<float, 3>(atom_num));

		for (std::size_t iframe = 0; iframe < frame_num; ++iframe) {
			result[iframe] = Snapshot<float, 3>(read_xyz());
		}

		close();

		return result;
	}


	std::vector<Snapshot<float, 3>> read_Trajectory(const std::string& file_name) {

		load(file_name);
		read_num_frame_and_atom();
		std::vector<Snapshot<float, 3>> result(frame_num, Snapshot<float, 3>(atom_num));

		for (std::size_t iframe = 0; iframe < frame_num; ++iframe) {
			result[iframe] = Snapshot<float, 3>(read_xyz());
		}

		close();

		return result;
	}




	DCD_1stHeader read_1st_header() const {

		if (!is_read_headers) {
			std::cerr << "Have not yet read headers" << std::endl;
			std::exit(1);
		}

		return dcd_header1;
	}


	DCD_2ndHeader read_2nd_header() const {

		if (!is_read_headers) {
			std::cerr << "Have not yet read headers" << std::endl;
			std::exit(1);
		}

		return dcd_header2;
	}


	DCD_3rdHeader read_3rd_header() const {

		if (!is_read_headers) {
			std::cerr << "Have not yet read headers" << std::endl;
			std::exit(1);
		}

		return dcd_header3;
	}




};

}

#endif /* TRYAMP_DCD_READER_HPP */
