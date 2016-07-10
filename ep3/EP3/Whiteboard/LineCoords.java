// LineCoords.java
//
// MAC-438 Programacao Concorrente
// USP - Instituto de Matematica e Estatistica
//
// Prof. Marcel P. Jackowski
// mjack@ime.usp.br
//

package Whiteboard;

public class LineCoords implements java.io.Serializable {

    private static final long serialVersionUID = -7345613674422511221L;

    int x1, y1, x2, y2;		// the two end points of a line

    public String toString() {
		return "(" + x1 + ", " + y1 + ", " + x2 + ", " + y2 + ")" ;
    }
}

// -eof-
