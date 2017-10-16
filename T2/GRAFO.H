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
*  Autores: gsa  ,tap
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     5       tap  16/out/2017  Finalização
*     4       tap  14/out/2017  DestruirAresta
*     3       tap  14/out/2017  CriarGrafo 
*     2       tap  14/out/2017  tipo enumerado+descrições+correções  
*     1            12/out/2017  início desenvolvimento
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

         GRF_CondRetFaltouMemoria,
               /* Faltou memória ao tentar criar um elemento do grafo */
		 GRF_CondRetValorRepetido,
		      /* Houve uma tentativa de inserção de um valor repetido */
		 GRF_CondRetGrafoNaoExiste

   } GRF_tpCondRet ;


   /***********************************************************************
*
*  $FC Função: GRF  &Criar grafo
*
*  $ED Descrição da função
*     Cria um grafo genérico.     
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


	 /***********************************************************************
*
*  $FC Função: GRF  &Destruir aresta
*
*  $ED Descrição da função
*     Destroi uma aresta do grafo.   
*     
*  $EP Parâmetros
*     pCab       -ponteiro para uma cabeça de grafo
*     pValor     -endereço da aresta que será do removida do nó corrente 
*
*  $FV Valor retornado
*     GRF_CondRetOK   -Se executou corretamente
*     GRF_CondRetGrafoVazio   -se o grafo estiver vazio 
*     GRF_CondRetGrafoNaoExiste   -se o grafo não existe  
*
***********************************************************************/

    GRF_tpCondRet GRF_DestruirAresta( GRF_tppGrafo pCab, void * pValor);


	/***********************************************************************
*
*  $FC Função: GRF  &Destruir vértice corrente
*
*  $ED Descrição da função
*     Destroi o vértice corrente do grafo 
*     
*  $EP Parâmetros
*     pCab       -ponteiro para uma cabeça de grafo
*     pValor     -endereço da aresta que será do removida do nó corrente 
*
*  $FV Valor retornado
*     GRF_CondRetOK   -Se executou corretamente
*     GRF_CondRetGrafoNaoExiste   -se o grafo não existe  
*
***********************************************************************/

   GRF_tpCondRet GRF_DestruirVerticeCorrente( GRF_tppGrafo pCab );


   /***********************************************************************
*
*  $FC Função: GRF  &Destruir Grafo
*
*  $ED Descrição da função
*     Destroi o grafo
*     
*  $EP Parâmetros
*     pCab       -ponteiro para uma cabeça de grafo
*     *
*  $FV Valor retornado
*     GRF_CondRetOK   -Se executou corretamente
*     GRF_CondRetGrafoVazio   -se o grafo estiver vazio 
*     GRF_CondRetGrafoNaoExiste   -se o grafo não existe 
*
***********************************************************************/  

   GRF_tpCondRet GRF_DestruirGrafo( GRF_tppGrafo pCab );


   /***********************************************************************
*
*  $FC Função: GRF  &Ir Vertice
*
*  $ED Descrição da função
*     Atualiza o elemento corrente do grafo com aquele cujo valor void 
*     é igual ao valor passado como parâmetro
*     
*  $EP Parâmetros
*     pCab		    - ponteiro para uma cabeça de grafo
*     pValor        - ponteiro void para um valor
*   *     
*  $FV Valor retornado
*     GRF_CondRetOK   -Se executou corretamente
*     GRF_CondRetGrafoVazio   -se o grafo estiver vazio 
*     GRF_CondRetGrafoNaoExiste   -se o grafo não existe 
*
***********************************************************************/   

   GRF_tpCondRet IrVertice ( GRF_tpGrafo * pCab, void * pValor );


      /***********************************************************************
*
*  $FC Função: GRF  &Criar Vertice
*
*  $ED Descrição da função
*     Cria um vértice do grafo
*     
*  $EP Parâmetros
*     pCab		    - ponteiro para uma cabeça de grafo
*     pValor        - ponteiro void para um valor
*     ExcluirValor  - ponteiro para a função que processa a
*                     exclusão do valor referenciado pelo elemento
*                     a ser excluído.
*                     Ver descrição do módulo.
*       
*  $FV Valor retornado
*     GRF_CondRetOK   -Se executou corretamente
*     GRF_CondRetGrafoVazio   -se o grafo estiver vazio 
*     GRF_CondRetGrafoNaoExiste   -se o grafo não existe 
*
***********************************************************************/ 

   GRF_tpCondRet GRF_CriarVertice( GRF_tppGrafo pCab, void * pValor,  void   ( * ExcluirValor ) ( void * pDado ));


     /***********************************************************************
*
*  $FC Função: GRF  &Criar Aresta
*
*  $ED Descrição da função
*     Cria uma aresta no grafo
*     
*  $EP Parâmetros
*     pCab		    - ponteiro para uma cabeça de grafo
*     pValor        - ponteiro void para um valor
*    
*  $FV Valor retornado
*     GRF_CondRetOK   -Se executou corretamente
*     GRF_CondRetValorRepetido   -se já existir uma aresta cujo valor seja o mesmo que o do parâmetro pValor     
*     GRF_CondRetGrafoVazio   -se o grafo estiver vazio 
*     GRF_CondRetGrafoNaoExiste   -se o grafo não existe 
*
***********************************************************************/ 

   GRF_tpCondRet GRF_CriarAresta ( GRF_tppGrafo pCab, void * pValor );


    /***********************************************************************
*
*  $FC Função: GRF  &Obter Corrente
*
*  $ED Descrição da função
*     Função que retorna o endereço do elemento corrente do grafo.
*     
*  $EP Parâmetros
*     pCab		    - ponteiro para uma cabeça de grafo
*    
*  $FV Valor retornado
*     Retorna o endereço do elemento corrente do grafo.
*
***********************************************************************/ 
   void * GRF_ObterCorrente( GRF_tppGrafo pCab );


#undef GRAFO_EXT

#else
#endif
