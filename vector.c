#include "vector.h"
#include <stdlib.h>
#include <stdio.h>


typedef struct vector_struct {
    /**Ein vorzeichenloser 2 Byte großer Datentyp. */
    unsigned short n;
    double *data;
} vector_struct;

/** Hiermit wird ein Vektor erstellt
 * 1. Als erstes müssen wir die struct (vector) erstellen und speicher mithilfe von malloc freigeben
 * 2. Danach zeigen wir mithilfe des -> auf die Variable die in der vector_struct deklariert ist und setzen sie.
 * 3. als nächstes sagen wir das für alle zeilen, des Vektors mithilfe von data speicher freigegeben wird und
 * alle Elemente auf 0 gesetzt werden mithilfe von calloc
 * 4. Am Ende wird der erstellte Vektor zurückgegeben.
 */
vector createVector(unsigned short n) {
    vector v = malloc(sizeof(vector_struct));
    v->n = n;
    v->data = (double *) calloc(n, sizeof(double));
    return v;
}

/** Hiermit wird der Speicher wieder freigegeben, zuerst für alle gesetzten Werte den Speicher freigeben.
 * dann den gesamten Vektor.
 *
 * Als Eingabeparameter geben wir unseren erstellten Vektor rein.
 */
void rmVector(vector v) {
    free(v->data);
    free(v);
}

/** Gibt die Größe des mitgegebenen Vektors zurück*/
unsigned short size(vector v) {
    return v->n;
}

/** Gibt alle Werte des mitgegebenen Vektors zurück.*/
double* values(vector v) {
    return v->data;
}

/** Gibt den spezifischen Wert der Zeile 'j' zurück
 * Zuerst muss allerdings überprüft werden ob 'j' <= size ist, denn sonst kommt ein Fehler.*/
double getValue(vector v, unsigned short j) {
    if(j >= size(v)) {
        printf("ERROR: Index out of bounds! \n");
        exit(-1);
    }
    return v->data[j];
}

/** Setzt einen spezifischen Wert der Zeile 'j', aber erst nach Prüfung ob 'j' <= size ist, sonst kommt ein Fehler. */
void setValue(vector v, unsigned short j, double value) {
    if(j >= size(v)) {
        printf("ERROR: Index out of bounds! \n");
        exit(-1);
    }
    v->data[j] = value;
}

/** scalar product between to vectors.
 * @param a vector reference
 * @param a vector reference
 * @return scalar product a*b
 * @print error and exits if dimensions wrong
 */
double vectorDotVector(vector a, vector b) {
    unsigned short i;
    double sum = 0;
    if(size(a) != size(b)) {
        printf("ERROR: Vector dimensions don't match! \n");
        exit(-1);
    }
    for(i = 0; i < size(a); i++) {
        sum += a->data[i] * b->data[i];
    }
    return sum;
}

/** addition of two vectors.
 * @param a vector reference
 * @param a vector reference
 * @return c=a+b vector
 * @print error and exits if dimensions wrong
 */
vector vectorPlusVector(vector a, vector b) {
    unsigned short i;
    /**Hier wird geprüft ob die Vektoren gleich groß sind.*/
    if(size(a) != size(b)) {
        printf("ERROR: Vector dimensions don't match! \n");
        exit(-1);
    }
    /** Ergebnisvektor deklarieren. */
    vector c = createVector(size(a));
    for(i = 0; i < size(a); i++) {
        c->data[i] = a->data[i] + b->data[i];
    }
    return c;
}