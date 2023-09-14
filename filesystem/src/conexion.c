#include "../include/conexion.h"

#define IP "127.0.0.1"
#define PUERTO "8003"

int server_filesystem;

int iniciar_filesystem(t_config_filesystem* filesystem_datos, t_log* logger_filesystem){
	conectar_MEMORIA(logger_filesystem, "SERVER MEMORIA", filesystem_datos->IP_MEMORIA, filesystem_datos->PUERTO_MEMORIA);
	crearServidor(logger_filesystem, "SERVER FILE SYSTEM", IP, PUERTO, server_filesystem);

	return 1;
}
