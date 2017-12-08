#if ! defined( PERFIL_ )
#define PERFIL_

/***************************************************************************
*
*  $MCD Módulo de definição: PRF  Perfil
*
*  Arquivo gerado:              PERFIL.h
*  Letras identificadoras:      PRF
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\PERFIL.BSW
*
*  Projeto: INF 1301 Implementação de um Grafo Genérico
*  Gestor:  INF 1301 PUC-Rio
*  Autores: gsa  ,tap
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*
*     1       tap  03/dez/2017  início desenvolvimento
*
*  $ED Descrição do módulo
*     Implementa um perfil utilizando o módulo grafo genérico
*     Podem existir n perfis em operação simultaneamente.
*     
*
*     O perfil é composto de quatro campos: email, nome, sobrenome e senha.
*     Sendo os quatro campos do struct strings de tamanho 51. 
*
*
*     
*
*     
*       
***************************************************************************/



#if defined( PERFIL_OWN )
   #define PERFIL_EXT
#else
   #define PERFIL_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para um perfil */

typedef struct PRF_tagPerfil * PRF_tppPerfil ;


/***********************************************************************
*
*  $TC Tipo de dados: PRF Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções do PERFIL
*
***********************************************************************/

   typedef enum {

         PRF_CondRetOK ,
               /* Concluiu corretamente */

		 PRF_CondRetGrafoNaoExiste ,
		       /* Não conseguiu efetuar ação, pois o grafo passado como parâmetro estava vazio */
			            
         PRF_CondRetNaoAchou ,
               /* Não encontrou o perfil procurado */

         PRF_CondRetFaltouMemoria ,
               /* Faltou memória ao tentar criar um perfil */

		 PRF_CondRetGrafoVazio 
		       /* O grafo recebido está vazio */

   } PRF_tpCondRet ;


      /***********************************************************************
*
*  $FC Função: PRF  &Criar perfil
*
*  $ED Descrição da função
*     Cria um perfil na rede de relacionamentos. O perfil criado
*     é uma estrutura composta por quatro campos, todos strings
*     O perfil é criado em um grafo, através da utilização do
*     módulo grafo genérico.
*     
*
*  $EP Parâmetros
*     pCab  		- ponteiro para a cabeça do grafo da rede de 
*					  relacionamentos onde o perfil será criado.
*
*     pEmail		- ponteiro para a string que contém o email
*					  do perfil que será criado.
*                     
*     pNome         - ponteiro para a string que contém o nome
*					  do perfil que será criado.
*
*     pSobrenome    - ponteiro para a string que contém o sobrenome
*					  do perfil que será criado.
*
*     pSenha        - ponteiro para a string que contém a senha
*					  do perfil que será criado.
*
*
*     ExcluirValor  - ponteiro para a função que processa a
*                     exclusão do valor referenciado pelo elemento
*                     a ser excluído.
*                     Ver descrição do módulo.
*
*  $FV Valor retornado
*     PRF_CondRetOK				  -se executou corretamente
*     PRF_CondRetGrafoNaoExiste   -se o grafo não existe 
*
***********************************************************************/

   PRF_tpCondRet PRF_CriarPerfil( GRF_tppGrafo pCab,
								   char * pEmail,
								   char * pNome,
								   char * pSobrenome,
								   char * pSenha,
								   void   ( * ExcluirValor ) ( void * pDado ) ) ;

    /***********************************************************************
*
*  $FC Função: PRF  &Obter email 
*
*  $ED Descrição da função
*     Obtém o email do perfil que está salvo no elemento corrente do grafo
*
*  $EP Parâmetros
*     pCab  		- ponteiro para a cabeça do grafo da rede de 
*					  relacionamentos onde o perfil será criado.
*
*     
*
*  $FV Valor retornado
*     NULL          - corrente não possui email, erro
*     !NULL         - endereço do email retornado
*
***********************************************************************/

   char * PRF_ObterEmailCorrente ( GRF_tppGrafo pCab ) ;


   
    /***********************************************************************
*
*  $FC Função: PRF  &Obter nome 
*
*  $ED Descrição da função
*     Obtém o nome do perfil que está salvo no elemento corrente do grafo
*
*  $EP Parâmetros
*     pCab  		- ponteiro para a cabeça do grafo da rede de 
*					  relacionamentos onde o perfil será criado.
*
*     
*
*  $FV Valor retornado
*     NULL          - corrente não possui nome, erro
*     !NULL         - endereço do nome retornado
*
***********************************************************************/

   char * PRF_ObterNomeCorrente ( GRF_tppGrafo pCab ) ;


       /***********************************************************************
*
*  $FC Função: PRF  &Obter sobrenome 
*
*  $ED Descrição da função
*     Obtém o sobrenome do perfil que está salvo no elemento corrente do grafo
*     Retorna um endereço para o sobrenome do perfil corrente.
*
*  $EP Parâmetros
*     pCab  		- ponteiro para a cabeça do grafo da rede de 
*					  relacionamentos onde o perfil será criado.
*
*     
*
*  $FV Valor retornado
*     NULL          - corrente não possui sobrenome, erro
*     pNaoNULL         - endereço do sobrenome retornado
*
***********************************************************************/

   char * PRF_ObterSobrenomeCorrente ( GRF_tppGrafo pCab ) ;


          /***********************************************************************
*
*  $FC Função: PRF  &Obter senha
*
*  $ED Descrição da função
*     Obtém a senha do perfil que está salva no elemento corrente do grafo
*     Retorna um endereço para o a senha do perfil corrente.
*
*  $EP Parâmetros
*     pCab  		- ponteiro para a cabeça do grafo da rede de 
*					  relacionamentos onde o perfil será criado.
*
*     
*
*  $FV Valor retornado
*     NULL          - corrente não possui sobrenome, erro
*     pNaoNULL         - endereço do sobrenome retornado
*
***********************************************************************/

   char * PRF_ObterSenhaCorrente ( GRF_tppGrafo pCab ) ;


    /***********************************************************************
*
*  $FC Função: PRF  &Compara perfil
*
*  $ED Descrição da função
*     Recebe dois endereços de perfil e compara o email salvo
*     em cada um deles. 
*
*  $EP Parâmetros
*     pDado1  		- ponteiro void para um perfil
*
*     
*
*  $FV Valor retornado
*     1         - perfis iguais
*     0         - perfis diferentes
*
***********************************************************************/

   int ComparaPerfil( void * pDado1, void * pDado2 ) ;

#undef PERFIL_EXT

   /********** Fim do módulo de definição: PRF  Perfil **********/

#else
#endif
