#include <iostream>
#include <thallium.hpp>
#include <fstream>
#include <chrono>
#include <thallium/serialization/stl/string.hpp>
#include <thallium/serialization/stl/vector.hpp>
#include <cmath>

#include "shared.hpp"

int main(int argc, const char** argv) {
    tl::engine myEngine(NETWORK_TYPE, THALLIUM_CLIENT_MODE);
    tl::remote_procedure rpc_resp_vec = myEngine.define("rpc_resp_vec");

    std::cout << "reading in server address from address book" << std::endl;
    std::ifstream is{ADDRESS_BOOK};
    std::string address;
    is >> address;
    std::cout << "server address: " << address << std::endl;

    tl::endpoint server = myEngine.lookup(address);

    std::ofstream csv_os{CLIENT_CSV};
    csv_os << CSV_HEADER << std::endl;

    int cur_pow = 0;
    do {
        const int cur_vec_size = std::pow(2, cur_pow);
        cur_pow++;

        for(int i = 1; i <= ITERATIONS; i++) {
            std::cout << "================================================" << std::endl;
            std::cout << "making request for vec of size: " << cur_vec_size << std::endl;
            auto start = std::chrono::high_resolution_clock::now();
            std::vector<std::byte> vec = rpc_resp_vec.on(server)(cur_vec_size, i);
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            std::cout << "received vec of byte size: " << vec.size() << std::endl;
            std::cout << "done requesting vec of bytes" << std::endl;
            std::cout << "time elapsed: " << duration.count() << " milliseconds" << std::endl;
            csv_os << cur_vec_size << "," << i << "," << duration.count() << std::endl;
            std::cout << "================================================" << std::endl;
        }
        // NOTE: 1 GB is 30
    } while(cur_pow <= 26);

    return 0;
}
