package org.example;

import java.io.Serializable;

public class Message implements Serializable {

    private String content;

    Message() {
    }
    public String getContent() {
        return content;
    }

    public void setContent(String content) {
        this.content = content;
    }
}
