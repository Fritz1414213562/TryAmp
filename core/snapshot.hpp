#ifndef TRYAMP_SNAPSHOT_HPP
#define TRYAMP_SNAPSHOT_HPP
#include<vector>
#include<array>
#include<type_traits>
#include<iostream>

namespace Amp {


template<typename realT , std::size_t Dim, typename std::enable_if<
	(Dim > 0), std::nullptr_t>::type = nullptr>
struct Snapshot {

public:

	Snapshot(const std::size_t& atom_number) : atom_num(atom_number) {
		for (std::size_t i_dim = 0; i_dim < Dim; ++i_dim) {
			snap_shot[i_dim].resize(atom_num, 0);
		}
	}


	Snapshot(const std::array<std::vector<realT>, Dim>& stl_snapshot) {
		std::size_t atom_number = stl_snapshot[0].size();
		bool isMatrix = true;
		for (std::size_t i_dim = 1; i_dim < Dim; ++i_dim) {
			isMatrix = isMatrix && (atom_number == stl_snapshot[i_dim].size());
		}
		if (!isMatrix) {
			std::cerr << "The trajectory is not a matrix shape" << std::endl;
			std::exit(1);
		}
		snap_shot = stl_snapshot;
		atom_num = atom_number;
	}

	Snapshot(const Snapshot& input) {
		snap_shot = input.snap_shot;
		atom_num = input.atom_num;
	}


	~Snapshot() = default;


	std::array<realT, Dim> operator[](const std::size_t& index) const {
		std::array<realT, Dim> result;

		for (std::size_t i_dim = 0; i_dim < Dim; ++i_dim) {
			result[i_dim] = snap_shot[i_dim][index];
		}
		return result;
	}


	std::array<realT, Dim>& operator[](const std::size_t& index) {
		std::array<realT, Dim> result;

		for (std::size_t i_dim = 0; i_dim < Dim; ++i_dim) {
			result[i_dim] = snap_shot[i_dim][index];
		}
		return result;
	}


	realT operator()(const std::size_t& i_index, const std::size_t& j_index) const {
		return snap_shot[i_index][j_index];
	}


	realT& operator()(const std::size_t& i_index, const std::size_t& j_index) {
		return snap_shot[i_index][j_index];
	}



	std::array<realT, Dim> center() const {
		std::array<realT, Dim> result;
		const realT& f_atom_size = static_cast<realT>(atom_num);
		
		for (std::size_t i_atom = 0; i_atom < atom_num; ++i_atom)
			for (std::size_t i_dim = 0; i_dim < Dim; ++i_dim)
				result[i_dim] += snap_shot[i_dim][i_atom];

		for (std::size_t i_dim = 0; i_dim < Dim; ++i_dim)
			result[i_dim] /= f_atom_size;

		return result;
	}


	std::array<realT, Dim> center(const std::vector<std::size_t>& atom_ids) const {
		std::array<realT, Dim> result = {0, 0, 0};
		const realT& f_atom_size = static_cast<realT>(atom_ids.size());
		for (const std::size_t& atom_id : atom_ids)
			for (std::size_t i_dim = 0; i_dim < Dim; ++i_dim)
				result[i_dim] += snap_shot[i_dim][atom_id];
				

		for (std::size_t i_dim = 0; i_dim < Dim; ++i_dim) {
			result[i_dim] /= f_atom_size;
		}

		return result;
	}



	std::size_t size() const {
		return atom_num;
	}

	std::size_t dimension() const {
		return Dim;
	}


private:

	std::array<std::vector<realT>, Dim> snap_shot;

	std::size_t atom_num;


};



}


#endif /* TRYAMP_SNAPSHOT_HPP */
