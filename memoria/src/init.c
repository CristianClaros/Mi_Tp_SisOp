#include "../utils/init.h"

int cargar_config_memoria(t_config* config, t_log* logger){
	t_config_memoria* memoria_struct = malloc(sizeof(t_config_memoria));

	memoria_struct->PUERTO_ESCUCHA = config_get_int_value(config, "PUERTO_ESCUCHA");
	log_info(logger, "PUERTO_ESCUCHA: %i", memoria_struct->PUERTO_ESCUCHA);

	memoria_struct->IP_FILESYSTEM = config_get_string_value(config, "IP_FILESYSTEM");
	log_info(logger, "IP_FILESYSTEM: %s", memoria_struct->IP_FILESYSTEM);

	memoria_struct->PUERTO_FILESYSTEM = config_get_int_value(config, "PUERTO_FILESYSTEM");
	log_info(logger, "PUERTO_FILESYSTEM: %i", memoria_struct->PUERTO_FILESYSTEM);

	memoria_struct->TAM_MEMORIA = config_get_int_value(config, "TAM_MEMORIA");
	log_info(logger, "TAM_MEMORIA: %i", memoria_struct->TAM_MEMORIA);

	memoria_struct->TAM_PAGINA = config_get_int_value(config, "TAM_PAGINA");
	log_info(logger, "TAM_PAGINA: %i", memoria_struct->TAM_PAGINA);

	memoria_struct->PATH_INSTRUCCIONES = config_get_string_value(config, "PATH_INSTRUCCIONES");
	log_info(logger, "PATH_INSTRUCCIONES: %s", memoria_struct->PATH_INSTRUCCIONES);

	memoria_struct->RETARDO_RESPUESTA = config_get_int_value(config, "RETARDO_RESPUESTA");
	log_info(logger, "RETARDO_RESPUESTA: %i", memoria_struct->RETARDO_RESPUESTA);

	memoria_struct->ALGORITMO_REEMPLAZO = config_get_string_value(config, "ALGORITMO_REEMPLAZO");
	log_info(logger, "ALGORITMO_REEMPLAZO: %s\n", memoria_struct->ALGORITMO_REEMPLAZO);

	return 1;
}