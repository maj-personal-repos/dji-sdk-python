#include "Drone.h"
#include <pybind11/pybind11.h>
#include <string>

using namespace Matrice;

namespace py = pybind11;

PYBIND11_MODULE(djisdkpy, m) {
    py::class_<Drone>(m, "Drone")
        .def(py::init<std::string>())
        .def("initialize", &Drone::initialize)
        .def("shutdown", &Drone::shutdown)
        .def("releaseControl", &Drone::relControl)
        .def("takeControl", &Drone::getControl)
        .def("arm", &Drone::engage)
        .def("disarm", &Drone::disengage)
        .def("takeoff", &Drone::takeoff)
        .def("land", &Drone::land)
        .def("returnHome", &Drone::returnHome)
        .def("setAttitude", &Drone::setAttitude)
        .def("setAttitudeAndAltitude", &Drone::setAttitudeAndAltitude)
        .def("setOffset", &Drone::setOffset)
        .def("setVelocity", &Drone::setVelocity);

    py::class_<ackReturnData>(m, "ackReturnData")
        .def_readwrite("status", &ackReturnData::status)
        .def_readwrite("ack", &ackReturnData::ack);
}

