package org.example;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public class Server {
    public static void main(String[] args) {
        Socket socket;
        ServerSocket serverSocket;
        int i = 1;
        try {
            serverSocket = new ServerSocket(1001);
            while(true)
            {
                socket = serverSocket.accept();
                new ClientThread(socket,i).start();
                i++;
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

    }

}

