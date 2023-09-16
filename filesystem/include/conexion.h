#ifndef FILESYSTEM_INCLUDE_CONEXION_H_
#define FILESYSTEM_INCLUDE_CONEXION_H_

#include "../../shared/include/config.h"
#include "../../shared/include/logger.h"
#include "../../shared/include/conexion.h"

int iniciar_filesystem(t_config_filesystem* filesystem_datos, t_log* logger_filesystem);
void procesar_conexion_filesystem(t_procesar_conexion_args* void_args);

#endif /* FILESYSTEM_INCLUDE_CONEXION_H_ */
