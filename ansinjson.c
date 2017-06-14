/*
 *	Analizador sintactico descendente recursivo
 *   JSON -> element EOF
 *   element -> object | array
 *   array -> [ a'
 *   a' -> element-list ] | ]
 *   element-list -> element el'
 *   el' ->  ,element el' | ε
 *   object -> { o'
 *   o' -> attributes-list} | }
 *   attributes-list -> attributes al'
 *   al' -> ,attributes al' | ε
 *   attribute -> att-name : att-value
 *   att-name -> string
 *   att-value -> element | string | number | true | false | null
*/

#include "anlexjson.c"
#define CANT 10

void json();
void element();
void object();
void obj();
void array();
void arr();
void attributeList();
void attrList();
void elementList();
void elmList();
void attribute();
void attName();
void attValue();
int aceptar = 1;

errorSint(){
	
}

void match (int expToken) {
	if (t.compLex = expToken) {
		sigLex();
	}
	else {
		errorSint();
	}
}

void checkInput(int primero[], int siguiente[]) {


}

// json -> element
void json(){
	int primero[2] = {L_CORCHETE, L_LLAVE};
	int siguiente[1] = {EOF};
}

//element -> object | array
void element(){
	int primero[2] = {L_CORCHETE, L_LLAVE}};
	int siguiente[4] = {EOF, COMA, R_CORCHETE, R_LLAVE};
}

//object -> { obj
void object(){
	int primero[1] = {L_LLAVE};
	int siguiente[4] = {EOF, COMA, R_CORCHETE, R_LLAVE};
}

//obj -> attributeList} | }
void obj(){
	int primero[2] = {R_LLAVE, STRING};
	int siguiente[4] = {EOF, COMA, R_CORCHETE, R_LLAVE};
}

//array -> [ arr 
void array(){
	int primero[1] = {L_CORCHETE};
	int siguiente[4] = {EOF, COMA, R_CORCHETE, R_LLAVE};
}

//arr -> elementList] | ]
void arr(){
	int primero[3] = {R_CORCHETE, L_CORCHETE, L_LLAVE};
	int siguiente[4] = {EOF, COMA, R_CORCHETE, R_LLAVE};
	
}

//attributeList -> attribute attrList
void attributeList(){
	int primero[1] = {STRING};
	int siguiente[1] = {R_LLAVE};
}

//attrList -> , attribute attrList | ES (empty string)
void attrList(){
	int primero[1] = {COMA};
	int siguiente[1] = {R_LLAVE};
}

//elementList -> element elmList
void elementList(){
	int primero[2] = {L_LLAVE, L_CORCHETE};
	int siguiente[1] = {R_CORCHETE};
}

//elmList -> , element elmList | ES (empty string)
void elmList(){
	int primero[1] = {COMA};
	int siguiente[1] = {R_CORCHETE};
}

//attribute -> attName : attValue
void attribute(){
	int primero[1] = {STRING}};
	int siguiente[2] = {COMA, R_LLAVE};
}

//attName -> string
void attName(){
	int primero[1] = {STRING};
	int siguiente[1] = {DOS_PUNTOS};
}

//attValue -> element | string | num | true | false | null
void attValue(){
	int primero[7] = {L_LLAVE, L_CORCHETE, STRING, NUMBER, PR_TRUE, PR_FALSE, PR_NULL};
	int siguiente[2] = {COMA, R_LLAVE};
}

