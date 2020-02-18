#include"tracker.h"
int main(int argc, char** argv){
        auto t = tracker();
        try{
            t.binding("127.0.0.1", atoi(argv[1]));
            t.work_thread();
        }catch(std::exception & e){
            //
            std::cerr << e.what() << std::endl;
        }
}

