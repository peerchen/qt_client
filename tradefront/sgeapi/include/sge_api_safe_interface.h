#ifndef SGE_API_SAFE_INTERFACE_H
#define SGE_API_SAFE_INTERFACE_H

#undef SGE_API
#ifdef __cplusplus
#define SGE_API extern "C"
#else
#define SGE_API extern
#endif

#ifdef WIN32

#define ssize_t long int

#ifdef API_WIN_EXPORTS
#define SGE_API_EXPORT __declspec(dllexport)
#else
#define SGE_API_EXPORT
#endif

#else //LINUX
#include <sys/types.h>
#define SGE_API_EXPORT
#endif

typedef void * api_safe_handle_t;

/* see the api manual for detail */

/* 
 * key_path: file path of UserKey.key
 * rootcert_path: file path of RootCert.der
 * svr_cert_path: file path of server.der
 * cli_cert_path: file path of UserCert.der
 * passwd: certificate password
 */
SGE_API SGE_API_EXPORT api_safe_handle_t api_safe_init(const char *key_path, const char *rootcert_path, const char *svr_cert_path, const char *cli_cert_path, const char *passwd);

SGE_API SGE_API_EXPORT int api_safe_deinit(api_safe_handle_t handle);

SGE_API SGE_API_EXPORT ssize_t api_safe_create_client_info(api_safe_handle_t handle, char *output, size_t cap);

SGE_API SGE_API_EXPORT int api_safe_check_server_info(api_safe_handle_t handle, const char *input, const size_t real_en_len);

SGE_API SGE_API_EXPORT int api_safe_encrypt(api_safe_handle_t handle, const unsigned char *src, const size_t len, unsigned char *dst, size_t *cap);

SGE_API SGE_API_EXPORT int api_safe_decrypt(api_safe_handle_t handle, const unsigned char *src, const size_t len, unsigned char *dst, size_t *cap);

SGE_API SGE_API_EXPORT const char *api_safe_get_version(api_safe_handle_t handle);
#endif
