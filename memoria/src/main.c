#include "../utils/main.h"

#define ARGUMENTOS 2


int main(int argc, char** argv ){
	t_log* logger_memoria;

	if(argc != ARGUMENTOS){
			perror("ERROR EN LA CANTIDAD DE ARGUMENTOS");
			return -1;
	}

	if(!(logger_memoria = iniciar_logger("../memoria.log", "LOGGER_MEMORIA")) || iniciar_config(argv[1], logger_memoria, cargar_config_memoria) != 1){
		perror("ERROR AL CARGAR DATOS!!!\n");
		return -1;
	}


	return 0;
}
