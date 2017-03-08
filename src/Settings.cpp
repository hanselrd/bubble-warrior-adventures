#include "Settings.hpp"
#include <cereal/archives/json.hpp>
#include <fstream>

Settings::Settings(const std::string& filename)
    : _filename(filename)
    , _fullscreen(false)
    , _resolution(800, 600)
    , _showFpsCounter(true)
    , _theme("black.conf")
    , _background("1692638-800x600.jpg")
    , _font("GFSCUS1D.ttf") {
    std::ifstream is(_filename);
    if (is.is_open()) {
        cereal::JSONInputArchive ar(is);
        ar(*this);
    }
}

Settings::~Settings() {
    std::ofstream os(_filename);
    cereal::JSONOutputArchive ar(os);
    ar(cereal::make_nvp("_settings", *this));
}

bool Settings::getFullscreen() const {
    return _fullscreen;
}

const std::tuple<unsigned, unsigned>& Settings::getResolution() const {
    return _resolution;
}

bool Settings::getShowFpsCounter() const {
    return _showFpsCounter;
}

const std::string& Settings::getTheme() const {
    return _theme;
}

const std::string& Settings::getBackground() const {
    return _background;
}

const std::string& Settings::getFont() const {
    return _font;
}

void Settings::setFullscreen(bool val) {
    _fullscreen = val;
}

void Settings::setResolution(const std::tuple<unsigned, unsigned>& val) {
    _resolution = val;
}

void Settings::setShowFpsCounter(bool val) {
    _showFpsCounter = val;
}

void Settings::setTheme(const std::string& val) {
    _theme = val;
}

void Settings::setFont(const std::string& val) {
    _font = val;
}

void initSettings(py::module& m) {
    py::class_<Settings>(m, "Settings")
        .def(py::init<const std::string&>())
        .def_property_readonly("fullscreen", &Settings::getFullscreen)
        .def_property_readonly("resolution", &Settings::getResolution)
        .def_property_readonly("showFpsCounter", &Settings::getShowFpsCounter)
        .def_property_readonly("theme", &Settings::getTheme)
        .def_property_readonly("background", &Settings::getBackground)
        .def_property_readonly("font", &Settings::getFont);
}
