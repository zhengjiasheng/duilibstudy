#include "stdafx.h"
#include "json_utils.h"
#include "string_utils.h"
#include "libjson/libjson.h"

#pragma comment(lib, "libjson.lib")

#define SAFE_DELETE(x) if ((x)) { delete x; x = NULL; }

////////////////////////////////////////////////////////////
//  class CJsonReader implementation
//

CJsonReader::CJsonReader() : reader_(NULL)
{
}

CJsonReader::~CJsonReader()
{
	this->clear();
}

void CJsonReader::clear()
{
	SAFE_DELETE(reader_);
}

void * CJsonReader::getRoot()
{ 
	if (reader_) 
		return reader_->get_root();

	return NULL; 
}

void * CJsonReader::release()
{ 
	if (reader_) 
		return reader_->release();

	return NULL; 
}

bool CJsonReader::parse(const string & json)
{
	this->clear();

	bool isParse = false;
	if((json.find("{") == 0 && json.find_last_of("}") >= json.length() - 10))
		isParse = true;

	else if((json.find("[") == 0 && json.find_last_of("]") >= json.length() - 10))
		isParse = true;

	if (isParse)
	{
		reader_ = DTE_CreateJsonReader();
		return reader_->parse(json.c_str());
	}

	return false;
}

string CJsonReader::getParam(const string & key)
{
	if (!reader_) return "";

	const char * data = reader_->get_value(key.c_str());
	if (!data) return "";

	return data;
}

int CJsonReader::getParamInt(const string & key, int default_vale)
{
	string value = getParam(key);
	sscanf(value.data(), "%d", &default_vale);

	return default_vale;
}

string CJsonReader::getParam(const string & key,const string & attr)
{
	if (!reader_) return "";

	LPJSON root =  reader_->get_root();

	LPJSON child = reader_->get_node(root, key.c_str());
	if (!child) return "";

	LPJSON json = reader_->get_node(child,  attr.c_str());

	const char * data = reader_->get_node_value(json);
	if (!data) return "";

	return data;
}

string CJsonReader::getParam(const string &key, const string & attr, const int index)
{
	if (!reader_) return "";

	LPJSON root =  reader_->get_root();

	LPJSON child = reader_->get_node(root, key.c_str(), index);
	if (!child) return "";

	LPJSON json = reader_->get_node(child,  attr.c_str());
	if (!json) {
		return "";
	}

	const char * data = reader_->get_node_value(json);
	if (!data) return "";

	return data;
}

string CJsonReader::getParam(const string &key, const string & attr1, const int index1, const string & attr2, const int index2)
{
	if (!reader_) return "";

	LPJSON root =  reader_->get_root();

	LPJSON child1 = reader_->get_node(root, key.c_str(), index1);
	if (!child1) return "";

	LPJSON child2 = reader_->get_node(child1, attr1.c_str(), index2);
	if (!child2) return "";

	LPJSON json = reader_->get_node(child2,  attr2.c_str());
	if (!json) {
		return "";
	}
	
	const char * data = reader_->get_node_value(json);
	if (!data) return "";

	return data;
}

string CJsonReader::getParamCommon(const string &key, const string & attr, const int index)
{
	if (!reader_) return "";

	LPJSON root =  reader_->get_root();

	LPJSON child = reader_->get_node(root, key.c_str(), index);
	if (!child) return "";

	LPJSON json = reader_->get_node(child,  attr.c_str());
	if (!json) {
		return "";
	}

	const char * data = reader_->get_node_value(json);
	if (!data) return "";

	return data;
}

string CJsonReader::getParamCommon(const string &key, const string & attr, const int index, const string &ckey, const int cindex)
{
	if (!reader_) return "";

	LPJSON root = reader_->get_root();

	LPJSON child = reader_->get_node(root, key.c_str(), index);
	if (!child) return "";

	LPJSON array = reader_->get_node(child, attr.c_str());
	if (!array) {
		return "";
	}

	LPJSON json = reader_->get_node(array, ckey.c_str(), cindex);

	const char * data = reader_->get_node_value(json);
	if (!data) return "";

	return data;
}

void * CJsonReader::getParam2Node(const string &key, const string & attr, const int index)
{
	if (!reader_) return NULL;

	LPJSON root =  reader_->get_root();

	LPJSON child = reader_->get_node(root, key.c_str(), index);
	if (!child) return NULL;

	LPJSON json = reader_->get_node(child,  attr.c_str());

	return json;
}

string CJsonReader::getParamNode(void * node, const string & attr, const int index)
{
	if (!node) return "";

	LPJSON child = reader_->get_node(node, attr.c_str(), index);

	const char * data = reader_->get_node_value(child);
	if (!data) return "";

	return data;
}

LPJSON 	CJsonReader::getNode(LPJSON parent, const char * key)
{
	if (!reader_) return NULL;
	return reader_->get_node(parent, key);
}

LPJSON 	CJsonReader::getNode(LPJSON parent, const char * key, int index)
{
	if (!reader_) return NULL;
	return reader_->get_node(parent, key, index);
}

const char * CJsonReader::getNodeValue(LPJSON node)
{
	if (!reader_) return NULL;
	return reader_->get_node_value(node);
}
const char * CJsonReader::getNodeName(void * node, int index)
{
	if (!reader_) return NULL;
	return reader_->get_node_name(node, index);
}

////////////////////////////////////////////////////////////
//  class CJSonWriter implementation
//

CJSonWriter::CJSonWriter() : writer_(NULL)
{
	writer_ = DTE_CreateJsonWriter();
}

CJSonWriter::~CJSonWriter()
{
	this->clear();
}

void CJSonWriter::clear()
{
	SAFE_DELETE(writer_);
}

void CJSonWriter::add(const char * key, const char * value)
{
	if (writer_) writer_->add(key, value);
}

void CJSonWriter::addList(const char * key, int index, const char * value)
{
	if (writer_) writer_->add_list(key, index, value);
}

string CJSonWriter::getJson()
{
	string json;
	if (writer_)
		json = writer_->get_json();

	CTextUtils::replace(json, "\n", "");

	return json;
}

void CJSonWriter::setRoot(void* root)
{
	if (writer_ && root)
		writer_->set_root(root);
}

void * CJSonWriter::getRoot()
{
	if (writer_)
		return writer_->get_root();
	return NULL;
}

void CJSonWriter::setJson(const char * json)
{
	if (!json) return;

	CJsonReader reader;
	reader.parse(json);
	void * p = reader.getRoot();

	if (p) setRoot(p);
}

void CJSonWriter::addNode(const char* key, void* data)
{
	if (!data) return;

	if (writer_) writer_->add_node(key, (LPJSON)data);
}
