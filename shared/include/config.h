#ifndef SHARED_INCLUDE_CONFIG_H_
#define SHARED_INCLUDE_CONFIG_H_

#include<stdio.h>
#include<string.h>
#include<commons/log.h>
#include<commons/config.h>
#include<stdlib.h>

typedef struct{
	char* IP_MEMORIA;
	int PUERTO_MEMORIA;
	char* IP_FILESYSTEM;
	int PUERTO_FILESYSTEM;
	char* IP_CPU;
	int PUERTO_CPU;
	char* ALGORITMO_PLANIFICACION;
	int QUANTUM;
	char** RECURSOS;
	char** INSTANCIAS_RECURSOS;
	int GRADO_MULTIPROGRAMACION_INI;
}t_config_kernel;

typedef struct{
	char* IP_MEMORIA;
	int PUERTO_MEMORIA;
	int PUERTO_ESCUCHA_DISPATCH;
	int PUERTO_INTERRUPT;
}t_config_cpu;

typedef struct{
	int PUERTO_ESCUCHA;
	char* IP_FILESYSTEM;
	int PUERTO_FILESYSTEM;
	int TAM_MEMORIA;
	int TAM_PAGINA;
	char* PATH_INSTRUCCIONES;
	int RETARDO_RESPUESTA;
	char* ALGORITMO_REEMPLAZO;
}t_config_memoria;

typedef struct{
	char* IP_MEMORIA;
	int PUERTO_MEMORIA;
	int PUERTO_ESCUCHA;
	char* PATH_FAT;
	char* PATH_BLOQUES;
	char* PATH_FCB;
	int CANT_BLOQUES_TOTAL;
	int CANT_BLOQUES_SWAP;
	int TAM_BLOQUE;
	int RETARDO_ACCESO_BLOQUE;
	int RETARDO_ACCESO_FAT;
}t_config_filesystem;

t_config* iniciar_config(char* ruta_config, t_log* logger);

#endif /* SHARED_INCLUDE_CONFIG_H_ */
