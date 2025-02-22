#include <stdio.h>
#include <locale.h>
#define MAX_LEN 100

int main() {
    setlocale(LC_ALL, "");
    
    char frase[MAX_LEN];
    int n, opcao;

    do {
        printf("\n--- Jogo da Imitação Textual ---\n");
        printf("1 - Digitar nova frase e criptografar\n");
        printf("2 - Descriptografar a frase salva\n");
        printf("3 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();
        
        switch (opcao) {
            case 1:
                printf("Digite a frase (max %d caracteres): ", MAX_LEN);
                fgets(frase, MAX_LEN, stdin);
                frase[strcspn(frase, "\n")] = '\0'; // Remover o '\n' do final                  

                printf("Escolha um numero N (1 a 26): ");
                scanf("%d", &n);
                getchar();
                break;

            case 2:
                printf("Texto criptografado carregado: %s\n");

                printf("Escolha o valor de N usado para criptografar (1 a 26): ");
                scanf("%d", &n);
                getchar();
                break;

            case 3:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida! Escolha novamente.\n");
        }
    } while (opcao != 3);

    return 0;
}
