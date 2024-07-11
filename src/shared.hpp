#ifndef CU_FUSE_SHARED_HPP
#define CU_FUSE_SHARED_HPP

#include <thallium.hpp>
#include <thallium/serialization/stl/pair.hpp>
#include <thallium/serialization/stl/string.hpp>
#include <thallium/serialization/stl/vector.hpp>

#define NETWORK_TYPE "tcp"
#define ADDRESS_BOOK "./address_book.txt"
#define ITERATIONS 1000
#define CLIENT_CSV "./client_time.csv"
#define SERVER_CSV "./server_time.csv"
#define CSV_HEADER "data_size (B),iteration,duration (ms)"

#undef VEC_MODE
#define CUSTAT_MODE

#ifdef VEC_MODE
#ifdef CUSTAT_MODE
#error "only VEC_MODE xor CUSTAT_MODE can be defined"
#endif
#endif

#ifdef CUSTAT_MODE
using lstat_return_type = std::pair<int, std::vector<std::byte>>;
#endif

namespace tl = thallium;

#endif // CU_FUSE_SHARED_HPP
