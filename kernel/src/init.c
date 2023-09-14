#include "../include/init.h"

t_config_kernel* cargar_config_kernel(t_config* config, t_log* logger){
	t_config_kernel* kernel_struct = malloc(sizeof(t_config_kernel));

	char* recursos;
	char* instancias;

	kernel_struct->IP_MEMORIA = strdup(config_get_string_value(config, "IP_MEMORIA"));
	log_info(logger, "IP_MEMORIA: %s", kernel_struct->IP_MEMORIA);

	kernel_struct->PUERTO_MEMORIA = strdup(config_get_string_value(config, "PUERTO_MEMORIA"));
	log_info(logger, "PUERTO_MEMORIA: %s", kernel_struct->PUERTO_MEMORIA);

	kernel_struct->IP_FILESYSTEM = strdup(config_get_string_value(config, "IP_FILESYSTEM"));
	log_info(logger, "IP_FILESYSTEM: %s", kernel_struct->IP_FILESYSTEM);

	kernel_struct->PUERTO_FILESYSTEM = strdup(config_get_string_value(config, "PUERTO_FILESYSTEM"));
	log_info(logger, "PUERTO_FILESYSTEM: %s", kernel_struct->PUERTO_FILESYSTEM);

	kernel_struct->IP_CPU = strdup(config_get_string_value(config, "IP_CPU"));
	log_info(logger, "IP_CPU: %s", kernel_struct->IP_CPU);

	kernel_struct->PUERTO_CPU = strdup(config_get_string_value(config, "PUERTO_CPU"));
	log_info(logger, "PUERTO_CPU: %s", kernel_struct->PUERTO_CPU);

	kernel_struct->ALGORITMO_PLANIFICACION = strdup(config_get_string_value(config, "ALGORITMO_PLANIFICACION"));
	log_info(logger, "ALGORITMO_PLANIFICACION: %s", kernel_struct->ALGORITMO_PLANIFICACION);

	kernel_struct->QUANTUM = config_get_int_value(config, "QUANTUM");
	log_info(logger, "QUANTUM: %i", kernel_struct->QUANTUM);

	kernel_struct->RECURSOS = strdup(config_get_array_value(config, "RECURSOS"));

	//Solo sirve para loguear los recursos
	recursos = config_get_string_value(config, "RECURSOS");
	log_info(logger, "RECURSOS: %s", recursos);

	kernel_struct->INSTANCIAS_RECURSOS = strdup(config_get_array_value(config, "INSTANCIAS_RECURSOS"));

	//Solo sirve para loguear las instancias
	instancias = config_get_string_value(config, "INSTANCIAS_RECURSOS");
	log_info(logger, "INSTANCIAS_RECURSOS: %s", instancias);

	kernel_struct->GRADO_MULTIPROGRAMACION_INI = config_get_int_value(config, "GRADO_MULTIPROGRAMACION_INI");
	log_info(logger, "GRADO_MULTIPROGRAMACION_INI: %i\n", kernel_struct->GRADO_MULTIPROGRAMACION_INI);

	return kernel_struct;
}

t_config_kernel* datos_kernel(char* ruta_config, t_log* logger){
	t_config_kernel* kernel_struct;
	t_config* config;


	if((config = iniciar_config(ruta_config, logger))){
		kernel_struct = cargar_config_kernel(config, logger);
		eliminar_config(config, logger);
	}else{
		return NULL;
	}

	return kernel_struct;

}
