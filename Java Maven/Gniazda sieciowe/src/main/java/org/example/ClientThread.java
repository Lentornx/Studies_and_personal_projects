package org.example;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.logging.Logger;

public class ClientThread extends Thread {
    private Socket socket;
    int id;
    private static final Logger LOGGER = Logger.getLogger(ClientThread.class.getName());
    public ClientThread(Socket socket, int id) {
        this.socket = socket;
        this.id = id;
    }

    public void run() {
        ObjectOutputStream objectOutputStream = null;
        ObjectInputStream objectInputStream = null;

        Message message;
        boolean ready = false;
        boolean nReceived = false;
        int n = 0, i = 0;
        try
        {
            objectOutputStream = new ObjectOutputStream(socket.getOutputStream());
            objectInputStream = new ObjectInputStream(socket.getInputStream());
            while(true)
            {

                if(!ready)
                {
                    message = new Message();
                    message.setContent("ready");
                    objectOutputStream.writeObject(message);
                    objectOutputStream.flush();
                    ready = true;
                    LOGGER.info("server - " + id + " - "+ message.getContent());
                }
                else if(!nReceived)
                {
                    message = (Message)objectInputStream.readObject();
                    n = Integer.valueOf(message.getContent());
                    LOGGER.info("client - "+ id + " - " + message.getContent() + " messages incoming");
                    nReceived = true;
                    message = new Message();
                    message.setContent("ready for messages");
                    objectOutputStream.writeObject(message);
                    objectOutputStream.flush();
                }
                else
                {
                    i++;
                    message = (Message) objectInputStream.readObject();
                    LOGGER.info("client - "+ id + " - " + message.getContent());
                    if(i == n)
                    {
                        i=0;
                        message = new Message();
                        message.setContent("finished");
                        objectOutputStream.writeObject(message);
                        objectOutputStream.flush();
                        LOGGER.info("server - " + id + " - "+ message.getContent());
                        socket.close();
                        break;
                    }
                }

            }
        }
        catch (IOException | ClassNotFoundException e) {
            throw new RuntimeException(e);
        }


    }

}
