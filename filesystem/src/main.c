#include "../include/main.h"

#define ARGUMENTOS 2


int main(int argc, char** argv ){
	t_log* logger_filesystem;
	t_config_filesystem* filesystem_datos;

	if(argc != ARGUMENTOS){
			perror("ERROR EN LA CANTIDAD DE ARGUMENTOS");
			return -1;
	}

	if(!(logger_filesystem = iniciar_logger("../filesystem.log", "LOGGER_FILESYSTEM")) || !(filesystem_datos = datos_filesystem(argv[1],logger_filesystem))){
		perror("ERROR AL CARGAR DATOS!!!\n");
		return -1;
	}


	return 0;
}
