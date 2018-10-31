#ifndef	_API_CONSTANT_H
#define _API_CONSTANT_H


#ifdef _WIN32
	#ifdef DLL_EXPORT
		#define FP_API __declspec(dllexport)
	#else
		#define FP_API __declspec(dllimport)
	#endif
#else
	#define FP_API __attribute__((visibility("default")))
#endif


#endif