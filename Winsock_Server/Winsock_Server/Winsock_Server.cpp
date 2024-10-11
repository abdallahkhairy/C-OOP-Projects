//// Winsock_Server.cpp : This file contains the 'main' function. Program execution begins and ends there.
////
//#include <iostream>   // Include standard input/output stream objects
//#include <winsock2.h> // Include the Winsock 2 API for networking functions
//#include <WS2tcpip.h> // Include additional TCP/IP specific functions such as InetPton()
//#include <tchar.h>    // Include functions and macros for handling generic text mappings (like _T())
//
//using std::cout, std::endl; // Bring cout and endl from std namespace for easier usage
//
//int main()
//{
//    // Output the first step of setting up Winsock
//    cout << endl << "================ Step 1 : Setup Dll ================" << endl;
//
//    SOCKET serverSocket, acceptSocket;  // Declare two sockets, one for the server and one for accepting connections
//    int port = 55555;                   // Define the port number on which the server will listen for connections
//    WSADATA wsaData;                    // A structure to hold details of the Winsock implementation
//    int wsaerr;                         // Variable to hold error codes returned by Winsock functions
//    WORD wVersionRequested = MAKEWORD(2, 2);  // Request Winsock version 2.2
//
//    // Initialize Winsock DLL, load it into memory, and check for errors
//    wsaerr = WSAStartup(wVersionRequested, &wsaData);
//    if (wsaerr != 0) {  // If an error occurs during startup
//        cout << "The Winsock dll not found!" << endl;  // Output an error message
//        return 0;  // Exit the program
//    }
//    else {  // If Winsock starts successfully
//        cout << "The Winsock dll found!" << endl;  // Confirm that Winsock was found
//        cout << "The status: " << wsaData.szSystemStatus << endl;  // Display status info
//    }
//
//    // Output the next step of setting up the server socket
//    cout << endl << "================ Step 2 : Setup Socket ================" << endl;
//
//    serverSocket = INVALID_SOCKET;  // Initialize the server socket as invalid
//    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);  // Create a TCP socket for IPv4
//
//    // Check if socket creation failed
//    if (serverSocket == INVALID_SOCKET) {
//        cout << "Error at socket() " << WSAGetLastError() << endl;  // Output error message and code
//        WSACleanup();  // Clean up Winsock resources
//        return 0;  // Exit the program
//    }
//    else {  // If socket creation is successful
//        cout << "socket() is OK" << endl;  // Output confirmation
//    }
//
//    // Output the third step of binding the socket to an IP address and port
//    cout << endl << "================ Step 3 : Bind Socket ================" << endl;
//
//    sockaddr_in service;  // Declare a structure to hold the address and port for binding the server
//    service.sin_family = AF_INET;  // Set the address family to IPv4
//    InetPton(AF_INET, _T("127.0.0.1"), &service.sin_addr.s_addr);  // Set the IP address to localhost (127.0.0.1)
//    service.sin_port = htons(port);  // Set the port number, converting it to network byte order
//
//    // Bind the server socket to the specified IP address and port
//    if (bind(serverSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
//        cout << "bind() failed " << WSAGetLastError() << endl;  // Output error message if binding fails
//        closesocket(serverSocket);  // Close the server socket
//        WSACleanup();  // Clean up Winsock resources
//        return 0;  // Exit the program
//    }
//    else {  // If binding is successful
//        cout << "bind() is OK" << endl;  // Output confirmation
//    }
//
//    // Output the fourth step of starting to listen for incoming connections
//    cout << endl << "================ Step 4 : Start Listen ================" << endl;
//
//    // Start listening on the server socket for incoming connection requests
//    if (listen(serverSocket, 1) == SOCKET_ERROR) {
//        cout << "listen() Error listening on socket: " << WSAGetLastError() << endl;  // Output error message if listen fails
//    }
//    else {
//        cout << "listen() is OK I'm waiting for connections " << endl;  // Notify that the server is listening for connections
//    }
//
//    // Output the fifth step of accepting a connection from a client
//    cout << endl << "================ Step 5 : Accept Connection ================" << endl;
//
//    // Accept a connection request from a client
//    acceptSocket = accept(serverSocket, NULL, NULL);
//    if (acceptSocket == INVALID_SOCKET) {  // If accepting the connection fails
//        cout << "accept failed: " << WSAGetLastError() << endl;  // Output error message
//        WSACleanup();  // Clean up Winsock resources
//        return -1;  // Exit the program with error
//    }
//    // Output confirmation of accepted connection
//    cout << "Accepted connection" << endl;
//
//    cout << endl << "================ Step 6 : Chat with the Client ================" << endl;
//
//    char buffer[200];  // Declare a character array (buffer) of size 200 to hold the received message
//
//    // Receive data from the accepted connection (acceptSocket)
//    // Parameters: acceptSocket (the connected socket), buffer (the message buffer), 200 (max buffer size), 0 (flags)
//    // 'recv()' returns the number of bytes received, or -1 if there's an error
//    int byteCount = recv(acceptSocket, buffer, 200, 0);
//
//    // Check if data was received successfully
//    if (byteCount > 0) {  // If 'byteCount' is greater than 0, it means some data was received
//        cout << "Message received : " << buffer << endl;  // Output the received message
//    }
//    else {  // If 'byteCount' is less than or equal to 0, it indicates an error or connection closure
//        WSACleanup();  // Clean up Winsock resources in case of an error
//    }
//    char acknowledgeBuffer[200]= "Message Received";  // Declare a character array (buffer) of size 200 to hold the message to be sent
//
//    // Send the message in the buffer through the clientSocket
//    // The 'send()' function sends the buffer data to the connected server
//    // Parameters: clientSocket (the socket), buffer (the message), 200 (the size of the buffer), 0 (flags)
//    byteCount = send(acceptSocket, acknowledgeBuffer, 200, 0);
//
//    // Check if the message was sent successfully
//    if (byteCount > 0) {  // If 'byteCount' is greater than 0, it means some bytes were sent
//        cout << "Message ACK sent " << endl;  // Output the sent message
//    }
//    else {  // If 'send()' failed
//        WSACleanup();  // Clean up Winsock resources in case of an error
//    }
//
//    cout << endl << "================ Step 5 : Close Socket ================" << endl;
//    
//    system("pause");  // Pause the program to wait for user input before exiting (Windows-specific)
//    WSACleanup();  // Clean up Winsock resources before exiting
//}
