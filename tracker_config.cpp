#include"tracker_config.h"
#include <cstring>

#define DEFSIZEBUF 1024
void tracker_config::initConfig(void){

}

void tracker_config::initConfig(std::string path){
	INIReader reader(path);
	std::string trackers_file=reader.Get("whitelist_trackers", "file", "NONE"); // 
	if( trackers_file != "NONE" ){
		FILE* f = fopen(trackers_file.c_str(), "r");
		if( f == NULL ) throw std::runtime_error("Can't open trackers_file");
		char buf[DEFSIZEBUF];
		char tmp[DEFSIZEBUF];
		char * p = (char*)&buf;
		char * pf=p;
		std::vector<std::string> whiteservers;
		while( fread(buf, DEFSIZEBUF-1, 1, f) > 0){
			while(*(p++)){
				if(*(p+1) == '\n'){
					memcpy(&tmp, pf, p-pf);
					tmp[ (p-pf)+1 ] = '\0';
					pf=(p+2);
					whiteservers.push_back( tmp ); 
				}
			}
			//TODO: add them
		}
	}
	listen_host = reader.Get("server", "listen_host", "localhost");
	serv_name = reader.Get("server", "name", "Undisclosed");
	listen_port = reader.GetInteger("server", "port", -1);

}

