#include <stdio.h>
#include <string.h>

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
    
    if (tipo_usuario < 0 || tipo_usuario > 2) {
      valido = 0;
      printf("Não é uma opção válida! Tente novamente.\n");
    } else {
      valido = 1;
    }

  } while (!valido);

  switch (tipo_usuario) {
    case 1:
      menu_cliente(void);
      break;
    case 2:
      menu_vendedor(void);
      break;
    case 0:
      printf("Saindo...\n");
      break;
  }
}

void cadastrar_cliente(void) {
  char nome[50];
  char senha [200];

  int opcao = 0;
  int valido = 0;

  do {
    printf("Realizar cadastro (1)\n");
    printf("Sair (0)\n");
    scanf("%d", &opcao);

    if (opcao < 0 || opcao > 1) {
      valido = 0;
      printf("Não é uma opção válida! Tente novamente.\n");
    } else {
      valido = 1;
    }
  } while (!valido);

  if (opcao == 1) {
    printf("Insira o seu nome: ");
    scanf("%s", nome);
    printf("Escolha uma senha: ");
    scanf("%s", senha);
  }

}

void login_vendedor(void) {
  int opcao = 0;
  int valido = 0;

  char senha[200];

  do {
    printf("Entrar como vendedor (1)\n");
    printf("Sair (0)\n");
    scanf("%d", &opcao);

    if (opcao == 1) {
      printf("Insira o código de verificação do vendedor (senha): ");
      scanf("%s", senha);

      if (strcmp(senha, "admin") == 0) {
        valido = 1;
      } else {
        valido = 0;
        printf("Senha incorreta! Tente novamente.\n");
      }
    }

    if (opcao < 0 || opcao > 1) {
      valido = 0;
      printf("Não é uma opção válida! Tente novamente.\n");
    } else {
      valido = 1;
    }

  } while (!valido);
}

void login_cliente(void) {
  int opcao = 0;
  int valido = 0;

  do {
    printf("Inserir informações de cadastro (1)\n");
    printf("Criar cadastro (2)\n");
    printf("Sair (0)\n");

    if (opcao == 1) {
      printf("Insira a sua senha: ");
      scanf("%s", senha);
      // TODO: Verificar se a senha está correta
      valido = 1;
    } else if (opcao == 2) {
      cadastrar_cliente(void);
      valido = 1;
    } else if (opcao == 0) {
      printf("Saindo...\n");
      valido = 1;
    } else {
      valido = 0;
      printf("Não é uma opção válida! Tente novamente.\n");
    }

    if (opcao < 0 || opcao > 2) {
      valido = 0;
      printf("Não é uma opção válida! Tente novamente.\n");
    } else {
      valido = 1;
    }

  } while (!valido);
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

      if (opcao < 0 || opcao > 9) {
        valido = 0;
        printf("Não é uma opção válida! Tente novamente.\n");
      } else {
        valido = 1;
      }

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

      if (opcao < 0 || opcao > 2) {
        valido = 0;
        printf("Não é uma opção válida! Tente novamente.\n");
      } else {
        valido = 1;
      }

    } while (!valido);
  }
}
int main(void) {

  menu_principal();

  return 0;

}
