#include <cereal/types/tuple.hpp>
#include <cereal/types/string.hpp>

template <class Archive>
void Settings::save(Archive& ar) const {
    ar(CEREAL_NVP(_fullscreen),
        CEREAL_NVP(_resolution),
        CEREAL_NVP(_showFpsCounter),
        CEREAL_NVP(_theme),
        CEREAL_NVP(_background),
        CEREAL_NVP(_font));
}

template <class Archive>
void Settings::load(Archive& ar) {
    ar(_fullscreen,
        _resolution,
        _showFpsCounter,
        _theme,
        _background,
        _font);
}
