// Board.java
//
// MAC-438 Programacao Concorrente
// USP - Instituto de Matematica e Estatistica
//
// Prof. Marcel P. Jackowski
// mjack@ime.usp.br
//

package Whiteboard;

import java.util.*;

public interface Board extends java.io.Serializable, java.rmi.Remote {
  public String getName();
  public int getNumLines();
  public Vector<WbClient> getConnClients();
}
