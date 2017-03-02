#include "Settings.hpp"

void initSettings(py::module& m) {
    py::class_<Settings>(m, "Settings")
        .def(py::init<>())
        .def_readonly("fullscreen", &Settings::fullscreen)
        .def_readonly("resolution", &Settings::resolution)
        .def_readonly("showFpsCounter", &Settings::showFpsCounter)
        .def_readonly("theme", &Settings::theme)
        .def_readonly("background", &Settings::background)
        .def_readonly("font", &Settings::font);
}
