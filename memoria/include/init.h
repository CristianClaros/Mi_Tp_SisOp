#ifndef KERNEL_UTILS_INIT_H_
#define KERNEL_UTILS_INIT_H_

#include "../../shared/include/config.h"
#include "../../shared/include/logger.h"

t_config_memoria* datos_memoria(char* ruta_config, t_log* logger);
t_config_memoria* cargar_config_memoria(t_config* config, t_log* logger);

#endif /* KERNEL_UTILS_INIT_H_ */
