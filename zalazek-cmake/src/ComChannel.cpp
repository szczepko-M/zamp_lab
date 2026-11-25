#include "ComChannel.hh"
#include <mutex>
#include <iostream>

using namespace std;


void ComChannel::print(const string& Msg){
    std::lock_guard<std::mutex> Lock(_Guard);

    std::cout << Msg << std::endl;
}

void ComChannel::print_error(const string& Msg){
    std::lock_guard<std::mutex> Lock(_Guard);

    std::cerr << Msg << std::endl;
}