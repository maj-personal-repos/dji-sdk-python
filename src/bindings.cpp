#include "Drone.h"
#include <pybind11/pybind11.h>
#include <string>

using namespace Matrice;

namespace py = pybind11;

PYBIND11_MODULE(osdkpy, m) {
    py::class_<Drone>(m, "Drone")
        .def(py::init<std::string>())
        .def("initialize", &Drone::initialize)
        .def("cleanup", &Drone::cleanup)
        .def("releaseControl", &Drone::releaseControl)
        .def("takeControl", &Drone::takeControl)
        .def("arm", &Drone::arm)
        .def("disarm", &Drone::disarm)
        .def("takeoff", &Drone::takeoff)
        .def("land", &Drone::land)
        .def("goHome", &Drone::goHome);

    py::class_<ackReturnData>(m, "ackReturnData")
        .def_readwrite("status", &ackReturnData::status)
        .def_readwrite("ack", &ackReturnData::ack);
}

