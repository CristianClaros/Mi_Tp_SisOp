#ifndef SHARED_INCLUDE_LOGGER_H_
#define SHARED_INCLUDE_LOGGER_H_

#include<stdio.h>
#include<string.h>
#include<commons/log.h>
#include<commons/config.h>
#include<stdlib.h>

t_log* iniciar_logger(char* ruta_log, char* name_log);

#endif /* SHARED_INCLUDE_LOGGER_H_ */
