from setuptools import setup, Extension
import os
import pybind11
import numpy as np

modules = ["hamaguchi", "hantzko", "jones", "romero"]

ext_modules = [
    Extension(
        f"paulidecomp._{module}",
        sources=[os.path.join("src", "wrappers", f"wrap_{module}.cpp")],
        include_dirs=[
            os.path.join("include"),
            pybind11.get_include(),
            pybind11.get_include(user=True),
            np.get_include()
        ],
        extra_compile_args=["-std=c++17", "-O3", "-fPIC"],
        define_macros=[("NPY_NO_DEPRECATED_API", "NPY_1_7_API_VERSION")],
        language="c++",
    ) for module in modules
]

setup(
    name="paulidecomp",
    version="1.0.0",
    author="Your Name",
    description="Pauli decomposition tools",
    ext_modules=ext_modules,
    install_requires=["pybind11", "numpy"],
)