#ifndef _LIB_JSON_H_INCLUDED_
#define _LIB_JSON_H_INCLUDED_

#ifdef _USRDLL
	#define JEXPORT   __declspec(dllexport)
#else
	#define JEXPORT
#endif

typedef void * LPJSON;

class IJSonReader
{
public:
	virtual ~IJSonReader() { }

	virtual bool	parse(const char * data) = 0;
	virtual int		get_error_size() = 0;
	virtual const char * get_error() = 0;
	virtual const char * get_value(const char * key) = 0;
	virtual const char * get_value(const char * key, int index) = 0;
	virtual LPJSON       get_root() = 0;

	virtual LPJSON       get_node(LPJSON parent, const char * key) = 0;
	virtual LPJSON       get_node(LPJSON parent, const char * key, int index) = 0;
	virtual const char * get_node_value(LPJSON node) = 0;
	virtual const char * get_json() = 0;
	virtual LPJSON       release()  = 0;
	virtual const char * get_node_name(LPJSON node, int index) = 0;
};

class IJSonWriter
{
public:
	virtual ~IJSonWriter() { }

	virtual bool     add(const char * key, const char * value) = 0;
	virtual bool     add_list(const char * key, int index, const char * value) = 0;
	virtual bool     add_node(const char * key, LPJSON value) = 0;

	virtual const char * get_json() = 0;
	virtual void         set_root(LPJSON root) = 0;
	virtual LPJSON       get_root() = 0;
};

#ifdef __cplusplus
extern "C" {
#endif

	JEXPORT IJSonReader * DTE_CreateJsonReader();
	JEXPORT IJSonWriter * DTE_CreateJsonWriter();

#ifdef __cplusplus
}
#endif

#endif
