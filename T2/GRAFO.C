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
*     14       tap    15/out/2017  IrVertice + CriarArestaCorreção
*     13       gsa    15/out/2017  typeCasting + Correções
*     12       tap    15/out/2017  CriarArestaCorreção
*     11       tap    15/out/2017  CorreçõesCriarAresta/ObterCorrente
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
    GRF_tpCondRet GRF_DestruirAresta( GRF_tppGrafo pCab, void *pValor )
    {
 	
       #ifdef _DEBUG
          assert( pCab != NULL ) ;
       #endif
 
       IrInicioLista( pCab->pOrigemGrafo );

       if ( pCab->pElemCorr == NULL )
       {
       	return GRF_CondRetGrafoVazio ;
       } /* if */
       
       tpElemGrafo *Vertice1 = pCab->pElemCorr;
       tpElemGrafo *Vertice2 ;
     
       while( pCab->pElemCorr != NULL)
       {
 	      if ( pCab->pElemCorr->pVertice == pValor)
 	      {
 		      Vertice2 = LIS_ObterValor( pCab->pOrigemGrafo );
 	      }
 	      LIS_AvancarElementoCorrente ( pCab->pOrigemGrafo, 1 ) ;
       }
       LIS_ProcurarValor( Vertice1->pAresta, LIS_ObterValor (Vertice2) ) ;
       LIS_ExcluirElemento( Vertice1 ) ;	   
       LIS_ProcurarValor( Vertice2->pAresta, LIS_ObterValor (Vertice1) ) ;
       
	   return GRF_CondRetOK;
 	  // (INCOMPLETA)
 	   
    } /* Fim função: GRF  &Obter referência para o vértice contido na lista Vértices */
	 
    /***************************************************************************
*
*  Função: GRF  &Destruir vértice
*  ****/
   GRF_tpCondRet GRF_DestruirVerticeCorrente( GRF_tppGrafo pCab ){
	   LIS_tpCondRet Resultado_Avancar;
	   LIS_tpCondRet Resultado_Excluir;

	   IrInicioLista( pCab->pOrigemGrafo );

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
	  IrInicioLista( pCab->pOrigemGrafo );

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

   GRF_tpCondRet IrVertice ( GRF_tpGrafo * pCab, void * pValor ){

	   LIS_tpCondRet Resultado;

	   IrInicioLista( pCab->pOrigemGrafo );

	   while( ((tpElemGrafo*)LIS_ObterValor(pCab->pOrigemGrafo))->pVertice != pValor )
	   {		     
		    Resultado = LIS_AvancarElementoCorrente( pCab->pOrigemGrafo,1);
			if(Resultado == LIS_CondRetFimLista) 
				return GRF_CondRetNaoAchou;
	   }
	   pCab->pElemCorr = (tpElemGrafo *) LIS_ObterValor( pCab->pOrigemGrafo );
	   return GRF_CondRetOK;
   } /* Fim função: GRF &Ir vértice

   /***************************************************************************
*
*  Função: GRF  &Criar vértice
*  ****/   
   GRF_tpCondRet GRF_CriarVertice( GRF_tppGrafo pCab, void * pValor)
   {	  
	   IrInicioLista( pCab->pOrigemGrafo );

	  tpElemGrafo * Elem = NULL;
	  LIS_tpCondRet Resultado_Vertice_S;	  
      Elem = ( tpElemGrafo * ) malloc( sizeof( tpElemGrafo )) ;
      if ( Elem == NULL )
      {
         return GRF_CondRetFaltouMemoria ;
      } /* if */
	  	 
	  Elem->pVertice = pValor; 
	  Elem->pAresta = NULL;
	  /*Inserção na lista de Vértices*/	  
	  Resultado_Vertice_S = LIS_InserirElementoApos( pCab->pOrigemGrafo, Elem );

	  /*Atualiza o ElemCorr da cabeça do grafo, vai para o vértice recém criado */	 
      pCab->pElemCorr = Elem;
      return GRF_CondRetOK;

   } /* Fim função: GRF  &Criar vértice */
      
   /***************************************************************************
 *
 *  Função: GRF  &Criar Aresta
 *  ****/
 GRF_tpCondRet GRF_CriarAresta ( GRF_tppGrafo pCab, void * pValor, void   ( * ExcluirValor ) ( void * pDado ) ){

	 LIS_tpCondRet Resultado_1;
	 LIS_tpCondRet Resultado_2;

	 tpElemGrafo* SalvaCorrente;
	 	
	 if (pCab == NULL || pCab->pElemCorr == NULL){
		 return GRF_CondRetGrafoVazio;
	 }

	 if( pCab->pElemCorr->pAresta == NULL )
		 pCab->pElemCorr->pAresta = LIS_CriarLista( ExcluirValor );

	 Resultado_1 = LIS_ProcurarValor( pCab->pElemCorr->pAresta, pValor );
	 
	 //Resultado_2 = LIS_ProcurarValor(  , pCab->pElemCorr->pVertice);

	 if ( Resultado_1 == LIS_CondRetOK)
		 return GRF_CondRetValorRepetido;
	 /*como o elemento ainda não está na lista de arestas, ele é inserido */
	 LIS_InserirElementoApos( pCab->pElemCorr->pAresta, pValor ); 

	 /* obter a lista de arestas do outro elemento */ 
	SalvaCorrente = pCab->pElemCorr;
	IrVertice( pCab, pValor);

	LIS_InserirElementoApos( pCab->pElemCorr->pAresta, SalvaCorrente->pVertice ); 

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
