#include "Script.hpp"
#include "Config.hpp"

Script::Script(const std::string& filename) {
    auto global = py::module::import("__main__").attr("__dict__");
    py::eval_file(SCRIPTS_DIR + filename, global, _local);
}
