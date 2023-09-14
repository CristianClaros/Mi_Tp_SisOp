#include "../include/main.h"

#define ARGUMENTOS 2

int main(int argc, char** argv ){
	t_log* logger_kernel;
	t_config_kernel* kernel_datos;

	if(argc != ARGUMENTOS){
			perror("ERROR EN LA CANTIDAD DE ARGUMENTOS");
			return -1;
	}

	if(!(logger_kernel = iniciar_logger("../kernel.log", "LOGGER_KERNEL")) || !(kernel_datos = datos_kernel(argv[1],logger_kernel))){
		perror("ERROR AL CARGAR DATOS!!!\n");
		return -1;
	}

	iniciar_kernel(kernel_datos, logger_kernel);

	return 0;
}
