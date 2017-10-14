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
*  Projeto: INF 1301 Implementação de um Grafo Genérico
*  Gestor:  INF 1301 PUC-Rio
*  Autores: g  ,tap
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     3       tap  14/out/2017 CriarGrafo 
*     2       tap  14/out/2017 tipo enumerado+descrições+correções  
*     1            12/out/2017 início desenvolvimento
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

typedef struct GRF_tagGrafo * GRF_tppGrafo ;

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


   /***********************************************************************
*
*  $FC Função: GRF  &Criar grafo
*
*  $ED Descrição da função
*     Cria um grafo genérico.*     
*     Não existe identificador de tipo associado ao grafo.
*
*  $EP Parâmetros
*     ExcluirValor  - ponteiro para a função que processa a
*                     exclusão do valor referenciado pelo elemento
*                     a ser excluído.
*                     Ver descrição do módulo.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para o grafo.
*     Este ponteiro será utilizado pelas funções que manipulem este grafo.
*
*     Se ocorreu algum erro, por exemplo falta de memória ou dados errados,
*     a função retornará NULL.     
*
***********************************************************************/
    GRF_tppGrafo GRF_CriarGrafo(
             void   ( * ExcluirValor ) ( void * pDado ) );


#undef GRAFO_EXT

#else
#endif
