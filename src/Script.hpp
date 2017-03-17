#pragma once
#include <pybind11/eval.h>
namespace py = pybind11;
#include <functional>
#include <string>

class Script final {
public:
    explicit Script(const std::string& filename);

    template <class... Args>
    inline decltype(auto) operator()(const std::string& name, Args&&... args) {
        return _local[name.c_str()].cast<py::function>()(std::forward<Args>(args)...);
    }

private:
    py::dict _local;
};
