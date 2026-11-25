#include "ComChannel.hh"
#include <mutex>

using namespace std;

ComChannel::ComChannel(){

}

ComChannel::print(const string& Msg){
    std::lock_guard<mutex> Lock(_Guard);

    std << Msg << endl;
}