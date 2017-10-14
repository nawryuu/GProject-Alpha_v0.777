#if ! defined( GRAFO_ )
#define GRAFO_

/***************************************************************************
*
*  $MCD Módulo de definição: GRF  Grafo
*
*  Arquivo gerado:              GRAFO.h
*  Letras identificadoras:      GRF
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*    
*     1       avs   12/out/2017 início desenvolvimento
*
*  $ED Descrição do módulo
*     Implementa um grafo genérico.
*     Podem existir n grafos em operação simultaneamente.
*     Os grafos possuem uma cabeça encapsulando o seu estado.
*
*     O grafo é composto por uma lista de vértices, onde cada um aponta para o
*      vétice correspondente, e este aponta para uma lista com suas arestas.
*
*     Os vértices são ponteiros para listas.
*       
***************************************************************************/



#if defined( GRAFO_OWN )
   #define GRAFO_EXT
#else
   #define GRAFO_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para um grafo */

typedef struct GRF_tagGrafo * GRF_tppGrafo;

/***********************************************************************
*
*  $TC Tipo de dados: GRF Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções do grafo
*
***********************************************************************/

   typedef enum {

         GRF_CondRetOK ,
               /* Concluiu corretamente */

         GRF_CondRetGrafoVazio ,
               /* O grafo está vazio */
			            
         GRF_CondRetNaoAchou ,
               /* Não encontrou o vértice procurado */

         GRF_CondRetFaltouMemoria
               /* Faltou memória ao tentar criar um elemento do grafo */

   } GRF_tpCondRet ;

   #undef GRAFO_EXT

   #else
#endif
