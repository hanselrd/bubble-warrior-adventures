#pragma once
#include <cereal/types/tuple.hpp>
#include <cereal/types/string.hpp>
#include <pybind11/stl.h>
namespace py = pybind11;
#include <memory>
#include <string>
#include <tuple>

class Settings final : public std::enable_shared_from_this<Settings> {
public:
    explicit Settings(const std::string& filename);
    ~Settings();
    bool getFullscreen() const;
    const std::tuple<unsigned, unsigned>& getResolution() const;
    bool getShowFpsCounter() const;
    const std::string& getTheme() const;
    const std::string& getBackground() const;
    const std::string& getFont() const;
    void setFullscreen(bool val);
    void setResolution(const std::tuple<unsigned, unsigned>& val);
    void setShowFpsCounter(bool val);
    void setTheme(const std::string& val);
    void setFont(const std::string& val);

private:
    std::string _filename;
    bool _fullscreen = false;
    std::tuple<unsigned, unsigned> _resolution{800, 600};
    bool _showFpsCounter = true;
    std::string _theme = "black.conf";
    std::string _background = "1692638-800x600.jpg";
    std::string _font = "GFSCUS1D.ttf";

    friend class cereal::access;

    template <class Archive>
    void save(Archive& ar) const {
        ar(CEREAL_NVP(_fullscreen),
            CEREAL_NVP(_resolution),
            CEREAL_NVP(_showFpsCounter),
            CEREAL_NVP(_theme),
            CEREAL_NVP(_background),
            CEREAL_NVP(_font));
    }

    template <class Archive>
    void load(Archive& ar) {
        ar(_fullscreen,
            _resolution,
            _showFpsCounter,
            _theme,
            _background,
            _font);
    }
};

void initSettings(py::module& m);
