/***************************************************************************
*  $MCI Módulo de implementação: GRF  Grafo
*
*  Arquivo gerado:              GRAFO.c
*  Letras identificadoras:      GRF
*
*  Nome da base de software:    
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\GRAFO.BSW
*
*  Projeto: INF 1301 T2 Módulo Grafo Genérico
*  Gestor: INF 1301 PUC-Rio
*  Autores: tap, gsa
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data        Observações
*     
*     10       tap    14/out/2017  CorreçõesNosStructs
*     9        gsa    14/out/2017  DestruirGrafo+Correção
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
#include "GRAFO2.h"
#undef GRAFO_OWN


/***********************************************************************
*
*  $TC Tipo de dados: GRF Elemento da lista
*
*
***********************************************************************/

typedef struct tagElemGrafo {

         LIS_tppLista pAresta ;
               /* Ponteiro para a aresta do elemento */

         void * pVertice ;
               /* Ponteiro para a lista de um só vértice, que representa o próprio vértice */

   } tpElemGrafo ;

/***********************************************************************
*
*  $TC Tipo de dados: GRF Descritor da cabeça do grafo
*
*
***********************************************************************/

   typedef struct GRF_tagGrafo {

         LIS_tppLista pOrigemGrafo ;
               /* Ponteiro para a origem da lista VerticeS */

         tpElemGrafo * pElemCorr ;
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

	  

	  /* cria a lista Vértices */
	  pCab->pOrigemGrafo = LIS_CriarLista( ExcluirValor );
	  pCab->pElemCorr = NULL;
      
      return pCab;

   } /* Fim função: GRF  &Criar grafo */


    /***************************************************************************
*
*  Função: GRF  &Destruir aresta
*  ****/
    void * GRF_DestruirAresta( GRF_tppGrafo pCab, void *pValor )
    {
 	
       #ifdef _DEBUG
          assert( pCab != NULL ) ;
       #endif
 
       if ( pCab->pElemCorr == NULL )
       {
       	return NULL ;
       } /* if */
       
       GRF_tppGrafo *Vertice1 = pCab->pElemCorr;
       GRF_tppGrafo *Vertice2 ;
     
       while( pCab->pElemCorr != NULL)
       {
 	      if ( LIS_ObterValor ( pCab->pElemCorr )== pValor)
 	      {
 		      Vertice2 = pCab->pElemCorr;
 	      }
 	      LIS_AvancarElementoCorrente ( pCab, 1 ) ;
       }
       LIS_ProcurarValor( Vertice1->pAresta, LIS_ObterValor (Vertice2) ) ;
       LIS_ExcluirElemento( Vertice1 ) ;	   
       LIS_ProcurarValor( Vertice2->pAresta, LIS_ObterValor (Vertice1) ) ;
       
 	  // (INCOMPLETA)
 	   
    } /* Fim função: GRF  &Obter referência para o vértice contido na lista Vértices */
	 
    /***************************************************************************
*
*  Função: GRF  &Destruir vértice
*  ****/
   GRF_tpCondRet GRF_DestruirVerticeCorrente( GRF_tppGrafo pCab ){
	   LIS_tpCondRet Resultado_Avancar;
	   LIS_tpCondRet Resultado_Excluir;

	   free(pCab->pElemCorr->pVertice);
	   LIS_DestruirLista( pCab->pElemCorr->pAresta );

	   while(LIS_ObterValor(pCab->pOrigemGrafo) != pCab->pElemCorr)
		Resultado_Avancar = LIS_AvancarElementoCorrente( pCab->pOrigemGrafo , 1 );
	   /* chegou no elemento corrente */
	   Resultado_Excluir = LIS_ExcluirElemento(pCab->pOrigemGrafo);
	   
	   IrInicioLista( pCab->pOrigemGrafo );

	   return GRF_CondRetOK;
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
	 while(pCab->pOrigemGrafo != NULL )
		 GRF_DestruirVerticeCorrente( pCab );
	 	  
      LIS_DestruirLista( pCab->pOrigemGrafo ) ;

      free( pCab ) ;

   } /* Fim função: LIS  &Destruir lista */

      
   /***************************************************************************
*
*  Função: GRF  &Ir vértice
*  ****/   

   void IrVertice ( GRF_tpGrafo * pCab, void * Vertice ){
	   
	   pCab->pElemCorr = Vertice;

   } /* Fim função: GRF &Ir vértice

   /***************************************************************************
*
*  Função: GRF  &Criar vértice
*  ****/   
   GRF_tppGrafo GRF_CriarVertice( GRF_tppGrafo pCab, void * pValor)
   {	  
	  tpElemGrafo * Elem = NULL;
	  LIS_tpCondRet Resultado_Vertice_S;	  
      Elem = ( tpElemGrafo * ) malloc( sizeof( tpElemGrafo )) ;
      if ( Elem == NULL )
      {
         return NULL ;
      } /* if */

	  /* cria a lista Vértice, de um só nó */
	  Elem->pVertice = pValor; 
	  /*Inserção na lista de Vértices*/	  
	  Resultado_Vertice_S = LIS_InserirElementoApos( pCab->pOrigemGrafo, Elem );

	  /*Atualiza o ElemCorr da cabeça do grafo, vai para o vértice recém criado */	 
      pCab->pElemCorr = Elem;
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

   tpElemGrafo GRF_ObterCorrente( GRF_tppGrafo pCab )
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
