#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#define LIMPAR_TELA() system("cls")
#else
#define LIMPAR_TELA() system("clear")
#endif

typedef enum {
    ESTADO_SAIR = 0,
    ESTADO_SPLASH,
    ESTADO_LOGIN,
    ESTADO_CADASTRO,
    ESTADO_MENU_PRINCIPAL,
    ESTADO_MAPA,
    ESTADO_DETALHES_ESTACAO,
    ESTADO_PLANEJAMENTO_ROTA,
    ESTADO_ROTA_CALCULADA,
    ESTADO_NAVEGACAO,
    ESTADO_ALERTAS,
    ESTADO_STATUS
} EstadoSistema;

void limpar_buffer();
int ler_opcao_segura();
void ler_texto(const char *mensagem, char *texto, int tamanho);
void exibir_cabecalho(const char *titulo_tela);
void pausar_sistema();

EstadoSistema processar_splash();
EstadoSistema processar_login();
EstadoSistema processar_cadastro();
EstadoSistema processar_menu_principal();
EstadoSistema processar_mapa();
EstadoSistema processar_detalhes_estacao();
EstadoSistema processar_planejamento_rota();
EstadoSistema processar_rota_calculada();
EstadoSistema processar_navegacao();
EstadoSistema processar_alertas();
EstadoSistema processar_status();

int usuario_cadastrado = 0;
int usuario_logado = 0;
char nome_usuario[100];

int main() {
    EstadoSistema estado_atual = ESTADO_SPLASH;

    while (estado_atual != ESTADO_SAIR) {
        switch (estado_atual) {
        case ESTADO_SPLASH:
            estado_atual = processar_splash();
            break;

        case ESTADO_LOGIN:
            estado_atual = processar_login();
            break;

        case ESTADO_CADASTRO:
            estado_atual = processar_cadastro();
            break;

        case ESTADO_MENU_PRINCIPAL:
            estado_atual = processar_menu_principal();
            break;

        case ESTADO_MAPA:
            estado_atual = processar_mapa();
            break;

        case ESTADO_DETALHES_ESTACAO:
            estado_atual = processar_detalhes_estacao();
            break;

        case ESTADO_PLANEJAMENTO_ROTA:
            estado_atual = processar_planejamento_rota();
            break;

        case ESTADO_ROTA_CALCULADA:
            estado_atual = processar_rota_calculada();
            break;

        case ESTADO_NAVEGACAO:
            estado_atual = processar_navegacao();
            break;

        case ESTADO_ALERTAS:
            estado_atual = processar_alertas();
            break;

        case ESTADO_STATUS:
            estado_atual = processar_status();
            break;

        default:
            printf("\nErro: Estado do sistema nao reconhecido. Retornando ao menu principal...\n");
            pausar_sistema();
            estado_atual = ESTADO_MENU_PRINCIPAL;
            break;
        }
    }

    LIMPAR_TELA();
    printf("====================================================\n");
    printf(" Obrigado por utilizar o Metro-DF!\n");
    printf(" Aplicativo encerrado com sucesso.\n");
    printf("====================================================\n");

    return 0;
}

void limpar_buffer() {
    int c;

    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

int ler_opcao_segura() {
    int opcao;
    int resultado = scanf("%d", &opcao);

    limpar_buffer();

    if (resultado != 1) {
        return -1;
    }

    return opcao;
}

void ler_texto(const char *mensagem, char *texto, int tamanho) {
    printf("%s", mensagem);

    if (fgets(texto, tamanho, stdin) != NULL) {
        texto[strcspn(texto, "\n")] = '\0';
    }
}

void exibir_cabecalho(const char *titulo_tela) {
    LIMPAR_TELA();

    printf("====================================================\n");
    printf("                 APLICATIVO METRO-DF                \n");
    printf("====================================================\n");
    printf(" Foco: %s\n", titulo_tela);
    printf("----------------------------------------------------\n");
}

void pausar_sistema() {
    printf("\nPressione [ENTER] para continuar...");
    getchar();
}

EstadoSistema processar_splash() {
    exibir_cabecalho("Inicializacao");

    printf("\nCarregando dados da malha do Metro-DF...\n");
    printf("Informacoes de linhas, estacoes e horarios carregadas.\n");

    pausar_sistema();

    return ESTADO_LOGIN;
}

EstadoSistema processar_login() {
    exibir_cabecalho("Login");

    printf(" 1 - Entrar\n");
    printf(" 2 - Criar conta\n");
    printf(" 0 - Sair da aplicacao\n");
    printf("----------------------------------------------------\n");
    printf("Escolha uma opcao: ");

    int opcao = ler_opcao_segura();

    switch (opcao) {
    case 1:
        if (!usuario_cadastrado) {
            printf("\nNenhum usuario cadastrado neste prototipo.\n");
            printf("Escolha a opcao 2 para criar uma conta.\n");
            pausar_sistema();
            return ESTADO_LOGIN;
        }

        usuario_logado = 1;
        printf("\nLogin realizado com sucesso, %s!\n", nome_usuario);
        pausar_sistema();
        return ESTADO_MENU_PRINCIPAL;

    case 2:
        return ESTADO_CADASTRO;

    case 0:
        return ESTADO_SAIR;

    default:
        printf("\nOpcao invalida!\n");
        pausar_sistema();
        return ESTADO_LOGIN;
    }
}

EstadoSistema processar_cadastro() {
    exibir_cabecalho("Cadastro de Usuario");

    ler_texto("Nome: ", nome_usuario, sizeof(nome_usuario));

    if (strlen(nome_usuario) == 0) {
        printf("\nO nome nao pode ficar vazio.\n");
        pausar_sistema();
        return ESTADO_CADASTRO;
    }

    usuario_cadastrado = 1;

    printf("\nCadastro realizado com sucesso!\n");
    printf("Usuario: %s\n", nome_usuario);

    pausar_sistema();

    return ESTADO_LOGIN;
}

EstadoSistema processar_menu_principal() {
    exibir_cabecalho("Tela Principal");

    printf(" Usuario: %s\n\n", nome_usuario);
    printf(" 1 - Exibir mapa das linhas\n");
    printf(" 2 - Pesquisar rota / Para onde vamos?\n");
    printf(" 3 - Consultar status das linhas\n");
    printf(" 4 - Configurar alertas\n");
    printf(" 5 - Consultar informacoes de estacoes\n");
    printf(" 6 - Notificacoes e avisos\n");
    printf(" 0 - Sair da aplicacao\n");
    printf("----------------------------------------------------\n");
    printf("Escolha uma opcao: ");

    int opcao = ler_opcao_segura();

    switch (opcao) {
    case 1:
        return ESTADO_MAPA;

    case 2:
        return ESTADO_PLANEJAMENTO_ROTA;

    case 3:
        return ESTADO_STATUS;

    case 4:
        return ESTADO_ALERTAS;

    case 5:
        return ESTADO_DETALHES_ESTACAO;

    case 6:
        return ESTADO_STATUS;

    case 0:
        return ESTADO_SAIR;

    default:
        printf("\nOpcao invalida!\n");
        pausar_sistema();
        return ESTADO_MENU_PRINCIPAL;
    }
}

EstadoSistema processar_mapa() {
    exibir_cabecalho("Mapa Geral");

    printf("LINHAS DO METRO-DF\n\n");
    printf(" 1 - Linha Verde\n");
    printf(" 2 - Linha Laranja\n");
    printf(" 3 - Ver detalhes de uma estacao\n");
    printf(" 9 - Voltar para a tela principal\n");
    printf("----------------------------------------------------\n");
    printf("Escolha uma opcao: ");

    int opcao = ler_opcao_segura();

    switch (opcao) {
    case 1:
        exibir_cabecalho("Linha Verde");
        printf("Linha Verde\n");
        printf("Consulte as estacoes e a situacao atual da linha.\n");
        printf("Status: Funcionamento normal.\n");
        pausar_sistema();
        return ESTADO_MAPA;

    case 2:
        exibir_cabecalho("Linha Laranja");
        printf("Linha Laranja\n");
        printf("Consulte as estacoes e a situacao atual da linha.\n");
        printf("Status: Funcionamento normal.\n");
        pausar_sistema();
        return ESTADO_MAPA;

    case 3:
        return ESTADO_DETALHES_ESTACAO;

    case 9:
        return ESTADO_MENU_PRINCIPAL;

    default:
        printf("\nOpcao invalida!\n");
        pausar_sistema();
        return ESTADO_MAPA;
    }
}

EstadoSistema processar_detalhes_estacao() {
    exibir_cabecalho("Detalhes da Estacao");

    printf(" 1 - Estacao Central\n");
    printf(" 2 - Estacao Ceilandia\n");
    printf(" 3 - Estacao Aguas Claras\n");
    printf(" 9 - Voltar\n");
    printf("----------------------------------------------------\n");
    printf("Escolha uma opcao: ");

    int opcao = ler_opcao_segura();

    switch (opcao) {
    case 1:
        exibir_cabecalho("Estacao Central");
        printf("Estacao: Central\n");
        printf("Status: Em funcionamento.\n");
        printf("Proximo trem: Informacao de demonstracao.\n");
        printf("Acessibilidade: Recursos disponiveis na estacao.\n");
        printf("Integracao: Consulte outros transportes disponiveis.\n");
        pausar_sistema();
        return ESTADO_DETALHES_ESTACAO;

    case 2:
        exibir_cabecalho("Estacao Ceilandia");
        printf("Estacao: Ceilandia\n");
        printf("Status: Em funcionamento.\n");
        printf("Proximo trem: Informacao de demonstracao.\n");
        printf("Acessibilidade: Recursos disponiveis na estacao.\n");
        printf("Integracao: Consulte outros transportes disponiveis.\n");
        pausar_sistema();
        return ESTADO_DETALHES_ESTACAO;

    case 3:
        exibir_cabecalho("Estacao Aguas Claras");
        printf("Estacao: Aguas Claras\n");
        printf("Status: Em funcionamento.\n");
        printf("Proximo trem: Informacao de demonstracao.\n");
        printf("Acessibilidade: Recursos disponiveis na estacao.\n");
        printf("Integracao: Consulte outros transportes disponiveis.\n");
        pausar_sistema();
        return ESTADO_DETALHES_ESTACAO;

    case 9:
        return ESTADO_MENU_PRINCIPAL;

    default:
        printf("\nOpcao invalida!\n");
        pausar_sistema();
        return ESTADO_DETALHES_ESTACAO;
    }
}

EstadoSistema processar_planejamento_rota() {
    char origem[100];
    char destino[100];

    exibir_cabecalho("Planejamento de Rota");

    ler_texto("Digite a estacao de origem: ", origem, sizeof(origem));

    if (strlen(origem) == 0) {
        printf("\nOrigem nao informada.\n");
        pausar_sistema();
        return ESTADO_PLANEJAMENTO_ROTA;
    }

    ler_texto("Digite a estacao de destino: ", destino, sizeof(destino));

    if (strlen(destino) == 0) {
        printf("\nDestino nao informado.\n");
        pausar_sistema();
        return ESTADO_PLANEJAMENTO_ROTA;
    }

    printf("\nOrigem: %s\n", origem);
    printf("Destino: %s\n", destino);
    printf("\n 1 - Validar e calcular trajeto\n");
    printf(" 9 - Cancelar busca / Voltar\n");
    printf("----------------------------------------------------\n");
    printf("Escolha uma opcao: ");

    int opcao = ler_opcao_segura();

    switch (opcao) {
    case 1:
        return ESTADO_ROTA_CALCULADA;

    case 9:
        return ESTADO_MENU_PRINCIPAL;

    default:
        printf("\nOpcao invalida!\n");
        pausar_sistema();
        return ESTADO_PLANEJAMENTO_ROTA;
    }
}

EstadoSistema processar_rota_calculada() {
    exibir_cabecalho("Rota Calculada");

    printf("TRAJETO CALCULADO\n\n");
    printf("Origem -> destino\n");
    printf("Melhor caminho encontrado entre as estacoes informadas.\n");
    printf("Verifique as linhas e as possiveis baldeacoes antes de iniciar.\n\n");

    printf(" 1 - Iniciar viagem\n");
    printf(" 9 - Voltar para planejamento de rota\n");
    printf("----------------------------------------------------\n");
    printf("Escolha uma opcao: ");

    int opcao = ler_opcao_segura();

    switch (opcao) {
    case 1:
        return ESTADO_NAVEGACAO;

    case 9:
        return ESTADO_PLANEJAMENTO_ROTA;

    default:
        printf("\nOpcao invalida!\n");
        pausar_sistema();
        return ESTADO_ROTA_CALCULADA;
    }
}

EstadoSistema processar_navegacao() {
    exibir_cabecalho("Navegacao Ativa");

    printf("VIAGEM EM ANDAMENTO\n\n");
    printf("Proxima parada: acompanhe o trajeto informado.\n");
    printf("Baldeacao confirmada: verifique a proxima linha.\n");
    printf("Proxima parada e o destino: prepare-se para desembarcar.\n\n");

    printf(" 1 - Alerta de transferencia\n");
    printf(" 2 - Alerta de desembarque\n");
    printf(" 3 - Destino alcancado\n");
    printf(" 9 - Cancelar viagem\n");
    printf("----------------------------------------------------\n");
    printf("Escolha uma opcao: ");

    int opcao = ler_opcao_segura();

    switch (opcao) {
    case 1:
        exibir_cabecalho("Alerta de Transferencia");
        printf("Atencao: prepare-se para realizar a baldeacao.\n");
        pausar_sistema();
        return ESTADO_NAVEGACAO;

    case 2:
        exibir_cabecalho("Alerta de Desembarque");
        printf("Atencao: proxima parada e o destino informado.\n");
        pausar_sistema();
        return ESTADO_NAVEGACAO;

    case 3:
        exibir_cabecalho("Destino Alcancado");
        printf("Viagem concluida com sucesso!\n");
        pausar_sistema();
        return ESTADO_MENU_PRINCIPAL;

    case 9:
        exibir_cabecalho("Viagem Cancelada");
        printf("A viagem foi cancelada pelo usuario.\n");
        pausar_sistema();
        return ESTADO_MENU_PRINCIPAL;

    default:
        printf("\nOpcao invalida!\n");
        pausar_sistema();
        return ESTADO_NAVEGACAO;
    }
}

EstadoSistema processar_alertas() {
    exibir_cabecalho("Alertas Personalizados");

    printf(" 1 - Ativar alerta de linha\n");
    printf(" 2 - Ativar alerta de estacao\n");
    printf(" 3 - Desativar alertas\n");
    printf(" 9 - Voltar para a tela principal\n");
    printf("----------------------------------------------------\n");
    printf("Escolha uma opcao: ");

    int opcao = ler_opcao_segura();

    switch (opcao) {
    case 1:
        printf("\nAlerta de linha configurado.\n");
        pausar_sistema();
        return ESTADO_ALERTAS;

    case 2:
        printf("\nAlerta de estacao configurado.\n");
        pausar_sistema();
        return ESTADO_ALERTAS;

    case 3:
        printf("\nAlertas desativados.\n");
        pausar_sistema();
        return ESTADO_ALERTAS;

    case 9:
        return ESTADO_MENU_PRINCIPAL;

    default:
        printf("\nOpcao invalida!\n");
        pausar_sistema();
        return ESTADO_ALERTAS;
    }
}

EstadoSistema processar_status() {
    exibir_cabecalho("Status e Notificacoes");

    printf("STATUS DAS LINHAS\n\n");
    printf("Linha Verde: Funcionamento normal.\n");
    printf("Linha Laranja: Funcionamento normal.\n");
    printf("\nAVISOS\n");
    printf("Nao ha alteracoes relevantes para apresentar neste prototipo.\n\n");

    printf(" 9 - Voltar para a tela principal\n");
    printf("----------------------------------------------------\n");
    printf("Escolha uma opcao: ");

    int opcao = ler_opcao_segura();

    switch (opcao) {
    case 9:
        return ESTADO_MENU_PRINCIPAL;

    default:
        printf("\nOpcao invalida!\n");
        pausar_sistema();
        return ESTADO_STATUS;
    }
}
