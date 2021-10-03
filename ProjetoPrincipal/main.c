#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct contatos Contatos;

struct contatos{
	int PK; //Primary Key
	char nome[100];
	char telefone[30];
	char endereco[300];
	Contatos *proximo;//indica o proximo endereco de memoria
};

//Crio duas variaveis de escopo global indicando que será dois espaços do tipo Struct contatos
Contatos *primeira;
Contatos *ultima;


//função que adiciona um contato na lista
void adicionar(int pk, char *nome, char *telefone, char *endereco){
	
	/*
		Aqui aloco um espaço em memoria para guardar a struct contatos.
		
		o malloc retorna um ponteiro void, por isso precisamos do cast (Contatos*),
		para converter o ponteiro void em um ponteiro struct contatos.
	*/
	Contatos *nova = (Contatos*) malloc(sizeof(Contatos));
	
	
	//Setando os atributos da struct contatos
	nova->PK = pk;
	strcpy(nova->nome, nome);
	strcpy(nova->telefone, telefone);
	strcpy(nova->endereco, endereco);

	nova->proximo = primeira;
	
	primeira = nova;
	
	
	
}

//Função responsável por exibir os cadastrados na lista telefonica
void mostrarLista(char* letra){
	
	//vai guardar as informaçoes da Lista
	Contatos *auxiliar = primeira;
	
	//Valida se o campo nao está em branco(se estiver mostrará todos os contatos, sem o filtro)
	if (letra == ""){
		
		//Este while percorre a lista toda
		while(auxiliar != NULL){
			printf("[LISTA TELEFONICA]\n[ID %d]\nNOME - %s \nTELEFONE - %s \nENDEREÇO - %s\n\n", auxiliar->PK, auxiliar->nome, auxiliar->telefone, auxiliar->endereco);
			
			//aqui vai passar o valor do proximo endereço para o auxiliar (Quando o proximo endereço for null significa que é o ultimo elemento)
	 		auxiliar = auxiliar->proximo; 
		}
	} else {
		while(auxiliar != NULL){
				//este if eu testo se o primeiro caractere do nome é igual a letra passada por parametro
				if(auxiliar->nome[0] == *letra ){
					printf("[LISTA TELEFONICA]\n[ID %d]\nNOME - %s \nTELEFONE - %s \nENDEREÇO - %s\n\n", auxiliar->PK, auxiliar->nome, auxiliar->telefone, auxiliar->endereco);
				}
			
			//faz a incrementaçao passando o proximo endereço
	 		auxiliar = auxiliar->proximo; 
		}
	}
	
}

Contatos* deletarContato(int pk){
	Contatos* atual = primeira;
	Contatos* anterior = NULL;
	
	//Testa se a lista é nula
	if (primeira == NULL){
		return NULL;
	}
	
	
	while(atual->PK != pk){
		if(atual->proximo == NULL){
			return NULL;
		} else {
			anterior = atual;
			atual = atual->proximo;
		}
	}
	
	if(atual == primeira){
		primeira = primeira->proximo;
	}else{
		anterior->proximo = atual->proximo;
	}
	
	return atual;
		
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL,"PORTUGUESE");
	
	//Adiciona contato
	adicionar(0, "Lucas", "999999999", "Vila virginia");
	adicionar(1, "Lola calypso", "888888888", "Av Henry nestlé, 1001");
	adicionar(2, "Rodrigo Maia", "888888888", "Lagoinha Nobre 2, 893");
	adicionar(3, "Claudia Balani", "9999999999", "Av Lagoinha 3233");
	
	//remove o contato da lista
	deletarContato(3);

	//mostra a lista (para listar todos os contatos deixe "")
	mostrarLista("L");
	
	return 0;
}
