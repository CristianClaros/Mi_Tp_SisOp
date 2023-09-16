#ifndef SHARED_INCLUDE_ESTRUCTURAS_H_
#define SHARED_INCLUDE_ESTRUCTURAS_H_

#include <commons/collections/list.h>
#include <commons/collections/queue.h>
#include <semaphore.h>
#include <malloc.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>


typedef enum
{
    //----------------BASICOS--------------------------------
    HANDSHAKE = 1,
    //-------------MENSAJES ENTRE CONSOLA-KERNEL------------------------------------
    GESTIONAR_CONSOLA_NUEVA = 0,
    SOLICITAR_VALOR,
    IMPRIMIR_VALOR,
    PROCESO_TERMINADO,
    //------------------------------------------------------------------------------
    //-------------MENSAJES SERIALIZACION GLOBALES---------------------------------
    PAQUETE = 4,
    MENSAJE = 5,
    PCB = 30,
    //MENSAJES KERNEL - MEMORIA
    TABLA_SEGMENTOS_INICIAL,
    //-------------MENSAJES MEMORIA - KERNEL---------------------------------
    PROCESO_INICIADO,
    CREAR_SEGMENTO,
    SEGMENTO_CREADO,
    ESPACIO_INSUFICIENTE,
    COMPACTACION,
    BORRAR_SEGMENTO
} op_code;


#endif /* SHARED_INCLUDE_ESTRUCTURAS_H_ */
