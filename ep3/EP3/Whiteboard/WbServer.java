// WbServer.java
//
// MAC-438 Programacao Concorrente
// USP - Instituto de Matematica e Estatistica
//
// Prof. Marcel P. Jackowski
// mjack@ime.usp.br
//

package Whiteboard;

import java.util.*;

public interface WbServer extends java.rmi.Remote {
    Vector<ABoard> getBoards() throws Exception;
    String getURL() throws Exception;
    void addClient(WbClient wc, String brnm) throws Exception;
    void delClient(WbClient wc, String brnm) throws Exception;
    void addLine(LineCoords ln, String brnm) throws Exception;
    void sendAllLines(WbClient wc, String brnm) throws Exception;
    void addBoard(ABoard b) throws Exception;
    void deleteBoard(String name) throws Exception;
}

// -eof-
