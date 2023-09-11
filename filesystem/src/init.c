#include "../utils/init.h"

int cargar_config_filesystem(t_config* config, t_log* logger){
	t_config_filesystem* filesystem_struct = malloc(sizeof(t_config_filesystem));

	filesystem_struct->IP_MEMORIA = config_get_string_value(config, "IP_MEMORIA");
	log_info(logger, "IP_MEMORIA: %s", filesystem_struct->IP_MEMORIA);

	filesystem_struct->PUERTO_MEMORIA = config_get_int_value(config, "PUERTO_MEMORIA");
	log_info(logger, "PUERTO_MEMORIA: %i", filesystem_struct->PUERTO_MEMORIA);

	filesystem_struct->PUERTO_ESCUCHA = config_get_int_value(config, "PUERTO_ESCUCHA");
	log_info(logger, "PUERTO_ESCUCHA: %i", filesystem_struct->PUERTO_ESCUCHA);

	filesystem_struct->PATH_FAT = config_get_string_value(config, "PATH_FAT");
	log_info(logger, "PATH_FAT: %s", filesystem_struct->PATH_FAT);

	filesystem_struct->PATH_BLOQUES = config_get_string_value(config, "PATH_BLOQUES");
	log_info(logger, "PATH_BLOQUES: %s", filesystem_struct->PATH_BLOQUES);

	filesystem_struct->PATH_FCB = config_get_string_value(config, "PATH_FCB");
	log_info(logger, "PATH_FCB: %s", filesystem_struct->PATH_FCB);

	filesystem_struct->CANT_BLOQUES_TOTAL = config_get_int_value(config, "CANT_BLOQUES_TOTAL");
	log_info(logger, "CANT_BLOQUES_TOTAL: %i", filesystem_struct->CANT_BLOQUES_TOTAL);

	filesystem_struct->CANT_BLOQUES_SWAP = config_get_int_value(config, "CANT_BLOQUES_SWAP");
	log_info(logger, "CANT_BLOQUES_SWAP: %i", filesystem_struct->CANT_BLOQUES_SWAP);

	filesystem_struct->TAM_BLOQUE = config_get_int_value(config, "TAM_BLOQUE");
	log_info(logger, "TAM_BLOQUE: %i", filesystem_struct->TAM_BLOQUE);

	filesystem_struct->RETARDO_ACCESO_BLOQUE = config_get_int_value(config, "RETARDO_ACCESO_BLOQUE");
	log_info(logger, "RETARDO_ACCESO_BLQOUE: %i", filesystem_struct->RETARDO_ACCESO_BLOQUE);

	filesystem_struct->RETARDO_ACCESO_FAT = config_get_int_value(config, "RETARDO_ACCESO_FAT");
	log_info(logger, "RETARDO_ACCESO_FAT: %i\n", filesystem_struct->RETARDO_ACCESO_FAT);


	return 1;
}
