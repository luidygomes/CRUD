#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>

#define MAX_PIZZAS 20
#define MAX_REFRI 10
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

typedef struct {
    char sabor[20];
    float valor350;
    float valor600;
    float valor2L;
}Refrigerante;

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

void BemVindo(){
    char BemVindo[50] = {"BEM - VINDO(A) AO CRUD'S PIZZARIA"};
    textBox(BemVindo);
}

void MensagemInicial() {
    system("clear");
    BemVindo();
    printf("\n");
    printf("                                        Carregando Dados...\n                                             🍕\n");
    sleep(1);
    system("clear");
    BemVindo();
    printf("\n");
    printf("                                        Carregando Dados...\n                                                🍕\n");
    printf("\n");
    sleep(1);
    system("clear");
    BemVindo();
    printf("\n");
    printf("                                        Carregando Dados...\n                                                  🍕\n");
    sleep(1);
}

void MensagemFinal() {
    char Texto[50] = {"ENCERRAMENTO DE PROGRAMA"};
    system("clear");
    textBox(Texto);
    printf("\n");
    printf("                                          Salvando Dados...\n                                             🍕\n");
    sleep(1);
    system("clear");
    textBox(Texto);
    printf("\n");
    printf("                                          Salvando Dados...\n                                                🍕\n");
    printf("\n");
    sleep(1);
    system("clear");
    textBox(Texto);
    printf("\n");
    printf("                                          Salvando Dados...\n                                                  🍕\n");
    sleep(1);
}

void CarregarDados(Pizza pizza[], int *qtd_pizza, Refrigerante refri[], int *qtd_refri) {
    FILE *f = fopen("cardapio.bin", "rb");
    MensagemInicial();
    if (f == NULL) {
        system("clear");
        BemVindo();
        printf("                       ❌ Arquivo não encontrado. Iniciando com cardápio vazio. ❌\n");
        printf("\n                        ");
        aguardarTecla();
        *qtd_pizza = 0;
        *qtd_refri = 0;
        return;
    }

    fread(qtd_pizza, sizeof(int), 1, f);
    fread(qtd_refri, sizeof(int), 1, f);

    fread(pizza, sizeof(Pizza), *qtd_pizza, f);
    fread(refri, sizeof(Refrigerante), *qtd_refri, f);

    fclose(f);
    printf("Dados carregados com sucesso!\n");
}

void SalvarDados(Pizza pizza[], int qtd_pizza, Refrigerante refri[], int qtd_refri) {
    FILE *f = fopen("cardapio.bin", "wb"); // Abre o arquivo para escrita binária

    if (f == NULL) {
        printf("Erro ao abrir o arquivo para salvar os dados.\n");
        return;
    }

    fwrite(&qtd_pizza, sizeof(int), 1, f);
    fwrite(&qtd_refri, sizeof(int), 1, f);

    for (int i = 0; i < qtd_pizza; i++) {
        fwrite(&pizza[i], sizeof(Pizza), 1, f);
    }

    for (int i = 0; i < qtd_refri; i++) {
        fwrite(&refri[i], sizeof(Refrigerante), 1, f);
    }

    fclose(f);
    printf("Dados salvos em formato binário com sucesso!\n");
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

void Menu(int selected) {
    system("clear");
    BemVindo();

    if (selected == 0)
        printf("                                    "ORANGE_BG"🖥️  CADASTRAR um novo produto 🍕" RESET "\n");
    else
        printf("                                       CADASTRAR um novo produto\n");

    if (selected == 1)
        printf("                                     "ORANGE_BG "🗒️  LISTAR todos os produtos 🍕" RESET "\n");
    else
        printf("                                        LISTAR todos os produtos\n");

    if (selected == 2)
        printf("                                    "ORANGE_BG "📝 DETALHAR um sabor de pizza 🍕" RESET "\n");
    else
        printf("                                       DETALHAR um sabor de pizza\n");

    if (selected == 3)
        printf("                                   "ORANGE_BG "🔁 ALTERAR um cadastro de pizza 🍕" RESET "\n");
    else
        printf("                                      ALTERAR um cadastro de pizza\n");

    if (selected == 4)
        printf("                                "ORANGE_BG "🔁 ALTERAR um cadastro de refrigerante 🥤" RESET "\n");
    else
        printf("                                  ALTERAR um cadastro de refrigerante\n");

    if (selected == 5)
        printf("                                    "ORANGE_BG "❌ REMOVER um sabor de pizza 🍕" RESET "\n");
    else
        printf("                                       REMOVER um sabor de pizza\n");

    if (selected == 6)
        printf("                                     "ORANGE_BG "❌ REMOVER um refrigerante 🥤" RESET "\n");
    else
        printf("                                       REMOVER um um refrigerante\n");

    if (selected == 7)
        printf("                                         "ORANGE_BG "🖨️  IMPRIMIR cardápio 🍕" RESET "\n");
    else
        printf("                                           IMPRIMIR cardápio\n");

    if (selected == 8)
        printf("                                               "ORANGE_BG "👋 SAIR 🍕" RESET "\n");
    else
        printf("                                                 SAIR\n");
}

void CadastroPizzas(char op1, Pizza pizza[], int *qtd, Refrigerante refri[], int *qtd_refri) {
    char TextoInicial[50] = {" CADASTRO DE PRODUTOS     "};
    char Sucesso[70] = {"   PRODUTO CADASTRADO COM SUCESSO!   "};
    int Escolha, tamanho;
    while (op1 == 's' || op1 == 'S') {
        textBox(TextoInicial);
        printf("                                  Escolha o que deseja cadastrar:\n");
        printf("                                       ");
        printf("1️⃣  Pizza\n");
        printf("                                       ");
        printf("2️⃣  Refrigerante");
        printf("\n                                       ➲  ");
        scanf("%d", &Escolha);
        while (Escolha < 1 || Escolha > 2) {
            system("clear");
            textBox(TextoInicial);
            printf("                              ");
            printf("Opção incorreta, insira um dos valores:\n");
            printf("                                       ");
            printf("1️⃣  Pizza\n");
            printf("                                       ");
            printf("2️⃣  Refrigerante");
            printf("\n                                       ➲  ");
            scanf("%d", &Escolha);
        }
        
        if(Escolha == 1){
            Pizza *novapizza = &pizza[*qtd];

            system("clear");
            textBox(TextoInicial);
            printf("                                     Digite o sabor da pizza:\n" "\n                                     ➲  ");
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
                char ingredienteTemp[100]; // Variável temporária para ler o ingrediente

                printf("                                       ➲ ");
                scanf(" %[^\n]", ingredienteTemp);

                // Verifica se o usuário quer parar
                if (strcmp(ingredienteTemp, "sair") == 0 || strcmp(ingredienteTemp, "SAIR") == 0) {
                    break; // Sai do loop se o usuário digitar "sair"
                }

                // Copia o ingrediente válido para a struct
                strcpy(novapizza->ingredientes[i], ingredienteTemp);
                novapizza->QtdIngredientes++; // Incrementa o contador de ingredientes
            }
            (*qtd)++;
        } else {
            Refrigerante *novorefri = &refri[*qtd_refri];

            system("clear");
            textBox(TextoInicial);
            printf("                                  Digite o sabor do refrigerante:\n" "\n                                     ➲  ");
            scanf(" %[^\n]", novorefri->sabor);
            system("clear");
            textBox(TextoInicial);
            printf("                       Digite o valor do refrigerante %s de lata (350ml): \n" "\n                                       ➲ R$  ", novorefri->sabor);
            scanf("%f", &novorefri->valor350);
            system("clear");
            textBox(TextoInicial);
            system("clear");
            textBox(TextoInicial);
            printf("                        Digite o valor do refrigerante %s de garrafa de 600ml: \n" "\n                                       ➲ R$  ", novorefri->sabor);
            scanf("%f", &novorefri->valor600);
            system("clear");
            textBox(TextoInicial);
            system("clear");
            textBox(TextoInicial);
            printf("                       Digite o valor do refrigerante %s de garrafa de 2 litros: \n" "\n                                       ➲ R$  ", novorefri->sabor);
            scanf("%f", &novorefri->valor2L);
            (*qtd_refri)++;
        }
        system("clear");
        textBox(Sucesso);
        printf("                          Deseja cadastrar outro produto? digite 's' ou 'n'\n""\n                                       ➲ ");
        scanf(" %c", &op1);
        if(op1 != 'n')
            return;
    }
    limparBuffer();
}

void ListarPizzas(int qtd, Pizza pizza[], int qtd_refri, Refrigerante refri[]) {
    char TextoInicial[50] = {"  CARDAPIO CRUD'S PIZZARIA      "};
    textBox(TextoInicial);
    if (qtd <= 0) {
        printf("\n                                Sem sabores de pizza registrados!\n");
    } else {
        printf("═══════════════════════════════════════════════════════════════════════════════════════════════════════\n");
        printf("                                             PIZZAS                          \n");
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
        printf("                                          REFRIGERANTES                          \n");
        printf("═══════════════════════════════════════════════════════════════════════════════════════════════════════\n");
        printf(ORANGE_TEXT"SABOR                           350ml                   600ml                        2L\n"RESET);
        printf("═══════════════════════════════════════════════════════════════════════════════════════════════════════\n");
        for (int i = 0; i < qtd_refri; i++) {
            printf("%-11s""┈┈┈┈┈┈┈┈┈┈┈┈┈", refri[i].sabor);
            printf("┈┈┈┈┈┈ R$%-7.2f" "┈┈┈┈┈┈┈┈┈┈┈┈┈", refri[i].valor350);
            printf("┈ R$%-7.2f" "┈┈┈┈┈┈┈┈┈┈┈┈┈", refri[i].valor600);
            printf("┈┈┈┈ R$%-7.2f", refri[i].valor2L);
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
                        char ingredienteTemp[100]; // Variável temporária para ler o ingrediente

                        printf("                                       ➲ ");
                        scanf(" %[^\n]", ingredienteTemp);

                        // Verifica se o usuário quer parar
                        if (strcmp(ingredienteTemp, "sair") == 0 || strcmp(ingredienteTemp, "SAIR") == 0) {
                            break; // Sai do loop se o usuário digitar "sair"
                        }

                        // Copia o ingrediente válido para a struct
                        strcpy(novapizza->ingredientes[i], ingredienteTemp);
                        novapizza->QtdIngredientes++; // Incrementa o contador de ingredientes
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

void AlterarRefri(int qtd_refri, Refrigerante refri[]){
    char TextoInicial[50] = {"   ALTERACAO DE REFRIGERANTE      "};

    textBox(TextoInicial);
    if (qtd_refri <= 0) {
        printf("                               ");
        printf("\nSem sabores de pizza registrados!\n");
        aguardarTecla();
        return;
    }

    char RefriEscolhido[20];
    int op, optam;
    int opcontinuar = 1;

    while (opcontinuar != 0) {
        system("clear");
        textBox(TextoInicial);
        int PosicaoRefri = -1;
        printf("                            ");
        printf("Qual nome do refrigerante que deseja alterar?");
        printf("\n                                         ➲  ");
        scanf(" %[^\n]", RefriEscolhido);

        for (int i = 0; i < qtd_refri; i++) {
            if (strcmp(RefriEscolhido, refri[i].sabor) == 0) {
                PosicaoRefri = i;
                break;
            }
        }

        if (PosicaoRefri == -1) {
            system("clear");
            textBox(TextoInicial);
            printf("                                ");
            printf("❌ Refrigerante não encontrado ❌\n");
        } else {
            system("clear");
            textBox(TextoInicial);
            Refrigerante *novorefri = &refri[PosicaoRefri];
            printf("                                     ");
            printf("O que deseja alterar?\n");
            printf("                                     ");
            printf("1️⃣  Nome\n");
            printf("                                     ");
            printf("2️⃣  Valor\n");
            printf("\n                                     ➲  ");
            scanf("%d", &op);
            while(op != 1 && op != 2) {
                system("clear");
                textBox(TextoInicial);
                printf("                              ");
                printf("Opção incorreta, insira um dos valores:\n");
                printf("                              ");
                printf("1️⃣  Nome\n");
                printf("                              ");
                printf("2️⃣  Valor");
                printf("\n                              ➲  ");
                scanf("%d", &op);
            }
            limparBuffer();
            switch (op) {
                case 1:
                    system("clear");
                    textBox(TextoInicial);
                    printf("                                ");
                    printf("Digite o novo sabor do refrigerante:");
                    printf("\n                                       ➲  ");
                    scanf(" %[^\n]", novorefri->sabor);
                    break;
                case 2:
                    system("clear");
                    textBox(TextoInicial);
                    printf("                              ");
                    printf("Qual tamanho você deseja alterar o valor?\n");
                    printf("                              ");
                    printf("1️⃣  Lata (350ml)\n");
                    printf("                              ");
                    printf("2️⃣  Garrafa de 600ml\n");
                    printf("                              ");
                    printf("3️⃣  Garrafa de 2L");
                    printf("\n                              ➲  ");
                    scanf("%d", &optam);
                    while(optam != 1 && optam != 2 && optam != 3) {
                        system("clear");
                        textBox(TextoInicial);
                        printf("                              ");
                        printf("Opção incorreta, insira um dos valores:\n");
                        printf("                              ");
                        printf("1️⃣  Lata (350ml)\n");
                        printf("                              ");
                        printf("2️⃣  Garrafa de 600ml\n");
                        printf("                              ");
                        printf("3️⃣  Garrafa de 2L");
                        printf("\n                              ➲  ");
                        scanf("%d", &optam);
                    }
                    limparBuffer();
                    switch (optam) {
                        case 1:
                            system("clear");
                            textBox(TextoInicial);
                            printf("                            ");
                            printf("Digite o novo valor da lata (350ml) de %s:", novorefri->sabor);
                            printf("\n                             ➲  ");
                            scanf("%f", &novorefri->valor350);
                            break;
                        case 2:
                            system("clear");
                            textBox(TextoInicial);
                            printf("                            ");
                            printf("Digite o novo valor da garrafa (600ml) de %s:", novorefri->sabor);
                            printf("\n                             ➲  ");
                            scanf("%f", &novorefri->valor600);
                            break;
                        case 3:
                            system("clear");
                            textBox(TextoInicial);
                            printf("                            ");
                            printf("Digite o novo valor da garrafa (2L) de %s:", novorefri->sabor);
                            printf("\n                             ➲  ");
                            scanf("%f", &novorefri->valor2L);
                            break;
                        default:
                            system("clear");
                            textBox(TextoInicial);
                            printf("                                  ");
                            printf("Tamanho incorreto.\n");
                            break;
                    }
                    break;
            }
        }
        printf("\n                  ");
        printf("Deseja alterar outro refrigerante? 0️⃣  para sair ou 1️⃣  para continuar");
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

void DeletarRefri(int *qtd_refri, Refrigerante refri[]) {
    char TextoInicial[50] = {"REMOVER REFRIGERANTE DO CARDAPIO"};
    system("clear");
    textBox(TextoInicial);
    if (*qtd_refri <= 0) {
        printf("                               ");
        printf("Sem sabores de refrigerantes registrados!\n");
        printf("                        ");
        aguardarTecla();
        return;
    }

    char RefriEscolhido[20];
    int PosicaoRefri = -1;

    printf("                                ");
    printf("Qual refrigerante gostaria de excluir?");
    printf("\n                                         ➲  ");
    scanf(" %[^\n]", RefriEscolhido);
    system("clear");
    for (int i = 0; i < *qtd_refri; i++) {
        if (strcmp(RefriEscolhido, refri[i].sabor) == 0) {
            PosicaoRefri = i;
            break;
        }
    }

    if (PosicaoRefri == -1) {
        system("clear");
        textBox(TextoInicial);
        printf("                                  ");
        printf("❌  Refrigerante não encontrado  ❌\n");
    } else {
        for (int i = PosicaoRefri; i < *qtd_refri - 1; i++) {
            refri[i] = refri[i + 1];
        }
        (*qtd_refri)--;
        system("clear");
        textBox(TextoInicial);
        printf("                             ");
        printf("✅  Refrigerante deletado com sucesso! ✅\n");
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
    Qtd_Ingredientes = pizza[PosicaoPizza].QtdIngredientes;
    if (Qtd_Ingredientes > 0)
        printf("%s", pizza[PosicaoPizza].ingredientes[0]);

    for (int i = 1; i < pizza[PosicaoPizza].QtdIngredientes; i++) {
        if (i > 0)
            printf(", ");
        printf("%s", pizza[PosicaoPizza].ingredientes[i]);
    }
    printf("\n═══════════════════════════════════════════════════════════════════════════════════════════════════════\n");
    printf("\n                       ");
    limparBuffer();
    aguardarTecla();
}

void ImprimirCardapio(int qtd, Pizza pizza[], int qtd_refri, Refrigerante refri[]) {
    FILE *f = fopen("CARDAPIO.txt", "w");
    char TextoInicial[50] = {"  IMPRESSAO DE CARDAPIO      "};
    textBox(TextoInicial);
    printf("                                    Criando arquivo de texto\n                                          🍕\n");
    sleep(1);
    system("clear");
    textBox(TextoInicial);
    printf("                                    Criando arquivo de texto\n                                             🍕\n");
    sleep(1);
    system("clear");
    textBox(TextoInicial);
    printf("                                    Criando arquivo de texto\n                                                 🍕\n");
    sleep(1);
    if (f == NULL) {
        printf("                             Erro ao criar arquivo de texto\n");
        aguardarTecla();
        return;
    }
    system("clear");
    textBox(TextoInicial);
    printf("                                Imprimindo cardápio no arquivo\n                                          🍕\n");
    sleep(1);
    system("clear");
    textBox(TextoInicial);
    printf("                                Imprimindo cardápio no arquivo\n                                             🍕\n");
    sleep(1);
    system("clear");
    textBox(TextoInicial);
    printf("                                Imprimindo cardápio no arquivo\n                                                 🍕\n");
    sleep(1);
    if (qtd <= 0) {
        printf("\n                              Sem sabores de pizza registrados!\n");
        printf("                      ");
        aguardarTecla();
        return;
    } else {
        fprintf(f,"╔═══════════════════════════════════════════════════════════════════════════╗\n");
        fprintf(f,"║                                 CARDAPIO CRUDS PIZZARIA                                               ║\n");
        fprintf(f,"╚═══════════════════════════════════════════════════════════════════════════╝\n");
        fprintf(f,"═════════════════════════════════════════════════════════════════════════════\n");
        fprintf(f,"                                           PIZZAS                          \n");
        fprintf(f,"═════════════════════════════════════════════════════════════════════════════\n");
        fprintf(f,"SABOR                           P                     M                        G\n");
        fprintf(f,"═════════════════════════════════════════════════════════════════════════════\n");
        for (int i = 0; i < qtd; i++) {
            fprintf(f,"%-11s""┈┈┈┈┈┈┈┈┈┈┈┈┈", pizza[i].sabor);
            fprintf(f,"┈┈┈┈┈┈ R$%-7.2f" "┈┈┈┈┈┈┈┈┈┈┈┈┈", pizza[i].valorP);
            fprintf(f,"┈ R$%-7.2f" "┈┈┈┈┈┈┈┈┈┈┈┈┈", pizza[i].valorM);
            fprintf(f,"┈┈┈┈ R$%-7.2f", pizza[i].valorG);
            fprintf(f,"\n");
        }
        fprintf(f,"═════════════════════════════════════════════════════════════════════════════\n");
        fprintf(f,"                                        REFRIGERANTES                          \n");
        fprintf(f,"═════════════════════════════════════════════════════════════════════════════\n");
        fprintf(f,"SABOR                         350ml                 600ml                      2L\n");
        fprintf(f,"═════════════════════════════════════════════════════════════════════════════\n");
        for (int i = 0; i < qtd_refri; i++) {
            fprintf(f,"%-11s""┈┈┈┈┈┈┈┈┈┈┈┈┈", refri[i].sabor);
            fprintf(f,"┈┈┈┈┈┈ R$%-7.2f" "┈┈┈┈┈┈┈┈┈┈┈┈┈", refri[i].valor350);
            fprintf(f,"┈ R$%-7.2f" "┈┈┈┈┈┈┈┈┈┈┈┈┈", refri[i].valor600);
            fprintf(f,"┈┈┈┈ R$%-7.2f", refri[i].valor2L);
            fprintf(f,"\n");
        }
        fprintf(f,"═════════════════════════════════════════════════════════════════════════════\n");
    }
    fclose(f);
    system("clear");
    textBox(TextoInicial);
    printf("                              ✅ Cardapio impresso com sucesso ✅\n                                          \n");
    printf("                      ");
    aguardarTecla();
}
    
void EncerramentoPrograma(){
    char TextoInicial[50] = {"ENCERRAMENTO DE PROGRAMA"};
    MensagemFinal();
    system("clear");
    textBox(TextoInicial);
    printf("\n                                          ");
    printf("🍕  Até logo! 👋\n");
    printf("\n                                 ");
    aguardarTeclaSaida();
    system("clear");
}    

void EscolhaOpcao(int opcao, char *PontOp1, Pizza pizzas[], int *Pontqtdpizzas, Refrigerante refris[], int *Pontqtdrefri) {
    switch (opcao) {
        case 1:
            system("clear");
            CadastroPizzas(*PontOp1, pizzas, Pontqtdpizzas, refris, Pontqtdrefri);
            break;
        case 2:
            system("clear");
            ListarPizzas(*Pontqtdpizzas, pizzas, *Pontqtdrefri, refris);
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
            AlterarRefri(*Pontqtdrefri, refris);
            break;    
        case 6:
            system("clear");
            DeletarPizza(Pontqtdpizzas, pizzas);
            break;
        case 7:
            system("clear");
            DeletarRefri(Pontqtdrefri, refris);
            break;
        case 8:
            system("clear");
            ImprimirCardapio(*Pontqtdpizzas, pizzas, *Pontqtdrefri, refris);
            break;
        default:
            break;
    }
}

int main() {
    int selected = 0, qtdpizzas = 3, qtdrefris = 1;
    char key, op1 = 's';
    Pizza cadastro[MAX_PIZZAS];
    Refrigerante cadastro_refri[MAX_REFRI];
    CarregarDados(cadastro, &qtdpizzas, cadastro_refri, &qtdrefris);
    while (selected != 9) {  
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
                        if (selected < 8) selected++;
                        break;
                }
            } else if (key == ENTER) {
                selected++;
                break;
            }
        }
        ativarBufferDeEntrada();
        EscolhaOpcao(selected, &op1, cadastro, &qtdpizzas, cadastro_refri, &qtdrefris);
    }
    SalvarDados(cadastro, qtdpizzas, cadastro_refri, qtdrefris);
    EncerramentoPrograma();
    return 0;
}