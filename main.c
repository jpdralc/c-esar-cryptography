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
        if (str[i] != ' ') { // Mantém espaços inalterados
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

int main() {
    setlocale(LC_ALL, "");
    
    char frase[MAX_LEN];
    int n, opcao;
    const char *arquivo = "mensagem.txt";

    do {
        printf("\n--- Jogo da Imitação Textual ---\n");
        printf("1 - Digitar nova frase e criptografar\n");
        printf("2 - Descriptografar a frase salva\n");
        printf("3 - Descriptografar frase livre\n");
        printf("4 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();
        
        switch (opcao) {
            case 1:
                printf("Digite a frase (max %d caracteres): ", MAX_LEN);
                fgets(frase, MAX_LEN, stdin);
                frase[strcspn(frase, "\n")] = '\0'; /* Remover o '\n' do final */
                
				toLowerCase(frase);                 

                printf("Escolha um numero N (1 a 26): ");
                scanf("%d", &n);
                getchar();
                
                criptografar(frase, n);
                printf("Texto criptografado: %s\n", frase);
				
				salvarArquivo(arquivo, frase);
                printf("Frase salva no arquivo.\n");                
                break;

            case 2:
            	carregarArquivo(arquivo, frase);
                printf("Texto criptografado carregado: %s\n", frase);

                printf("Escolha o valor de N usado para criptografar (1 a 26): ");
                scanf("%d", &n);
                getchar();
                
                descriptografar(frase, n);
                printf("\n\nTexto original: %s\n", frase);
                break;
            case 3:
            	printf("Digite a frase (max %d caracteres): ", MAX_LEN);
                fgets(frase, MAX_LEN, stdin);
                frase[strcspn(frase, "\n")] = '\0'; /* Remover o '\n' do final */
                
				toLowerCase(frase);
				
				printf("Escolha o valor de N usado para criptografar (1 a 26): ");
                scanf("%d", &n);
                getchar();	
                
                descriptografar(frase, n);
                printf("\n\nTexto original: %s\n", frase);
				break;                 
	
            case 4:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida! Escolha novamente.\n");
        }
    } while (opcao != 4);

    return 0;
}
