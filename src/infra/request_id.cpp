#include "request_id.h"

#include <array>
#include <iomanip>
#include <random>
#include <sstream>

namespace infra {

std::string GenerateRequestId() {
    thread_local std::mt19937_64 rng{std::random_device{}()};

    std::array<unsigned char, 16> bytes{};
    for (auto& byte : bytes) {
        byte = static_cast<unsigned char>(rng() & 0xff);
    }

    std::ostringstream out;
    out << std::hex << std::setfill('0');
    for (unsigned char byte : bytes) {
        out << std::setw(2) << static_cast<int>(byte);
    }
    return out.str();
}

}  // namespace infra
