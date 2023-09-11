#include "../utils/main.h"

#define ARGUMENTOS 2

int main(int argc, char** argv ){
	t_log* logger_kernel;

	if(argc != ARGUMENTOS){
			perror("ERROR EN LA CANTIDAD DE ARGUMENTOS");
			return -1;
	}

	if(!(logger_kernel = iniciar_logger("../kernel.log", "LOGGER_KERNEL")) || iniciar_config(argv[1], logger_kernel, cargar_config_kernel) != 1){
		perror("ERROR AL CARGAR DATOS!!!\n");
		return -1;
	}

	return 0;
}
