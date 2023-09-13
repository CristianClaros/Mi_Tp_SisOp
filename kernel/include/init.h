#ifndef KERNEL_INCLUDE_INIT_H_
#define KERNEL_INCLUDE_INIT_H_

#include "../../shared/include/config.h"
#include "../../shared/include/logger.h"

t_config_kernel* datos_kernel(char* ruta_config, t_log* logger);
t_config_kernel* cargar_config_kernel(t_config* config, t_log* logger);

#endif /* KERNEL_INCLUDE_INIT_H_ */
