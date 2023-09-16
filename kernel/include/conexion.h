#ifndef KERNEL_INCLUDE_CONEXION_H_
#define KERNEL_INCLUDE_CONEXION_H_

#include "../../shared/include/config.h"
#include "../../shared/include/logger.h"
#include "../../shared/include/conexion.h"

int iniciar_kernel(t_config_kernel* kernel_datos, t_log* logger_kernel);
void procesar_conexion_kernel(t_procesar_conexion_args* void_args);

#endif /* KERNEL_INCLUDE_CONEXION_H_ */
