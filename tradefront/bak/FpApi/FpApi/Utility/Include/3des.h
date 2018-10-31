#ifndef _3DES__H_  
#define _3DES__H_  
  
#define ENCRYPT 0  
#define DECRYPT 1  
  
#define ECB 0  
#define CBC 1  
  
#define KEY_LEN_8 8  
#define KEY_LEN_16 16  
#define KEY_LEN_24 24  
  
#define PAD_ISO_1   0  
#define PAD_ISO_2   1  
#define PAD_PKCS_7  2 

typedef char (*PSubKey)[16][48];  

int  Crypt_3Des(char* in, int in_len, char *out, int &out_len, char* key,int key_len, char* vi);
int DCrypt_3Des(char* in, int in_len, char *out, int &out_len, char* key,int key_len, char* vi);
int  Crypt_3DesWithBase64(char* in, int in_len, char *out, int &out_len, char* key,int key_len, char* vi);
int DCrypt_3DesWithBase64(char* in, int in_len, char *out, int &out_len, char* key,int key_len, char* vi);

  
#endif  