/*
 * requestdata.h
 *
 *  Created on: Oct 15, 2016
 *      Author: SONY
 */

#ifndef REQUESTDATA_H_
#define REQUESTDATA_H_

#include <string>
#include <curl/curl.h>
#include <curl/easy.h>

using namespace std;
class CRequestData
{
public:
	CRequestData();
	~CRequestData();
	static string getData(string url);
	static string postData(string url, string speed, string data);
	static size_t write_to_string(void *ptr, size_t size, size_t count,void *stream);
};


#endif /* REQUESTDATA_H_ */
