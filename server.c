#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {

	int server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd == -1)
	{
		perror("Erro ao criar socket");
		exit(EXIT_FAILURE);
	}

	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(8080);


	if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) == -1)
	{
		perror("Erro no bind");
		close(server_fd);	
		exit(EXIT_FAILURE);
	}

	if (listen(server_fd, 5) == -1)
	{
		perror("Error no listen");
		close(server_fd);
		exit(EXIT_FAILURE);
	}

	printf("Aguardando conexões (porta 8080)....\n");

	struct sockaddr_in client_address;
	socklen_t client_size = sizeof(client_address);
	int client_fd = accept(server_fd, (struct sockaddr*)&client_address, &client_size);
	if (client_fd == -1) 
	{
		perror("Erro no accept");
		close(server_fd);
		return(EXIT_FAILURE);	
	}

	printf("Cliente conectado!\n");

	

	char buffer[1024] = {0};
	char *message = "Servidor Simples Criado com Sucesso e Funcionando!";
	send(client_fd, message, strlen(message), 0);
	printf("Mensagem Enviada!\n");

	close(client_fd);
	close(server_fd);
	return 0;
}
