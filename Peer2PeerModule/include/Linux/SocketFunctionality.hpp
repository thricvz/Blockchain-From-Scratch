#pragma once
#include "NetworkComponents.hpp"

using Port = const char*;

enum class ConnectionDirection{INCOMING,OUT_GOING};

int setupSocket(const IPV4Address&,Port,ConnectionDirection);


