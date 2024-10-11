// Main.cpp
#include "WinsockClient.h"
#include <iostream>
#include <string>

int main() {
    try {
        WinsockClient client("127.0.0.1", 55555);
        client.start();
        std::cout << "Client started. Messages will be sent automatically." << std::endl;
        std::cout << "Type 'Quit' or 'quit' to exit." << std::endl;

        // Wait for the client threads to finish
        // This will happen when 'Quit' or 'quit' is entered in the sendMessages thread
        while (true) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            if (!client.isRunning()) {
                break;
            }
        }

        std::cout << "Client stopping..." << std::endl;
        client.stop();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}