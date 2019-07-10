#include <stdio.h>
#include "dec_dat.h"

<<<<<<< HEAD
int test2;
int test1;
int n;
list_int l_result;
list_int lista_e_2;
list_int lista_e_1;
list_double lista_r_2;
list_double lista_r_1;
=======
int hola;
int b;
int a;
int valor;
int boo2;
int boo;
double r;
char c;
list_int la;
list_int le;
>>>>>>> 08b0f0675f365dbe5e80fa02fb15cd2c3dbdaf18
int main()
{

	void test(int e1, int e2)
	{

<<<<<<< HEAD
		void test2(int e3, int e4)
		{

		
		}
		test2(e1, e2);
	
	}
	void mostrarLista(list_int l)
	{

		int n;
		n = 0;
		etiqueta1: ;
		int temp1 =   getLength(&l);
		int temp2 = n < temp1;
		if (!temp2) goto etiqueta2;
		{

			printf("%s", "\n Valor de la posicion ");
			printf("%d", n);
			printf("%s", " = ");
			int temp3 =   get_int(&l,n);
			printf("%d", temp3);
			printf("%s", "\n");
			n = n + 1;
		
		}
		goto etiqueta1;
		etiqueta2: ;
	
	}
	lista_e_1 = createList_int(6,1,2,3,4,5,6);
	lista_e_2 = createList_int(5,7,8,9,10,11);
	printf("%s", "\n Mostramos lista lista_e_1: \n");
	mostrarLista(lista_e_1);
	printf("%s", "\n Mostramos lista lista_e_2: ");
	mostrarLista(lista_e_2);
	printf("%s", "\n Concatenamos las listas y mostramos el resultado: ");
	l_result =   link_int(&lista_e_1,&lista_e_2);
	mostrarLista(l_result);
	test1 = 0;
	test2 = 0;
	test(test1, test2);

}
=======
		hola = 2;
	
	}
	etiqueta1: ;
	hola = 1;
	etiqueta3: ;
	int temp7 = hola < 10;
	if (!temp7) goto etiqueta4;
>>>>>>> 08b0f0675f365dbe5e80fa02fb15cd2c3dbdaf18
