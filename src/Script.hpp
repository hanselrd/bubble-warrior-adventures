#pragma once
#include <pybind11/eval.h>
namespace py = pybind11;
#include <string>

class Script final {
public:
    explicit Script(const std::string& filename);
    template <class... Args>
    decltype(auto) operator()(const std::string& name, Args&&... args);

private:
    py::dict _local;
};

#include "Script.tpp"
