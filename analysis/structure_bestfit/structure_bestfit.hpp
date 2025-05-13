#ifndef TRYAMP_ANALYSIS_STRUCTURE_BESTFIT_HPP
#define TRYAMP_ANALYSIS_STRUCTURE_BESTFIT_HPP
#include<coffee-makers/Core>
#include<TryAmp/core/snapshot.hpp>
#include<iostream>
#include<vector>
#include<array>
#include<memory>
#include<numeric>


namespace Amp::analysis {

namespace bestfit {
constexpr static int DIM = 3;
class StructureBestFit {


public:

	StructureBestFit(const Snapshot<float, DIM>& reference_structure, std::vector<std::size_t>& ids):
		_ref_structure(reference_structure) {
		ref_ids.resize(ids.size());
		for (std::size_t idx = 0; idx < ids.size(); ++idx)
			ref_ids[idx] = ids[idx] - 1;
	}
	StructureBestFit(const Snapshot<float, DIM>& reference_structure): _ref_structure(reference_structure) {
		ref_ids.resize(reference_structure.size(), 0);
		std::iota(ref_ids.begin(), ref_ids.end(), 0);
	}
	~StructureBestFit() = default;

	Snapshot<float, DIM> fit(const Snapshot<float, DIM>& source) const {
		return _fit(source, ref_ids);
	}

	Snapshot<float, DIM> fit(const Snapshot<float, DIM>& source, const std::vector<std::size_t>& ids) const {
		if (ids.size() != ref_ids.size())
			throw std::runtime_error("The number of the ids for source structure is not consistent with those for reference.");
		std::vector<std::size_t> src_ids(ids.size());
		for (std::size_t idx = 0; idx < ids.size(); ++idx)
			src_ids[idx] = ids[idx] - 1;
		return _fit(source, src_ids);
	}


private:

	Snapshot<float, DIM> _fit(const Snapshot<float, DIM>& source, const std::vector<std::size_t>& ids) const;
	Snapshot<float, DIM> _rotate(const Snapshot<float, DIM>& source, const makers::Mat3f& rot, const std::vector<std::size_t>& ids) const;

	makers::Mat3f _covariance(const Snapshot<float, DIM>& source, const std::vector<std::size_t>& ids) const;


	Snapshot<float, DIM> _ref_structure;
	std::vector<std::size_t> ref_ids;
};


Snapshot<float, DIM> StructureBestFit::_fit(const Snapshot<float, DIM>& source, const std::vector<std::size_t>& ids) const {
	const makers::Mat3f& cov = _covariance(source, ids);
	std::unique_ptr<makers::JacobiSVSolver<makers::Mat3f>> jsv_solver = std::make_unique<makers::JacobiSVSolver<makers::Mat3f>>();
	jsv_solver->solve(cov);

	const makers::Mat3f& matrixU = jsv_solver->left_singular_vectors();
	makers::Mat3f matrixV = jsv_solver->right_singular_vectors();
	makers::Vec3f sing_vals = jsv_solver->singular_values();

	makers::Mat3f matrixS;

	for (int idx = 0; idx < DIM; ++idx) {
		if (sing_vals[idx] < 0) matrixS(idx, idx) = -1;
		else matrixS(idx, idx) = 1;
	}

//	makers::Mat3f rot = (matrixV * matrixS * matrixU.transpose()).transpose();
	makers::Mat3f rot = (matrixV * matrixS * matrixU.transpose());
	Snapshot<float, DIM> retval = _rotate(source, rot, ids);

	const std::array<float, DIM>& ref_center = _ref_structure.center(ref_ids);
//	std::cout << ref_center[0] << " " << ref_center[1] << " " << ref_center[2] << std::endl;
	for (std::size_t iatom = 0; iatom < retval.size(); ++iatom) {
		for (std::size_t idim = 0; idim < DIM; ++idim) {
			retval(idim, iatom) += ref_center[idim];
		}
	}

	return retval;
}


Snapshot<float, DIM> StructureBestFit::_rotate(const Snapshot<float, DIM>& source, const makers::Mat3f& rot, const std::vector<std::size_t>& ids) const {

	Snapshot<float, DIM> retval(source.size());
	const std::array<float, DIM>& src_center = source.center(ids);

	for (std::size_t iatom = 0; iatom < source.size(); ++iatom) {
		const std::array<float, DIM>& src_atom = source[iatom];
		for (int idim = 0; idim < DIM; ++idim) {
			for (int idx = 0; idx < DIM; ++idx) {
				retval(idim, iatom) += (src_atom[idx] - src_center[idx]) * rot(idim, idx);
			//	retval(idim, iatom) += (src_atom[idx] + src2ref[idx]) * rot(idim, idx);
			}
		}
	}

	return retval;
}


makers::Mat3f StructureBestFit::_covariance(const Snapshot<float, DIM>& source, const std::vector<std::size_t>& ids) const {


	const std::array<float, DIM>& src_center = source.center(ids);
	const std::array<float, DIM>& ref_center = _ref_structure.center(ref_ids);
	makers::Mat3f retval;
	const std::size_t& atom_num = ids.size();
	for (int idx = 0; idx < DIM; ++idx) {
		for (int jdx = 0; jdx < DIM; ++jdx) {
			for (std::size_t iatom = 0; iatom < atom_num; ++iatom) {
				const std::size_t& srcid = ids[iatom];
				const std::size_t& refid = ref_ids[iatom];
				retval(idx, jdx) += (source(idx, srcid) - src_center[idx]) * (_ref_structure(jdx, refid) - ref_center[jdx]);
			//	retval(idx, jdx) += (source(idx, id) + src2ref[idx]) * _ref_structure(jdx, id);
			}
		}
	}

	return retval;
}
}

}


#endif // TRYAMP_ANALYSIS_STRUCTURE_BESTFIT_HPP
