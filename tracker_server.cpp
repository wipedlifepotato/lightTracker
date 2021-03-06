#include"tracker.h"
#include"socket.h"

void tracker_server::do_work(Socket sock){
 int fd = sock.getFD();
 //char buf[1024];
 std::string test ="test msg\r\n";
 send_msg(fd, test );
 auto buf = reading(fd);
 std::cout << buf << std::endl;

}
void tracker_server::work_thread(void){
    accepting();
}


void tracker_server::accepting(){
        for(;;){
		struct sockaddr_in addr;
		socklen_t  clientlen  = sizeof(addr);
		int newfd;// = accept(m_fd, (sockaddr*)&addr, &clientlen);
        

		if(newfd < 0) throw Throw::throw_error("Can't accept");
        
        auto nfds = epoll_wait(epollfd, events, (deflimit+magicnumber), -1);
        if ( nfds < 0 ){
                Throw::throw_error("epoll_wait");
        }
        
        
        for ( auto n=0; n< nfds;n++ ){
                if (events[n].data.fd == m_fd) {
                        newfd=accept(m_fd, (struct sockaddr*)&addr, &clientlen);
                        if(newfd < 0) {
                                Throw::throw_error("can't accept");
                        }
                        char ipv4[INET_ADDRSTRLEN];
                        std::cerr << newfd << std::endl;
                        inet_ntop(AF_INET, &addr.sin_addr, ipv4, INET_ADDRSTRLEN);
                        auto port = htons (addr.sin_port);


                        conn_sockets[newfd]={ipv4, port };
                        std::cout << "Connected: " << conn_sockets[newfd].host << ":" << conn_sockets[newfd].port << std::endl;

                        auto flags = fcntl(newfd, F_GETFL, 0);
                        if(flags < 0) Throw::throw_error("cant get flags of socket");
                        flags|= O_NONBLOCK;
                        auto s = fcntl(newfd, F_SETFL, flags);
                        if(s < 0) Throw::throw_error("cant set flags to socket(O_NONBLOCK)");
                        
                        ev.events = EPOLLIN | EPOLLET;
                        ev.data.fd = newfd;
                        if( epoll_ctl(epollfd, EPOLL_CTL_ADD, newfd, &ev) < 0 ){
                                Throw::throw_error("cant add fd to epoll");
                        }
                }else{
                            int fd = events[n].data.fd;
                            std::cerr << "FD: " << fd << std::endl;
                            Socket returns;
                            returns.setFD(fd);
                            do_work(returns);
                           
                          //  if( epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, &ev ) < 0){
                                    //std::cerr << "WARNING: Can't delete socket from epoll" << std::endl;
                            //}
                            close(fd);
                            conn_sockets[fd].host="";
                            conn_sockets[fd].port=0;
                }
        }

		//m.m_fd=newfd;
		//m.m_family=AF_INET;
		//m.m_host=ipv4;
    }
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
