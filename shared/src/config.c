#include "../utils/config.h"

int iniciar_config(char* ruta_config, t_log* logger, int (*cargar_config)(t_config* config, t_log* logger)){
	t_config* config = config_create(ruta_config);

	if(!config){
		perror("ERROR AL CREAR EL CONFIG!!!\n");
		return -1;
	}

	if(cargar_config(config, logger) != 1){
		perror("ERROR AL CARGAR DATOS DEL CONFIG!!!\n");
		return -1;
	}

	log_info(logger, "DATOS DEL CONFIG CARGADOS CORRECTAMENTE!!!\n");

	return 1;
}
