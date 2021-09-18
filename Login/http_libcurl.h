#ifndef _HTTP_LIBCURL_
#define _HTTP_LIBCURL_

#include<Windows.h>
#include<curl/curl.h>
#include <string> 
#include<iostream>

#pragma comment(lib, "libcurl.lib")   

using namespace std;

// reply of the requery 
static size_t req_reply(void *ptr, size_t size, size_t nmemb, void *stream);  
// http GET 
static CURLcode curl_get_req(const std::string &url, std::string &response); 
// http POST  
static CURLcode curl_post_req(const string &url, const string &postParams, string &response);
//UTF8תGBK/GB2312
static string UTF8ToGBK(const char* strUTF8);
//GBK/GB2312תUTF8
static string GBKToUTF8(const char* strGBK);


// reply of the requery  
static size_t req_reply(void *ptr, size_t size, size_t nmemb, void *stream)  
{  
    cout << "----->reply" << endl;  
    string *str = (string*)stream;  
    cout << *str << endl;  
    (*str).append((char*)ptr, size*nmemb);  
    return size * nmemb;  
}  

/*
���������е�&��ʾ���ã�����ʵ�Σ�������ʵ�ε�һ���������������ñ������൱�ڲ���ʵ�α���
&�ڱ�������������ʾȡ��ַ����
&�ڱ�������������ʾ���á����ó����ں��������У�����������ʹ�������൱�ڰ�ʵ����������ˣ��������൱�ڲ���ʵ���ˡ�
*/
// http GET  
static CURLcode curl_get_req(const std::string &url, std::string &response)  
{  
    // init curl  
    CURL *curl = curl_easy_init();                  //��ʼ��CURL ����CURL *
    // res code  
    CURLcode res;  
	struct curl_slist *head = NULL;
    if (curl)  
    {  
		//��������ͷ��Content-Type����ʽ��application/json,UTF-8
		curl_slist_append(head,"Content-Type:application/x-www-form-urlencoded;charset=UTF-8");
		curl_easy_setopt(curl,CURLOPT_HTTPHEADER,head);

        // set params  
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); // url  ��������url
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false); // if want to use https �����Ƿ�ʹ��https  
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false); // set peer and host verify false ��������SSL֤�����Ƿ����һ��������(common name)   0/1/2
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);            //�Ƿ����������Ϣ��libcurl�ڲ���һ���߳����
        curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);    //�ص�����
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, req_reply);   //�ص����� req_reply ���յ����ݾʹ��������ܻᴥ����Ρ�ʵ�ֱ������ݵĹ��̣�����������
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&response);  //���ڱ������󷵻ص����ݣ�ʵ�ֽ������Ҫ���浽��λ�õ�ָ�룬�ò�����req_reply�ĵ��ĸ�����һ�£������ûص�����ʵ�ֱ������ݣ�Ҳ����ֱ��ʹ�������������Ʋ������ͱ�����FILEָ�룬�������ص����ݻ��Զ�д�����ļ�ָ��ָ����ļ����С�
        curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);           //����ʱ�������е�curl���ݸ�php���е��źš���SAPI���̴߳���ʱ���Ĭ�����á� 
        curl_easy_setopt(curl, CURLOPT_HEADER, 0);            //��������Ϊ 1����ô��֪ͨ curl �������ʱҪͬʱ���� "ͷ���� �� "��������" �������֡���ѡ����Ƕ���Щͬʱ�����ˡ�ͷ�����͡��������ݡ��������ֵ�Э�����(�� HTTP)��
        curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 3); // set transport and time out time  ����tcp���ӽ����ĳ�ʱ�������������ӳ�ʱ��������Ϊ0�������޵ȴ���3��
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3);        //���û�ȡ���ݳ�ʱ������tcp�����ѽ��������ǻ�ȡhttp�������ݳ�ʱ��3��
        // start req  
        res = curl_easy_perform(curl);           //ִ��CURL�����úø������ݵ�CURL��ִ����������״̬��  CURLE_OK���ɹ�
    } 
    // release curl  
    curl_easy_cleanup(curl);                    //ִ����ϣ����CURL���ͷ��ڴ� 
	curl_slist_free_all(head);
    return res;  
}  
  
// http POST  
static CURLcode curl_post_req(const string &url, const string &postParams, string &response)  
{  
    // init curl  
    CURL *curl = curl_easy_init();  
    // res code  
    CURLcode res;  
    if (curl)  
    {  
        // set params  
        curl_easy_setopt(curl, CURLOPT_POST, 1); // post req  ����ʱ�ᷢ��һ�������POST��������Ϊ��application/x-www-form-urlencoded��������ύ��һ����
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); // url  ��������url
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postParams.c_str()); // params  post����Ҫ�ύ�����ݣ��������Ҫ���ݷ������ľ���Ҫ����д
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false); // if want to use https  ͬ��
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false); // set peer and host verify false  ͬ��
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);            //ͬ��
        curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);    //ͬ��
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, req_reply);  //ͬ��
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&response); //ͬ��  
        curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);         //ͬ��
        curl_easy_setopt(curl, CURLOPT_HEADER, 0);           //ͬ��
        curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 3);   //ͬ��
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3);          //ͬ��
        // start req  
        res = curl_easy_perform(curl);  
    }  
    // release curl  
    curl_easy_cleanup(curl);  
    return res;  
}  

/*
����ת��
*/
//UTF8תGBK/GB2312
static string UTF8ToGBK(const char* strUTF8)
{
    int len = MultiByteToWideChar(CP_UTF8, 0, strUTF8, -1, NULL, 0);
    wchar_t* wszGBK = new wchar_t[len+1];
    memset(wszGBK, 0, len*2+2);
    MultiByteToWideChar(CP_UTF8, 0, strUTF8, -1, wszGBK, len);
    len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);
    char* szGBK = new char[len+1];
    memset(szGBK, 0, len+1);
    WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, szGBK, len, NULL, NULL);
    string strTemp(szGBK);
    if(wszGBK) delete[] wszGBK;
    if(szGBK) delete[] szGBK;
    return strTemp;
}

//GBK/GB2312תUTF8
static string GBKToUTF8(const char* strGBK)
{
    int len = MultiByteToWideChar(CP_ACP, 0, strGBK, -1, NULL, 0);
    wchar_t* wstr = new wchar_t[len+1];
    memset(wstr, 0, len+1);
    MultiByteToWideChar(CP_ACP, 0, strGBK, -1, wstr, len);
    len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
    char* str = new char[len+1];
    memset(str, 0, len+1);
    WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
    string strTemp = str;
    if(wstr) delete[] wstr;
    if(str) delete[] str;
    return strTemp;
}
#endif