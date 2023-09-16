#ifndef MEMORIA_INCLUDE_CONEXION_H_
#define MEMORIA_INCLUDE_CONEXION_H_

#include "../../shared/include/config.h"
#include "../../shared/include/logger.h"
#include "../../shared/include/conexion.h"

int iniciar_memoria(t_config_memoria* cpu_datos, t_log* logger_cpu);
void procesar_conexion_memoria(t_procesar_conexion_args* void_args);

#endif /* MEMORIA_INCLUDE_CONEXION_H_ */
