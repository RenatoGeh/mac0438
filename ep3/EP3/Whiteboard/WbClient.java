// WbClient.java
//
// MAC-438 Programacao Concorrente
// USP - Instituto de Matematica e Estatistica
//
// Prof. Marcel P. Jackowski
// mjack@ime.usp.br
//

package Whiteboard;

public interface WbClient
    extends java.rmi.Remote, java.io.Serializable {
    int getID() throws Exception;
    void updateBoard(LineCoords ln) throws Exception;
    void sendAllLines() throws Exception;
    void sendLine(LineCoords ln) throws Exception;
    void pleaseDie() throws Exception;
    void recvDisplayObj(BoardFrame ab) throws Exception;
}

// -eof-
