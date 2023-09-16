#ifndef CPU_INCLUDE_CONEXION_H_
#define CPU_INCLUDE_CONEXION_H_

#include "../../shared/include/config.h"
#include "../../shared/include/logger.h"
#include "../../shared/include/conexion.h"

int iniciar_cpu(t_config_cpu* cpu_datos, t_log* logger_cpu);
void procesar_conexion_cpu(t_procesar_conexion_args* void_args);

#endif /* CPU_INCLUDE_CONEXION_H_ */
