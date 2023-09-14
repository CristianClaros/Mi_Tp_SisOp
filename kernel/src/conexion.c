#include "../include/conexion.h"

#define IP "127.0.0.1"
#define PUERTO "8000"

int socket_kernel;

int iniciar_kernel(t_config_kernel* kernel_datos, t_log* logger_kernel){
	conectar_CPU(logger_kernel, "SERVIDOR CPU", kernel_datos->IP_CPU, kernel_datos->PUERTO_CPU);
	conectar_MEMORIA(logger_kernel, "SERVIDOR MEMORIA", kernel_datos->IP_MEMORIA, kernel_datos->PUERTO_MEMORIA);
	conectar_FILESYSTEM(logger_kernel, "SERVIDOR FILESYSTEM", kernel_datos->IP_FILESYSTEM, kernel_datos->PUERTO_FILESYSTEM);
	crearServidor(logger_kernel, "SERVIDOR KERNEL", IP, PUERTO , socket_kernel);

	return 1;
}

