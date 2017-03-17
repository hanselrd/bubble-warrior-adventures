#pragma once
#include <boost/any.hpp>
#include <memory>
#include <unordered_map>

struct ResourceHandler final {

private:
    static std::unordered_map<std::string, boost::any> _cache;
}
