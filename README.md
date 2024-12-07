
# Secure VPN Application

This project implements a **secure VPN Application** using the **Poco** library for SSL/TLS communication. It demonstrates how to establish a secure tunnel between a VPN client and a VPN server using encryption and secure socket connections.

## Table of Contents
- [Project Overview](#project-overview)
- [System Architecture](#system-architecture)
- [Installation & Setup](#installation-setup)
- [Building & Running](#building-running)
  - [Server Setup](#server-setup)
  - [Client Setup](#client-setup)
- [Core Components](#core-components)
- [Usage Examples](#usage-examples)

## Project Overview

The **Secure VPN Application** includes both a **VPN server** and **VPN client** for secure, encrypted communication. The server listens for incoming client connections and encrypts/decrypts traffic using SSL/TLS, while the client establishes a secure connection to the server and sends/receives data over this encrypted tunnel.

### Key Features:
- **SSL/TLS Encryption**: All communication is encrypted for privacy.
- **Multi-threading**: Server handles multiple client connections simultaneously.
- **Client Authentication**: Secure user authentication using certificates.
- **Session Management**: Store session details and status using a database.
- **Cross-platform Support**: Runs on both Linux and Windows systems.

## System Architecture

The application follows a **client-server** model:
- **VPN Server**: The server handles incoming client connections, authenticates them, and forwards encrypted data between clients.
- **VPN Client**: The client establishes a secure connection to the server and sends/receives encrypted data.
- **Poco C++ Libraries**: Utilized for network communication, SSL/TLS encryption, and multi-threading.

## Installation & Setup

### Ubuntu Setup:
1. **Install essential packages**:
    ```bash
    sudo apt update\
    sudo apt install cmake make build-essential    
    ```

### Windows Setup with WSL:
1. **Install WSL** (Windows Subsystem for Linux):
    ```bash
    wsl --install
    ```

2. After the restart, follow the **Ubuntu setup** instructions above.

## Building & Running

### Building the Project:

1. **Clone repository**:
    ```bash
    git clone https://github.com/your-username/secure-vpn-application.git
    cd secure-vpn-application
    ```

2. **Build the project**:
    ```bash
    mkdir build && cd build
    cmake ..
    make 
    ```

### Running the System:

#### Server Setup:
1. **Start the server**:
    ```bash
    ./VPNServer
    ```
    - This command will start the VPN server and listen for incoming connections.

#### Client Setup:
1. **Start the client**:
    ```bash
    ./VPNClient <server_ip> <server_port>
    ```
    - Replace `<server_ip>` and `<server_port>` with the IP address and port number of the VPN server.

## Core Components

### VPN Server:
The server listens for incoming connections and handles SSL/TLS encryption for secure communication. It authenticates users and forwards encrypted traffic between connected clients.

### VPN Client:
The client application connects to the server over a secure, encrypted tunnel. It sends requests to the server and handles the encrypted data transfer.

### SSL/TLS Encryption:
SSL/TLS encryption is used to protect all data transmitted between the server and the client.

### Authentication:
Clients must authenticate with the server using a secure method, such as certificates, before being allowed to establish a connection.

### Multi-threading:
The server can handle multiple concurrent client connections using multi-threading, improving scalability and performance.

## Usage Examples

1. **Start the VPN server**:
    ```bash
    ./VPNServer
    ```

2. **Start the VPN client**:
    ```bash
    ./VPNClient 127.0.0.1 4433
    ```

3. **Verify VPN connection**:
    Once the client is connected to the server, data sent through the tunnel will be encrypted, and the client and server can securely communicate.

### Contact
**Project Maintainer**: Kartika Kannojiya  
**Project Link**: [GitHub Link](https://github.com/your-username/secure-vpn-application)

---

