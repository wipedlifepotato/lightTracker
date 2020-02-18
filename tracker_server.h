#include"socket.h"
#include<vector>
#include<map>

//#define MAXEVENTS 40

class tracker_server : public Server{
    constexpr unsigned char magicnumber =24;
    constexpr unsigned char deflimit = 100;
	protected:
        int max_events, epollfd;
        struct epoll_event ev, events[deflimit+magicnumber];
        std::vector<int> conn_sockets;
    protected:
		using clients_it = std::map<std::string, Client>::iterator;
	public:
		Socket accepting(void);
		bool binding(std::string host, int port);
        void work_thread(void);
};
