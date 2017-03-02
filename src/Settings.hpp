#pragma once
#include <cereal/types/tuple.hpp>
#include <cereal/types/string.hpp>
#include <pybind11/stl.h>
namespace py = pybind11;
#include <string>
#include <tuple>

struct Settings {
    bool fullscreen = false;
    std::tuple<unsigned, unsigned> resolution{800, 600};
    bool showFpsCounter = true;
    std::string theme = "black.conf";
    std::string background = "1692638-800x600.jpg";
    std::string font = "GFSCUS1D.ttf";

    template <class Archive>
    void save(Archive& ar) const {
        ar(CEREAL_NVP(fullscreen),
            CEREAL_NVP(resolution),
            CEREAL_NVP(showFpsCounter),
            CEREAL_NVP(theme),
            CEREAL_NVP(background),
            CEREAL_NVP(font));
    }

    template <class Archive>
    void load(Archive& ar) {
        ar(fullscreen,
            resolution,
            showFpsCounter,
            theme,
            background,
            font);
    }
};

void initSettings(py::module& m);
