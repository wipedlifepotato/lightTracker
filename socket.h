#pragma once
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<sys/time.h>

#include"throw.hpp"

#define ELIF(what) else if(what)
class Socket{
	protected:
		std::string m_host;
		bool blocked=0;
		int m_fd=-1, m_family;
	protected:
		//bool binding(std::string, int port, int limit=100);
		//Socket accepting(void);
	public:
		bool isBlocked(void){
			return blocked;
		}
	public: 
		void setHost(std::string h){
			m_host=h;
		}
		void setFD(int fd){
			m_fd=fd;
		}
		int getFD(void){
                return m_fd;
        }
		void setFamily(int f){
			m_family=f;
		}
		void closeConnect(){
			close(m_fd);
		}
	public:
		Socket operator=(Socket & sock){
			close(m_fd);
			blocked=sock.blocked;
			m_fd=sock.m_fd;
			return *this;
		}
		Socket operator=(Socket sock){
			close(m_fd);
			blocked=sock.blocked;
			m_fd=sock.m_fd;
			return *this;
		}
		bool operator!(void){
			if(m_fd == -1) return true;
		} 
	public:
		void setNonblock(bool nonblock=true);
		void openSocket(int domain, int type, int protocol);
		const int & getFD(){
			return m_fd;
		}
		~Socket(void);	 
};


class SocketTalking : public Socket{
	protected:
		SocketTalking()=default;
	public:
		void write(int fd, std::string msg, int flag=MSG_DONTWAIT){
			if( send(fd, msg.c_str(), msg.size(), flag) == -1)	
				Throw::throw_error("Can't send to socket" );
		}
		std::string read(int fd, std::size_t size=1024, int flag=MSG_DONTWAIT){
			char buf[size];
			memset(buf, 0, size);
			//char * buf = new char[size];
			if( recv(fd, buf, size, flag) == -1 ){
			//	delete buf;
				Throw::throw_error("Can't read from socket" );
			}
			//delete buf;
			return std::string(buf);
		}
};

class Client : public SocketTalking{

};

class Server : public SocketTalking{
		
		public:
			Server(int domain=AF_INET, int type=SOCK_STREAM, int protocol=0){
				openSocket(domain, type, protocol);
			}
			virtual Socket accepting(void)=0;
			virtual bool binding ( std::string& , int, unsigned int limit=100 ) = 0;
};
