#ifndef COMCHANNEL_HH
#define COMCHANNEL_HH

#include <mutex>
#include <string>

class ComChannel{
    private:
        std::mutex _Guard;

    public:
        void print(const std::string& Msg); //tu będzie potrzebna obłsuga stream'a
        virtual void Lock(){_Guard.lock();}
        virtual void Unlock(){_Guard.unlock();}
};

#endif