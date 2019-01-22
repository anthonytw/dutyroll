#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
#include <pybind11/numpy.h>

#include "rollduty.hpp"

PYBIND11_MODULE(_dutyroll, m) {
	using namespace dutyroll;

    m.doc() = "dutyroll wrapper";

    m.def("__rollduty_fixed", &rollduty_fixed);
    m.def("__rollduty_variable", &rollduty_variable);
}
