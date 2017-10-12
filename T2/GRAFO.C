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
*     Versão  Autor    Data     Observações
*     
*     
*     
*     1             02/out/2017 início desenvolvimento
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

         struct tagElemGrafo * pAresta ;
               /* Ponteiro para a aresta do elemento */

         struct tagElemLista * pVertice ;
               /* Ponteiro para a lista de um só vértice, que representa o próprio vértice */

   } tpElemGrafo ;

/***********************************************************************
*
*  $TC Tipo de dados: GRF Descritor da cabeça do grafo
*
*
***********************************************************************/

   typedef struct GRF_tagGrafo {

         tpElemLista * pOrigemGrafo ;
               /* Ponteiro para a origem da lista VerticeS */

         tpElemLista * pElemCorr ;
               /* Ponteiro para o vértice corrente */

         int numElem ;
               /* Número de elementos da lista Vértices */

         void ( * ExcluirValor ) ( void * pValor ) ;
               /* Ponteiro para a função de destruição do valor contido em um elemento */

   } GRF_tpGrafo ;


   /***** Protótipos das funções encapuladas no módulo *****/

   static void LiberarElemento( GRF_tppGrafo   pGrafo ,
                                tpElemGrafo  * pElem   ) ;

   static tpElemGrafo * CriarElemento( LIS_tppGrafo pGrafo ,
                                       void *       pValor  ) ;

   static void LimparCabeca( LIS_tppLista pLista ) ;

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: GRF  &Criar grafo
*  ****/



   LIS_tppGrafo GRF_CriarGrafo(
             void   ( * ExcluirValor ) ( void * pDado ) )
   {

	  /* cabeça do grafo é iniciada como NULL */
      GRF_tpGrafo * pVertices = NULL ; //Ponteiro para a lista VerticeS, a lista inicial que contém todos os vértives duplamente encadeados, a cabeça do grafo aponta para seu começo

      pVertices = ( GRF_tpGrafo * ) malloc( sizeof( LIS_tpLista )) ;
      if ( pLista == NULL )
      {
         return NULL ;
      } /* if */

      LimparCabeca( pLista ) ;

      pLista->ExcluirValor = ExcluirValor ;

      return pLista ;

   } /* Fim função: GRF  &Criar grafo */
