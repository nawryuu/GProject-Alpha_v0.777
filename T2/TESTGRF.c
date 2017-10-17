/***************************************************************************
*  $MCI Módulo de implementação: TLIS Teste lista de símbolos
*
*  Arquivo gerado:              TestLIS.c
*  Letras identificadoras:      TLIS
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: gsa, tap
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     4       tap   16/out/2017  Correções
*     3       gsa   15/out/2017
*     2       tap   15/out/2017 
*     1       avs   16/abr/2003 início desenvolvimento
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_ESPC.h"

#include    "GENERICO.h"
#include    "LERPARM.h"

#include    "LISTA.h"
#include    "GRAFO2.h"


static const char RESET_GRAFO_CMD                 [ ] = "=resetteste"     ;
static const char CRIAR_GRAFO_CMD                 [ ] = "=criargrafo"     ;
static const char DESTRUIR_GRAFO_CMD              [ ] = "=destruirgrafo"  ;
static const char CRIAR_VERTICE_CMD               [ ] = "=criarvertice"   ;
static const char CRIAR_ARESTA_CMD                [ ] = "=criararesta"    ;
static const char OBTER_CORRENTE_CMD              [ ] = "=obtercorrente"  ;
static const char DESTRUIR_ARESTA_CMD             [ ] = "=destruiraresta" ;
static const char DESTRUIR_VERTICE_CORRENTE_CMD   [ ] = "=destruirvertice";
static const char IR_VERTICE_CMD				  [ ] = "=irvertice"      ;

#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_GRAFO   10
#define DIM_VALOR     100

GRF_tppGrafo   vtGrafos[ DIM_VT_GRAFO ] ;

/***** Protótipos das funções encapuladas no módulo *****/

   static void DestruirValor( void * pValor ) ;

   static int ValidarInxGrafo( int inxGrafo , int Modo ) ;

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TLIS &Testar grafo
*
*  $ED Descrição da função
*     Podem ser criadas até 10 grafos, identificadas pelos índices 0 a 10
*
*     Comandos disponíveis:
*
*     =resetteste
*           - anula o vetor de grafos. Provoca vazamento de memória
*     =criargrafo                   inxGrafo
*     =destruirgrafo                inxGrafo  CondRetEsp 
*     =criarvertice                 inxGrafo  string  CondRetEsp
*     =criararesta                  inxGrafo  string  CondRetEsp
*     =obtercorrente                inxGrafo  
*     =destruiraresta               inxGrafo  string  CondRetEsp
*     =destruirvértice              inxGrafo  CondRetEsp
*     =irvertice                    inxGrafo string CondretPonteiro     
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      int inxGrafo  = -1 ,
          numLidos   = -1 ,
          CondRetEsp = -1  ;

      TST_tpCondRet CondRet  ;

      char   StringDado[  DIM_VALOR ] ;
      char * pDado ;

      int ValEsp = -1 ;

      int i ;

      int numElem = -1 ;

      StringDado[ 0 ] = 0 ;

      /* Efetuar reset de teste de grafo */

         if ( strcmp( ComandoTeste , RESET_GRAFO_CMD ) == 0 )
         {

            for( i = 0 ; i < DIM_VT_GRAFO ; i++ )
            {
               vtGrafos[ i ] = NULL ;
            } /* for */

            return TST_CondRetOK ;

         } /* fim ativa: Efetuar reset de teste de grafo */

      /* Testar CriarGrafo */

         else if ( strcmp( ComandoTeste , CRIAR_GRAFO_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" , 
                       &inxGrafo ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxGrafo( inxGrafo , VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            vtGrafos[ inxGrafo ] =
                 GRF_CriarGrafo( DestruirValor ) ;

            return TST_CompararPonteiroNulo( 1 , vtGrafos[ inxGrafo ] ,
               "Erro em ponteiro de novo grafo."  ) ;

         } /* fim ativa: Testar CriarGrafo */
		     
      /* Testar Destruir grafo */

         else if ( strcmp( ComandoTeste , DESTRUIR_GRAFO_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,
                               &inxGrafo ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxGrafo( inxGrafo , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            GRF_DestruirGrafo( vtGrafos[ inxGrafo ] ) ;
            vtGrafos[ inxGrafo ] = NULL ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar Destruir lista */

      /* Testar criar vértice */

         else if ( strcmp( ComandoTeste , CRIAR_VERTICE_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "isi" ,
                       &inxGrafo , StringDado , &CondRetEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxGrafo( inxGrafo , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            pDado = ( char * ) malloc( strlen( StringDado ) + 1 ) ;
            if ( pDado == NULL )
            {
               return TST_CondRetMemoria ;
            } /* if */

            strcpy( pDado , StringDado ) ;


            CondRet = GRF_CriarVertice ( vtGrafos[ inxGrafo ] , pDado, DestruirValor ) ;

            if ( CondRet != GRF_CondRetOK )
            {
               free( pDado ) ;
            } /* if */

            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao criar vertice."                   ) ;

         } /* fim ativa: Testar inserir elemento antes */

		  /* Testar criar aresta */

         else if ( strcmp( ComandoTeste , CRIAR_ARESTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "isi" ,
                       &inxGrafo , StringDado , &CondRetEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxGrafo( inxGrafo , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            pDado = ( char * ) malloc( strlen( StringDado ) + 1 ) ;
            if ( pDado == NULL )
            {
               return TST_CondRetMemoria ;
            } /* if */

            strcpy( pDado , StringDado ) ;


            CondRet = GRF_CriarAresta ( vtGrafos[ inxGrafo ] , pDado ) ;

            if ( CondRet != GRF_CondRetOK )
            {
               free( pDado ) ;
            } /* if */

            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao criar aresta."                   ) ;

         } /* fim ativa: Testar criar aresta */



		  /* Testar obter o elemento corrente */

         else if ( strcmp( ComandoTeste , OBTER_CORRENTE_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "isi" ,
                       &inxGrafo , StringDado , &ValEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxGrafo( inxGrafo , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            pDado = ( char * ) GRF_ObterCorrente( vtGrafos[ inxGrafo ] ) ;

            if ( ValEsp == 0 )
            {
               return TST_CompararPonteiroNulo( 0 , pDado ,
                         "Valor não deveria existir." ) ;
            } /* if */

            if ( pDado == NULL )
            {
               return TST_CompararPonteiroNulo( 1 , pDado ,
                         "Dado tipo um deveria existir." ) ;
            } /* if */

            return TST_CompararString( StringDado , pDado ,
                         "Valor do elemento errado." ) ;

         } /* fim ativa: Testar obter valor do elemento corrente */


		 /* Testar destruir aresta */

		 else if ( strcmp( ComandoTeste , DESTRUIR_ARESTA_CMD ) == 0 )
         {
		    
            numLidos = LER_LerParametros( "isi" ,
                       &inxGrafo , StringDado , &CondRetEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxGrafo( inxGrafo , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            pDado = ( char * ) malloc( strlen( StringDado ) + 1 ) ;
            if ( pDado == NULL )
            {
               return TST_CondRetMemoria ;
            } /* if */

            strcpy( pDado , StringDado ) ;
						
            CondRet = GRF_DestruirAresta ( vtGrafos[ inxGrafo ] , pDado );

            if ( CondRet != GRF_CondRetOK )
            {
               free( pDado ) ;
            } /* if */

            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao criar aresta."                   ) ;

         } /* fim ativa: Testar criar aresta */


      /* Testar destruir vértice corrente */

         else if ( strcmp( ComandoTeste , DESTRUIR_VERTICE_CORRENTE_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
                  &inxGrafo , &CondRetEsp ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxGrafo( inxGrafo , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            return TST_CompararInt( CondRetEsp ,
                      GRF_DestruirVerticeCorrente( vtGrafos[ inxGrafo ] ) ,
                     "Condição de retorno errada ao destruir corrente."   ) ;

         } /* fim ativa: Testar excluir simbolo */

		 else if ( strcmp( ComandoTeste , IR_VERTICE_CMD ) == 0 )
		 {
			 numLidos = LER_LerParametros( "isi" ,
				 &inxGrafo , &CondRetEsp ) ;

			 if ( ( numLidos != 3 )
              || ( ! ValidarInxGrafo( inxGrafo , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

			pDado = ( char * ) malloc( strlen( StringDado ) + 1 ) ;
            if ( pDado == NULL )
            {
               return TST_CondRetMemoria ;
            } /* if */

            strcpy( pDado , StringDado ) ;

			CondRet = GRF_IrVertice ( vtGrafos[ inxGrafo ] , pDado );

			if ( CondRet != GRF_CondRetOK )
            {
               free( pDado ) ;
            } /* if */

            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao ir para o vertice"                   ) ;



		 } /* fim ativa: Testar Ir Vertice */
          
	
      return TST_CondRetNaoConhec ;

   } /* Fim função: TGRF &Testar lista */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: TGRF -Destruir valor
*
***********************************************************************/

   void DestruirValor( void * pValor )
   {

      free( pValor ) ;

   } /* Fim função: TGRF -Destruir valor */


/***********************************************************************
*
*  $FC Função: TGRF -Validar indice de grafo
*
***********************************************************************/

   int ValidarInxGrafo( int inxGrafo , int Modo )
   {

      if ( ( inxGrafo <  0 )
        || ( inxGrafo >= DIM_VT_GRAFO ))
      {
         return FALSE ;
      } /* if */
         
      if ( Modo == VAZIO )
      {
         if ( vtGrafos[ inxGrafo ] != 0 )
         {
            return FALSE ;
         } /* if */
      } else
      {
         if ( vtGrafos[ inxGrafo ] == 0 )
         {
            return FALSE ;
         } /* if */
      } /* if */
         
      return TRUE ;

   } /* Fim função: TGRF -Validar indice de grafo */

/********** Fim do módulo de implementação: TGRF Teste grafo de símbolos **********/

