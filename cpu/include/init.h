#ifndef CPU_INCLUDE_INIT_H_
#define CPU_INCLUDE_INIT_H_

#include "../../shared/include/config.h"
#include "../../shared/include/logger.h"

t_config_cpu* datos_cpu(char* ruta_config, t_log* logger);
t_config_cpu* cargar_config_cpu(t_config* config, t_log* logger);

#endif /* CPU_INCLUDE_INIT_H_ */
