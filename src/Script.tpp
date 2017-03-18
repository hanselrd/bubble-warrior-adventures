#include <functional>

template <class... Args>
decltype(auto) Script::operator()(const std::string& name, Args&&... args) {
    return _local[name.c_str()].cast<py::function>()(std::forward<Args>(args)...);
}
