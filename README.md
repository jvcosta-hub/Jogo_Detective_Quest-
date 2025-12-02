# Jogo_Detective_Quest-

🕵️‍♂️ Detective Quest – Sistema de Investigação

Projeto em C que integra árvore binária, BST de pistas e tabela hash de suspeitos para criar um sistema interativo de exploração e dedução dentro de uma mansão misteriosa.

🚀 Funcionalidades

Navegação pela mansão usando uma árvore binária de cômodos.

Coleta automática de pistas ao entrar em cada sala.

Armazenamento das pistas em uma BST, ficando ordenadas alfabeticamente.

Associação pista → suspeito usando tabela hash.

Sistema final de acusação: o jogador indica um suspeito e o programa verifica se duas ou mais pistas o incriminam.

🧠 Estruturas Utilizadas

Árvore Binária: mapa da mansão.

BST: lista ordenada de pistas.

Hash Table: busca rápida de suspeitos relacionados às pistas.

🕹️ Fluxo do Jogo

Jogador começa no Hall de Entrada.

Explora salas escolhendo e (esquerda), d (direita) ou s (sair).

Cada sala pode fornecer uma pista.

Ao sair, todas as pistas coletadas são exibidas.

Jogador acusa um suspeito.

O sistema valida se há evidências suficientes.

▶️ Como Rodar
gcc detective_quest.c -o detective_quest
./detective_quest

🎯 Objetivo Educacional

Projeto voltado ao ensino de:

ponteiros e structs

árvores binárias

tabelas hash

lógica de decisão e recursividade
