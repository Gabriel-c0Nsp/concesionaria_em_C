#include <stdio.h>

// Estruturas 
typedef struct Carro {
  char modelo[50];
  double preco;
} Carro ;

typedef struct Cliente {
  char nome[50];
  char senha[100];
} Cliente;

typedef struct Vendedor {
  char nome[50];
  char senha[100];
} Vendedor;

typedef struct Estoque {
  struct Carro carros[200];
  int qtd_carros;
} Estoque;

// Funções
void menu_principal(void) {
  int tipo_usuario = 0;
  int valido = 0;

  do {
    printf("Insira o tipo de usuário [(1) Cliente, (2) Vendedor, (0) Sair]: ");
    scanf("%d", &tipo_usuario);
    
    if (tipo_usuario != 1 && tipo_usuario != 2 && tipo_usuario != 0) {
      valido = 0;
      printf("Não é uma opção válida! Tente novamente.\n");
    } else {
      valido = 1;
    }

  } while (!valido);

  switch (tipo_usuario) {
    case 1:
      menu_cliente();
      break;
    case 2:
      menu_vendedor();
      break;
    case 0:
      printf("Saindo...\n");
      break;
  }
}

void menu_vendedor(void) {
  int opcao = 0;
  int valido = 0;

  if (login_vendedor()) {
    do {
      printf("\n============ Referente ao estoque ============\n");
      printf("Inserir carro: (1)\n");
      printf("Buscar carro: (2)\n");
      printf("Alterar carro: (3)\n");
      printf("Exluir carro: (4)\n");
      printf("Exibir estoque: (5)\n");
      printf("Consultar vendas: (6)\n");
      printf("\n============ Referente aos clientes ============\n");
      printf("Alterar Cliente: (7)\n");
      printf("Excluir Cliente: (8)\n");
      printf("Exibir Clientes: (9)\n");
      printf("\n============ Sair ============\n");
      printf("Sair: (0)\n");
    } while (!valido);
  }
}

void menu_cliente(void) {
  int opcao = 0;
  int valido = 0;

  if (login_cliente()) {
    do {
      printf("Pesquisar carros: (1)\n");
      printf("Comprar carro: (2)\n");
      printf("Sair: (0)\n");
    } while (!valido);
  }
}
int main(void) {

  menu_principal();

  return 0;

}
