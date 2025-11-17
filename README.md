# Sistema de Ponto de Venda - Projeto em C

---

## Equipe

* Amanda Cardoso Lopes
* Arthur Amaral Correia de Almeida
* Arthur de Carvalho Lima
* Mariana Assunção Soares Vieira
* Rafael Mota Freitas

---

## Descrição do Projeto

Este projeto implementa um sistema básico de Ponto de Venda (PDV) em Linguagem C. O objetivo é aplicar conceitos de modularidade, coesão, acoplamento e manipulação de `structs` para criar um programa de console interativo.

O sistema é dividido em três módulos principais: Cadastro de Clientes, Cadastro de Produtos e Efetuar Venda.

---

## Funcionalidades Implementadas

O programa segue as especificações detalhadas no exercício proposto.

### 1. Gestão de Clientes
* **Incluir Cliente:** Adiciona um novo cliente (código e nome). O sistema valida para não permitir códigos de cliente repetidos[cite: 152].
* **Excluir Cliente:** Remove um cliente pelo código, após solicitar confirmação.
* **Alterar Cliente:** Permite a modificação do nome de um cliente existente com base no seu código.

### 2. Gestão de Produtos
* **Incluir Produto:** Adiciona um novo produto (código, descrição e preço).
* **Excluir Produto:** Remove um produto pelo código, após confirmação.
* **Alterar Produto:** Permite a modificação da descrição e/ou preço de um produto existente.

### 3. Módulo de Venda
* **Efetuar Venda:** Inicia o processo de venda solicitando o código do cliente.
* **Adicionar Produtos:** Permite ao usuário inserir o código de múltiplos produtos. O sistema exibe uma mensagem de erro caso o produto seja inexistente.
* **Finalizar Venda:** Ao digitar `-1`, o sistema encerra a compra.
* **Exibir Recibo:** Após finalizar, o sistema exibe um resumo da venda contendo o nome do cliente, a lista de produtos (com descrição e preço unitário) e o valor total da compra.
