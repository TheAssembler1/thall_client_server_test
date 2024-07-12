#include <iostream>
#include <thallium.hpp>
#include <fstream>
#include <chrono>
#include <thallium/serialization/stl/string.hpp>
#include <thallium/serialization/stl/vector.hpp>
#include <cmath>

#include "shared.hpp"

int main(int argc, const char** argv) {
    tl::engine my_engine(NETWORK_TYPE, THALLIUM_SERVER_MODE, true, 16);
    tl::remote_procedure rpc_resp_vec = my_engine.define("rpc_resp_vec");

    std::cout << "reading in server address from address book" << std::endl;
    std::ifstream is{ADDRESS_BOOK};
    std::string address;
    is >> address;
    std::cout << "server address: " << address << std::endl;

    if(address.empty()) {
        throw std::runtime_error("address was not found!");
    }

    is.close();

    tl::endpoint server = my_engine.lookup(address);

    std::ofstream csv_os{CLIENT_CSV};
    csv_os << CSV_HEADER << std::endl;
    int vec_size = 144;

    for(int i = 1; i <= ITERATIONS; i++) {
        std::cout << "================================================" << std::endl;
        std::cout << "making request for vec of size: " << vec_size << std::endl;
        auto start = std::chrono::high_resolution_clock::now();
        lstat_return_type return_type = rpc_resp_vec.on(server)(vec_size, i);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "received vec of byte size: " << "0" << std::endl;
        std::cout << "done requesting vec of bytes" << std::endl;
        std::cout << "time elapsed: " << duration.count() << " milliseconds" << std::endl;
        csv_os << "0" << "," << i << "," << duration.count() << std::endl;
        std::cout << "================================================" << std::endl;
    }

    std::cout << "DONE!!!" << std::endl;

    return 0;
}
