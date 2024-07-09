#ifndef CU_FUSE_SHARED_HPP
#define CU_FUSE_SHARED_HPP

#define NETWORK_TYPE "sockets"
#define ADDRESS_BOOK "./address_book.txt"
#define ITERATIONS 10
#define CLIENT_CSV "./client_time.csv"
#define SERVER_CSV "./server_time.csv"
#define CSV_HEADER "data_size (B),iteration,duration (ms)"

namespace tl = thallium;

#endif // CU_FUSE_SHARED_HPP
