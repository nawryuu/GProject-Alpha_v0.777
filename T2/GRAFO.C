/***************************************************************************
*  $MCI Módulo de implementação: GRF  Grafo
*
*  Arquivo gerado:              GRAFO.c
*  Letras identificadoras:      GRF
*
*  Nome da base de software:    
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\GRAFO.BSW
*
*  Projeto: INF1301 T2 Módulo Grafo Genérico
*  Gestor: INF1301 PUC-Rio
*  Autores: tap, gsa
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data        Observações
*     8        gsa    14/out/2017  DestruirGrafo+Correção
*     8        gsa    14/out/2017  CriarAresta
*     7        tap    14/out/2017  IrVertice+correção
*     6        tap    14/out/2017  CriarVertice 
*     5        tap    14/out/2017  DestruirGrafo
*     4        gsa    13/out/2017  CriarGrafo v2
*     3        tap    13/out/2017  CriarGrafo v1
*     2        gsa    13/out/2017  Structs 
*     1               02/out/2017  início desenvolvimento
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>
#include "LISTA.h"

#define GRAFO_OWN
#include "GRAFO.h"
#undef GRAFO_OWN

#define DIM_VT_LISTA   10

GRF_tppGrafo * pCabeca;

/***********************************************************************
*
*  $TC Tipo de dados: GRF Elemento da lista
*
*
***********************************************************************/

typedef struct tagElemGrafo {

         LIS_tppLista * pAresta ;
               /* Ponteiro para a aresta do elemento */

         LIS_tppLista * pVertice ;
               /* Ponteiro para a lista de um só vértice, que representa o próprio vértice */

   } tpElemGrafo ;

/***********************************************************************
*
*  $TC Tipo de dados: GRF Descritor da cabeça do grafo
*
*
***********************************************************************/

   typedef struct GRF_tagGrafo {

         LIS_tppLista * pOrigemGrafo ;
               /* Ponteiro para a origem da lista VerticeS */

         LIS_tppLista * pElemCorr ;
               /* Ponteiro para o vértice corrente */	
		 void ( * ExcluirValor ) ( void * pValor ) ;

   } GRF_tpGrafo ;



/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************/

/***************************************************************************
*
*  Função: GRF  &Criar grafo
*  ****/

   GRF_tppGrafo GRF_CriarGrafo(
             void   ( * ExcluirValor ) ( void * pDado ) )
   {
	  /* cabeça do grafo é iniciada como NULL */
      GRF_tpGrafo * pCab = NULL; //Ponteiro para a lista VerticeS, a lista inicial que contém todos os vértives duplamente encadeados, a cabeça do grafo aponta para seu começo

      pCab = ( GRF_tpGrafo * ) malloc( sizeof( GRF_tpGrafo )) ;
      if ( pCab == NULL )
      {
         return NULL ;
      } /* if */

	  LIS_tppLista  * pOrig;
	  pCab->pElemCorr = NULL;
	  pOrig = pCab->pOrigemGrafo;


	  /* cria a lista Vértices */
	  pCab->pOrigemGrafo = LIS_CriarLista( ExcluirValor );
	  pCab->pElemCorr = NULL;
      
      return pCab;

   } /* Fim função: GRF  &Criar grafo */


    /***************************************************************************
*
*  Função: GRF  &Destruir aresta
*  ****/


    /***************************************************************************
*
*  Função: GRF  &Destruir vértice
*  ****/
   void GRF_DestruirVertice( tpElemGrafo * Elem ){

	   LIS_DestruirLista(  Elem->pAresta );
	   LIS_DestruirLista(  Elem->pVertice );
	   free( Elem );


   } /*Fim função: GRF &Destruir vértice

   /***************************************************************************
*
*  Função: GRF  &Destruir grafo
*  ****/

   void GRF_DestruirGrafo( GRF_tppGrafo pCab )
   {
	  
	  tpElemGrafo *valor;
	  LIS_tpCondRet Resultado;
      #ifdef _DEBUG
         assert( pCab != NULL ) ;
      #endif
	
	 /*precisa percorrer a lista Vertices destruindo as arestas e vértices para depois do while destruir a lista Vertices */
	 for(valor = LIS_ObterValor( pCab->pOrigemGrafo ); valor !=NULL; Resultado = LIS_AvancarElementoCorrente( pCab->pOrigemGrafo, 1))
		 GRF_DestruirVertice( valor );
	 	  
      LIS_DestruirLista( pCab->pOrigemGrafo ) ;

      free( pCab ) ;

   } /* Fim função: LIS  &Destruir lista */

      
   /***************************************************************************
*
*  Função: GRF  &Ir vértice
*  ****/   

   void IrVertice ( GRF_tpGrafo * pCab, LIS_tppLista * Vertice ){
	   
	   pCab->pElemCorr = Vertice;

   } /* Fim função: GRF &Ir vértice

   /***************************************************************************
*
*  Função: GRF  &Criar vértice
*  ****/   
   GRF_tppGrafo GRF_CriarVertice( GRF_tppGrafo pCab, void * pValor)
   {
	  //LIS_tppLista * vtListas[ 10 ];
	  tpElemGrafo * Elem = NULL;
	  LIS_tpCondRet Resultado_Vertice_S;
	  LIS_tpCondRet Resultado_Vertice;
      Elem = ( tpElemGrafo * ) malloc( sizeof( tpElemGrafo )) ;
      if ( Elem == NULL )
      {
         return NULL ;
      } /* if */

	  /* cria a lista Vértice, de um só nó */
	  Elem->pVertice = LIS_CriarLista( pCab->ExcluirValor );
	  /*condições de retorno*/
	  Resultado_Vertice = LIS_InserirElementoApos( Elem->pVertice, pValor);	  
	  Resultado_Vertice_S = LIS_InserirElementoApos( pCab->pOrigemGrafo, Elem );

	  /*Atualiza o ElemCorr da cabeça do grafo, vai para o vértice recém criado */
	  IrVertice(pCab, Elem->pVertice);
      
      return pCab;

   } /* Fim função: GRF  &Criar vértice */

   /***************************************************************************
 *
 *  Função: GRF  &Criar Aresta
 *  ****/
 
 //A função vai pegar dois vértices e vai formar uma aresta entre eles
 void GRF_CriarAresta( tpElemGrafo * pVertice1, tpElemGrafo * pVertice2, void ( * ExcluirValor ) ( void * pValor ) )
 {
 	tpElemGrafo *Elem1 = pVertice1; 
 	tpElemGrafo *Elem2 = pVertice2;
 	LIS_tpCondRet Resultado_Aresta1;
 	LIS_tpCondRet Resultado_Aresta2;
 	
 	#ifdef _DEBUG
 	assert( Elem1->pVertice != NULL && Elem2->pVertice != NULL );
 	#endif
 
 	
 	//Criando lista de aresta em Elem1 caso ela não exista
 	if ( Elem1->pAresta == NULL )
 	{
 		Elem1->pAresta = LIS_CriarLista( ExcluirValor );
 	} /* if */
 	//Criando lista de aresta em Elem2 caso ela não exista
 	if ( Elem2->pAresta == NULL ){
 		Elem2->pAresta = LIS_CriarLista( ExcluirValor );
 	 } /* if */
 	//Verifica se a aresta já existe, caso não exista adiciona elemento nas listas de arestas dos dois elementos
 	if ( LIS_ProcurarValor ( Elem1->pAresta , Elem2 ) == LIS_CondRetNaoAchou )
 	{
 		if ( LIS_ProcurarValor ( Elem2->pAresta , Elem1 ) == LIS_CondRetNaoAchou )
 		{
 			Resultado_Aresta1 = LIS_InserirElementoApos( Elem1->pAresta, Elem2);	
 			Resultado_Aresta2 = LIS_InserirElementoApos( Elem2->pAresta, Elem1);
 		} /* if */
 	} /* if */
 }
 	/* Fim função: GRF &Criar Aresta */

   /***************************************************************************
*
*  Função: GRF  &Obter referência para o vértice contido na lista Vértices
*  ****/

   void * GRF_ObterCorrente( GRF_tppGrafo pCab )
   {

      #ifdef _DEBUG
         assert( pCab != NULL ) ;
      #endif

      if ( pCab->pElemCorr == NULL )
      {
        return NULL ;
      } /* if */

      return pCab->pElemCorr;

   } /* Fim função: GRF  &Obter referência para o vértice contido na lista Vértices */
