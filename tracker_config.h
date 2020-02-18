#include<string>
#include<vector>
#include"inih/cpp/INIReader.h"
class tracker_config{
	private:
		const std::string defConfPath = std::string("./config.ini");
	protected:
		void initConfig(void);
		void initConfig(std::string);//path
	protected:
		std::string listen_host;
		std::string serv_name;
		int listen_port;
		//init from file
		std::vector<std::string> whitelist_trackers; // download scrape files from another trackers;add them to self
		
		
		
};
