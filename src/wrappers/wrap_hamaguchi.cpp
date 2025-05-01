#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include "common.hpp"
#include "hamaguchi.hpp"

namespace py = pybind11;


// Don't put PYBIND11_MODULE inside a namespace!
PYBIND11_MODULE(_hamaguchi, m) {
    // Initialize NumPy (ensures NumPy C API is ready)
    py::module::import("numpy");

    m.def("_calc_pauli_vector",
        paulidecomp::wrap_calc_pauli_vector<paulidecomp::hamaguchi::calc_pauli_vector_internal>, 
          "Calculate the Pauli vector");
}
