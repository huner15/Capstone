#include <iostream>
#include <string.h>
#include <string>

#include "ServerSocket.h"
#include "SocketException.h"
#include "message.pb.h"

#include <sstream>

//TODO: Get rid of this
template <typename T>
std::string to_string(T value)
{
    std::ostringstream os ;
    os << value ;
    return os.str() ;
}


int main(int argC, char *argV[]) {
    int port;

    if (argC < 2) {
        std::cout << "usage: [port]: Specify connection port";
        return EXIT_SUCCESS;
    }
    else {
        port = atoi(argV[1]);
    }
    
    try {
        ServerSocket server(port);
        //While the program is running

        std::cout << "listening on " << port << std::endl;
        while (true) {
            ServerSocket new_sock;
            server.accept(new_sock);
            //Fork/thread would probably happen here
            std::cout << "Client has connected!" << std::endl;
            try {
                while (true) {
                    test::Msg data;
                    new_sock >> data;
                    std::cout << "Recieved " << data.name() << std::endl;
                    data.set_age(data.age() + 1);
                    data.set_name(data.name() + " is " + to_string(data.name().size()) + " characters long");
                    new_sock << data;
                }
            }
            catch (SocketException &e) {

            }
        }
    }
    catch (SocketException &e) {
        std::cout << "Exception was caught:" << e.description() << "Exiting..." << std::endl;
        return EXIT_FAILURE;
    }
}