#ifndef SHARED_INCLUDE_CONEXION_H_
#define SHARED_INCLUDE_CONEXION_H_

#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netdb.h>
#include <commons/log.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

#include "../include/estructuras.h"

typedef struct {
    t_log *log;
    int fd;
    char *server_name;
} t_procesar_conexion_args;

typedef struct
{
	int size;
	void* stream;
} t_buffer;

typedef struct
{
	op_code codigo_operacion;
	t_buffer* buffer;
} t_paquete;



void crearServidor(t_log* logger, char* name_server, char* ip_server, char* puerto_server, int* socket_server, void (*procesar_conexion)(t_procesar_conexion_args* args));
int iniciar_servidor(t_log* logger, const char* name_server, char* ip_server, char* puerto_server);
int server_escuchar(t_log *logger, char *server_name, int server_socket, void (*procesar_conexion)(t_procesar_conexion_args* args));
void procesar_conexion(t_procesar_conexion_args* void_args);
int crear_conexion(t_log* logger, const char* server_name, char* ip, char* puerto);
int esperar_cliente(t_log* logger, const char* name, int socket_servidor);

int conectar_CPU(t_log* logger, char* server_name, char* ip, char* puerto);
int conectar_MEMORIA(t_log* logger, char* server_name, char* ip, char* puerto);
int conectar_FILESYSTEM(t_log* logger, char* server_name, char* ip, char* puerto);

void enviar_mensaje(char* mensaje, int socket_cliente);
void* serializar_paquete(t_paquete* paquete, int bytes);
void crear_buffer(t_paquete* paquete);
t_paquete* crear_paquete(void);
void agregar_a_paquete(t_paquete* paquete, void* valor, int tamanio);
void enviar_paquete(t_paquete* paquete, int socket_cliente);
void eliminar_paquete(t_paquete* paquete);
void liberar_conexion(int socket_cliente);

t_list* recibir_paquete(int socket_cliente);
void recibir_mensaje(int socket_cliente);
void* recibir_buffer(int* size, int socket_cliente);
int recibir_operacion(int socket_cliente);



#endif /* SHARED_INCLUDE_CONEXION_H_ */
