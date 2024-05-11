# Service Banner Scanner in C

## Overview
This project includes a simple service banner scanner written in C. It connects to a specified IP address and port, sends a basic HTTP GET request, and prints any service banner returned by the server. This tool can be useful for network administrators and security professionals to quickly identify running services on exposed ports.

## Features
- Connect to a remote server using TCP.
- Send a basic HTTP GET request to the server.
- Retrieve and display the service banner.

## Requirements
- GCC for compiling the program.
- Linux environment as it uses system calls specific to Unix-based systems.

## Compilation and Usage
To compile and run the Service Banner Scanner, use the following commands:

```bash
gcc -o banner_scanner banner_scanner.c
./banner_scanner <IP Address> <Port>
````
