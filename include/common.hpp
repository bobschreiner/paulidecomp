#pragma once

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <complex>
#include <vector>

namespace paulidecomp {

namespace py = pybind11;
namespace np = pybind11;

constexpr std::complex<double> pow_i[4] = {
    {1.0, 0.0}, {0.0, 1.0}, {-1.0, 0.0}, {0.0, -1.0}
};

inline int get_power_of_2(int n) { return 1 << n; }

inline bool is_pow2(int n) { return n > 0 && ((n & -n) == n); }

inline int get_log2(int n) {
    int r = (n & 0xAAAAAAAA) != 0;
    r |= ((n & 0xFFFF0000) != 0) << 4;
    r |= ((n & 0xFF00FF00) != 0) << 3;
    r |= ((n & 0xF0F0F0F0) != 0) << 2;
    r |= ((n & 0xCCCCCCCC) != 0) << 1;
    return r;
}

inline int get_bit(int n, int t) { return (n >> t) & 1; }

inline int get_gray_code(int n) { return n ^ (n >> 1); }

inline int get_changed_bit(int i, int j) { return get_log2(i ^ j); }

inline int get_pauli_flag(int n, int t) { return (n >> (2 * t)) & 0b11; }

inline int get_mask_of_XY(int n, int n_qubit) {
    int mask = 0;
    for (int t = 0; t < n_qubit; t++) {
        int p = get_pauli_flag(n, t);
        int b = (0 < p && p < 3);
        mask |= b << t;
    }
    return mask;
}

// Converts 1D NumPy array to std::vector<int>
std::vector<int> ndarray_to_vector_1d(const py::array_t<int> &arr) {
    auto r = arr.unchecked<1>();
    std::vector<int> vec(r.shape(0));
    for (ssize_t i = 0; i < r.shape(0); i++) {
        vec[i] = r(i);
    }
    return vec;
}

// Converts 2D NumPy complex array to vector<vector<complex>>
std::vector<std::vector<std::complex<double>>> ndarray_to_vector_2d(
    const py::array_t<std::complex<double>> &arr) {
    auto r = arr.unchecked<2>();
    std::vector<std::vector<std::complex<double>>> result(r.shape(0),
        std::vector<std::complex<double>>(r.shape(1)));
    for (ssize_t i = 0; i < r.shape(0); i++) {
        for (ssize_t j = 0; j < r.shape(1); j++) {
            result[i][j] = r(i, j);
        }
    }
    return result;
}

// Converts raw complex array to 1D NumPy array with memory ownership
py::array_t<std::complex<double>> raw_array_to_ndarray_1d(
    std::complex<double>* ptr, int length) {
    return py::array_t<std::complex<double>>(
        {length},
        {sizeof(std::complex<double>)},
        ptr,
        py::capsule(ptr, [](void *p) {
            delete[] reinterpret_cast<std::complex<double> *>(p);
        }));
}

// Wrap calc_pauli_vector function for pybind11
template <std::complex<double> *(*calc_pauli_vector_internal)(
    std::vector<std::vector<std::complex<double>>> &)>
py::array_t<std::complex<double>> wrap_calc_pauli_vector(
    py::array_t<std::complex<double>> density_matrix) {
    const int size = density_matrix.shape(0);
    auto density_matrix_vec = ndarray_to_vector_2d(density_matrix);
    auto result_ptr = calc_pauli_vector_internal(density_matrix_vec);
    return raw_array_to_ndarray_1d(result_ptr, size * size);
}

// Wrap calc_inner_prods function for pybind11
template <std::complex<double> *(*calc_inner_prods_internal)(
    std::vector<std::vector<std::complex<double>>> &, std::vector<int> &)>
py::array_t<std::complex<double>> wrap_calc_inner_prods(
    py::array_t<std::complex<double>> density_matrix,
    py::array_t<int> indices) {
    auto density_matrix_vec = ndarray_to_vector_2d(density_matrix);
    auto indices_vec = ndarray_to_vector_1d(indices);
    auto result_ptr = calc_inner_prods_internal(density_matrix_vec, indices_vec);
    return raw_array_to_ndarray_1d(result_ptr, indices_vec.size());
}

} // namespace paulidecomp