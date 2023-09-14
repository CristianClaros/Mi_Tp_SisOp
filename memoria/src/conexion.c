#include "../include/conexion.h"

#define IP "127.0.0.1"
#define PUERTO "8002"

int server_memoria;

int iniciar_memoria(t_config_memoria* memoria_datos, t_log* logger_memoria){
	conectar_FILESYSTEM(logger_memoria, "SERVER FILESYSTEM", memoria_datos->IP_FILESYSTEM, memoria_datos->PUERTO_FILESYSTEM);
	crearServidor(logger_memoria, "SERVER MEMORIA", IP, PUERTO, server_memoria);

	return 1;
}
