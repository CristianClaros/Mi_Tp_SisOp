#include "../include/conexion.h"

void* crearServidor(t_log* logger, char* name_server, char* ip_server, int puerto_server, int puerto, int socket){
    puerto_server = puerto;
    socket = iniciar_servidor(logger, name_server, ip_server, puerto_server);
    if (socket == 0) {
        log_error(logger, "FALLO AL CREAR EL SERVIDOR, CERRANDO %s", name_server);
        return -1;
    }

    while (server_escuchar(logger, name_server, socket));

    return 1;
}

// INICIA SERVER ESCUCHANDO EN IP:PUERTO
int iniciar_servidor(t_log* logger, const char* name, char* ip, char* puerto){
    int socket_servidor;
    struct addrinfo hints, *servinfo;

    // Inicializando hints
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    // Recibe los addrinfo
    getaddrinfo(ip, puerto, &hints, &servinfo);

    bool conecto = false;

    // Itera por cada addrinfo devuelto
    for (struct addrinfo *p = servinfo; p != NULL; p = p->ai_next) {
        socket_servidor = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (socket_servidor == -1) // fallo de crear socket
            continue;
        int yes=1;
        setsockopt(socket_servidor, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes);
        if (bind(socket_servidor, p->ai_addr, p->ai_addrlen) == -1) {
            // Si entra aca fallo el bind
            perror("ERROR EN EL BIND!!!\n");
            close(socket_servidor);
            continue;
        }
        // Ni bien conecta uno nos vamos del for
        conecto = true;
        break;
    }

    if(!conecto) {
        free(servinfo);
        return 0;
    }

    listen(socket_servidor, SOMAXCONN); // Escuchando (hasta SOMAXCONN conexiones simultaneas)

    // Aviso al logger
    log_info(logger, "Escuchando en puerto: %s (%s)\n", ip, puerto, name);

    freeaddrinfo(servinfo);

    return socket_servidor;
}

int server_escuchar(t_log *logger, char *server_name, int server_socket){
    int cliente_socket = esperar_cliente(logger, server_name, server_socket);

    if (cliente_socket != -1) {
        pthread_t atenderProcesoNuevo;
        t_procesar_conexion_args *args = malloc(sizeof(t_procesar_conexion_args));
        args->log = logger;
        args->fd = cliente_socket;
        args->server_name = server_name;
        pthread_create(&atenderProcesoNuevo, NULL,procesar_conexion,args);
        pthread_detach(atenderProcesoNuevo);
        return 1;
    }
    return 0;
}

void procesar_conexion(void *void_args){
    t_procesar_conexion_args *args = (t_procesar_conexion_args *) void_args;
    t_log* logger = args->log;
    int cliente_socket = args->fd;
    char *server_name = args->server_name;
    free(args);

    op_code cop;
    while (cliente_socket != -1) {

        if (recv(cliente_socket, &cop, sizeof(op_code), 0) != sizeof(op_code)) {
            log_info(logger, "DISCONNECT!");
            return;
        }

        switch (cop) {
            //----------------------------------------CONSOLA-----------------------
            case GESTIONAR_CONSOLA_NUEVA:
            {
                pthread_t procesoNuevo;
                /*t_procesar_fd_conexion* conexion = malloc(sizeof(t_procesar_fd_conexion));
                conexion->conexion = cliente_socket;*/
//                pthread_create(&procesoNuevo,NULL, atenderProcesoNuevo,cliente_socket);
//                pthread_join(procesoNuevo, NULL);
//                atenderProcesoNuevo(conexion->conexion);

                log_info(logger,"INSTRUCCIONES LISTAS");
                break;
            }

                //----------------------------------MEMORIA----------------------------------------
            case TABLA_SEGMENTOS_INICIAL:
            {
                //ACA SE RECIBIRIA LA BASE DEL SEGMENTO COMPARTIDO DONDE ESTA
//                pthread_mutex_lock(&BASE_INICIAL);
//                base_segmento_0 = recibir_base_segmento_0(cliente_socket);
                //HAY QUE ASIGNAR ESA BASE AL PROCESO.
                break;
            }
            case CREAR_SEGMENTO:
            {
                //El Kernel deberá enviarle a la Memoria el mensaje para crear un segmento con el tamaño definido
                break;
            }
            case SEGMENTO_CREADO:
            {
                //El segmento se creo exitosamente y la memoria nos devuelvio la base del nuevo segmento.
                break;
            }
            case ESPACIO_INSUFICIENTE:
            {
                //No se tiene más espacio disponible en la memoria y por lo tanto el proceso tiene que finalizar con error Out of Memory.
                break;
            }
            case COMPACTACION:
            {
                /*Se tiene el espacio disponible, pero el mismo no se encuentra contiguo,
                  por lo que se debe compactar, este caso lo vamos a analizar más en detalle,
                  ya que involucra controlar las operaciones de File System que se estén ejecutando.*/
                break;
            }
            case BORRAR_SEGMENTO:
            {
                /*Para realizar un DELETE_SEGMENT, el Kernel deberá enviarle a la Memoria el Id del
                  segmento a eliminar y recibirá como respuesta de la Memoria la tabla de segmentos actualizada.
                  Nota: No se solicitará nunca la eliminación del segmento 0 o de un segmento inexistente.*/
                break;
            }
            case -1:
                log_error(logger, "Cliente desconectado de %s...", server_name);
                return;
            default:
                log_error(logger, "Algo anduvo mal en el server de %s", server_name);
                log_info(logger, "Cop: %d", cop);
                return;
        }
    }

    log_warning(logger, "El cliente se desconecto de %s server", server_name);
    return;
}

int crear_conexion(t_log* logger, const char* server_name, char* ip, char* puerto){
    struct addrinfo hints, *servinfo;

    // Init de hints
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    // Recibe addrinfo
    getaddrinfo(ip, puerto, &hints, &servinfo);

    // Crea un socket con la informacion recibida (del primero, suficiente)
    int socket_cliente = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
    int yes=1;
    setsockopt(socket_cliente, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes);
    // Fallo en crear el socket
    if(socket_cliente == -1) {
        log_error(logger, "Error creando el socket para %s", ip, puerto);
        log_error(logger, "y puerto %s", puerto);
        //freeaddrinfo(servinfo);
        return 0;
    }

    // Error conectando
    if(connect(socket_cliente, servinfo->ai_addr, servinfo->ai_addrlen) == -1) {
        log_error(logger, "Error al conectar (a %s)\n", server_name);
        freeaddrinfo(servinfo);
        return 0;
    } else
        log_info(logger, "Cliente conectado en %s:%s (a %s)\n", ip, puerto, server_name);

    freeaddrinfo(servinfo);

    return socket_cliente;
}

// ESPERAR CONEXION DE CLIENTE EN UN SERVER ABIERTO
int esperar_cliente(t_log* logger, const char* name, int socket_servidor){
    struct sockaddr_in dir_cliente;
    socklen_t tam_direccion = sizeof(struct sockaddr_in);

    int socket_cliente = accept(socket_servidor, (void*) &dir_cliente, &tam_direccion);

    log_info(logger, "Cliente conectado (a %s)\n", name);

    return socket_cliente;
}

//void generarConexionesConCPU(){
//    char* ip;
//
//    ip = strdup(cfg_kernel->IP_CPU);
//    log_info(logger_kernel,"Lei la ip %s", ip);
//
//    char* puertoDispatch;
//    puertoDispatch = strdup(cfg_kernel->PUERTO_CPU);
//
//    log_info(logger_kernel,"Lei el puerto %s", puertoDispatch);
//
//    fd_dispatch = crear_conexion(
//            logger_kernel,
//            "SERVER CPU DISPATCH",
//            ip,
//            puertoDispatch
//    );
//}

