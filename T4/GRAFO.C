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
*     17       tap    02/nov/2017  Identação e padrões
*     16       tap    16/out/2017  Correção DestruirVerticeCorrente
*     15       gsa    16/out/2017  DestruirAresta
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
*     1        gsa    02/out/2017  início desenvolvimento
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>

#define LISTA_OWN
#include "LISTA.h"
#undef LISTA_OWN

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
       GRF_tpGrafo * pCab = NULL ; 

       pCab = ( GRF_tpGrafo * ) malloc( sizeof( GRF_tpGrafo )) ;
       if ( pCab == NULL )
       {
           return NULL ;
       } /* if */	  
	  
	   /* cria a lista Vértices */
	  
	   pCab->pOrigemGrafo = LIS_CriarLista( ExcluirValor ) ;
	   pCab->pElemCorr = NULL ;
      
      return pCab ;

   } /* Fim função: GRF  &Criar grafo */


    /***************************************************************************
*
*  Função: GRF  &Destruir aresta
*  ****/
   GRF_tpCondRet GRF_DestruirAresta( GRF_tppGrafo pCab, void *pValor )
   {
       LIS_tpCondRet Resultado ;
	   GRF_tpCondRet Resultado_G ;

	   tpElemGrafo *Vertice1 ;
	   tpElemGrafo *Vertice2 ;

	   /* Verifica se o grafo existe */
   	   if (pCab == NULL)
	       return GRF_CondRetGrafoNaoExiste ;
 
       IrInicioLista( pCab->pOrigemGrafo ) ;
	
	   /* Verifica se o grafo está vazio */   
       if ( pCab->pElemCorr == NULL )
	   {
       		return GRF_CondRetGrafoVazio ;
	   } /* if */
       
	   if ( LIS_AvancarElementoCorrente( pCab->pElemCorr->pAresta, 0) == LIS_CondRetListaVazia )
	   {
	       return GRF_CondRetGrafoListaVazia;
	   } /* if */

       Vertice1 = pCab->pElemCorr ;
       
       Resultado_G = GRF_IrVertice ( pCab, pValor ) ;
	   if( Resultado_G == GRF_CondRetNaoAchou )
	   {
	       return GRF_CondRetNaoAchou ;
	   } /* if */
       
       Vertice2 = pCab->pElemCorr ;
       
       /* Procura o vertice 2 na lista de arestas do vertice 1 */   

       Resultado = LIS_ProcurarValor( Vertice1->pAresta, Vertice2 ) ;
       if ( Resultado == LIS_CondRetNaoAchou )
	   {
	       return GRF_CondRetNaoAchouGrafoElemLista ;
	   } /* if */

       if ( Resultado ==  LIS_CondRetListaVazia )
	   {
	       return  GRF_CondRetGrafoListaVazia ;
	   } /* if */
	    
	    
	/* Exclui elemento vertice2 da lista de arestas do vertice 1 */ 

       LIS_ExcluirElemento( Vertice1->pAresta ) ;
	    
    /* Procura o vertice 1 na lista de arestas do vertice 2 */

       LIS_ProcurarValor( Vertice2->pAresta, Vertice1 ) ;
       if ( Resultado == LIS_CondRetNaoAchou )
	   {
	       return GRF_CondRetNaoAchouGrafoElemLista ;
	   } /* if */

       if ( Resultado ==  LIS_CondRetListaVazia )
	   {
	       return GRF_CondRetGrafoListaVazia ;
	   } /* if */

    /* Exclui o Vertice 1 da lista de arestas do vertice 2 */

       LIS_ExcluirElemento( Vertice2->pAresta ) ;	
       
	   return GRF_CondRetOK ;
 	   
    } /* Fim função: GRF  &Obter referência para o vértice contido na lista Vértices */
	 
    /***************************************************************************
*
*  Função: GRF  &Destruir vértice
*  ****/

   GRF_tpCondRet GRF_DestruirVerticeCorrente( GRF_tppGrafo pCab )
   {

       LIS_tpCondRet Resultado_Avancar ;
	   LIS_tpCondRet Resultado_Excluir ;

	   if ( pCab == NULL ) 
	   {
	       return GRF_CondRetGrafoNaoExiste ;
	   } /* if */

	    if ( pCab->pElemCorr == NULL ) 
		{
		    return GRF_CondRetGrafoVazio ;
		} /* if */

	   IrInicioLista( pCab->pOrigemGrafo ) ;
	   	   
	   while( LIS_AvancarElementoCorrente( pCab->pElemCorr->pAresta , 0) != LIS_CondRetListaVazia )
	   {
	       GRF_DestruirAresta( pCab, (( tpElemGrafo *) LIS_ObterValor( pCab->pElemCorr->pAresta ))->pVertice ) ;
	   } /* while */

	   pCab->pElemCorr->pVertice = NULL ;	
	   free( pCab->pElemCorr->pAresta ) ;

	   while(LIS_ObterValor(pCab->pOrigemGrafo) != pCab->pElemCorr)
	   {
	       Resultado_Avancar = LIS_AvancarElementoCorrente( pCab->pOrigemGrafo , 1 ) ;
	   } /* while */

	   /* chegou no elemento corrente */

	   Resultado_Excluir = LIS_ExcluirElemento(pCab->pOrigemGrafo) ;	   
	   IrInicioLista( pCab->pOrigemGrafo ) ;
	   pCab->pElemCorr = ( tpElemGrafo * ) LIS_ObterValor(pCab->pOrigemGrafo) ;

	   return GRF_CondRetOK ;

   } /*Fim função: GRF &Destruir vértice

   /***************************************************************************
*
*  Função: GRF  &Destruir grafo
*  ****/

   GRF_tpCondRet GRF_DestruirGrafo( GRF_tppGrafo pCab )
   {
   
       if ( pCab == NULL )
	   {
	       return GRF_CondRetGrafoNaoExiste;
	   } /* if */

	   IrInicioLista( pCab->pOrigemGrafo ) ;
	     	        	
	 /*precisa percorrer a lista Vertices destruindo as arestas e vértices para depois do while destruir a lista Vertices */
	   
	   while(pCab->pOrigemGrafo != NULL )
	   {
	       GRF_DestruirVerticeCorrente( pCab ) ;
	   } /* while */
	 	  
       LIS_DestruirLista( pCab->pOrigemGrafo ) ;

       free( pCab ) ;

	   return GRF_CondRetOK ;

   } /* Fim função: LIS  &Destruir lista */

      
   /***************************************************************************
*
*  Função: GRF  &Ir vértice
*  ****/   

   GRF_tpCondRet GRF_IrVertice ( GRF_tpGrafo * pCab,
							     void * pValor      )
   {

       LIS_tpCondRet Resultado;

	   if ( pCab == NULL )
	   {
	       return GRF_CondRetGrafoNaoExiste;
	   } /* if */

	   if ( pCab->pElemCorr == NULL )
	   {
	       return GRF_CondRetGrafoVazio ;
	   } /* if */
	   	   
	   IrInicioLista( pCab->pOrigemGrafo ) ;

	   while( ((tpElemGrafo*)LIS_ObterValor(pCab->pOrigemGrafo))->pVertice != pValor )
	   {		     
		   Resultado = LIS_AvancarElementoCorrente( pCab->pOrigemGrafo,1) ;
	       if( Resultado == LIS_CondRetFimLista && ((tpElemGrafo*)LIS_ObterValor(pCab->pOrigemGrafo))->pVertice != pValor  )
		   {			  
			    return GRF_CondRetNaoAchou ;
		   } /* if */

	   } /* while */

	   pCab->pElemCorr = (tpElemGrafo *) LIS_ObterValor( pCab->pOrigemGrafo ) ;

	   return GRF_CondRetOK ;

   } /* Fim função: GRF &Ir vértice

   /***************************************************************************
*
*  Função: GRF  &Criar vértice
*  ****/   
   GRF_tpCondRet GRF_CriarVertice( GRF_tppGrafo pCab,
								   void * pValor,
								   void   ( * ExcluirValor ) ( void * pDado ) ) 
   {	  
       tpElemGrafo * Elem ;
       LIS_tpCondRet Resultado_Vertice_S ;

 	   IrInicioLista( pCab->pOrigemGrafo ) ;
	   Elem = NULL ;
	  
       Elem = ( tpElemGrafo * ) malloc( sizeof( tpElemGrafo )) ;
       
	   if ( Elem == NULL ) 
	   {
           return GRF_CondRetFaltouMemoria ;
	   } /* if */
      	  	 
	   Elem->pVertice = pValor ; 
	   Elem->pAresta = LIS_CriarLista( ExcluirValor ) ;

	  /*Inserção na lista de Vértices*/	 

	   Resultado_Vertice_S = LIS_InserirElementoApos( pCab->pOrigemGrafo, Elem ) ;

	  /*Atualiza o ElemCorr da cabeça do grafo, vai para o vértice recém criado */	 

       pCab->pElemCorr = Elem ;

       return GRF_CondRetOK ;

   } /* Fim função: GRF  &Criar vértice */
      
   /***************************************************************************
 *
 *  Função: GRF  &Criar Aresta
 *  ****/

 GRF_tpCondRet GRF_CriarAresta (GRF_tppGrafo pCab, void * pValor)
 {

     GRF_tpCondRet Resultado_G ;
     LIS_tpCondRet Resultado ;
  
     tpElemGrafo *Vertice1 ;
     tpElemGrafo *Vertice2 ;
  
     if ( pCab == NULL || pCab->pElemCorr == NULL ) 
	 {
         return GRF_CondRetGrafoVazio ;
     } /* if */
  
     Vertice1 = pCab->pElemCorr ; 

  /* Obtendo o ponteiro para o Vertice 2 */

     Resultado_G = GRF_IrVertice ( pCab, pValor) ;

     if ( Resultado_G == GRF_CondRetNaoAchou )
	 {
         return GRF_CondRetNaoAchou ;
	 } /* if */
       
     Vertice2 = pCab->pElemCorr ;
   
  /* Verifica se o valor já está na lista de arestas do vértice 1*/

      Resultado = LIS_ProcurarValor( Vertice1->pAresta, Vertice2 ) ;
      if ( Resultado == LIS_CondRetOK)
	  {
          return GRF_CondRetValorRepetido;
	  } /* if */
  
  /* Se o elemento ainda não está na lista de arestas, ele é inserido nas listas de vertice 1 e 2 */

      LIS_InserirElementoApos( Vertice1->pAresta, Vertice2 ) ; 
      LIS_InserirElementoApos( Vertice2->pAresta, Vertice1 ) ; 
 
      return GRF_CondRetOK ;

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

	   return pCab->pElemCorr->pVertice ;

   } /* Fim função: GRF  &Obter referência para o vértice contido na lista Vértices */
