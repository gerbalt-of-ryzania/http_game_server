#pragma once

#include <string>

namespace api {

struct RequestContext {
    std::string request_id;
    std::string method;
    std::string path;
};

}  // namespace api
