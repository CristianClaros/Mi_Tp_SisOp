#include "../include/conexion.h"

#define IP "127.0.0.1"
#define PUERTO "8001"

int server_cpu;

int iniciar_cpu(t_config_cpu* cpu_datos, t_log* logger_cpu){
	conectar_MEMORIA(logger_cpu, "SERVER MEMORIA", cpu_datos->IP_MEMORIA, cpu_datos->PUERTO_MEMORIA);
	crearServidor(logger_cpu, "SERVER_CPU", IP, PUERTO, server_cpu);

	return 1;
}
