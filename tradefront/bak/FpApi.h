#ifndef	SIGEX_API_H
#define	SIGEX_API_H

#include "ApiConstant.h"
#ifdef __cplusplus
	extern "C"
	{
#endif

		typedef struct API_CALLBACK_
		{

			//----------------------------------------------------------------
			//�������ܣ�socket���ӳɹ�ʱ֪ͨ
			//����������� 
			//�� ��	ֵ����
			void ( *on_fp_api_connect )( void *paramter );

			//----------------------------------------------------------------
			//�������ܣ�socket�����쳣�Ͽ�ʱ֪ͨ
			//����������� 
			//�� ��	ֵ����
			void ( *on_fp_api_connect_lost )( void *paramter );

			//----------------------------------------------------------------
			//�������ܣ��㲥socket���ӳɹ�ʱ֪ͨ
			//����������� 
			//�� ��	ֵ����
			void ( *on_fp_api_exception )( const char *exception_code, const char *exception_msg, void *paramter );

			//----------------------------------------------------------------
			//�������ܣ��յ�����
			//���������Gtp��ʽ����
			//�� ��	ֵ����
			void ( *on_fp_api_recv_msg )( const char *packet, void *paramter );

		}API_CALLBACK;

		int FP_API fp_api_init( const char   *ip,           //ǰ�õ�ַ
								const int    port,          //ǰ�ö˿�
								API_CALLBACK *api_callback, //�ص�����
								const char   *private_cert_path,    //˽Կ֤��·��
								const char   *public_cert_path,     //��Կ֤��·��
								const char   *public_server_cert_path,//��������Կ֤��·��
								const char   *private_cert_password,//˽Կ֤������
								const char   *cert_cert_path,       //��֤������
								void         *paramter );

		void FP_API fp_api_wait();

		int FP_API fp_api_send_msg( const char *head, const char *body );

		const char FP_API*fp_api_get_version( );

		void FP_API fp_api_free();

		int FP_API fp_api_set_recv_timeout( long long rt);

		long long FP_API fp_api_get_recv_timeout();

		int FP_API fp_api_set_send_timeout( long long wt);

		long long FP_API fp_api_get_send_timeout();

		int FP_API fp_api_log_start( const char * tname );

		void FP_API fp_api_log_end(void);
#ifdef __cplusplus
	}
#endif
#endif
