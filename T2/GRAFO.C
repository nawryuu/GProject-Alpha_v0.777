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
*  $TC Tipo de dados: GRF Elemento do Grafo
*
*
***********************************************************************/

 typedef struct tagElemGrafo {

         struct tagElemGrafo * pAresta ;
               /* Ponteiro para o elemento predecessor */

         struct tagElemLista * pVertice ;
               /* Ponteiro para o elemento sucessor */

   } tpElemGrafo ;
