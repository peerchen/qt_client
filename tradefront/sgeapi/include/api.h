#ifndef __API_H__
#define __API_H__

#ifdef __cplusplus
#define SGE_API extern "C" 
#else
#define SGE_API extern
#endif

#ifdef WIN32

#ifdef DLL_EXPORT
    #define DLL_DECLARE  __declspec(dllexport)
#else
    #define DLL_DECLARE  __declspec(dllimport)
#endif

#else  //Linux
    #define DLL_DECLARE
#endif

//recv msg type from server
#define GTP_TYPE_STRING     1
#define GTP_TYPE_ENCRYPT    4

#define IS_CONNECTED              1
#define IS_ERROR_DISCONNECTED     2
#define IS_ACTIVE_DISCONNECTED    3 

typedef struct api api_t;

typedef struct {
    char ip[32];
    int port;
    int state;
} api_connection_state_t;

typedef struct {
    /**
     * api_recv_msg_ recv msg callback by api
     *
     * @param msg recv msg(gtp) from server
     * @param type recv msg(gtp) type from server 
     * @param con_len recv msg (gtp) len of the recv msg
     *
     * @return 
     *
     */
    void (* api_recv_msg_)(const char * msg, int type, unsigned int con_len, void * ctx);

    /**
     * api_cb_connected, callback if the connection is connected
     *
     * @param cs 	the status of the connection
	 * @param ctx	the ctx ptr , set from the api init
	 * @return
     */
    void (* api_cb_connected_)(api_connection_state_t * cs, void * ctx);

    /**
     * api_cb_disconnect, callback if the connection is disconnected
     *
     * @param cs 	the status of the connection
	 * @param ctx	the ctx ptr , set from the api init
     *
	 * @return
     */
    void (* api_cb_disconnected_)(api_connection_state_t * cs, void * ctx);
} api_cb_t;

/**
 * api_init: 	initialize of api
 *
 * @param ip:   ip address of server side
 * @param port: port of the dest server
 * @param cb:   struct pointer of callback struct, see the struct describe for detail
 * @param ctx:	context struct to all callback functions
 *
 * @return api_t*: success
 *           NULL: failed
 */
SGE_API DLL_DECLARE api_t * api_init(const char * ip, int port, api_cb_t * cb, void * ctx);

/**
 * api_wait: 	wait the api
 *
 * @param api:  api struct pointer
 *
 * @return void
 */
SGE_API DLL_DECLARE void api_wait(api_t * api);


/**
 * api_stop: 	stop the api
 *
 * @param api:  api struct pointer
 *
 * @return void
 */
SGE_API DLL_DECLARE void api_stop(api_t * api);

/**
 * api_free: free resource of api
 *
 * @param api: api struct pointer
 *
 * @return void
 */
SGE_API DLL_DECLARE void api_free(api_t * api);

/**
 * api_send_msg: 	send the encrypted msg to server
 *
 * @param api       api struct pointer
 * @param encrypted_msg   encrypted msg
 * @param len   	msg len of encrypted msg
 *
 * @return  0: success
 *         -1: error parameters
 *         -2: allocate memory failed
 *         -4: no connect with server
 */
SGE_API DLL_DECLARE int api_send_msg(api_t * api, const char * encrypted_msg, unsigned int len);

/**
 * api_send_msg_no_enc:		send the plan msg to server
 *
 * @param api     				api struct pointer
 * @param plain_gtp_msg plain 	gtp msg to send to server
 * @param len   				len of the gtp msg
 *
 * @return  0: success
 *         -1: error parameters
 *         -2: allocate memory failed
 *         -4: no connect with server
 */
SGE_API DLL_DECLARE int api_send_msg_no_enc(api_t * api, const char * plain_gtp_msg, unsigned int len);

/**
 * api_get_version:	get the api version info
 *
 * @param api 		api struct pointer
 *
 * @return  NOT NULL:  version string of the api   
 *          NULL	:  got error
 */
SGE_API DLL_DECLARE char * api_get_version(api_t * api);

/**
 * api_thread_begin		init the custome created thread log object
 *
 * @param api			api struct pointer
 * @param tname			the sub name of the log file
 *
 * @retrun  0: success
 *         -1: failed
 */
SGE_API DLL_DECLARE int api_thread_begin(api_t * api, const char * tname);

/**
 * api_thread_end		free the thread log
 *
 * @param api_t			api struct pointer			
 *
 * @return  0: success
 *         -1: error parameters	
 */
SGE_API DLL_DECLARE int api_thread_end(api_t * api);

/**
 * api_disconnect		flash disconnect, disconnect it and connect agian automatically
 *
 * @param api 	api struct pointer
 *
 * @return  0: success
 *         -1: error parameters
 */
SGE_API DLL_DECLARE int api_disconnect(api_t * api);

/**
 * api_set_endpoint      set the new ip & port  for api, just set the value; 
 *                          Note: you need to break the current connection use(api_disconnect) to effect the new ip & port
 *
 * @param api 	        api struct pointer
 * @param remote_ip 	remote ip 
 * @param remote_port 	remote port
 *
 * @return  0: success
 *         -1: error parameters
 */
SGE_API DLL_DECLARE int api_set_new_endpoint(api_t * api, const char * remote_ip , int remote_port);

/**
 * api_is_running      get the server running status
 *
 * @param api 	        api struct pointer
 *
 * @return   0: not running 
 *          ~0: running
 */
SGE_API DLL_DECLARE int api_is_running(api_t * api);


/**
 * api_get_ip:	get the current connecting remote ip of api
 *
 * @param api 		api struct pointer
 *
 * @return  NOT NULL:  ip of current connecting remote host
 *          NULL	:  got error
 */
SGE_API DLL_DECLARE const char *  api_get_ip(api_t * api);
/**
 * api_get_port:	get the current connecting remote port of api
 *
 * @param api 		api struct pointer
 *
 * @return >=0:     port of current connecting remote host
 *          -1:     error parameters
 */
SGE_API DLL_DECLARE int api_get_port(api_t * api);
#endif  /* __API_H__ */

