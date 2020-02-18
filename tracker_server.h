#include"socket.h"
#include<vector>
#include<map>
#include <sys/epoll.h>


//#define MAXEVENTS 40
constexpr unsigned char magicnumber =24;
constexpr unsigned char deflimit = 100;
class tracker_server : public Server{
    struct BoxServer{
      std::string host;
      int port;
    };
	protected:
        int max_events, epollfd;
        struct epoll_event ev, events[deflimit+magicnumber];
        std::map<int, BoxServer> conn_sockets;
        void do_work(Socket);
    protected:
		using clients_it = std::map<std::string, Client>::iterator;
	public:
		void accepting(void);
		bool binding(std::string host, int port, int limit =(deflimit+magicnumber));
        void work_thread(void);
        
};
