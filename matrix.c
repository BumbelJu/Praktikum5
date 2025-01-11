#include "matrix.h"
#include "vector.h"
#include <stdlib.h>
#include <stdio.h>


typedef struct matrix_struct {
  unsigned short n;
  unsigned short m;
  double **data;
} matrix_struct;

matrix createMatrix(unsigned short rows, unsigned short cols) {
  unsigned short i;
  matrix m = (matrix) malloc(sizeof(matrix_struct));
  m->n = rows;
  m->m = cols;
  /** calloc gibt speicher Frei und initalisiert alle Elemente = 0*/
  m->data = (double **) calloc(rows, sizeof(double *));

  /** Die For-Schleife benötigen wir jetzt, damit wir auch von jeder Zeile alle
 * Spalten auf 0 setzen können, deshalb benutzen wir hier auch wieder calloc, damit
   alle Elemente = 0 gesetzt werden können*/
  for (i = 0; i < rows; i++) {
    m->data[i] = (double *) calloc(cols, sizeof(double));
  }

  /** Zusastzaufgabe Informatik, Idee For-For schleife also data[i][j] = (double **) calloc...*/
  return m;
}

/** Wir deklarieren uns ein i für die For schleife, damit wir erstmal
 * den gesamten Speicher für die einzelnen Zeilen freigeben.
 * Zudem müssen wir danach den Speicher von data freigeben, wo drin die
 * einzelnen Zeilen schon freigegeben wurden
 * am Ende setzen wir den matrix Speicher frei.*/
void rmMatrix(matrix m) {
   unsigned short i;
   for(i = 0; i < m->n; i++) {
     free(m->data[i]);
   }
   free(m->data);
   free(m);
}


/** Deklaration von einer variable rows um es besser zu unterscheiden
 * mit hilfe des pointers greifen wir auf die variable 'n' zu die in der matrix
 * deklariert ist und geben diesen Wert zurück*/
unsigned short rows(matrix a){
  unsigned short rows = 0;
  rows = a->n;
  return rows;
}


/** Deklaration von einer variable cols um es besser zu unterscheiden
 * mit hilfe des pointers greifen wir auf die variable 'm' zu die in der matrix
 * deklariert ist und geben diesen Wert zurück*/
unsigned short cols(matrix a){
  unsigned short cols = 0;
  cols = a->m;
  return cols;
}

/** Deklaration von einer variable data um es verständlicher für andere auszudrücken
 * mit hilfe des pointers greifen wir auf die varaible 'data' zu die in der matrix
 * deklartiert ist und geben diesen Wert zurück. um die Matrix NxM zu sehen.*/
double** data(matrix a){
  double** data = 0;
  data = a->data;
  return data;
}


/** Zuerst prüfen wir ob die gesetzten Variablen r und c zu groß sind, wenn diese größer sind
 * als die gesetzten Rows und Cols innerhalb der Matrix wird ein Error herausgegeben,
 * wenn diese passen, wird der Wert zurückgegeben, der innerhalb der Matrix steht.*/
double getEntry(matrix a, unsigned short r, unsigned short c){
  if(r >= rows(a) || c >= cols(a)){
    printf("ERROR: Die Matrix Dimension ist zu groß! \n");
    exit(-1);
  }
  return a->data[r][c];
}

/** Mit der Methode set Entry soll ein Wert innerhalb der Matrix gesetzt werden können,
 * Dafür muss erst geprüft werden ob die mitgegebenen Variablen r und c größer sind als
 * eigentlich innerhalb der Matrix gesetzt, wenn dies der Fall ist wird ein Error geschmissen.
 *
 * Wenn nicht, wird auf data zugegriffen und der Wert 'v' wird gesetzt. */
void setEntry(matrix a, unsigned short r, unsigned short c, double v){
  if(r >= rows(a) || c >= cols(a)){
    printf("ERROR: Die Matrix Dimension ist zu groß! \n");
    exit(-1);
  }
  a->data[r][c] = v;
}


/** In dieser Methode werden zwei Matrizen multipliziert M*M*/
matrix matrixDotMatrix(matrix a, matrix b){
  /** Deklaration der for-Schleifen Variablen */
  unsigned short i, j, k;
  /** Prüfung ob der die Zeilen und Spalten größe gleich sind. */
  if(rows(a) != cols(b)){
    printf("ERROR: Die Zeilen und Spalten sind nicht gleich groß. \n");
    exit(-1);
  }
  /** Ergebnis Matrix erstellten 'c'. */
  matrix c = createMatrix(rows(a), cols(b));

  /** Matrix*Matrix bedeutet, dass wir für jede Zeile von Matrix a, durch jede
 * Spalte von b müssen, sobald wir diese beiden Werte haben können wir auf die
 * einzelne Spalte von a zugreifen und Zeile von B und diese immer wieder miteinander multiplizieren um sie dann
 * aufzuaddieren um es in der data von Matrix 'c' zu speichern, bis die Spalten von a und Zeilen von b vollständig
 * miteinander multipliziert wurden.*/
  for(i = 0; i < rows(a); i++){
    for(j = 0; j < cols(b); j++){
      for(k = 0; k < cols(a); k++){
        c->data[i][j] += a->data[i][k] * b->data[k][j];
      }
    }
  }
  return c;
}

/**
 * Calculate the matrix addition C = A + B. This method reports an
 * error if the matrix dimensions don't match and calls exit(-1).
 * @param a the A matrix reference
 * @param b the B matrix reference
 * @return the matrix C=A+B
 * @print error and exits if dimensions wrong
 */
matrix matrixPlusMatrix(matrix a, matrix b){
  /** Deklaration der for-Schleifen Variablen */
  unsigned short i, j;
  if(rows(a) != rows(b) || cols(a) != cols(b)) {
    printf("ERROR: Die Zeilen und Spalten sind nicht gleich groß. \n");
  }
  /** Ergebnis Matrix erstellten 'c'. */
  matrix c = createMatrix(rows(a), cols(b));

  // Hier fehlt noch erklärung.
  for(i = 0; i < rows(a); i++) {
    for(j = 0; j < cols(a); j++) {
      c->data[i][j] = a->data[i][j] + b->data[i][j];
    }
  }
  return c;
}

/** Hier muss noch Matrix*Vector hin programmiert werden. */




