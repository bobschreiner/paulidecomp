#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include "common.hpp"
#include "jones.hpp"

namespace py = pybind11;

PYBIND11_MODULE(_jones, m) {
        
        // Initialize NumPy
        py::module::import("numpy");  // This imports numpy internally

        m.def("_calc_inner_prods",
            paulidecomp::wrap_calc_inner_prods<paulidecomp::jones::calc_inner_prods>,
                "Calculate inner products using Jones algorithm");
        m.def("_calc_pauli_vector",
            paulidecomp::wrap_calc_pauli_vector<paulidecomp::jones::calc_pauli_vector>,
                "Calculate Pauli vector using Jones algorithm");
}