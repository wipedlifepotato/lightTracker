#include"socket.h"
#include<vector>
#include<map>

class tracker_server : public Server{

	protected:
		
		using clients_it = std::map<std::string, Client>::iterator;
	public:
		Socket accepting(void);
		bool binding(std::string host, int port, int limit=100);
};
