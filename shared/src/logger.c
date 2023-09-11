#include "../utils/logger.h"

t_log* iniciar_logger(char* ruta_log, char* name_log){
	t_log* logger = log_create(ruta_log, name_log, 1, LOG_LEVEL_INFO);

	if(!logger){
		perror("ERROR AL INICIAR EL LOGGER!!\n");
		return NULL;
	}
	log_info(logger, "LOGGER CREADO CORRECTAMENTE!!!\n");

	return logger;
}
