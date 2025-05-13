#ifndef TRYAMP_DCD_WRITER_HPP
#define TRYAMP_DCD_WRITER_HPP
#include<TryAmp/core/base/Writer.hpp>
#include<TryAmp/core/snapshot.hpp>
#include<string>
#include<iostream>
#include<sstream>
#include<iomanip>
#include<tuple>
#include<type_traits>
#include<vector>
#include<array>


namespace Amp {

template<typename T>
using is_array4dcd_writing = std::disjunction<
	std::is_same<T, std::array<char, 4>>,
	std::is_same<T, std::array<char, 80>>,
	std::is_same<T, std::array<int, 4>>,
	std::is_same<T, std::array<int, 9>>>;



class DCDWriter : public FileWriter {


public:
	DCDWriter(const std::string& output_file_name) : FileWriter(output_file_name) {}

	DCDWriter() : FileWriter() {}

	~DCDWriter() = default;


	void write_1st_block(int& nframes, int& istart, int& nstep_save, int& nsteps, int& nunits, float& delta) {
		write_block(signature, nframes, istart, nstep_save, nsteps, nunits, zero_4times, delta, zero_9times, version);
	}


	void write_2nd_block(std::vector<int>& chain_lengths, float& tempk) {

		int block_size = sizeof(int) + (3 + chain_lengths.size()) * 80;
	//	std::cout << block_size << std::endl;
		write_binary(block_size);
		int nlines = 3 + chain_lengths.size();
		write_binary(nlines);

		std::array<char, 80> title0 = convert_Str2Arr<80>(CafeMol_code);
		write_binary(title0);
		std::array<char, 80> title1 = convert_Str2Arr<80>(Developer_name);
		write_binary(title1);

		std::stringstream buffer;
		buffer
			<< std::right << std::setw(21) << std::setprecision(prec) << std::fixed << tempk
			<< "                                                           ";
		std::array<char, 80> tempk_title = convert_Str2Arr<80>(buffer.str());
		write_binary(tempk_title);

		for (std::size_t i_chain = 0; i_chain < chain_lengths.size(); ++i_chain) {
			std::stringstream chain_length_buffer;
			chain_length_buffer
				<< std::right << std::setw(6) << chain_lengths[i_chain]
				<< "                                                                          ";
			std::array<char, 80> chain_length = convert_Str2Arr<80>(chain_length_buffer.str());
			write_binary(chain_length);
		}

		write_binary(block_size);
	//	std::cout << block_size << std::endl;
	}


	void write_3rd_block(int& natoms) {write_block(natoms);}


	template<typename realT, std::size_t Dim>
	void write_body(Snapshot<realT, Dim> snap) {
		int block_size = static_cast<int>(snap.size()) * sizeof(realT);

		for (std::size_t i_dim = 0; i_dim < Dim; ++i_dim) {
			write_binary(block_size);
			for (std::size_t i_atom = 0; i_atom < snap.size(); ++i_atom)
				write_binary(snap(i_dim, i_atom));

			write_binary(block_size);
		}

	}


private:


	template<typename... Types>
	void write_block(Types&... arguments) {
		std::tuple<Types...> args_tup = std::make_tuple(arguments...);

	//	constexpr int tuple_elem_size = count_TupleElementSize(args_tup);
		int tuple_elem_size = count_TupleElementSize(args_tup);

	//	std::cout << tuple_elem_size << std::endl;

		write_binary(tuple_elem_size);
		iterate_binary(args_tup);
		write_binary(tuple_elem_size);

	}



private:


	template<std::size_t I = 0, typename tupleT>
	void iterate_binary(tupleT& tup) {
		if constexpr ((I >= 0) && (I < std::tuple_size<tupleT>::value)) {
			write_binary(std::get<I>(tup));
			iterate_binary<I + 1>(tup);
		}
	}


	template<typename T>
	void write_binary(T& value) {
		if constexpr (is_array4dcd_writing<T>::value)
			iterate_array(value);
		else if constexpr (!is_array4dcd_writing<T>::value)
			output_file.write(reinterpret_cast<char*>(&value), sizeof(T));
	}

	template<std::size_t I = 0, typename T, std::size_t Len>
	void iterate_array(std::array<T, Len>& arr) {
		if constexpr ((I >= 0) && (I < Len)) {
			output_file.write(reinterpret_cast<char*>(&std::get<I>(arr)), sizeof(T));
			iterate_array<I + 1>(arr);
		}
	}


	template<typename T>
	constexpr int element_size_of(T& elem) {
		if constexpr (is_array4dcd_writing<T>::value)
			return sizeof(typename std::tuple_element<0, T>::type) * std::tuple_size<T>::value;
		else if constexpr (!is_array4dcd_writing<T>::value)
			return sizeof(T);
	}


	template<std::size_t I = 0, typename tupleT>
	constexpr int count_TupleElementSize(tupleT& tup) {
		static_assert((0 <= I) || (I < std::tuple_size<tupleT>::value), "Iteration number is out of tuple range");
		
		if constexpr (I == std::tuple_size<tupleT>::value - 1)
			return element_size_of(std::get<I>(tup));
		else if constexpr (I < std::tuple_size<tupleT>::value - 1)
			return element_size_of(std::get<I>(tup)) + count_TupleElementSize<I + 1>(tup);
	}


	template<std::size_t N>
	std::array<char, N> convert_Str2Arr(const std::string& input_string) {
		if (input_string.size() != N) {
			std::cerr << "String length is not " << N << std::endl;
			std::exit(1);
		}
		std::array<char, N> result;

		for (std::size_t i_str = 0; i_str < N; ++i_str)
			result[i_str] = input_string[i_str];

		return result;
	}
	

private:
	std::array<char, 4> signature = {'C', 'O', 'R', 'D'};
	std::array<int, 4> zero_4times = {0, 0, 0, 0};
	std::array<int, 9> zero_9times = {0, 0, 0, 0, 0, 0, 0, 0, 0};
	std::string CafeMol_code = 
	  "==================== TryAmp DCD Writer Code : Analysis tools for MD    =========";
	std::string Developer_name =
	  "==================== Developed by Fritz Nagae ==================================";

	int prec = 14;
	int version = 24;


};

}


#endif /* TRYAMP_DCD_WRITER_HPP */
