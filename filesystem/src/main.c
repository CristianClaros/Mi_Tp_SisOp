#include "../utils/main.h"

#define ARGUMENTOS 2


int main(int argc, char** argv ){
	t_log* logger_filesystem;

	if(argc != ARGUMENTOS){
			perror("ERROR EN LA CANTIDAD DE ARGUMENTOS");
			return -1;
	}

	if(!(logger_filesystem = iniciar_logger("../filesystem.log", "LOGGER_FILESYSTEM")) || iniciar_config(argv[1], logger_filesystem, cargar_config_filesystem) != 1){
		perror("ERROR AL CARGAR DATOS!!!\n");
		return -1;
	}


	return 0;
}
