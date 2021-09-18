#ifndef __JSON_UTIL_H__
#define __JSON_UTIL_H__

#include <map>
#include <string>
using namespace std;

class IJSonReader;
class IJSonWriter;

class CJsonReader
{
public:
	CJsonReader();
	virtual ~CJsonReader();

	bool			parse(const string & json);
	string			getParam(const string & key);
	int			    getParamInt(const string & key, int default_vale = 0);
	string			getParam(const string & key,const string & attr);
	string			getParam(const string &key, const string & attr, const int index);
	string			getParam(const string &key, const string & attr1, const int index1, const string & attr2, const int index2);
	string			getParamCommon(const string &key, const string & attr, const int index);
	string			getParamCommon(const string &key, const string & attr, const int index, const string &ckey, const int cindex);
	void *          getParam2Node(const string &key, const string & attr, const int index);
	string          getParamNode(void * node, const string & attr, const int index);
	IJSonReader *	getJsonReader() { return reader_; }
	void *          getRoot();
	void *			release();

	void *			getNode(void * parent, const char * key);
	void *			getNode(void * parent, const char * key, int index);
	const char *	getNodeValue(void * node);
	const char*     getNodeName(void* node, int index);


private:
	void            clear();
	
private:
	IJSonReader *  reader_;
};

class CJSonWriter
{
public:
	CJSonWriter();
	virtual ~CJSonWriter();

	void     add(const char * key, const char * value);
	void     addList(const char * key, int index, const char * value);
	void     addNode(const char* key, void* data);
	string   getJson();
	void     setRoot(void* root);
	void     setJson(const char * json);
	void *   getRoot();

private:
	void     clear();

private:
	IJSonWriter *  writer_;
};

#endif
