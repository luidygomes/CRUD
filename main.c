#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>

#define MAX_PIZZAS 10
#define MAX_INGREDIENTES 20
#define TAMANHO_INGREDIENTES 30
#define UP_ARROW 65
#define DOWN_ARROW 66
#define ENTER 10
#define GREEN_BG "\033[42m"
#define ORANGE_BG "\e[48;5;208m"
#define ORANGE_TEXT "\e[38;5;208m"
#define RESET "\033[0m"

typedef struct {
    char sabor[20];
    float valorP;
    float valorM;
    float valorG;
    char ingredientes[MAX_INGREDIENTES][TAMANHO_INGREDIENTES];
    int QtdIngredientes;
} Pizza;

void inicializarPizzas(Pizza pizza[]){
    strcpy(pizza[0].sabor, "Mussarela");
    pizza[0].valorP = 28;
    pizza[0].valorM = 36;
    pizza[0].valorG = 40;
    strcpy(pizza[0].ingredientes[0], "Molho");
    strcpy(pizza[0].ingredientes[1], "Mussarela");
    strcpy(pizza[0].ingredientes[2], "Tomate");
    strcpy(pizza[0].ingredientes[3], "Azeitona");
    strcpy(pizza[0].ingredientes[4], "Oregano");
    pizza[0].QtdIngredientes = 5;

    strcpy(pizza[1].sabor, "Portuguesa");
    pizza[1].valorP = 33;
    pizza[1].valorM = 40;
    pizza[1].valorG = 46;
    strcpy(pizza[1].ingredientes[0], "Molho");
    strcpy(pizza[1].ingredientes[1], "Mussarela");
    strcpy(pizza[1].ingredientes[2], "Presunto");
    strcpy(pizza[1].ingredientes[3], "Calabresa");
    strcpy(pizza[1].ingredientes[4], "Ovo");
    strcpy(pizza[1].ingredientes[5], "Cebola");
    strcpy(pizza[1].ingredientes[6], "Azeitona");
    strcpy(pizza[1].ingredientes[7], "Oregano");
    pizza[1].QtdIngredientes = 8;

    strcpy(pizza[2].sabor, "Frango");
    pizza[2].valorP = 33;
    pizza[2].valorM = 40;
    pizza[2].valorG = 46;
    strcpy(pizza[2].ingredientes[0], "Molho");
    strcpy(pizza[2].ingredientes[1], "Mussarela");
    strcpy(pizza[2].ingredientes[2], "Frango");
    strcpy(pizza[2].ingredientes[3], "Bacon");
    strcpy(pizza[2].ingredientes[4], "Milho");
    strcpy(pizza[2].ingredientes[5], "Tomate");
    strcpy(pizza[2].ingredientes[6], "Azeitona");
    strcpy(pizza[2].ingredientes[7], "Oregano");
    pizza[2].QtdIngredientes = 8;
}

void desativarBufferDeEntrada() {
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag &= ~(ICANON | ECHO); 
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

void ativarBufferDeEntrada() {
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag |= ICANON | ECHO; 
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void aguardarTecla() {
    struct termios oldt, newt;
    int ch;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    printf("Pressione qualquer tecla para voltar ao menu principal...\n");

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

void aguardarTeclaSaida() {
    struct termios oldt, newt;
    int ch;

    // Salvar as configurações atuais do terminal
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    // Desativar o modo canônico e a exibição de entrada (ECHO)
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    printf("Pressione qualquer tecla para sair...\n");

    // Capturar uma tecla
    ch = getchar();

    // Restaurar as configurações originais do terminal
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

void textBox(char frase[]) {
    int largura_caixa = 100;

    int len_frase = strlen(frase);
    
    int espacos_esquerda = (largura_caixa - len_frase) / 2;
    
    printf("╔");
    for (int i = 0; i < largura_caixa+1; i++) printf("═");
    printf("╗\n");

    printf("║");
    for (int i = 0; i < espacos_esquerda; i++) printf(" ");
    printf("\e[38;5;208m""%s", frase);
    for (int i = 0; i < largura_caixa - len_frase - espacos_esquerda; i++) printf(" ");
    printf(RESET" ║\n");

    printf("╚");
    for (int i = 0; i < largura_caixa+1; i++) printf("═");
    printf("╝\n");
}

void Menu(int selected) {
    system("clear");
    char BemVindo[50] = {"   BEM - VINDO(A) AO CRUD'S PIZZARIA"};

    textBox(BemVindo);

    if (selected == 0)
        printf("                                 "ORANGE_BG"🖥️  CADASTRAR um novo sabor de pizza 🍕" RESET "\n");
    else
        printf("                                    CADASTRAR um novo sabor de pizza\n");

    if (selected == 1)
        printf("                                "ORANGE_BG "🗒️  LISTAR todos os sabores de pizza 🍕" RESET "\n");
    else
        printf("                                    LISTAR todos os sabores de pizza\n");

    if (selected == 2)
        printf("                                    "ORANGE_BG "📝 DETALHAR um sabor de pizza 🍕" RESET "\n");
    else
        printf("                                       DETALHAR um sabor de pizza\n");

    if (selected == 3)
        printf("                                   "ORANGE_BG "🔁 ALTERAR um cadastro de pizza 🍕" RESET "\n");
    else
        printf("                                      ALTERAR um cadastro de pizza\n");

    if (selected == 4)
        printf("                                     "ORANGE_BG "❌ REMOVER um sabor de pizza 🍕" RESET "\n");
    else
        printf("                                        REMOVER um sabor de pizza\n");

    if (selected == 5)
        printf("                                               "ORANGE_BG "👋 SAIR 🍕" RESET "\n");
    else
        printf("                                                 SAIR\n");
}

void CadastroPizzas(char op1, Pizza pizza[], int *qtd) {
    char TextoInicial[50] = {" CADASTRO DE PIZZAS      "};
    char Sucesso[70] = {"    PIZZA CADASTRADA COM SUCESSO!   "};
    textBox(TextoInicial);
    while (op1 == 's' || op1 == 'S') {
        Pizza *novapizza = &pizza[*qtd];

        printf("                                    Digite o sabor da pizza:\n" "\n                                     ➲  ");
        scanf(" %[^\n]", novapizza->sabor);
        system("clear");
        textBox(TextoInicial);
        printf("                           Digite o valor da pizza pequena (P) de %s: \n" "\n                                       ➲ R$  ", novapizza->sabor);
        scanf("%f", &novapizza->valorP);
        system("clear");
        textBox(TextoInicial);
        printf("                           Digite o valor da pizza media (M) de %s: \n" "\n                                       ➲ R$  ", novapizza->sabor);
        scanf("%f", &novapizza->valorM);
        system("clear");
        textBox(TextoInicial);
        printf("                           Digite o valor da pizza grande (G) de %s: \n" "\n                                       ➲ R$  ", novapizza->sabor);
        scanf("%f", &novapizza->valorG);
        system("clear");
        textBox(TextoInicial);

        novapizza->QtdIngredientes = 0;
        printf("           Digite os ingredientes da pizza de %s um por um (para parar digite 'sair'): \n", novapizza->sabor);
        printf("\n");
        for (int i = 0; i < MAX_INGREDIENTES; i++) {
            printf("                                       ➲ ");
            scanf(" %[^\n]", novapizza->ingredientes[i]);
            if (strcmp(novapizza->ingredientes[i], "sair") == 0 || strcmp(novapizza->ingredientes[i], "SAIR") == 0) {
                break;
            }
            novapizza->QtdIngredientes++;
        }

        system("clear");
        textBox(Sucesso);

        (*qtd)++;

        printf("                         Deseja cadastrar outro sabor? digite 's' ou 'n'\n""\n                                       ➲ ");
        scanf(" %c", &op1);
        if(op1 != 's')
            break;
        system("clear");
        textBox(TextoInicial);
    }
    limparBuffer();
}

void ListarPizzas(int qtd, Pizza pizza[]) {
    char TextoInicial[50] = {"  CARDAPIO DE PIZZAS      "};
    textBox(TextoInicial);
    if (qtd <= 0) {
        printf("\n              Sem sabores de pizza registrados!\n");
    } else {
        printf("═══════════════════════════════════════════════════════════════════════════════════════════════════════\n");
        printf(ORANGE_TEXT"SABOR                             P                       M                          G\n"RESET);
        printf("═══════════════════════════════════════════════════════════════════════════════════════════════════════\n");

        for (int i = 0; i < qtd; i++) {
            printf("%-11s""┈┈┈┈┈┈┈┈┈┈┈┈┈", pizza[i].sabor);
            printf("┈┈┈┈┈┈ R$%-7.2f" "┈┈┈┈┈┈┈┈┈┈┈┈┈", pizza[i].valorP);
            printf("┈ R$%-7.2f" "┈┈┈┈┈┈┈┈┈┈┈┈┈", pizza[i].valorM);
            printf("┈┈┈┈ R$%-7.2f", pizza[i].valorG);
            printf("\n");
        }
        printf("═══════════════════════════════════════════════════════════════════════════════════════════════════════\n");
    }
    
    printf("\n                       ");
    aguardarTecla();
}

void AlterarPizza(int qtd_pizzas, Pizza pizza[]) {
    char TextoInicial[50] = {"  ALTERACAO DE PIZZA      "};

    textBox(TextoInicial);
    if (qtd_pizzas <= 0) {
        printf("                               ");
        printf("\nSem sabores de pizza registrados!\n");
        aguardarTecla();
        return;
    }

    char PizzaEscolhida[20];
    int op, optam;
    int opcontinuar = 1;

    while (opcontinuar != 0) {
        system("clear");
        textBox(TextoInicial);
        int PosicaoPizza = -1;
        printf("                               ");
        printf("Qual nome da pizza que deseja alterar?");
        printf("\n                                         ➲  ");
        scanf(" %[^\n]", PizzaEscolhida);

        for (int i = 0; i < qtd_pizzas; i++) {
            if (strcmp(PizzaEscolhida, pizza[i].sabor) == 0) {
                PosicaoPizza = i;
                break;
            }
        }

        if (PosicaoPizza == -1) {
            system("clear");
            textBox(TextoInicial);
            printf("                                    ");
            printf("❌ Pizza não encontrada ❌\n");
        } else {
            system("clear");
            textBox(TextoInicial);
            Pizza *novapizza = &pizza[PosicaoPizza];
            printf("                                       ");
            printf("O que deseja alterar?\n");
            printf("                                       ");
            printf("1️⃣  Sabor\n");
            printf("                                       ");
            printf("2️⃣  Valor\n");
            printf("                                       ");
            printf("3️⃣  Ingredientes");
            printf("\n                                       ➲  ");
            scanf("%d", &op);
            while(op != 1 && op != 2 && op != 3) {
                system("clear");
                textBox(TextoInicial);
                printf("                                  ");
                printf("Opção incorreta, insira um dos valores:\n");
                printf("                                          ");
                printf("1️⃣  Sabor\n");
                printf("                                          ");
                printf("2️⃣  Valor\n");
                printf("                                          ");
                printf("3️⃣  Ingredientes");
                printf("\n                                       ➲  ");
                scanf("%d", &op);
            }
            limparBuffer();
            switch (op) {
                case 1:
                    system("clear");
                    textBox(TextoInicial);
                    printf("                                   ");
                    printf("Digite o novo sabor da pizza:");
                    printf("\n                                       ➲  ");
                    scanf(" %[^\n]", novapizza->sabor);
                    break;
                case 2:
                    system("clear");
                    textBox(TextoInicial);
                    printf("                                ");
                    printf("Qual tamanho você deseja alterar o valor?\n");
                    printf("                                ");
                    printf("1️⃣  Pequena\n");
                    printf("                                ");
                    printf("2️⃣  Media\n");
                    printf("                                ");
                    printf("3️⃣  Grande");
                    printf("\n                                ➲  ");
                    scanf("%d", &optam);
                    while(optam != 1 && optam != 2 && optam != 3) {
                        system("clear");
                        textBox(TextoInicial);
                        printf("                                  ");
                        printf("Opção incorreta, insira um dos valores:\n");
                        printf("                                  ");
                        printf("1️⃣  Pequena\n");
                        printf("                                  ");
                        printf("2️⃣  Media\n");
                        printf("                                  ");
                        printf("3️⃣  Grande");
                        printf("\n                                  ➲  ");
                        scanf("%d", &optam);
                    }
                    limparBuffer();
                    switch (optam) {
                        case 1:
                            system("clear");
                            textBox(TextoInicial);
                            printf("                                  ");
                            printf("Digite o novo valor da pizza P de %s:", novapizza->sabor);
                            printf("\n                                  ➲  ");
                            scanf("%f", &novapizza->valorP);
                            break;
                        case 2:
                            system("clear");
                            textBox(TextoInicial);
                            printf("                                  ");
                            printf("Digite o novo valor da pizza M de %s:", novapizza->sabor);
                            printf("\n                                  ➲  ");
                            scanf("%f", &novapizza->valorM);
                            break;
                        case 3:
                            system("clear");
                            textBox(TextoInicial);
                            printf("                                  ");
                            printf("Digite o novo valor da pizza G de %s:", novapizza->sabor);
                            printf("\n                                  ➲  ");
                            scanf("%f", &novapizza->valorG);
                            break;
                        default:
                            system("clear");
                            textBox(TextoInicial);
                            printf("                                  ");
                            printf("Tamanho incorreto.\n");
                            break;
                    }
                    break;
                case 3:
                    system("clear");
                    textBox(TextoInicial);
                    printf("       ");
                    printf("Digite os novos ingredientes da pizza de %s um por um (para parar digite 'sair'): \n", novapizza->sabor);
                    novapizza->QtdIngredientes = 0;
                    for (int i = 0; i < MAX_INGREDIENTES; i++) {
                        printf("                                       ➲ ");
                        scanf(" %[^\n]", novapizza->ingredientes[i]);
                        if (strcmp(novapizza->ingredientes[i], "sair") == 0 || strcmp(novapizza->ingredientes[i], "SAIR") == 0 || strcmp(novapizza->ingredientes[i], "Sair") == 0) {
                            break;
                        }
                        novapizza->QtdIngredientes++;
                    }
                    break;
                default:
                    printf("Opção inválida.\n");
                    break;
            }
        }
        printf("\n                  ");
        printf("Deseja alterar outro sabor? 0️⃣  para sair ou 1️⃣  para continuar");
        printf("\n                                         ➲  ");
        scanf("%d", &opcontinuar);
        limparBuffer();
    }
}

void DeletarPizza(int *qtd_pizzas, Pizza pizza[]) {
    char TextoInicial[50] = {"REMOVER PIZZA DO CARDAPIO"};
    system("clear");
    textBox(TextoInicial);
    if (*qtd_pizzas <= 0) {
        printf("                               ");
        printf("\nSem sabores de pizza registrados!\n");
        aguardarTecla();
        return;
    }

    char PizzaEscolhida[20];
    int PosicaoPizza = -1;

    printf("                                ");
    printf("Qual nome da pizza gostaria de excluir?");
    printf("\n                                         ➲  ");
    scanf(" %[^\n]", PizzaEscolhida);
    system("clear");
    for (int i = 0; i < *qtd_pizzas; i++) {
        if (strcmp(PizzaEscolhida, pizza[i].sabor) == 0) {
            PosicaoPizza = i;
            break;
        }
    }

    if (PosicaoPizza == -1) {
        system("clear");
        textBox(TextoInicial);
        printf("                                    ");
        printf("❌  Pizza não encontrada  ❌\n");
    } else {
        for (int i = PosicaoPizza; i < *qtd_pizzas - 1; i++) {
            pizza[i] = pizza[i + 1];
        }
        (*qtd_pizzas)--;
        system("clear");
        textBox(TextoInicial);
        printf("                                 ");
        printf("✅  Pizza deletada com sucesso! ✅\n");
    }

    printf("\n                       ");
    limparBuffer();
    aguardarTecla();
}

void DetalharPizza(int qtd_pizzas, Pizza pizza[], int Qtd_Ingredientes) {
    char TextoInicial[50] = {"  DETALHAMENTO DE PIZZA      "};
    textBox(TextoInicial);
    if (qtd_pizzas <= 0) {
        printf("\nSem sabores de pizza registrados!\n");
        aguardarTecla();
        return;
    }

    char PizzaEscolhida[20];
    int PosicaoPizza = -1;

    printf("                                   Qual pizza deseja detalhar?\n""                                         ➲  ");
    scanf(" %[^\n]", PizzaEscolhida);
    system("clear");
    textBox(TextoInicial);

    for (int i = 0; i < qtd_pizzas; i++) {
        if (strcmp(PizzaEscolhida, pizza[i].sabor) == 0) {
            PosicaoPizza = i;
            break;
        }
    }

    if (PosicaoPizza == -1) {
        system("clear");
        textBox(TextoInicial);
        printf("                                    ❌ Pizza não encontrada ❌\n");
        printf("\n                       ");
        limparBuffer();
        aguardarTecla();
        return;
    }

    printf("═══════════════════════════════════════════════════════════════════════════════════════════════════════\n");
    printf(ORANGE_TEXT"SABOR                             P                       M                          G\n"RESET);
    printf("═══════════════════════════════════════════════════════════════════════════════════════════════════════\n");
    printf("%-11s""┈┈┈┈┈┈┈┈┈┈┈┈┈", pizza[PosicaoPizza].sabor);
    printf("┈┈┈┈┈┈ R$%-7.2f" "┈┈┈┈┈┈┈┈┈┈┈┈┈", pizza[PosicaoPizza].valorP);
    printf("┈ R$%-7.2f" "┈┈┈┈┈┈┈┈┈┈┈┈┈", pizza[PosicaoPizza].valorM);
    printf("┈┈┈┈ R$%-7.2f", pizza[PosicaoPizza].valorG);
    printf("\n");
    printf("═══════════════════════════════════════════════════════════════════════════════════════════════════════\n");
    printf(ORANGE_TEXT"                                         INGREDIENTES \n"RESET);
    printf("═══════════════════════════════════════════════════════════════════════════════════════════════════════\n");

    printf("%s", pizza[PosicaoPizza].ingredientes[0]);

    for (int i = 1; i < pizza[PosicaoPizza].QtdIngredientes; i++) {
        if (i > 0) {
            printf(", ");
        }
        printf("%s", pizza[PosicaoPizza].ingredientes[i]);
    }
    printf("\n═══════════════════════════════════════════════════════════════════════════════════════════════════════\n");
    printf("\n                       ");
    limparBuffer();
    aguardarTecla();
}

void EscolhaOpcao(int opcao, char *PontOp1, Pizza pizzas[], int *Pontqtdpizzas) {
    switch (opcao) {
        case 1:
            system("clear");
            CadastroPizzas(*PontOp1, pizzas, Pontqtdpizzas);
            break;
        case 2:
            system("clear");
            ListarPizzas(*Pontqtdpizzas, pizzas);
            break;
        case 3:
            system("clear");
            DetalharPizza(*Pontqtdpizzas, pizzas, 0);
            break;
        case 4:
            system("clear");
            AlterarPizza(*Pontqtdpizzas, pizzas);
            break;
        case 5:
            system("clear");
            DeletarPizza(Pontqtdpizzas, pizzas);
            break;
        default:
            break;
    }
}

int main() {
    int selected = 0;
    char key;
    int qtdpizzas = 3;
    char op1 = 's';
    Pizza cadastro[MAX_PIZZAS];
    inicializarPizzas(cadastro);
    while (selected != 6) {  
        selected = 0;
        desativarBufferDeEntrada(); 
        while (1) {
            Menu(selected);

            key = getchar();
            if (key == '\e') {  
                getchar();
                switch (getchar()) {
                    case UP_ARROW:
                        if (selected > 0) selected--;
                        break;
                    case DOWN_ARROW:
                        if (selected < 5) selected++;
                        break;
                }
            } else if (key == ENTER) {
                selected++;
                break;
            }
        }
        ativarBufferDeEntrada();
        EscolhaOpcao(selected, &op1, cadastro, &qtdpizzas);
    }
    char TextoInicial[50] = {"ENCERRAMENTO DE PROGRAMA"};
    system("clear");
    textBox(TextoInicial);
    printf("\n                                          ");
    printf("🍕  Até logo! 👋\n");
    printf("\n                                 ");
    aguardarTeclaSaida();
    system("clear");
    return 0;
}