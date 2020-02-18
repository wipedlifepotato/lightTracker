#include"tracker.h"
#include"socket.h"
#include <sys/epoll.h>

void tracker_server::work_thread(void){
    for(;;){
        auto sock = accepting();
        sock.write("Hello \r\n");
        if( epoll_ctl(epollfd, EPOLL_CTL_DEL, sock.getFD() ) < 0){
                std::cerr << "WARNING: Can't delete socket from epoll" << std::endl;
        }
        sock.closeConnect();
    }
}

Socket tracker_server::accepting(){
		struct sockaddr_in addr;
		socklen_t  clientlen  = sizeof(addr);
		int newfd;// = accept(m_fd, (sockaddr*)&addr, &clientlen);
        

		if(newfd < 0) throw Throw::throw_error("Can't accept");
        
        auto nfds = epoll_wait(epollfd, events, (deflimit+magicnumber), -1);
        if ( nfds < 0 ){
                Throw::throw_error("epoll_wait");
        }
        
        
        for ( auto n=nfds;n--; ){
                if (events[n].data.fd == m_fd) {
                        newfd=accept(m_fd, (struct sockaddr*)&addr, &clientlen);
                        if(newfd < 0) {
                                Throw::throw_error("can't accept");
                        }
                        setnonblocking(newfd);
                        ev.events = EPOLLIN | EPOLLET;
                        ev.data.fd = newfd;
                        if( epoll_ctl(epollfd, EPOLL_CTL_ADD, newfd, &ev) < 0 ){
                                Throw::throw_error("cant add fd to epoll");
                        }
                        
                }else{
                            char ipv4[INET_ADDRSTRLEN];
                            inet_ntop(AF_INET, &addr.sin_addr, ipv4, INET_ADDRSTRLEN);
                            Socket returns;
                            returns.setHost(ipv4);
                            returns.setFamily(AF_INET);
                            returns.setFD(events[n].data.fd);
                            return m;
                }
        }

		//m.m_fd=newfd;
		//m.m_family=AF_INET;
		//m.m_host=ipv4;
		
}

bool tracker_server::binding(std::string host, int port, int limit){
	struct sockaddr_in addr;
	addr.sin_family=m_family;
	addr.sin_port = htons(port);
	addr.sin_addr = { inet_addr(host.c_str()) };
	int res = bind( m_fd, (struct sockaddr *) &addr, sizeof(addr) ) ;
	if( listen(m_fd, limit) < 0) return false;	
	//return res >= 0 ;

    
    
    int conn_sock;
    epollfd = epoll_create1(0);
    if( epollfd < 0 ) {
            Throw::throw_error("Can't do epoll_create1" );
            //throw new std::runtime_error("Can't do epoll_create1");
    }
    ev.events=EPOLLIN;
    ev.data.fd=m_fd;
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, m_fd, &ev) == -1) {
            Throw::throw_error("Cant' add fd to epoll");
    }
    return true;
}
