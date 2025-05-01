#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include "common.hpp"
#include "romero.hpp"

namespace py = pybind11;

PYBIND11_MODULE(_romero, m) {

        py::module::import("numpy"); ;  // This imports numpy internally

        m.def("_calc_inner_prods",
            paulidecomp::wrap_calc_inner_prods<paulidecomp::romero::calc_inner_prods>,
                "Calculate inner products using Romero algorithm");
        m.def("_calc_pauli_vector",
            paulidecomp::wrap_calc_pauli_vector<paulidecomp::romero::calc_pauli_vector>,
                "Calculate Pauli vector using Romero algorithm");
}
