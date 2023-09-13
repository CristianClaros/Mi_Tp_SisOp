#include "../include/main.h"

#define ARGUMENTOS 2


int main(int argc, char** argv ){
	t_log* logger_memoria;
	t_config_memoria* memoria_datos;

	if(argc != ARGUMENTOS){
			perror("ERROR EN LA CANTIDAD DE ARGUMENTOS");
			return -1;
	}

	if(!(logger_memoria = iniciar_logger("../memoria.log", "LOGGER_MEMORIA")) || !(memoria_datos = datos_memoria(argv[1],logger_memoria))){
		perror("ERROR AL CARGAR DATOS!!!\n");
		return -1;
	}


	return 0;
}
