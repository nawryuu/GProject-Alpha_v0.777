/***************************************************************************
*  $MCI Módulo de implementação: GRF  Grafo
*
*  Arquivo gerado:              GRAFO.c
*  Letras identificadoras:      GRF
*
*  Nome da base de software:    
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\GRAFO.BSW
*
*  Projeto: 
*  Gestor: 
*  Autores: 
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data        Observações
*     5        tap    14/out/2017  CriarVertice 
*     4        tap    14/out/2017  DestruirGrafo
*     3        tap    13/out/2017  CriarGrafo
*     2        g      13/out/2017  Structs 
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

/***********************************************************************
*
*  $TC Tipo de dados: GRF Elemento da lista
*
*
***********************************************************************/

typedef struct tagElemGrafo {

         struct LIS_tppLista * pAresta ;
               /* Ponteiro para a aresta do elemento */

         struct LIS_tppLista * pVertice ;
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

   } GRF_tpGrafo ;


   /***** Protótipos das funções encapuladas no módulo *****/

   static void LiberarElemento( GRF_tppGrafo   pGrafo ,
                                tpElemGrafo  * pElem   ) ;

   static tpElemGrafo * CriarElemento( LIS_tppGrafo pGrafo ,
                                       void *       pValor  ) ;

   static void LimparCabeca( LIS_tppLista pLista ) ;

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************/

/***************************************************************************
*
*  Função: GRF  &Criar grafo
*  ****/

   GRF_tpGrafo GRF_CriarGrafo(
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
*  Função: LIS  &Destruir lista
*  ****/

   void GRF_DestruirGrafo( GRF_tpGrafo pCab )
   {
	  LIS_tppLista *elem;
      #ifdef _DEBUG
         assert( pCab != NULL ) ;
      #endif
	 elem = pCab->pOrigemGrafo;
	 /*precisa percorrer a lista Vertices destruindo as arestas e vértices para depois do while destruir a lista Vertices */
      while(elem != NULL){
		  /* FALTA DIVIDIR EM MAIS 2 OUTRAS FUNÇÕES */
		  LIS_DestruirLista( elem->valor->pAresta ); 
          LIS_DestruirLista( elem->valor->vertice );
		  elem += sizeof( LIS_tppLista ); 
	  }
      LIS_DestruirLista( elem ) ;

      free( pCab ) ;

   } /* Fim função: LIS  &Destruir lista */

   /***************************************************************************
*
*  Função: GRF  &Criar vértice
*  ****/

   GRF_tpGrafo GRF_CriarVertice( GRF_tpGrafo pCab, void * pValor
             void   ( * ExcluirValor ) ( void * pDado ) )
   {
	  tpElemGrafo * Elem;
	  LIS_tpCondRet Resultado_Vertice_S;
	  LIS_tpCondRet Resultado_Vertice;
      Elem = ( tpElemGrafo * ) malloc( sizeof( tpElemGrafo )) ;
      if ( Elem == NULL )
      {
         return NULL ;
      } /* if */

	  /* cria a lista Vértice */
	  Elem->pVertice = LIS_CriarLista( ExcluirValor );
	  Resultado_Vertice = LIS_InserirElementoApos( Elem->Vertice, pDado);	  
	  Resultado_Vertice_S = LIS_InserirElementoApos( pCab->pOrigemGrafo, Elem );

	  /*Atualiza o ElemCorr da cabeça do grafo */
	  IrVertice(pCab, Elem->pVertice);
      
      return pCab;

   } /* Fim função: GRF  &Criar vértice */

   /***************************************************************************
*
*  Função: LIS  &Obter referência para o valor contido no elemento
*  ****/

   void * GRF_ObterCorrente( GRF_tpGrafo pCab )
   {

      #ifdef _DEBUG
         assert( pCab != NULL ) ;
      #endif

      if ( pCab->pElemCorr == NULL )
      {
        return NULL ;
      } /* if */

      return pCab->pElemCorr;

   } /* Fim função: LIS  &Obter referência para o valor contido no elemento */
