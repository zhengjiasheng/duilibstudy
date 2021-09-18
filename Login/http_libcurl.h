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
//UTF8转GBK/GB2312
static string UTF8ToGBK(const char* strUTF8);
//GBK/GB2312转UTF8
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
函数参数中的&表示引用，引用实参，即代表实参的一个别名，操作引用变量就相当于操作实参变量
&在变量操作区，表示取地址符。
&在变量定义区，表示引用。引用常用于函数参数中，函数参数中使用引用相当于把实参引入进来了，这样就相当于操作实参了。
*/
// http GET  
static CURLcode curl_get_req(const std::string &url, std::string &response)  
{  
    // init curl  
    CURL *curl = curl_easy_init();                  //初始化CURL 返回CURL *
    // res code  
    CURLcode res;  
	struct curl_slist *head = NULL;
    if (curl)  
    {  
		//设置请求头，Content-Type，格式：application/json,UTF-8
		curl_slist_append(head,"Content-Type:application/x-www-form-urlencoded;charset=UTF-8");
		curl_easy_setopt(curl,CURLOPT_HTTPHEADER,head);

        // set params  
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); // url  设置请求url
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false); // if want to use https 设置是否使用https  
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false); // set peer and host verify false 检查服务器SSL证书中是否存在一个公用名(common name)   0/1/2
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);            //是否输出调试信息，libcurl内部另开一个线程输出
        curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);    //回调函数
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, req_reply);   //回调函数 req_reply 接收到数据就触发，可能会触发多次。实现保存数据的过程，及其他操作
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&response);  //用于保存请求返回的数据，实现结果，传要保存到的位置的指针，该参数和req_reply的第四个参数一致，不想用回调函数实现保存数据，也可以直接使用它，不过限制参数类型必须是FILE指针，这样返回的数据会自动写到该文件指针指向的文件流中。
        curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);           //启用时忽略所有的curl传递给php进行的信号。在SAPI多线程传输时此项被默认启用。 
        curl_easy_setopt(curl, CURLOPT_HEADER, 0);            //参数设置为 1，那么会通知 curl 库在输出时要同时包含 "头部“ 和 "主题内容" 两个部分。该选项仅是对那些同时包含了”头部“和”主题内容“这两部分的协议而言(如 HTTP)。
        curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 3); // set transport and time out time  设置tcp连接建立的超时秒数，设置连接超时数，设置为0，则无限等待。3秒
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3);        //设置获取内容超时秒数（tcp连接已建立，但是获取http返回内容超时）3秒
        // start req  
        res = curl_easy_perform(curl);           //执行CURL，设置好各项内容的CURL，执行它，返回状态码  CURLE_OK：成功
    } 
    // release curl  
    curl_easy_cleanup(curl);                    //执行完毕，清除CURL，释放内存 
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
        curl_easy_setopt(curl, CURLOPT_POST, 1); // post req  启用时会发送一个常规的POST请求，类型为：application/x-www-form-urlencoded，就像表单提交的一样。
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); // url  设置请求url
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postParams.c_str()); // params  post请求要提交的数据，这段数据要根据服务器的具体要求填写
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false); // if want to use https  同上
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false); // set peer and host verify false  同上
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);            //同上
        curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);    //同上
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, req_reply);  //同上
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&response); //同上  
        curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);         //同上
        curl_easy_setopt(curl, CURLOPT_HEADER, 0);           //同上
        curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 3);   //同上
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3);          //同上
        // start req  
        res = curl_easy_perform(curl);  
    }  
    // release curl  
    curl_easy_cleanup(curl);  
    return res;  
}  

/*
编码转换
*/
//UTF8转GBK/GB2312
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

//GBK/GB2312转UTF8
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