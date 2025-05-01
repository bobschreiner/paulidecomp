#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include "common.hpp"
#include "hantzko.hpp"

namespace py = pybind11;


PYBIND11_MODULE(_hantzko, m) {

    // Initialize NumPy
    py::module::import("numpy");  // This imports numpy internally 

    m.def(
        "_calc_pauli_vector_recursive",
        paulidecomp::wrap_calc_pauli_vector<paulidecomp::hantzko::calc_pauli_vector_recursive_internal>,
        "Calculate the pauli vector recursively using Hantzko algorithm ");
    m.def(
        "_calc_pauli_vector_iterative",
        paulidecomp::wrap_calc_pauli_vector<paulidecomp::hantzko::calc_pauli_vector_iterative_internal>,
        "Calculate the pauli vector iteratively using Hantzko algorithm ");
}