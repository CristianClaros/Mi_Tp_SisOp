#include "../include/main.h"

#define ARGUMENTOS 2


int main(int argc, char** argv ){
	t_log* logger_cpu;
	t_config_cpu* cpu_datos;

	if(argc != ARGUMENTOS){
			perror("ERROR EN LA CANTIDAD DE ARGUMENTOS");
			return -1;
	}

	if(!(logger_cpu = iniciar_logger("../cpu.log", "LOGGER_CPU")) || !(cpu_datos = datos_cpu(argv[1],logger_cpu))){
		perror("ERROR AL CARGAR DATOS!!!\n");
		return -1;
	}


	return 0;
}
