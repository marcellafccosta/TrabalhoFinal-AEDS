/*
Nomes: Ana Julia Teixeira Candido e Marcella Ferreira Chaves Costa
Professor: Jose Laerte Pires Xavier Junior
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_CHAR 100
#define MAX_PASSAGEIROS 10
#define MAX_ESPERA 5

typedef struct {

  char cpf[MAX_CHAR];
  char nome[MAX_CHAR];
  char endereco[MAX_CHAR];
  char telefone[MAX_CHAR];
  char numPassagem[MAX_CHAR];
  char numPoltrona[MAX_CHAR];
  char numVoo[MAX_CHAR];
  char horario[MAX_CHAR];
} Passageiro;

typedef struct {

  Passageiro passageiros[MAX_ESPERA];
  int numPassageiros;
} FilaEspera;

// ----------------------------------------------------------------------------------------------------- //

// LER ARQUIVOS
int readFile(char filePath[], Passageiro passageiros[]) {

	FILE *arquivo = fopen(filePath, "r");

	if (arquivo == NULL) {

		printf("Erro ao abrir o arquivo.\n");
		return 0;
	}

	char linha[MAX_CHAR];
	int passageirosCount = 0;

	while (fgets(linha, MAX_CHAR, arquivo)) {

		if(strstr(linha, "CPF: ") != NULL) {

			sscanf(linha, "CPF: %s", passageiros[passageirosCount].cpf);

			fgets(linha, MAX_CHAR, arquivo);
			sscanf(linha, "Nome: %[^\n]", passageiros[passageirosCount].nome);

			fgets(linha, MAX_CHAR, arquivo);
			sscanf(linha, "Endereço: %[^\n]", passageiros[passageirosCount].endereco);

			fgets(linha, MAX_CHAR, arquivo);
			sscanf(linha, "Telefone: %[^\n]", passageiros[passageirosCount].telefone);

			fgets(linha, MAX_CHAR, arquivo);
			sscanf(linha, "Número da Passagem: %[^\n]", passageiros[passageirosCount].numPassagem);

			fgets(linha, MAX_CHAR, arquivo);
			sscanf(linha, "Número da Poltrona: %[^\n]", passageiros[passageirosCount].numPoltrona);

			fgets(linha, MAX_CHAR, arquivo);
			sscanf(linha, "Voo: %[^\n]", passageiros[passageirosCount].numVoo);

			fgets(linha, MAX_CHAR, arquivo);
			sscanf(linha, "Horário: %[^\n]", passageiros[passageirosCount].horario);

			passageirosCount++;

			if (passageirosCount == MAX_PASSAGEIROS) break;
		}
	}

	fclose(arquivo);

	return passageirosCount;
}

// BUSCAR PASSAGEIRO POR NOME
Passageiro buscarPassageiroPorNome(Passageiro passageiros[], int numPassageiros) {

	char searchTerm[MAX_CHAR];

	printf("Digite o nome do passageiro: ");
	scanf(" %[^\n]", searchTerm);

	if (passageiros && !(searchTerm[0] == '\0')) {

		for (int i = 0; i < numPassageiros; i++) {

			if (!strcmp(passageiros[i].nome, searchTerm)) return passageiros[i];
		}
	}

	Passageiro passageiroDefault;
	return passageiroDefault;
}

// BUSCAR PASSAGEIRO POR CPF
Passageiro buscarPassageiroPorCpf(Passageiro passageiros[], int arraySize) {

	char searchTerm[MAX_CHAR];


	printf("Digite o CPF do passageiro: ");
	scanf("%s", searchTerm);

	if (passageiros && !(searchTerm[0] == '\0')) {

		for (int i = 0; i < arraySize; i++) {

			if (!strcmp(passageiros[i].cpf, searchTerm)) return passageiros[i];
		}
	}

	Passageiro passageiroDefault;

	strcpy(passageiroDefault.cpf, "N/A");

	return passageiroDefault;
}


Passageiro lerNovoPassageiro(char voo[]);

void escreverArquivo(FILE *arquivo, Passageiro passageiro);

// ADICIONAR PASSAGEIRO
void adicionarPassageiroNoVoo(char voo[]) {

	FILE *arquivo;
	Passageiro passageiro = lerNovoPassageiro(voo);

	if ((arquivo = fopen(voo, "a")) == NULL) {

		printf("Erro na abertura do arquivo.\n");
		exit(1); // Finaliza a execucao do programa com status (1)
	}

	escreverArquivo(arquivo, passageiro);
}

//ADICIONAR PASSAGEIRO NA FILA DE ESPERA
void adicionarPassageiroNaFilaEspera(char voo[]) {

	FILE *arquivo;
	Passageiro passageiro = lerNovoPassageiro(voo);

	if ((arquivo = fopen(voo, "a")) == NULL) {

		printf("Erro na abertura do arquivo.\n");
		exit(1); // Finaliza a execucao do programa com status (1)
	}
	escreverArquivo(arquivo, passageiro);
}

// ESCREVER ARQUIVO
void escreverArquivo(FILE *arquivo, Passageiro passageiro) {

	// O fseek vai buscar uma posicao do arquivo, e partir dela, voltar ou avancar
	// X posicoes e escrever o novo valor. No caso que eu fiz, ele vai para o fim
	// do arquivo (SEEK_END) e, a partir dele, movimenta 0 caracteres, e escreve o
	// novo valor.
	fseek(arquivo, 0, SEEK_END);
	fprintf(arquivo, "\nCPF: %s\n", passageiro.cpf);
	fprintf(arquivo, "Nome: %s\n", passageiro.nome);
	fprintf(arquivo, "Endereço: %s\n", passageiro.endereco);
	fprintf(arquivo, "Telefone: %s\n", passageiro.telefone);
	fprintf(arquivo, "Número da Passagem: %s\n", passageiro.numPassagem);
	fprintf(arquivo, "Número da Poltrona: %s\n", passageiro.numPoltrona);
	fprintf(arquivo, "Voo: %s\n", passageiro.numVoo);
	fprintf(arquivo, "Horário: %s\n", passageiro.horario);
	fclose(arquivo);
}

// LER PASSAGEIRO
Passageiro lerNovoPassageiro(char voo[]) {

	Passageiro novoPassageiro;

	printf("CPF: ");
	scanf(" %[^\n]", novoPassageiro.cpf);

	printf("Nome: ");
	scanf(" %[^\n]", novoPassageiro.nome);

	printf("Endereço: ");
	scanf(" %[^\n]", novoPassageiro.endereco);

	printf("Telefone: ");
	scanf(" %[^\n]", novoPassageiro.telefone);

	printf("Número da Passagem: ");
	scanf(" %[^\n]", novoPassageiro.numPassagem);

	printf("Número da Poltrona: ");
	scanf(" %[^\n]", novoPassageiro.numPoltrona);

	printf("Horário: ");
	scanf(" %[^\n]", novoPassageiro.horario);

	strcpy(novoPassageiro.numVoo, voo);

	return novoPassageiro;
}

// EXIBIR PASSAGEIROS
void exibePassageiros(Passageiro passageiros[]) {

	for (int i = 0; i < MAX_PASSAGEIROS; i++) {

		printf("\nCPF: %s\n", passageiros[i].cpf);
		printf("Nome: %s\n", passageiros[i].nome);
		printf("Endereco: %s\n", passageiros[i].endereco);
		printf("Telefone: %s\n", passageiros[i].telefone);
		printf("Número da Passagem: %s\n", passageiros[i].numPassagem);
		printf("Número da Poltrona: %s\n", passageiros[i].numPoltrona);
		printf("Voo: %s\n", passageiros[i].numVoo);
		printf("Horário: %s\n", passageiros[i].horario);
	}
}

// EXIBIR LISTA DE ESPERA
void exibirListaDeEspera(const char *voo) {

	char nomeArquivo[30];
	sprintf(nomeArquivo, "%s-FDE.txt", voo);

	FILE *arquivo = fopen(nomeArquivo, "r");

	if (arquivo == NULL) {

		printf("Erro ao abrir o arquivo.\n");
		return;
	}

	char linha[MAX_CHAR];

	while (fgets(linha, sizeof(linha), arquivo) != NULL) printf("%s", linha);

	fclose(arquivo);
}

// EXCLUIR PASSAGEIRO
void excluirPassageiroDaLista(char filePath[], Passageiro passageiro, int numPassageiros) {

	FILE *arquivo = fopen(filePath, "r");

	if (arquivo == NULL) {

		printf("Erro ao abrir o arquivo.\n");
		return;
	}

	// -------------------------------------------------------------------------------------------- //

	FILE *arquivoTemp = fopen("temp.txt", "w");

	if (arquivoTemp == NULL) {

		printf("Erro ao abrir o arquivo.\n");
		return;
	}

	char linha[MAX_CHAR];

	while (fgets(linha, sizeof(linha), arquivo) != NULL) {

		// if found cpf
		if (strstr(linha, passageiro.cpf) != NULL) {

			// skip 7 lines
			for (int i = 0; i < 7; i++) fgets(linha, sizeof(linha), arquivo);

		} 
		else fprintf(arquivoTemp, "%s", linha);
	}

	fclose(arquivo);
	fclose(arquivoTemp);

	// Rename and remove
	remove(filePath);
	rename("temp.txt", filePath);
	
	// -------------------------------------------------------------------------------------------- //

	// Se o passageiro excluído estava na lista normal, então realocar os passageiros da lista de espera
	if(strstr(filePath, "-FDE.txt") == NULL) {

		// Get lista de espera
		char filePathFDE[30];
		strcpy(filePathFDE, filePath);

		filePathFDE[strlen(filePathFDE) - 4] = '\0';
		strcat(filePathFDE, "-FDE.txt");

		Passageiro passageirosFDE[MAX_ESPERA];

		int listaEspera = readFile(filePathFDE, passageirosFDE);

		// ----------------------------------------------------- //

		if(listaEspera > 0) {

			// Get passageiro da lista de espera
			Passageiro passageiroFDE = passageirosFDE[0];

			// Reconstruir arquivo da lista normal com o passageiro da lista de espera
			FILE *arquivo = fopen(filePath, "a");

			if (arquivo == NULL) {

				printf("Erro ao abrir o arquivo.\n");
				return;
			}

			fprintf(arquivo, "\nCPF: %s\n", passageiroFDE.cpf);
			fprintf(arquivo, "Nome: %s\n", passageiroFDE.nome);
			fprintf(arquivo, "Endereco: %s\n", passageiroFDE.endereco);
			fprintf(arquivo, "Telefone: %s\n", passageiroFDE.telefone);
			fprintf(arquivo, "Número da Passagem: %s\n", passageiroFDE.numPassagem);
			fprintf(arquivo, "Número da Poltrona: %s\n", passageiroFDE.numPoltrona);
			fprintf(arquivo, "Voo: %s\n", passageiroFDE.numVoo);
			fprintf(arquivo, "Horário: %s\n", passageiroFDE.horario);

			fclose(arquivo);

			// ----------------------------- //

			// Excluir passageiro da lista de espera
			excluirPassageiroDaLista(filePathFDE, passageiroFDE, listaEspera);
		}
	}
}

// -------------------------------------------------------------------------------------------- //

// MAIN
int main() {

	Passageiro passageiros[MAX_PASSAGEIROS];
	int numPassageiros = 0;
	int numEspera = 0;
	FilaEspera filaEspera;
	filaEspera.numPassageiros = 0;

	int opcao, opcao2;
	char voo[20];
	char numVoo[MAX_CHAR];

 printf("Digite o voo (BH-RIO, BH-SP, BH-BSB): ");
scanf(" %19s", voo);
getchar();

if (strcmp(voo, "BH-SP") == 0 || strcmp(voo, "BH-BSB") == 0 || strcmp(voo, "BH-RIO") == 0 ) {
    
    // MENU DE OPCOES
    printf("\nEMPRESA AÉREA QUEDA LIVRE - VOO %s\n", voo);
    printf("\n-------- menu de opções --------\n");
    printf("1. Mostrar Lista de Passageiros\n");
    printf("2. Pesquisar Passageiro por CPF\n");
    printf("3. Pesquisar Passageiro por nome\n");
    printf("4. Cadastrar um passageiro na lista de determinado voo\n");
    printf("5. Excluir um passageiro da lista de um determinado voo\n");
    printf("6. Mostrar a fila de espera dos passageiros de um determinado voo\n");
    printf("7. Sair\n");

    printf("\n");
    printf("Digite sua opção: ");
    scanf("%d", &opcao);
    getchar();

    switch (opcao) {
            case 1: {

			Passageiro passageiros[MAX_PASSAGEIROS];
			readFile(strcat(voo, ".txt"), passageiros);
			exibePassageiros(passageiros);
			break;
		}

		// pesquisar passageiros por cpf
		case 2: {

			Passageiro passageiros[MAX_PASSAGEIROS];
			readFile(strcat(voo, ".txt"), passageiros);

			int arraySize = sizeof(passageiros) / sizeof(passageiros[0]); // pegar o tamanho do array
			Passageiro passageirosEncontrado = buscarPassageiroPorCpf(passageiros, arraySize);

			// Verificar se houve algum resultado encontrado
			if (strlen(passageirosEncontrado.cpf) != 0) {

				printf("\n-----------------------------");
				printf("\nPassageiro encontrado:\n");
				printf("CPF: %s\n", passageirosEncontrado.cpf);
				printf("Nome: %s\n", passageirosEncontrado.nome);
				printf("Endereço: %s\n", passageirosEncontrado.endereco);
				printf("Telefone: %s\n", passageirosEncontrado.telefone);
				printf("Número de Passagem: %s\n", passageirosEncontrado.numPassagem);
				printf("Número de Poltrona: %s\n", passageirosEncontrado.numPoltrona);
				printf("Voo: %s\n", passageirosEncontrado.numVoo);
				printf("Horário: %s\n", passageirosEncontrado.horario);
				printf("-----------------------------\n");
			} 
			else printf("Passageiro não consta neste voo.");
			break;
		}

		// pesquisar passageiro por nome
		case 3: {

			Passageiro passageiros[MAX_PASSAGEIROS];
			int numPassageiros = readFile(strcat(voo, ".txt"), passageiros);
			int arraySize = sizeof(passageiros) / sizeof(passageiros[0]); // pegar o tamanho do array

			// Pesquisar passageiro por nome
			Passageiro passageirosEncontrado = buscarPassageiroPorNome(passageiros, numPassageiros);

			// Verificar se houve algum resultado encontrado
			if (strlen(passageirosEncontrado.nome) != 0) {

				printf("\n-----------------------------");
				printf("\nPassageiro encontrado:\n");
				printf("CPF: %s\n", passageirosEncontrado.cpf);
				printf("Nome: %s\n", passageirosEncontrado.nome);
				printf("Endereço: %s\n", passageirosEncontrado.endereco);
				printf("Telefone: %s\n", passageirosEncontrado.telefone);
				printf("Número de Passagem: %s\n", passageirosEncontrado.numPassagem);
				printf("Número de Poltrona: %s\n", passageirosEncontrado.numPoltrona);
				printf("Voo: %s\n", passageirosEncontrado.numVoo);
				printf("Horário: %s\n", passageirosEncontrado.horario);
				printf("-----------------------------\n");
			} 
			else printf("Passageiro não consta neste voo.");
			break;
		}

		// cadastrar um passageiro na lista de determinado voo
		case 4: {

			char arquivo_temp01[20], arquivo_temp02[20];
			strcpy(arquivo_temp01, voo);
			strcat(arquivo_temp01, ".txt");
			strcpy(arquivo_temp02, voo);
			strcat(arquivo_temp02, "-FDE.txt");
			
			int numPassageiros = readFile(arquivo_temp01, passageiros);
			int filaEspera = readFile(arquivo_temp02, passageiros) - 1;

			if (numPassageiros != MAX_PASSAGEIROS) {

				adicionarPassageiroNoVoo(arquivo_temp01);
				numPassageiros++;

				printf("Passageiro cadastrado com sucesso!\n");
				break;
			}

			if (filaEspera != MAX_ESPERA) {

				adicionarPassageiroNaFilaEspera(arquivo_temp02);
				filaEspera++;

				printf("Este voo está cheio, passageiro adicionado à fila de espera com sucesso!\n");
				break;
			}

			printf("Fila cheia, a reserva não pode ser feita.\n");
			break;
		}

		// excluir um passageiro da lista de um determinado voo
		case 5: {
        printf("Serão disponibilizadas duas linhas para entrada do CPF , digite em ambas para certificar que ele seja excluído se estiver na lista de espera\n");

			char voo_tmp[20];
			strcpy(voo_tmp, voo);

			char voo_normal_txt[20] = "";
			strcat(voo_normal_txt, voo_tmp);
			strcat(voo_normal_txt, ".txt");

			char voo_espera_txt[20] = "";
			strcat(voo_espera_txt, voo_tmp);
			strcat(voo_espera_txt, "-FDE.txt");
      

			Passageiro passageiros_normal[MAX_PASSAGEIROS];
			int numPassageirosNormal = readFile(voo_normal_txt, passageiros_normal);

			Passageiro passageiros_espera[MAX_ESPERA];
			int numPassageirosEspera = readFile(voo_espera_txt, passageiros_espera);

			Passageiro buscaPassageiro = buscarPassageiroPorCpf(passageiros_normal, numPassageirosNormal);
			Passageiro buscaPassageiroEspera = buscarPassageiroPorCpf(passageiros_espera, numPassageirosEspera);



			if(!strcmp(buscaPassageiro.cpf, "N/A") && !strcmp(buscaPassageiroEspera.cpf, "N/A")) {

				printf("Passageiro não encontrado.\n");
				break;
			}

			if(strcmp(buscaPassageiro.cpf, "N/A")) {

				excluirPassageiroDaLista(voo_normal_txt, buscaPassageiro, numPassageirosNormal);
				break;
			}
			else if(strcmp(buscaPassageiroEspera.cpf, "N/A")) {

				excluirPassageiroDaLista(voo_espera_txt, buscaPassageiroEspera, numPassageirosEspera);
				break;
			}
			break;
		}

		// mostrar a fila de espera dos passageiros de um determinado voo
		case 6: {

			exibirListaDeEspera(voo);
			break;
		}

		// sair
		case 7: {

			printf("Sessão finalizada, obrigada.\n");
			break;
		}
      default: {
      printf("Opção inválida.Sessão finalizada, obrigada.\n");
			break;
    }
    }}
        
else {
    printf("Voo não encontrado\n");
}

return 0;}