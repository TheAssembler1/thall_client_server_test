#include <fstream>
#include <iostream>
#include <vector>
#include <cassert>

#include "cu_stat.h"
#include "shared.hpp"

void rpc_resp_vec(const tl::request& req, int vec_size, int iteration) {
    std::ofstream csv_os{SERVER_CSV, std::ios::app};

#ifdef VEC_MODE
    std::cout << "================================================" << std::endl;
    std::cout << "client requested ved of size: " << vec_size << std::endl;
    std::vector<std::byte> vec(vec_size);
    std::cout << "start sending vec of bytes" << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    req.respond(vec);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "done sending vec of bytes" << std::endl;
    std::cout << "time elapsed: " << duration.count() << " milliseconds" << std::endl;
    csv_os << vec.size() << "," << iteration << "," << duration.count() << std::endl;
    std::cout << "================================================" << std::endl;
#endif

#ifdef CUSTAT_MODE
    lstat_return_type lstat_response;

    CuStat cu_stat;
    if(lstat("/", cu_stat.get_st()) == -1) {
        assert(0);
    } else {
        lstat_response = lstat_return_type(0, cu_stat.get_vec());
    }

    std::cout << "================================================" << std::endl;
    std::cout << "client requested ved of size: " << vec_size << std::endl;
    std::cout << "start sending vec of bytes" << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    req.respond(lstat_response);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "done sending vec of bytes" << std::endl;
    std::cout << "time elapsed: " << duration.count() << " milliseconds" << std::endl;
    csv_os << "0" << "," << iteration << "," << duration.count() << std::endl;
    std::cout << "================================================" << std::endl;
#endif
}

int main(int argc, const char** argv) {
    tl::engine my_engine(NETWORK_TYPE, THALLIUM_SERVER_MODE, true, 16);
    my_engine.define("rpc_resp_vec", rpc_resp_vec);

    std::cout << "writing address to address book" << std::endl;
    std::ofstream os = std::ofstream(ADDRESS_BOOK);
    os << my_engine.self();

    std::ofstream csv_os{SERVER_CSV};
    csv_os << CSV_HEADER << std::endl;

    std::cout << "server running at address " << my_engine.self() << std::endl;

    return 0;
}
