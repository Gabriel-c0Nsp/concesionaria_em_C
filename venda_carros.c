#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estruturas 
typedef struct {
  char modelo[50];
  double preco;
} Carro;

// Variáveis globais relacionadas à venda de carros
Carro carros_encomendados[200];
int qtd_carros_encomendados = 0;

typedef struct {
  char nome[50];
  char senha[200];
} Cliente;

// Variáveis globais relacionadas aos clientes
Cliente clientes[200];
Cliente cliente_logado;
Cliente cliente_fila_espera[200]; // Clientes que reservaram um carro
int qtd_clientes_fila_espera = 0;
int cliente_logado_index;
int qtd_clientes = 0;

typedef struct {
  Carro carros_vendidos[200];
  char nome[50];
  char senha[200];
} Vendedor;

typedef struct {
  char nome_cliente[50];
  char modelo[50];
  double preco;
} Venda;

// Variáveis globais relacionadas às vendas
Venda vendas[200];
int qtd_vendas = 0;
double renda_total = 0;

typedef struct {
  Carro carros_estoque[200];
  int qtd_carros;
} Estoque;

// Variáveis globais relacionadas ao estoque
Estoque estoque;

// Funções
void limpa_tela(void);
void menu_principal(void);
void menu_cliente(void);
void menu_vendedor(void);
void cadastrar_cliente(void);
int verificar_dados(char nome[50], char senha[200]);
int login_vendedor(void);
void login_cliente(void);
void inserir_carro(Estoque *estoque, Carro carro);
void exibir_estoque(Estoque estoque);
void pesquisar_carro(Estoque estoque, char modelo[50]);
int excluir_carro(Estoque *estoque, char modelo[50]);
void alterar_carro(Estoque *estoque, char modelo[50]);
void exibir_clientes(void);
void excluir_cliente(void);
void alterar_cliente(void);
void realizar_venda(void);
void registrar_venda(Venda *venda);
void consultar_vendas(void);
void realizar_cadastro(void);

// Função principal
int main(void) {
  limpa_tela();

  menu_principal();

  return 0;
}

void menu_principal(void) {
  int tipo_usuario = 0;
  int valido = 0;

  do {
    printf("Insira o tipo de usuário: \n(1) Cliente \n(2) Vendedor \n(0) Sair\n");
    printf("\n-->  ");
    scanf("%d", &tipo_usuario);
    limpa_tela();
    
    if (tipo_usuario < 0 || tipo_usuario > 2) {
      valido = 0;
      printf("Não é uma opção válida! Tente novamente.\n");
    } else {
      valido = 1;
    }
  } while (!valido);

  switch (tipo_usuario) {
    case 1:
      login_cliente();
      break;
    case 2:
      menu_vendedor();
      break;
    case 0:
      printf("Saindo...\n");
      exit(0);
  }
}

void cadastrar_cliente(void) {
  int opcao = 0;
  int valido = 0;

  do {
    printf("Realizar cadastro (1)\n");
    printf("Voltar (0)\n");
    printf("\n-->  ");
    scanf("%d", &opcao);

    if (opcao < 0 || opcao > 1) {
      valido = 0;
      printf("Não é uma opção válida! Tente novamente.\n");
    } else {
      valido = 1;
    }
  } while (!valido);

  switch (opcao) {
    case 1:
      realizar_cadastro();
      menu_principal();
      break;
    case 0:
      limpa_tela();
      login_cliente();
      break;
  }
}

int verificar_dados(char nome[50], char senha[200]) {
  int achado = 0;

  for (int i = 0; i < qtd_clientes; i++) {
    if (strcmp(nome, clientes[i].nome) == 0 && strcasecmp(senha, clientes[i].senha) == 0) {
      achado = 1;

      strcpy(cliente_logado.nome, nome);
      strcpy(cliente_logado.senha, senha);
      cliente_logado_index = i;
      break;
    }
  }

  return achado;
}

int login_vendedor(void) {
  int opcao = 0;
  int valido = 0;

  char senha[200];

  do {
    printf("Entrar como vendedor (1)\n");
    printf("Sair (0)\n");
    printf("\n-->  ");
    scanf("%d", &opcao);
    limpa_tela();

    if (opcao < 0 || opcao > 1) {
      valido = 0;
      printf("Não é uma opção válida! Tente novamente.\n");
    } else if (opcao == 1) {
      printf("Insira o código de verificação do vendedor (senha): ");
      scanf("%s", senha);

      if (strcmp(senha, "admin") == 0) {
        valido = 1;
      } else {
        valido = 0;
        limpa_tela();
        printf("Senha incorreta! Tente novamente.\n");
      }
    } else if (opcao == 0) {
      printf("Saindo...\n");
      menu_principal();
    }
  } while (!valido);

  limpa_tela();
  return valido;
}

void login_cliente(void) {
  int opcao = 0;
  int valido = 0;

  char nome[50];
  char senha[200];

  do {
    printf("Inserir informações de cadastro (1)\n");
    printf("Criar cadastro (2)\n");
    printf("Sair (0)\n");
    printf("\n-->  ");
    scanf("%d", &opcao);

    if (opcao == 1) {
      printf("Insira o seu nome: ");
      scanf("%s", nome);
      printf("Insira a sua senha: ");
      scanf("%s", senha);
      if (verificar_dados(nome, senha)) {
        limpa_tela();
        printf("Login realizado com sucesso!\n\n");
        menu_cliente();
      } else {
        limpa_tela();
        printf("Senha incorreta! Tente novamente.\n");
        menu_principal();
      }
      valido = 1;
    } else if (opcao == 2) {
      cadastrar_cliente();
      valido = 1;
    } else if (opcao == 0) {
      printf("Saindo...\n");
      menu_principal();
    } else {
      printf("Não é uma opção válida! Tente novamente.\n");
      valido = 0;
    }
  } while (!valido);
}

void menu_vendedor(void) {
  int opcao = 0;
  int valido = 0;

  if (login_vendedor()) {
    do {
      printf("\n\n============ Referente ao estoque ============\n");
      printf("Inserir carro: (1)\n");
      printf("Buscar carro: (2)\n");
      printf("Alterar carro: (3)\n");
      printf("Exluir carro: (4)\n");
      printf("Exibir estoque: (5)\n");
      printf("Consultar vendas: (6)\n");
      printf("\n============ Referente aos clientes ============\n");
      printf("Excluir Cliente: (7)\n");
      printf("Exibir Clientes: (8)\n");
      printf("\n============ Sair ============\n");
      printf("Sair: (0)\n");
      printf("\n-->  ");
      scanf("%d", &opcao);

      if (opcao < 0 || opcao > 8) {
        valido = 0;
        printf("Não é uma opção válida! Tente novamente.\n");
      } else if (opcao == 0) {
        printf("Saindo...\n");
        menu_principal();
      } else if (opcao == 1) {
        Carro carro;

        printf("Insira o modelo do carro: ");
        scanf("%s", carro.modelo);
        printf("Insira o preço do carro: ");
        scanf("%lf", &carro.preco);
        limpa_tela();

        inserir_carro(&estoque, carro);
      } else if (opcao == 2) {
        char modelo[50];
        printf("Insira o modelo do carro: ");
        scanf("%s", modelo);

        pesquisar_carro(estoque, modelo);
      } else if (opcao == 3) {
        char modelo[50];

        printf("Insira o nome do modelo do carro que deseja alterar: ");
        scanf("%s", modelo);

        alterar_carro(&estoque, modelo);
      } else if (opcao == 4) {
        char modelo[50];

        printf("Insira o nome do modelo do carro que deseja excluir: ");
        scanf("%s", modelo);

        if (excluir_carro(&estoque, modelo)) {
          printf("Carro excluído com sucesso!\n");
        } else {
          printf("Carro não encontrado!\n");
        }

        excluir_carro(&estoque, modelo);
      } else if (opcao == 5) {
        exibir_estoque(estoque);
      } else if (opcao == 6) {
        consultar_vendas();
      } else if (opcao == 7) {
        excluir_cliente();
      } else if (opcao == 8) {
        exibir_clientes();
      } 

    } while (!valido);
  }
}

void menu_cliente(void) {
  int opcao = 0;
  int valido = 0;

  do {
    printf("Pesquisar carros: (1)\n");
    printf("Comprar carro: (2)\n");
    printf("Alterar informações do usuário: (3)\n");
    printf("Sair: (0)\n");
    printf("\n-->  ");
    scanf("%d", &opcao);

    if (opcao < 0 || opcao > 3) {
      valido = 0;
      printf("Não é uma opção válida! Tente novamente.\n");
    } else if (opcao == 1) {
      char modelo[50];

      printf("Insira o modelo do carro que deseja pesquisar: ");
      scanf("%s", modelo);

      pesquisar_carro(estoque, modelo);
      printf("\n\n");
    } else if (opcao == 2) {
      realizar_venda();
    } else if (opcao == 3) {
      alterar_cliente();
    } else if (opcao == 0) {
      printf("Saindo...\n");
      menu_principal();
    } else {
      valido = 1;
    }
  } while (!valido);
}

// Adiciona um carro no estoque
void inserir_carro(Estoque *estoque, Carro carro) {
  for (int i = 0; i < qtd_carros_encomendados; i++) {
    if (strcmp(carro.modelo, carros_encomendados[i].modelo) == 0) {
      for (int j = i; j < qtd_carros_encomendados; j++) {
        carros_encomendados[j] = carros_encomendados[j + 1];
      }
      printf("O carro %s estava na lista de encomendas. A venda foi realizada automaticamente!\n", carro.modelo);

      Venda venda;
      strcpy(venda.nome_cliente, cliente_fila_espera[i].nome);
      strcpy(venda.modelo, carro.modelo);
      venda.preco = carro.preco;

      registrar_venda(&venda);
      qtd_carros_encomendados--;
    } else {
      estoque -> carros_estoque[estoque -> qtd_carros] = carro;
      estoque -> qtd_carros++;

      printf("\nCarro inserido com sucesso!\n");
    }
  }
}

void exibir_estoque(Estoque estoque) {
  limpa_tela();

  int achado = 0;

  for (int i = 0; i < estoque.qtd_carros; i++) {
    printf("\nModelo: %s\n", estoque.carros_estoque[i].modelo);
    printf("Preço: R$%.2lf\n", estoque.carros_estoque[i].preco);

    achado = 1;
  }

  if (achado == 0) {
    printf("Não há carros no estoque\n");
  }
}

// Buscar carro
void pesquisar_carro(Estoque estoque, char modelo[50]) {
  limpa_tela();

  int achado = 0;

  for (int i = 0; i < estoque.qtd_carros; i++) {
    if (strcmp(modelo, estoque.carros_estoque[i].modelo) == 0) {
      printf("\nModelo: %s\n", estoque.carros_estoque[i].modelo);
      printf("Preço: %.2lf\n", estoque.carros_estoque[i].preco);

      achado = 1;
    }  
  }

  if (!achado) {
    printf("Carro não encontrado!\n");
  }
}

// Exclusão de carro por parte do vendedor
int excluir_carro(Estoque *estoque, char modelo[50]) {
  int achado = 0;

  for (int i = 0; i < estoque -> qtd_carros; i++) {
    if (strcmp(modelo, estoque -> carros_estoque[i].modelo) == 0) {
      for (int j = i; j < estoque -> qtd_carros; j++) {
        estoque -> carros_estoque[j] = estoque -> carros_estoque[j + 1];
      }
      estoque -> qtd_carros--;
      achado = 1;
    }
  }
  return achado;
}

void alterar_carro(Estoque *estoque, char modelo[50]) {
  int achado = 0;

  for (int i = 0; i < estoque -> qtd_carros; i++) {
    if (strcmp(modelo, estoque -> carros_estoque[i].modelo) == 0) {
      printf("Insira o novo modelo do carro: ");
      scanf("%s", estoque -> carros_estoque[i].modelo);
      printf("Insira o novo preço do carro: ");
      scanf("%lf", &estoque -> carros_estoque[i].preco);
      achado = 1;

      limpa_tela();
      printf("Carro alterado com sucesso!\n");
    }
  }

  if (!achado) {
    limpa_tela();
    printf("Carro não encontrado!\n");
  }
}

// Lista os clientes cadastrados
void exibir_clientes(void) {
  limpa_tela();

  printf("CLIENTES CADASTRADOS:\n");

  for (int i = 0; i < qtd_clientes; i++) {
    printf("Nome: %s\n", clientes[i].nome);
  } 
}

void excluir_cliente(void) {
  char nome[50];
  int achado = 0;

  printf("Insira o nome do cliente que deseja excluir: ");
  scanf("%s", nome);

  limpa_tela();

  for (int i = 0; i < qtd_clientes; i++) {
    if (strcmp(nome, clientes[i].nome) == 0) {
      for (int j = i; j < qtd_clientes; j++) {
        clientes[j] = clientes[j + 1];
      }
      qtd_clientes--;
      achado = 1;
    }
  }

  if (achado) {
    printf("Cliente excluído com sucesso!\n");
  } else {
    printf("Cliente não encontrado!\n");
  }
}

void alterar_cliente(void) {
  char nome[50];
  char senha[200];

  int valido = 0;

  printf("Insira o nome atual: ");
  scanf("%s", nome);
  printf("Insira a senha atual: ");
  scanf("%s", senha);

  limpa_tela();

  if (strcmp(nome, cliente_logado.nome) == 0 && strcmp(senha, cliente_logado.senha) == 0) {
    printf("Insira o novo nome: ");
    scanf("%s", cliente_logado.nome);
    printf("Insira a nova senha: ");
    scanf("%s", cliente_logado.senha);

    valido = 1;
  } else {
    limpa_tela();
    printf("Senha incorreta! Tente novamente.\n");
  }

  if (valido) {
    strcpy(clientes[cliente_logado_index].nome, cliente_logado.nome);
    strcpy(clientes[cliente_logado_index].senha, cliente_logado.senha);

    limpa_tela();
    printf("Informações alteradas com sucesso!\n");
  }
}

void realizar_venda(void) {
  char modelo[50];
  int achado = 0;
  int opcao = 0;
  int valido = 0;

  printf("Insira o modelo do carro que deseja comprar: ");
  scanf("%s", modelo);

  for (int i = 0; i < estoque.qtd_carros; i++) {
    if (strcmp(modelo, estoque.carros_estoque[i].modelo) == 0) {
      achado = 1;

      limpa_tela();
      printf("o carro %s está disponível por R$%.2lf\n", estoque.carros_estoque[i].modelo, estoque.carros_estoque[i].preco);
      printf("Deseja comprar? (1) Sim (0) Não\n");
      printf("\n-->  ");
      scanf("%d", &opcao);

      while (!valido) {
        if (opcao == 1) {
          limpa_tela();
          printf("Compra realizada com sucesso!\n\n");

          double preco = estoque.carros_estoque[i].preco;

          excluir_carro(&estoque, modelo);

          Venda venda;
          strcpy(venda.nome_cliente, cliente_logado.nome);
          strcpy(venda.modelo, modelo);
          venda.preco = preco; 

          registrar_venda(&venda);
          valido = 1;
          break;
        } else if (opcao == 0) {
          limpa_tela();
          printf("Compra cancelada!\n\n");
          valido = 1;
          break;
        } else {
          printf("Não é uma opção válida! Tente novamente.\n");
          printf("\n-->  ");
          scanf("%d", &opcao);
        }
      }
      break;
    }
  }

  if (achado == 0) {
    limpa_tela();
    printf("O carro %s não está disponível no momento\n", modelo);

    printf("Deseja encomendar? (1) Sim (0) Não\n");
    printf("\n-->  ");
    scanf("%d", &opcao);

    while (!valido) {
      if (opcao == 1) {
        limpa_tela();
        printf("Encomenda realizada com sucesso!\n\n");
        strcpy(carros_encomendados[qtd_carros_encomendados].modelo, modelo);
        qtd_carros_encomendados++;
        strcpy(cliente_fila_espera[qtd_clientes_fila_espera].nome, cliente_logado.nome);
        qtd_clientes_fila_espera++;

        valido = 1;
      } else if (opcao == 0) {
        limpa_tela();
        printf("Compra cancelada!\n");

        valido = 1;
      } else {
        printf("Não é uma opção válida! Tente novamente.\n");
        printf("\n-->  ");
        scanf("%d", &opcao);
      }
    }
  }
}

void registrar_venda(Venda *venda) {
  strcpy(vendas[qtd_vendas].nome_cliente, venda -> nome_cliente);
  strcpy(vendas[qtd_vendas].modelo, venda -> modelo);
  vendas[qtd_vendas].preco = venda -> preco;
  renda_total += venda -> preco; 
  qtd_vendas++; 
}

void consultar_vendas(void) {
  limpa_tela();

  printf("VENDAS REALIZADAS:\n");

  for (int i = 0; i < qtd_vendas; i++) {
    printf("\n------------------\n");
    printf("Nome do cliente: %s\n", vendas[i].nome_cliente);
    printf("Modelo do carro: %s\n", vendas[i].modelo);
    printf("Preço: R$%.2lf\n", vendas[i].preco);
    printf("------------------");
  }

  printf("\n\nTotal de vendas realizadas: %d\n", qtd_vendas);
  printf("Renda total: R$%.2lf\n", renda_total);
}

void realizar_cadastro(void) {
  char nome[50];
  char senha[200];

  printf("Insira o seu nome: ");
  scanf("%s", nome); 
  printf("Escolha uma senha: ");
  scanf("%s", senha);
  qtd_clientes++;

  // Armazena o novo cliente no array clientes
  strcpy(clientes[qtd_clientes - 1].nome, nome);
  strcpy(clientes[qtd_clientes - 1].senha, senha);

  limpa_tela();
  printf("Cadastro realizado com sucesso!\n\n");
}

// Função para limpar a tela independente do sistema operacional 
void limpa_tela(void) {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}
