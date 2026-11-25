#ifndef COMCHANNEL_HH
#define COMCHANNEL_HH


class ComChannel{
    private:
        std::mutex _Guard;

    public:
        void print(const string& Msg);
}

#endif