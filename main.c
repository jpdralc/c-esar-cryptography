#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 100

/*
    Função para criptografar usando a cifra de César,
    na qual o deslocamento (N) varia de 1 a 26 sendo limitado pelo uso do módulo 26.
*/

void criptografar(char *str, int n) {
    int i;
    /* Percorrendo a string até o terminador '\0' */
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] != ' ') { /* Mantém espaços inalterados */
            str[i] = 'a' + (str[i] - 'a' + n + 26) % 26;
        }
    }
}

void descriptografar(char *str, int n) {	
    int i;
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] != ' ') {
            /* Ao invés de somar, subtrai o N para descriptografar */
            str[i] = 'a' + (str[i] - 'a' - n + 26) % 26;
        }
    }
}

/*Função para converter string para minúsculas */
void toLowerCase(char *str) {
	int i;
    for (i = 0; str[i] != '\0'; i++) {
        str[i] = tolower(str[i]);
    }
}

/* Função para salvar a string em um arquivo */
void salvarArquivo(const char *nomeArquivo, const char *texto) {
    FILE *file = fopen(nomeArquivo, "w");
    if (file == NULL) {
        printf("Erro ao salvar o arquivo.\n");
        return;
    }
    fprintf(file, "%s", texto);
    fclose(file);
}

/* Função para carregar a string de um arquivo */
void carregarArquivo(const char *nomeArquivo, char *texto) {
    FILE *file = fopen(nomeArquivo, "r");
    if (file == NULL) {
        printf("Erro ao ler o arquivo.\n");
        return;
    }
    fgets(texto, MAX_LEN, file);
    fclose(file);
}

/* Gera uma mensagem randômica */
void mensagemAleatoria(const char *mensagens[], int tamanho) {
    printf("\n\n%s\n", mensagens[rand() % tamanho]);
}

int entradaVazia(const char *str) {
    while (*str) {
        if (!isspace(*str)) return 0;
        str++;
    }
    return 1;
}

int main() {
    
    char frase[MAX_LEN], entrada[MAX_LEN];
    int i, n, opcao, error;
    const char *arquivo = "mensagem.txt";
    
    const char *errosN[] = {
        "Ops... acho que voce errou! Escolha um numero de 1 a 26.",
        "Hmm... isso nao parece um numero valido! Tente de novo.",
        "Opa! Entre 1 e 26, por favor!" 
    };
    
    const char *errosEntrada[] = {
        "Eh... parece que isso nao eh um numero entre 1 e 4",
        "Hmm... nao, isso nao eh um numero entre 1 e 4...",
        "Opa! Entre 1 e 4, por favor!",
		"Nos sabemos que este numero nao está entre 1 e 4..." 
    };
    
    const char *errosLetra[] = {
        "Isso nem eh um numero!",
        "Hmm... que numero eh esse? Nao me parece 1 nem 2 nem 3 nem 4...",
        "Acho que estamos nos desentendendo, isso eh uma letra." 
    };
    
    

    do {
        printf("\n--- Jogo da Imitacao Textual ---\n\n");
        printf("1 - Digitar nova frase e criptografar\n");
        printf("2 - Descriptografar a frase salva\n");
        printf("3 - Descriptografar frase livre\n");
        printf("4 - Sair\n");
        printf("\n\nEscolha uma opcao: ");
		
        /* Captura a entrada como string para evitar problemas */
        if (fgets(entrada, sizeof(entrada), stdin) == NULL) {
            printf("Erro ao ler entrada.\n");
            continue;
        }

        /* Remove o '\n' do final */
        entrada[strcspn(entrada, "\n")] = '\0';

        /* Verifica se a entrada contém apenas espaços */
        int apenasEspaco = 1;
        for (i = 0; entrada[i] != '\0'; i++) {
            if (!isspace(entrada[i])) {
                apenasEspaco = 0;
                break;
            }
        }

        if (apenasEspaco) {
            printf("\n\nEspaco? Nao, essa nao eh uma das opcoes...\n");
            continue;
        }
        
        /* Verifica se há alguma letra na entrada */
        int contemLetra = 0;
        for (i = 0; entrada[i] != '\0'; i++) {
            if (isalpha(entrada[i])) {
                contemLetra = 1;
                break;
            }
        }

        if (contemLetra) {
            mensagemAleatoria(errosLetra, 3);
            continue;
        }

        /* Converte a entrada para número */
        if (sscanf(entrada, "%d", &opcao) != 1) {
            mensagemAleatoria(errosEntrada, 3);
            continue;
        }

        error = 0;
        
        switch (opcao) {
            case 1:
            	do {
                	printf("Digite a frase (max %d caracteres): ", MAX_LEN);
                	fgets(frase, MAX_LEN, stdin); /* Recuperando entrada do usuário de forma segura */
                	frase[strcspn(frase, "\n")] = '\0'; /* Remover o '\n' do final */
                	if (entradaVazia(frase)) {
                        printf("Vazio nao pode.\n");
                    }
                } while (entradaVazia(frase));
                
                /* Validação da string */
			    for (i = 0; frase[i] != '\0'; i++) {
			        if (!isalpha(frase[i]) && frase[i] != ' ') {
			            error = 1;
			            break;
			        }
			    }
			    
			     if (error) {
			        printf("Caracteres invalidos detectados! Use apenas letras (nao acentuadas) e espacos.\n");
			        break; /* Volta ao menu sem processar */
			    }
			                
				toLowerCase(frase);                 

                do {
                    printf("Escolha um numero N (1 a 26): ");
                    if (scanf("%d", &n) != 1 || n < 1 || n > 26) {
                        mensagemAleatoria(errosN, 3);
                        while (getchar() != '\n'); /* Limpa o buffer de entrada */
                        continue;
                    }
                    break;
                } while (1);
                getchar();
                
                criptografar(frase, n);
                printf("Texto criptografado: %s\n", frase);
                
                salvarArquivo(arquivo, frase);
                printf("Frase salva no arquivo.\n");                
                break;

            case 2:
                carregarArquivo(arquivo, frase);
                printf("Texto criptografado carregado: %s\n", frase);
                
                do {
                    printf("Escolha o valor de N usado para criptografar (1 a 26): ");
                    if (scanf("%d", &n) != 1 || n < 1 || n > 26) {
                        mensagemAleatoria(errosN, 3);
                        while (getchar() != '\n'); /* Limpa o buffer de entrada */
                        continue;
                    }
                    break;
                } while (1);
                getchar();
                
                descriptografar(frase, n);
                printf("\n\nTexto descriptografado: %s\n", frase);
                break;
            case 3:
            	do {
            		printf("Digite a frase (max %d caracteres): ", MAX_LEN);
                	fgets(frase, MAX_LEN, stdin);
                	frase[strcspn(frase, "\n")] = '\0'; /* Remover o '\n' do final */
                 	if (entradaVazia(frase)) {
                        printf("Vazio nao pode.\n");
                    }
                } while (entradaVazia(frase));
                
                toLowerCase(frase);
                
                do {
                    printf("Escolha o valor de N usado para criptografar (1 a 26): ");
                    if (scanf("%d", &n) != 1 || n < 1 || n > 26) {
                        printf("Valor invalido! Digite um numero entre 1 e 26.\n");
                        while (getchar() != '\n'); /* Limpa o buffer de entrada */
                        continue;
                    }
                    break;
                } while (1);
                
                getchar();    
                
                descriptografar(frase, n);
                printf("\n\nTexto original: %s\n", frase);
                break;                 
    
            case 4:
                printf("Saindo...\n");
                break;

            default:
                mensagemAleatoria(errosEntrada, 4);
        }
    } while (opcao != 4);

    return 0;
}
