/***************************************************************************
*  $MCI Módulo de implementação: PRF  Perfil
*
*  Arquivo gerado:              PERFIL.c
*  Letras identificadoras:      PRF
*
*  Nome da base de software:    
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\PERFIL.BSW
*
*  Projeto: INF 1301 T2 Módulo Grafo Genérico
*  Gestor: INF 1301 PUC-Rio
*  Autores: tap, gsa
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data        Observações
*    
*     2        tap    03/dez/2017  Structs 
*     1        tap    03/dez/2017  início desenvolvimento
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
#include "GRAFO.h"
#undef GRAFO_OWN

#define PERFIL_OWN
#include "PERFIL.h"
#undef PERFIL_OWN


/***********************************************************************
*
*  $TC Tipo de dados: PRF Estrutura perfil
*
*
***********************************************************************/

   typedef struct PRF_tagPerfil {

         char email[51] ;
               /* Ponteiro para o email do perfil */

         char nome[51] ;
               /* Ponteiro para o nome do perfil */	

		 char sobrenome[51] ;
		       /* Ponteiro para o sobrenome do perfil */	

		 char senha[51] ;
		       /* Ponteiro para a senha do perfil */	

   } PRF_tpPerfil ;

   /*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************/
         

/***************************************************************************
*
*  Função: PRF  &Criar perfil
*  ****/

   PRF_tpCondRet PRF_CriarPerfil( GRF_tppGrafo pCab,
								   char * pEmail,
								   char * pNome,
								   char * pSobrenome,
								   char * pSenha,
								   void   ( * ExcluirValor ) ( void * pDado ) ) 
   {
	   
	  PRF_tpPerfil * pPerfil;

	  if ( pCab == NULL ) 
	  {
		  return PRF_CondRetGrafoNaoExiste ;
	  }

	  

	  pPerfil =( PRF_tpPerfil * )  malloc ( sizeof( PRF_tpPerfil ) ) ;
	  if ( pPerfil == NULL )
	  {
		  return PRF_CondRetFaltouMemoria ;
	  }
	  
	  strcpy( pPerfil->email, pEmail ) ;
	  strcpy( pPerfil->nome, pNome ) ;
	  strcpy( pPerfil->sobrenome, pSobrenome ) ;
	  strcpy( pPerfil->senha, pSenha ) ;
	  
	  GRF_CriarVertice ( pCab, pPerfil, ExcluirValor ) ; 

	  return PRF_CondRetOK ;

   } /* Fim função: PRF  &Criar perfil */


/***************************************************************************
*
*  Função: PRF  &Obter email corrente
*  ****/

   char * PRF_ObterEmailCorrente ( GRF_tppGrafo pCab ) 
   {
	   PRF_tpPerfil * pPerfil;

	   if ( pCab == NULL ) 
	   {
		   return NULL ;
	   }

	   pPerfil = (PRF_tpPerfil *) GRF_ObterCorrente ( pCab );
	   if ( pPerfil == NULL ) 
	   {
		   return NULL ;		  
	   }

	   return pPerfil->email ;


   } /* Fim função: PRF  &Obter email corrente */


   /***************************************************************************
*
*  Função: PRF  &Obter nome
*  ****/

   char * PRF_ObterNomeCorrente ( GRF_tppGrafo pCab ) 
   {
	   PRF_tpPerfil * pPerfil ;

	   if ( pCab == NULL ) 
	   {
		   return NULL ;
	   }

	   pPerfil = (PRF_tpPerfil *) GRF_ObterCorrente ( pCab );
	   if ( pPerfil == NULL ) 
	   {
		   return NULL ;		  
	   }

	   return pPerfil->nome ;


   } /* Fim função: PRF  &Obter nome corrente */


   /***************************************************************************
*
*  Função: PRF  &Obter sobrenome
*  ****/

   char * PRF_ObterSobrenomeCorrente ( GRF_tppGrafo pCab ) 
   {
	   PRF_tpPerfil * pPerfil ; 

	   if ( pCab == NULL ) 
	   {
		   return NULL ;
	   }

	   pPerfil = (PRF_tpPerfil *) GRF_ObterCorrente ( pCab );
	   if ( pPerfil == NULL ) 
	   {
		   return NULL ;		  
	   }

	   return pPerfil->sobrenome ;


   }  /* Fim função: PRF  &Obter sobrenome corrente */


      /***************************************************************************
*
*  Função: PRF  &Obter senha
*  ****/

   char * PRF_ObterSenhaCorrente ( GRF_tppGrafo pCab ) 
   {
	   PRF_tpPerfil * pPerfil ;

	   if ( pCab == NULL ) 
	   {
		   return NULL ;
	   }

	   pPerfil = (PRF_tpPerfil *) GRF_ObterCorrente ( pCab );
	   if ( pPerfil == NULL ) 
	   {
		   return NULL ;		  
	   }

	   return pPerfil->senha ;


   } /* Fim função: PRF  &Obter senha corrente */


      /***************************************************************************
*
*  Função: PRF  &Compara perfil
*  ****/

   int ComparaPerfil( void * pDado1, void * pDado2 ) {

	PRF_tpPerfil * perfil_1 = (PRF_tpPerfil *) pDado1 ;
    PRF_tpPerfil * perfil_2 = (PRF_tpPerfil *) pDado2 ;

	int compResultado ;

	compResultado = strcmp ( perfil_1->email, perfil_2->email ) ;

	if ( compResultado == 0)
	{
		return 1 ;
	}
	else 
		return 0;

    } /* Fim função: PRF  &Compara perfil */
   
