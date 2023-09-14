#ifndef FILESYSTEM_INCLUDE_INIT_H_
#define FILESYSTEM_INCLUDE_INIT_H_

#include "../../shared/include/config.h"
#include "../../shared/include/logger.h"

t_config_filesystem* datos_filesystem(char* ruta_config, t_log* logger);
t_config_filesystem* cargar_config_filesystem(t_config* config, t_log* logger);

#endif /* FILESYSTEM_INCLUDE_INIT_H_ */
