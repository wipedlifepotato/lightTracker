#include<iostream>

#include<string>

#include"tracker_server.h"
#include"tracker_config.h"





class tracker : public tracker_config, public tracker_server{
	private:		
	protected:
	//using command = 
	//	bool (tracker::*)(Client & client, const std::vector<std::string> msgs, const std::map<std::string, client> clients ); 
	public:
		tracker(void);
		tracker(std::string host, unsigned int port);
};
