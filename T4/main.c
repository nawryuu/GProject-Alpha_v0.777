#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>
#include   "LISTA.h"
#include   "GRAFO.h"


void DestruirValor( void * pValor )
   {

      free( pValor ) ;

   } /* Fim função: TLIS -Destruir valor */

int main()
{
	int condret;
	LIS_tppLista aresta;

    GRF_tppGrafo g1 = GRF_CriarGrafo( *DestruirValor );

	GRF_CriarVertice( g1, "abc", DestruirValor);
    GRF_CriarVertice( g1, "def", DestruirValor);
	GRF_CriarVertice( g1, "ghi", DestruirValor);
	
	condret = GRF_IrVertice( g1, "abc");

	printf( "\n%s\n", GRF_ObterCorrente(g1) );
	printf( "\n%d\n", condret );
	
	/*
	printf( "\n%s\n", GRF_ObterCorrente(g1) );
	printf( "\n%d\n", condret );
	*/
		
	condret = GRF_CriarAresta(g1,"ghi");
	printf( "\nCriacao de aresta: %d\n", condret );		
	condret = GRF_CriarAresta(g1,"def");
	printf( "\nCriacao de aresta: %d\n", condret );		

	aresta = GRF_ObterListaArestas(g1);

	printf( "\ncorrente: %s\n", GRF_ObterCorrente(g1) );
	IrInicioLista(aresta);	
	printf("\narestas: %s\n",GRF_ObterValorAresta(aresta));
	LIS_AvancarElementoCorrente(aresta,1);	
	printf("\narestas: %s\n",GRF_ObterValorAresta(aresta));

	return 0;
}
