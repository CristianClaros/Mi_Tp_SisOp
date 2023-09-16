#include "../include/conexion.h"

void crearServidor(t_log* logger, char* name_server, char* ip_server, char* puerto_server, int* socket_server, void (*procesar_conexion)(t_procesar_conexion_args* args)){
    socket_server = iniciar_servidor(logger, name_server, ip_server, puerto_server);

    if (socket_server == -1) {
        log_error(logger, "FALLO AL CREAR EL SERVIDOR, CERRANDO %s", name_server);
    }

    server_escuchar(logger, name_server , socket_server,procesar_conexion);
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

int server_escuchar(t_log *logger, char* server_name, int socket_server, void (*procesar_conexion)(t_procesar_conexion_args* args)){
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

//void procesar_conexion(t_procesar_conexion_args* void_args){
//
//    t_log* logger = void_args->log;
//    int cliente_socket = void_args->fd;
//    char *server_name = void_args->server_name;
//
//    op_code cop;
//    while (cliente_socket != -1) {
//
//        if (recv(cliente_socket, &cop, sizeof(op_code), 0) != sizeof(op_code)) {
//            log_info(logger, "DISCONNECT!");
//            return;
//        }
//
//        switch (cop) {
//            //----------------------------------------CONSOLA-----------------------
//            case GESTIONAR_CONSOLA_NUEVA:
//            {
//                pthread_t procesoNuevo;
//                /*t_procesar_fd_conexion* conexion = malloc(sizeof(t_procesar_fd_conexion));
//                conexion->conexion = cliente_socket;*/
////                pthread_create(&procesoNuevo,NULL, atenderProcesoNuevo,cliente_socket);
////                pthread_join(procesoNuevo, NULL);
////                atenderProcesoNuevo(conexion->conexion);
//
//                log_info(logger,"INSTRUCCIONES LISTAS");
//                break;
//            }
//
//                //----------------------------------MEMORIA----------------------------------------
//            case TABLA_SEGMENTOS_INICIAL:
//            {
//                //ACA SE RECIBIRIA LA BASE DEL SEGMENTO COMPARTIDO DONDE ESTA
////                pthread_mutex_lock(&BASE_INICIAL);
////                base_segmento_0 = recibir_base_segmento_0(cliente_socket);
//                //HAY QUE ASIGNAR ESA BASE AL PROCESO.
//                break;
//            }
//            case CREAR_SEGMENTO:
//            {
//                //El Kernel deberá enviarle a la Memoria el mensaje para crear un segmento con el tamaño definido
//                break;
//            }
//            case SEGMENTO_CREADO:
//            {
//                //El segmento se creo exitosamente y la memoria nos devuelvio la base del nuevo segmento.
//                break;
//            }
//            case ESPACIO_INSUFICIENTE:
//            {
//                //No se tiene más espacio disponible en la memoria y por lo tanto el proceso tiene que finalizar con error Out of Memory.
//                break;
//            }
//            case COMPACTACION:
//            {
//                /*Se tiene el espacio disponible, pero el mismo no se encuentra contiguo,
//                  por lo que se debe compactar, este caso lo vamos a analizar más en detalle,
//                  ya que involucra controlar las operaciones de File System que se estén ejecutando.*/
//                break;
//            }
//            case BORRAR_SEGMENTO:
//            {
//                /*Para realizar un DELETE_SEGMENT, el Kernel deberá enviarle a la Memoria el Id del
//                  segmento a eliminar y recibirá como respuesta de la Memoria la tabla de segmentos actualizada.
//                  Nota: No se solicitará nunca la eliminación del segmento 0 o de un segmento inexistente.*/
//                break;
//            }
//            case -1:
//                log_error(logger, "Cliente desconectado de %s...", server_name);
//                return;
//            default:
//                log_error(logger, "Algo anduvo mal en el server de %s", server_name);
//                log_info(logger, "Cop: %d", cop);
//                return;
//        }
//    }
//
//    log_warning(logger, "El cliente se desconecto de %s server", server_name);
//    return;
//}

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

//PAQUETES ENVIO

void enviar_mensaje(char* mensaje, int socket_cliente)
{
	t_paquete* paquete = malloc(sizeof(t_paquete));

	paquete->codigo_operacion = MENSAJE;
	paquete->buffer = malloc(sizeof(t_buffer));
	paquete->buffer->size = strlen(mensaje) + 1;
	paquete->buffer->stream = malloc(paquete->buffer->size);
	memcpy(paquete->buffer->stream, mensaje, paquete->buffer->size);

	int bytes = paquete->buffer->size + 2*sizeof(int);

	void* a_enviar = serializar_paquete(paquete, bytes);

	send(socket_cliente, a_enviar, bytes, 0);

	free(a_enviar);
	eliminar_paquete(paquete);
}

void* serializar_paquete(t_paquete* paquete, int bytes)
{
	void * magic = malloc(bytes);
	int desplazamiento = 0;

	memcpy(magic + desplazamiento, &(paquete->codigo_operacion), sizeof(int));
	desplazamiento+= sizeof(int);
	memcpy(magic + desplazamiento, &(paquete->buffer->size), sizeof(int));
	desplazamiento+= sizeof(int);
	memcpy(magic + desplazamiento, paquete->buffer->stream, paquete->buffer->size);
	desplazamiento+= paquete->buffer->size;

	return magic;
}

void crear_buffer(t_paquete* paquete)
{
	paquete->buffer = malloc(sizeof(t_buffer));
	paquete->buffer->size = 0;
	paquete->buffer->stream = NULL;
}

t_paquete* crear_paquete(void)
{
	t_paquete* paquete = malloc(sizeof(t_paquete));
	paquete->codigo_operacion = PAQUETE;
	crear_buffer(paquete);
	return paquete;
}

void agregar_a_paquete(t_paquete* paquete, void* valor, int tamanio)
{
	paquete->buffer->stream = realloc(paquete->buffer->stream, paquete->buffer->size + tamanio + sizeof(int));

	memcpy(paquete->buffer->stream + paquete->buffer->size, &tamanio, sizeof(int));
	memcpy(paquete->buffer->stream + paquete->buffer->size + sizeof(int), valor, tamanio);

	paquete->buffer->size += tamanio + sizeof(int);
}

void enviar_paquete(t_paquete* paquete, int socket_cliente)
{
	int bytes = paquete->buffer->size + 2*sizeof(int);
	void* a_enviar = serializar_paquete(paquete, bytes);

	send(socket_cliente, a_enviar, bytes, 0);

	free(a_enviar);
}

void eliminar_paquete(t_paquete* paquete)
{
	free(paquete->buffer->stream);
	free(paquete->buffer);
	free(paquete);
}

void liberar_conexion(int socket_cliente)
{
	close(socket_cliente);
}


//PAQUETE RECEPCION
int recibir_operacion(int socket_cliente)
{
	int cod_op;
	if(recv(socket_cliente, &cod_op, sizeof(int), MSG_WAITALL) > 0)
		return cod_op;
	else
	{
		close(socket_cliente);
		return -1;
	}
}

void* recibir_buffer(int* size, int socket_cliente)
{
	void * buffer;

	recv(socket_cliente, size, sizeof(int), MSG_WAITALL);
	buffer = malloc(*size);
	recv(socket_cliente, buffer, *size, MSG_WAITALL);

	return buffer;
}

void recibir_mensaje(int socket_cliente)
{
	int size;
	char* buffer = recibir_buffer(&size, socket_cliente);
//	log_info(logger, "Me llego el mensaje %s", buffer);
	free(buffer);
}

t_list* recibir_paquete(int socket_cliente)
{
	int size;
	int desplazamiento = 0;
	void * buffer;
	t_list* valores = list_create();
	int tamanio;

	buffer = recibir_buffer(&size, socket_cliente);
	while(desplazamiento < size)
	{
		memcpy(&tamanio, buffer + desplazamiento, sizeof(int));
		desplazamiento+=sizeof(int);
		char* valor = malloc(tamanio);
		memcpy(valor, buffer+desplazamiento, tamanio);
		desplazamiento+=tamanio;
		list_add(valores, valor);
	}
	free(buffer);
	return valores;
}


