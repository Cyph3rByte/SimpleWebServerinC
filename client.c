#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


int main() {

	int client_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (client_fd == -1)
	{
		perror("Erro ao criar socket");
		exit(EXIT_FAILURE);
	}

	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(8080);
	if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0)
	{
		perror("Endereço Inválido");
		close(client_fd);
		exit(EXIT_FAILURE);
	}

	if (connect(client_fd, (struct sockaddr*)&server_address, sizeof(server_address)) == -1)
	{
		perror("Erro no connect");
		close(client_fd);
		exit(EXIT_FAILURE);
	}

	char buffer[1024] = {0};
	recv(client_fd, buffer, sizeof(buffer), 0);
	printf("Mensagem do Servidor: %s\n", buffer);

	close(client_fd);

	return 0;
}
