#include "../include/conexion.h"

void crearServidor(t_log* logger, char* name_server, char* ip_server, char* puerto_server, int* socket_server){
    socket_server = iniciar_servidor(logger, name_server, ip_server, puerto_server);

    if (socket_server == -1) {
        log_error(logger, "FALLO AL CREAR EL SERVIDOR, CERRANDO %s", name_server);
    }

    server_escuchar(logger, name_server , socket_server);
//    while (server_escuchar(logger, name_server, socket_server));

}

// INICIA SERVER ESCUCHANDO EN IP:PUERTO
int iniciar_servidor(t_log* logger, const char* name_server, char* ip_server, char* puerto_server){
    int socket_servidor;
    struct addrinfo hints, *servinfo;

    // Inicializando hints
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    // Recibe los addrinfo
    getaddrinfo(ip_server, puerto_server, &hints, &servinfo);

    //Creo un socket servidor
    socket_servidor = 0;

    socket_servidor = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);

    if(socket_servidor == -1){
    	perror("NO PUEDE CREARSE EL SERVIDOR!!!\n");
    }

    if(bind(socket_servidor, servinfo->ai_addr, servinfo->ai_addrlen) == -1){
    	perror("ERROR EN EL BIND!!!\n");
    }

    //Asociamos y escuhamos atraves del puerto
    if(listen(socket_servidor,SOMAXCONN) == -1){
    	perror("ERROR EN EL LISTEN!!!\n");
    }

    freeaddrinfo(servinfo);

    // Aviso al logger
    log_info(logger, "Escuchando en puerto: %s (%s)\n", ip_server, puerto_server, name_server);

    return socket_servidor;
}

int server_escuchar(t_log *logger, char* server_name, int socket_server){
    int cliente_socket = esperar_cliente(logger, server_name, socket_server);

    t_procesar_conexion_args* args = malloc(sizeof(t_procesar_conexion_args));
    args->log = logger;
    args->fd = cliente_socket;
    args->server_name = server_name;

    procesar_conexion(args);

//    if (cliente_socket != -1) {
//        pthread_t atenderProcesoNuevo;
//        t_procesar_conexion_args *args = malloc(sizeof(t_procesar_conexion_args));
//        args->log = logger;
//        args->fd = cliente_socket;
//        args->server_name = server_name;
//        pthread_create(&atenderProcesoNuevo, NULL,procesar_conexion,args);
//        pthread_detach(atenderProcesoNuevo);
//        return 1;
//    }
    return 0;
}

void procesar_conexion(t_procesar_conexion_args* void_args){

    t_log* logger = void_args->log;
    int cliente_socket = void_args->fd;
    char *server_name = void_args->server_name;

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
    int socket_cliente = 0;

    // Fallo en crear el socket
    if((socket_cliente = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol)) == -1) {
        log_info(logger, "ERROR AL CREAR EL SOCKET CLIENTE!!!\n");
        return -1;
    }

    // Error conectando
    if(connect(socket_cliente, servinfo->ai_addr, servinfo->ai_addrlen) == -1) {
        log_error(logger, "Error al conectar (a %s)\n", server_name);
        return 0;
    } else
        log_info(logger, "Cliente conectado en %s:%s (a %s)\n", ip, puerto, server_name);

    freeaddrinfo(servinfo);

    return socket_cliente;
}

// ESPERAR CONEXION DE CLIENTE EN UN SERVER ABIERTO
int esperar_cliente(t_log* logger, const char* name, int socket_servidor){
    int socket_cliente;

    if((socket_cliente = accept(socket_servidor, NULL, NULL)) == -1){
    	perror("ERROR EN EL ACCEPT!!!\n");
    	return -1;
    }

    log_info(logger, "Cliente conectado (a %s)\n", name);

    return socket_cliente;
}

//Conexiones con modulos

int conectar_CPU(t_log* logger, char* server_name, char* ip, char* puerto){

	crear_conexion(logger, server_name, ip, puerto);

	return 1;
}

int conectar_MEMORIA(t_log* logger, char* server_name, char* ip, char* puerto){

	crear_conexion(logger, server_name, ip, puerto);

	return 1;
}

int conectar_FILESYSTEM(t_log* logger, char* server_name, char* ip, char* puerto){

	crear_conexion(logger, server_name, ip, puerto);

	return 1;
}
