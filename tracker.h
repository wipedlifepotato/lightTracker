#include<iostream>

#include<string>

#include"tracker_server.h"


class tracker_config{
	private:
		const std::string defConfPath = std::string("./config.ini");
	protected:
		void initConfig(void);
		void initConfig(std::string);//path
};



class tracker : public tracker_config, public tracker_server{
	private:		
	protected:
	//using command = 
	//	bool (tracker::*)(Client & client, const std::vector<std::string> msgs, const std::map<std::string, client> clients ); 
	public:
		tracker(void);
		tracker(std::string host, unsigned int port);
};
