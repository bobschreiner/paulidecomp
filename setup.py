import os
from setuptools import setup, Extension
import pybind11
import numpy as np

ext_modules = [
    Extension(
        "paulidecomp._hamaguchi",  # Note: Single underscore prefix
        sources=[os.path.join("src", "wrappers", "wrap_hamaguchi.cpp")],
        include_dirs=[
            os.path.join("include"),
            pybind11.get_include(),
            pybind11.get_include(user=True),
            np.get_include()
        ],
        extra_compile_args=["-std=c++17", "-O3", "-fPIC"],
        define_macros=[("NPY_NO_DEPRECATED_API", "NPY_1_7_API_VERSION")],
        language="c++",
    )
]

setup(
    ext_modules=ext_modules,
    package_dir={"": "src"},  # Critical for finding Python packages
)