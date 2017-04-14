/*
 *	Analizador Léxico	
 *	Curso: Compiladores y Lenguajes de Bajo de Nivel
 *	Práctica de Programación Nro. 1
 *	
 *	Descripcion:
 *	Implementa un analizador léxico que reconoce números, literales 
 *  en cadena y signos de puntuación. para un lenguaje con sintaxis 
 * 	tipo JSON.
 *	
 */

/*********** Inclusión de cabecera **************/
#include "anlexjson.h"


/************* Variables globales **************/

int consumir;			/* 1 indica al analizador lexico que debe devolver
						el sgte componente lexico, 0 debe devolver el actual */

char cad[5*TAMLEX];		// string utilizado para cargar mensajes de error
token t;				// token global para recibir componentes del Analizador Lexico

// variables para el analizador lexico

FILE *archivo;			// Fuente pascal
char buff[2*TAMBUFF];	// Buffer para lectura de archivo fuente
char id[TAMLEX];		// Utilizado por el analizador lexico
int delantero=-1;		// Utilizado por el analizador lexico
int fin=0;				// Utilizado por el analizador lexico
int numLinea=1;			// Numero de Linea

/**************** Funciones **********************/


// Rutinas del analizador lexico

void error(const char* mensaje)
{
	printf("Lin %d: Error Lexico. %s.\n",numLinea,mensaje);	
}


void sigLex()
{
	int i=0;
	char c=0;
	int acepto=0;
	int estado=0;
	char msg[41];
	entrada e;

	while((c=fgetc(archivo))!=EOF)
	{
		if (c==' ' || c=='\t'){

			printf(" ");
			continue;	//eliminar espacios en blanco
		}
		else if(c=='\t')
		{
			//incrementar el numero de linea
			printf("\t");
			continue;
		}
		else if(c=='\n')
		{
			//incrementar el numero de linea
			printf("\n");
			numLinea++;
			continue;
		}
		else if (c==':')
		{
		    t.compLex=DOS_PUNTOS;
		    t.lexema="DOS_PUNTOS";
		    break;
		}
		else if (c=='{')
		{
		    t.compLex=L_LLAVE;
		    t.lexema="L_LLAVE";
		    break;
		}
		else if (c=='}')
		{
		    t.compLex=R_LLAVE;
		    t.lexema="R_LLAVE";
		    break;
		}
		else if (c=='[')
		{
		    t.compLex=L_CORCHETE;
		    t.lexema="L_CORCHETE";
		    break;
		}
		else if (c==']')
		{
		    t.compLex=R_CORCHETE;
		    t.lexema="R_CORCHETE";
		    break;
		}
		else if (c==',')
		{
		    t.compLex=COMA;
		    t.lexema="COMA";
		    break;
		}
		else if (c == '"')
		{

			//es un STRING /*VERIFICA QUE SE INGRESA UN STRING VALIDO*/
			c=fgetc(archivo);
			while(c!=EOF){
				if(c == '"'){
					t.compLex=STRING;
		    			t.lexema="STRING";
					break;
				}else{
				   c=fgetc(archivo);
				}
			}
			if (c==EOF)
				error("Se llego al fin sin cerrar el String");
			
			break;
		}
		else if (isdigit(c))
		{
			//es un numero

			i=0;
			estado=0;
			acepto=0;
			id[i]=c;
		
			while(!acepto)
			{
				switch(estado){
					case 0: //una secuencia netamente de digitos, puede ocurrir . o e
						c=fgetc(archivo);
						if (isdigit(c))
						{
							id[++i]=c;
							estado=0;
						}
						else if(c=='.'){
							id[++i]=c;
							estado=1;
						}
						else if(tolower(c)=='e'){
							id[++i]=c;
							estado=3;
						}
						else{
							estado=6;
						}
						break;
				
					case 1://un punto, debe seguir un digito (caso especial de array, puede venir otro punto)
						c=fgetc(archivo);						
						if (isdigit(c))
						{
							id[++i]=c;
							estado=2;
						}
						else if(c=='.')
						{
							i--;
							fseek(archivo,-1,SEEK_CUR);
							estado=6;
						}
						else{
							sprintf(msg,"No se esperaba '%c'",c);
							estado=-1;
						}
						break;
					case 2://la fraccion decimal, pueden seguir los digitos o e
						c=fgetc(archivo);
						if (isdigit(c))
						{
							id[++i]=c;
							estado=2;
						}
						else if(tolower(c)=='e')
						{
							id[++i]=c;
							estado=3;
						}
						else
							estado=6;
						break;
					case 3://una e, puede seguir +, - o una secuencia de digitos
						c=fgetc(archivo);
						if (c=='+' || c=='-')
						{
							id[++i]=c;
							estado=4;
						}
						else if(isdigit(c))
						{
							id[++i]=c;
							estado=5;
						}
						else{
							sprintf(msg,"No se esperaba '%c'",c);
							estado=-1;
						}
						break;
					case 4://necesariamente debe venir por lo menos un digito
						c=fgetc(archivo);
						if (isdigit(c))
						{
							id[++i]=c;
							estado=5;
						}
						else{
							sprintf(msg,"No se esperaba '%c'",c);
							estado=-1;
						}
						break;
					case 5://una secuencia de digitos correspondiente al exponente
						c=fgetc(archivo);
						if (isdigit(c))
						{
							id[++i]=c;
							estado=5;
						}
						else{
							estado=6;
						}break;
					case 6://estado de aceptacion, devolver el caracter correspondiente a otro componente lexico
						if (c!=EOF)
							ungetc(c,archivo);
						else
							c=0;
						id[++i]='\0';
						acepto=1;
						if (t.pe->compLex==-1)
						{
							//strcpy(e.lexema,id);
							//e.compLex=NUM;
						}
						t.compLex=NUM;
						t.lexema="NUMBER";
						break;
					case -1:
						if (c==EOF)
							error("No se esperaba el fin de archivo");
						else
							error(msg);
						exit(1);
					}
				}
			break;
		}
	}
	if (c==EOF)
	{
		t.compLex=EOF;
		t.lexema="EOF";
	}
}

int main(int argc,char* args[])
{
	// inicializar analizador lexico

	initTabla();
	initTablaSimbolos();
	
	if(argc > 1)
	{
		if (!(archivo=fopen(args[1],"rt")))
		{
			printf("Archivo no encontrado.\n");
			exit(1);
		}
		while (t.lexema!="EOF"){
			sigLex();
			printf("%s ",t.lexema); 
		}
		fclose(archivo);
	}else{
		printf("Debe pasar como parametro el path al archivo fuente.\n");
		exit(1);
	}

			printf("\n");

	return 0;
}
