#ifndef COMCHANNEL_HH
#define COMCHANNEL_HH

#include <mutex>
#include <string>

class ComChannel{
    private:
        std::mutex _Guard;

    public:
        void print(const std::string& Msg);
        void print_error(const std::string& Msg);
        void lock(){_Guard.lock();};
        void unlock(){_Guard.unlock();};
};

#endif