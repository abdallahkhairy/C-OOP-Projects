//// Winsock_Client.cpp : This file contains the 'main' function. Program execution begins and ends there.
////
//#include <winsock2.h> // Include the Winsock 2 API for networking functions
//#include <WS2tcpip.h> // Include additional TCP/IP specific functions such as InetPton()
//#include <iostream>   // Include standard input/output stream objects
//#include <tchar.h>    // Include functions and macros for handling generic text mappings (like _T())
//
//using std::cout, std::endl; // Bring cout and endl from std namespace for easier usage
//
//int main()
//{
//    // Output the first step of setting up Winsock
//    cout << endl << "================ Step 1 : Setup Dll ================" << endl;
//
//    SOCKET clientSocket;   // Declare a variable to hold the client socket
//    int port = 55555;      // Define the port number that the client will connect to
//    WSADATA wsaData;       // A structure to hold details of the Winsock implementation
//    int wsaerr;            // Variable to hold error codes returned by Winsock functions
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
//    // Output the next step of setting up the client socket
//    cout << endl << "================ Step 2 : Setup Client Socket ================" << endl;
//
//    clientSocket = INVALID_SOCKET;  // Initialize the socket as invalid
//    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);  // Create a TCP socket for IPv4
//
//    // Check if socket creation failed
//    if (clientSocket == INVALID_SOCKET) {
//        cout << "Error at socket() " << WSAGetLastError() << endl;  // Output error message and code
//        WSACleanup();  // Clean up Winsock resources
//        return 0;  // Exit the program
//    }
//    else {  // If socket creation is successful
//        cout << "socket() is OK" << endl;  // Output confirmation
//    }
//
//    // Output the third step of connecting to the server
//    cout << endl << "================ Step 3 : Connect with the server ================" << endl;
//
//    sockaddr_in clientService;  // Declare a structure to hold server connection information
//    clientService.sin_family = AF_INET;  // Set the address family to IPv4
//    InetPton(AF_INET, _T("127.0.0.1"), &clientService.sin_addr.s_addr);  // Set the server IP address to localhost (127.0.0.1)
//    clientService.sin_port = htons(port);  // Set the port number, converting it to network byte order
//
//    // Attempt to connect to the server
//    if (connect(clientSocket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR) {
//        cout << "Client Connect()- Failed to connect " << WSAGetLastError() << endl;  // Output error message if connection fails
//        WSACleanup();  // Clean up Winsock resources
//        return 0;  // Exit the program
//    }
//    else {  // If connection is successful
//        cout << "Client: connect() is OK" << endl;  // Output confirmation of successful connection
//        cout << "Client: Can start sending and receiving data.." << endl;  // Notify that the client can communicate
//    }
//
//    // Output that the connection has been accepted
//    cout << "Accepted connection" << endl;
//
//    cout << endl << "================ Step 4 : Chat with the server ================" << endl;
//    
//    char buffer[200];  // Declare a character array (buffer) of size 200 to hold the message to be sent
//    cout << "Enter message to send: " << endl;  // Prompt the user to enter a message
//    std::cin.getline(buffer, 200);  // Get the user's input and store it in the buffer, reading up to 200 characters
//
//    // Send the message in the buffer through the clientSocket
//    // The 'send()' function sends the buffer data to the connected server
//    // Parameters: clientSocket (the socket), buffer (the message), 200 (the size of the buffer), 0 (flags)
//    int byteCount = send(clientSocket, buffer, 200, 0);
//
//    // Check if the message was sent successfully
//    if (byteCount > 0) {  // If 'byteCount' is greater than 0, it means some bytes were sent
//        cout << "Message Sent: " << buffer << endl;  // Output the sent message
//    }
//    else {  // If 'send()' failed
//        WSACleanup();  // Clean up Winsock resources in case of an error
//    }
//    char ackbuffer[200];  // Declare a character array (buffer) of size 200 to hold the received message
//
//    // Receive data from the accepted connection (acceptSocket)
//    // Parameters: acceptSocket (the connected socket), buffer (the message buffer), 200 (max buffer size), 0 (flags)
//    // 'recv()' returns the number of bytes received, or -1 if there's an error
//    byteCount = recv(clientSocket, ackbuffer, 200, 0);
//
//    // Check if data was received successfully
//    if (byteCount > 0) {  // If 'byteCount' is greater than 0, it means some data was received
//        cout << "Status : " << ackbuffer << endl;  // Output the received message
//    }
//    else {  // If 'byteCount' is less than or equal to 0, it indicates an error or connection closure
//        WSACleanup();  // Clean up Winsock resources in case of an error
//    }
//
//    cout << endl << "================ Step 5 : Close Socket ================" << endl;
//    
//    system("pause");  // Pause the program to wait for user input before exiting (Windows-specific)
//    WSACleanup();  // Clean up Winsock resources before exiting
//}
