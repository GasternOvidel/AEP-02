#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "usuarios.txt"

// Função simples para criar um hash básico da senha
unsigned long hash_senha(const char *senha) {
    unsigned long hash = 5381;
    int c;
    while ((c = *senha++))
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    return hash;
}

// Função para cadastrar um novo usuário
void cadastrarUsuario() {
    FILE *file = fopen(FILENAME, "a");
    if (!file) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    char username[50], senha[50];
    printf("Digite o nome de usuário: ");
    scanf("%s", username);

    printf("Digite a senha: ");
    scanf("%s", senha);

    unsigned long hash = hash_senha(senha); // Cria o hash da senha

    fprintf(file, "%s %lu\n", username, hash); // Salva no arquivo
    fclose(file);
    printf("Usuário cadastrado com sucesso!\n");
}

// Função para verificar login
void login() {
    FILE *file = fopen(FILENAME, "r");
    if (!file) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    char username[50], senha[50];
    printf("Digite o nome de usuário: ");
    scanf("%s", username);

    printf("Digite a senha: ");
    scanf("%s", senha);

    unsigned long hash = hash_senha(senha);
    char file_user[50];
    unsigned long file_hash;
    int found = 0;

    // Procura o usuário e compara hashes
    while (fscanf(file, "%s %lu", file_user, &file_hash) != EOF) {
        if (strcmp(file_user, username) == 0 && file_hash == hash) {
            found = 1;
            break;
        }
    }
    fclose(file);

    if (found) {
        printf("Login bem-sucedido!\n");
    } else {
        printf("Nome de usuário ou senha incorretos!\n");
    }
}

// Função para listar todos os usuários (somente nomes, sem senhas)
void listarUsuarios() {
    FILE *file = fopen(FILENAME, "r");
    if (!file) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    char username[50];
    unsigned long hash;
    printf("Lista de usuários:\n");
    while (fscanf(file, "%s %lu", username, &hash) != EOF) {
        printf("Username: %s\n", username);
    }
    fclose(file);
}

// Menu principal
int main() {
    int opcao;
    while (1) {
        printf("\nMenu:\n1. Cadastrar Usuário\n2. Login\n3. Listar Usuários\n4. Sair\nEscolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarUsuario();
                break;
            case 2:
                login();
                break;
            case 3:
                listarUsuarios();
                break;
            case 4:
                exit(0);
            default:
                printf("Opção inválida!\n");
        }
    }
    return 0;
}
