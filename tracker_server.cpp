#include"tracker.h"
#include"socket.h"

Socket tracker_server::accepting(){
		struct sockaddr_in addr;
		socklen_t  clientlen  = sizeof(addr);
		int newfd = accept(m_fd, (sockaddr*)&addr, &clientlen);

		char ipv4[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &addr.sin_addr, ipv4, INET_ADDRSTRLEN);
		if(newfd < 0) throw Throw::throw_error("Can't accept");
		Socket m;
		m.setHost(ipv4);
		m.setFamily(AF_INET);
		m.setFD(newfd);

		//m.m_fd=newfd;
		//m.m_family=AF_INET;
		//m.m_host=ipv4;
		return m;
}

bool tracker_server::binding(std::string host, int port, int limit){
	struct sockaddr_in addr;
	addr.sin_family=m_family;
	addr.sin_port = htons(port);
	addr.sin_addr = { inet_addr(host.c_str()) };
	int res = bind( m_fd, (struct sockaddr *) &addr, sizeof(addr) ) ;
	if( listen(m_fd, limit) < 0) return false;	
	return res >= 0 ;
}
