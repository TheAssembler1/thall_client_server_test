#!/bin/bash

cd ..

echo "formating thall_client_server_test"
find src -iname '*.h' -o -iname '*.cpp' | xargs clang-format -i -style=file:"$(pwd)/.clang-format"
