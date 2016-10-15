/*
 * requestdata.cpp
 *
 *  Created on: Oct 15, 2016
 *      Author: SONY
 */

#include <requestdata.h>

CRequestData::CRequestData(){}
CRequestData::~CRequestData(){}
string CRequestData::getData(string url)
{
	CURL *curl;
	CURLcode res;
	string response_header;
	string response_data;
	string Cache = "Cache-Control: no-cache";
	int httpRespCode;
	curl = curl_easy_init();
	if (curl)
	{
		struct curl_slist *chunk = NULL;
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_to_string);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);
		curl_easy_setopt(curl, CURLOPT_HEADERDATA, &response_header);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
		curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);
		curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 10L);
		chunk = curl_slist_append(chunk, Cache.c_str());
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
		res = curl_easy_perform(curl);
		res = curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpRespCode);
		if (res != CURLE_OK || httpRespCode != 200)
		{
			return "";
		}
		curl_easy_cleanup(curl);
		curl_slist_free_all(chunk);
	}
	return response_data;
}
string  CRequestData::postData(string url, string speed, string data)
{
	CURL *curl;
	CURLcode res;
	string contentType;
	string response_data;
	string response_header;
	string cookieData;
	int httpRespCode;
	string dataRq = "";
	curl = curl_easy_init();
	if (curl)
	{
		struct curl_slist *chunk = NULL;
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_to_string);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);
		curl_easy_setopt(curl, CURLOPT_HEADERDATA, &response_header);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
		curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);
		curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 10L);
		chunk = curl_slist_append(chunk, speed.c_str());
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
		curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, write_to_string);
		res = curl_easy_perform(curl);
		res = curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpRespCode);
		if (res != CURLE_OK || httpRespCode != 200)
		{
			fprintf(stderr,"post data fail!");
			return "";
		}
		curl_easy_cleanup(curl);
		curl_slist_free_all(chunk);
	}
	return response_data;
}
size_t CRequestData::write_to_string(void *ptr, size_t size, size_t count,void *stream)
{
	((string*) stream)->append((char*) ptr, 0, size * count);
	return size * count;
}


