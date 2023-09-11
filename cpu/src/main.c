#include "../utils/main.h"

#define ARGUMENTOS 2


int main(int argc, char** argv ){
	t_log* logger_cpu;

	if(argc != ARGUMENTOS){
			perror("ERROR EN LA CANTIDAD DE ARGUMENTOS");
			return -1;
	}

	if(!(logger_cpu = iniciar_logger("../cpu.log", "LOGGER_CPU")) || iniciar_config(argv[1], logger_cpu, cargar_config_cpu) != 1){
		perror("ERROR AL CARGAR DATOS!!!\n");
		return -1;
	}


	return 0;
}
