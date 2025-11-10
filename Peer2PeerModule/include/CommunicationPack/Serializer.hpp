#pragma once
#include "Message.hpp"
#include <vector>
#include <cstdint>

using std::vector;
using std::uint8_t;

class Serializer{
    static Message deserialize(vector<uint8_t>);
    static vector<uint8_t> serialize(const Message &);
};
