// Main.cpp
#include "WinsockServer.h"
#include <iostream>
#include <string>

int main() {
    try {
        WinsockServer server(55555);  // Create server instance on port 55555
        server.start();  // Start the server
        std::cout << "Server started. Type messages to broadcast. Enter 'Quit' or 'quit' to exit." << std::endl;

        std::string message;
        // Loop while the server is running
        while (server.isRunning()) {
            std::getline(std::cin, message);  // Get input from user
            if (message == "Quit" || message == "quit") break;  // Check for quit command

            server.sendToAllClients("Server: " + message);  // Use public method to send message
        }
        server.stop();  // Stop the server after quitting
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;  // Print any errors
    }

    return 0;
}
