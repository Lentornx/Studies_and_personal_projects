package org.example;

import java.io.*;
import java.net.Socket;
import java.util.Scanner;
import java.util.logging.Logger;

public class Client {
    public static void main(String[] args) {

        Socket socket;
        ObjectOutputStream objectOutputStream;
        ObjectInputStream objectInputStream;
        int n = 0;
        String s="";
        try {
            socket = new Socket( "localhost", 1001);

            objectOutputStream = new ObjectOutputStream(socket.getOutputStream());
            objectInputStream = new ObjectInputStream(socket.getInputStream());
            Scanner scanner = new Scanner(System.in);

            while(true) {
                Message message = (Message) objectInputStream.readObject();
                LOGGER.info("server - " + message.getContent());
                if(message.getContent().equals("ready"))
                {
                    message = new Message();
                    s = scanner.nextLine();
                    message.setContent(s);
                    objectOutputStream.writeObject(message);
                    objectOutputStream.flush();
                    LOGGER.info("client - " + message.getContent());
                    n = Integer.valueOf(s);
                } else if (message.getContent().equals("ready for messages")) {
                    for (int i = 0; i < n; i++) {
                        s = scanner.nextLine();
                        message = new Message();
                        message.setContent(s);
                        objectOutputStream.writeObject(message);
                        objectOutputStream.flush();
                        LOGGER.info("client - " + message.getContent());
                    }
                }
                else if (message.getContent().equals("finished")) {
                    socket.close();
                    break;
                }
            }
        } catch (IOException | ClassNotFoundException e) {
            throw new RuntimeException(e);
        }

    }
    private static final Logger LOGGER = Logger.getLogger(Client.class.getName());
}