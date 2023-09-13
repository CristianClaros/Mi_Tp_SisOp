#include "../include/conexion.h"

#define IP "127.0.0.1"
#define PUERTO 8000
int puerto_kernel;

int socket_kernel;

int activar_kernel(t_config_kernel* kernel_datos, t_log* logger_kernel){
	crearServidor(logger_kernel, "SERVIDOR KERNEL", IP, puerto_kernel, PUERTO , socket_kernel);

	return 1;
}
