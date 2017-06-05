#include "Drone.h"
#include <pybind11/pybind11.h>
#include "LinuxSetup.h"

namespace py = pybind11;

PYBIND11_MODULE(osdkpy, m) {
    py::class_<ackReturnData>(m, "ackReturnData")
        .def_readwrite("status", &ackReturnData::status)
        .def_readwrite("ack", &ackReturnData::ack);
}

