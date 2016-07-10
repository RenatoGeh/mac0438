// BoardFrame.java
//
// MAC-438 Programacao Concorrente
// USP - Instituto de Matematica e Estatistica
//
// Prof. Marcel P. Jackowski
// mjack@ime.usp.br
//

package Whiteboard;

public interface BoardFrame extends java.rmi.Remote, java.io.Serializable {
    public void recvOneLine(LineCoords ln) throws java.rmi.RemoteException;
}

// -eof-
