#include "../utils/init.h"

int cargar_config_cpu(t_config* config, t_log* logger){
	t_config_cpu* cpu_struct = malloc(sizeof(t_config_cpu));


	cpu_struct->IP_MEMORIA = config_get_string_value(config, "IP_MEMORIA");
	log_info(logger, "IP_MEMORIA: %s", cpu_struct->IP_MEMORIA);

	cpu_struct->PUERTO_MEMORIA = config_get_int_value(config, "PUERTO_MEMORIA");
	log_info(logger, "PUERTO_MEMORIA: %i", cpu_struct->PUERTO_MEMORIA);

	cpu_struct->PUERTO_ESCUCHA_DISPATCH = config_get_int_value(config, "PUERTO_ESCUCHA_DISPATCH");
	log_info(logger, "PUERTO_ESCUCHA_DISPATCH: %i", cpu_struct->PUERTO_ESCUCHA_DISPATCH);

	cpu_struct->PUERTO_ESCUCHA_DISPATCH = config_get_int_value(config, "PUERTO_ESCUCHA_INTERRUPT");
	log_info(logger, "PUERTO_ESCUCHA_INTERRUPT: %i\n", cpu_struct->PUERTO_ESCUCHA_DISPATCH);

	return 1;
}
