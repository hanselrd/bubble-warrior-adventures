#pragma once
#include <cereal/cereal.hpp>
#include <pybind11/pybind11.h>
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
    friend class cereal::access;

    template <class Archive>
    void save(Archive& ar) const;
    template <class Archive>
    void load(Archive& ar);

    std::string _filename;
    bool _fullscreen = false;
    std::tuple<unsigned, unsigned> _resolution{800, 600};
    bool _showFpsCounter = true;
    std::string _theme = "black.conf";
    std::string _background = "1692638-800x600.jpg";
    std::string _font = "GFSCUS1D.ttf";
};

void initSettings(py::module& m);

#include "Settings.tpp"
