#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
cria struct
que recebera os dados do comando
*/

typedef struct cmd{
	char command[100];
	char subcommand[100];
	char param[100][100];
        int  n_params;
}Commands;

/*
funcao para converter uma string de comando no struct Commands
*/
Commands convertCommand(char * command)
{

   	char * token[99];
	int j, k, i=0, par=2;
	
	//separa no indicie 0 a primeira separação por espaço
    	token[0] = strtok(command, " ");

    	while(token[i]!= NULL) {
        	//separa para cada indicie o que resta da string separando por espaço
		i++;
        	token[i] = strtok(NULL, " ");
    	}
	
	//cria variavel com do typo Commands
	Commands com;
	//insere os valores nas propriedades
	strncpy(com.command, token[0], strlen(token[0]));
	strncpy(com.subcommand, token[1], strlen(token[1]));
	
	//separa os parametros em uma array de strings
	for(k = 0; k < i-2; k++ ){
	        strncpy(com.param[k],token[par],sizeof(token[par]));
		par++;
	}
	//o numero de parametros existentes
	com.n_params = i-2;
	return com;

}


/*
Funcao retorna json 
convertendo o Struct Commands em String
*/
char * json_encode(Commands comandos)
{
	char str_nova[150];
	int j;
	
	//inicia a str json inserindo o comando
	strcpy(str_nova, "{\"command\":\"");
	strcat(str_nova, comandos.command);
	//concatena o subcomando
	strcat(str_nova, "\",\"subcommand\":\"");
	strcat(str_nova, comandos.subcommand);
	//prepara a string para receber uma array de parametros no formato json
	strcat(str_nova, "\",\"params\":[");
	for(j=0; j < comandos.n_params; j++){
		//concatena todos os paramentros
		strcat(str_nova, "\"");
		strcat(str_nova, comandos.param[j]);
		strcat(str_nova, "\",");
	}
	//retira o ultima virgula
	str_nova[strlen(str_nova)-1] = ']';
	//fecha todo o objeto json
	strcat(str_nova, "}");
	
	//cria a variavel que retornara a string json do tamanho da string criada
	char *type = malloc(sizeof(str_nova));
	//insere na variavel o valor da string json
	strncpy(type, str_nova, (sizeof(str_nova)));
	return(type);
}


void main(void)
{
	char comando[100];
	char * point;
	char str_json[150];
	char * array[100];

	printf("digite a função:\n");
	scanf("%[^\n]", comando);

	Commands comRet;

	comRet = convertCommand(comando);
	point = json_encode(comRet);

	strncpy( str_json, point, strlen(point));
	printf("\n\n%s\n\n", str_json);
}
