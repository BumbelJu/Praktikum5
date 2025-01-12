#include "matrix.h"
#include "vector.h"
#include <stdlib.h>
#include <stdio.h>


typedef struct matrix_struct {
  /**Zwei vorzeichenloser 2 Byte großer Datentyp. */
  unsigned short n;
  unsigned short m;
  double **data;
} matrix_struct;

matrix createMatrix(unsigned short rows, unsigned short cols) {
  unsigned short i;
  size_t total_size = sizeof(matrix_struct) + sizeof(double)* rows + sizeof(double)* rows * cols;
  matrix_struct *matrix = (matrix_struct*) calloc(1, total_size);

  matrix->n = rows;
  matrix->m = cols;

  double **row_ptrs = (double **)(matrix + 1);
  double *data_start = (double *)(row_ptrs + rows);

  for (i = 0; i < rows; i++) {
    row_ptrs[i] = data_start + i * cols;
  }

  matrix->data = row_ptrs;

  return matrix;
}

/** Speicher wieder freigeben für Zeiger auf Zeilen und Speicher für die Matrixstruktur freigeben. */
void rmMatrix(matrix m) {
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
  /** Prüfung ob die Spalten von Vektor 'a' und die Zeilen von Vektor 'b' gleich groß sind.*/
  if(cols(a) != rows(b)){
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

/**Hier werden zwei Matrizen miteinander addiert. */
matrix matrixPlusMatrix(matrix a, matrix b){
  /** Deklaration der for-Schleifen Variablen */
  unsigned short i, j;
  if(rows(a) != rows(b) || cols(a) != cols(b)) {
    printf("ERROR: Die Zeilen und Spalten sind nicht gleich gross. \n");
  }
  /** Ergebnis Matrix erstellten 'c'. */
  matrix c = createMatrix(rows(a), cols(b));

  /**In dieser For schleife passiert die eigentliche Matrizen-Addition.
   * Hierbei nehmen wir zwei for-Schleifen, in der ersten for-Schleife gehen wir durch alle Zeilen durch
   * die zweite for Schleife ist für die Anzahl der Spalten. Nun addieren wir einfach jeden einzelnen Wert
   * der jeweiligen Zeilen, Spalten Kombination von Vektor 'a' und Vektor 'b'.
   */
  for(i = 0; i < rows(a); i++) {
    for(j = 0; j < cols(a); j++) {
      c->data[i][j] = a->data[i][j] + b->data[i][j];
    }
  }
  return c;
}


/** Mit dieser Methode wird Matrix*Vektor gerechnet. */
vector matrixDotVector(matrix a, vector x) {
  unsigned short i, j;
  double ergebnis = 0;
  if (cols(a) != size(x)) {
    printf("ERROR: Die Zeilen sind nicht gleich groß. \n");
    exit(-1);
  }
  vector y = createVector(rows(a));
  for (i = 0; i < rows(a); i++) {
    for (j = 0; j < cols(a); j++) {
      ergebnis += a->data[i][j] * getValue(x, j);
    }
    setValue(y, i, ergebnis);
    ergebnis = 0;
  }
  return y;
}




