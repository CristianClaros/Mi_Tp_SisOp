#ifndef SHARED_INCLUDE_CONEXION_H_
#define SHARED_INCLUDE_CONEXION_H_

#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netdb.h>
#include <commons/log.h>
#include <string.h>
#include <stdlib.h>

#include "../include/estructuras.h"

typedef struct {
    t_log *log;
    int fd;
    char *server_name;
} t_procesar_conexion_args;

void* crearServidor(t_log* logger, char* name_server, char* ip_server, int puerto_server, int puerto, int socket);
int iniciar_servidor(t_log* logger, const char* name, char* ip, char* puerto);
int server_escuchar(t_log *logger, char *server_name, int server_socket);
void procesar_conexion(void *void_args);
int crear_conexion(t_log* logger, const char* server_name, char* ip, char* puerto);
int esperar_cliente(t_log* logger, const char* name, int socket_servidor);


#endif /* SHARED_INCLUDE_CONEXION_H_ */
