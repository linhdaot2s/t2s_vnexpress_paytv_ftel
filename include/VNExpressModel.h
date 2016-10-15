/*
 * requestdata.h
 *
 *  Created on: Oct 15, 2016
 *      Author: SONY
 */

#ifndef VNEXPRESSMODEL_H_
#define VNEXPRESSMODEL_H_

#include <string>
#include <json/json.h>
#include "requestdata.h"
#include <sstream>

using namespace std;

struct ListMenu
{
	int size;
	string parent_id;
	string catename;
	string catecode;
	string full_parent;
	string show_folder;
	string level;
	string category_id;
	string display_order;
	ListMenu *childMenu;
	ListMenu()
	{
		childMenu = NULL;
	}
	~ListMenu()
	{
		if(childMenu != NULL)
		{
			delete[] childMenu;
			childMenu = NULL;
		}
	}
};
struct StArticle
{
};
struct ListItem
{
	int size;
	string original_cate;
	string title;
	string lead;
	string share_url;
	string thumbnail_url;
	string publish_time;
	string article_id;
	string *article;
	ListItem()
	{
		article = NULL;
	}
	~ListItem()
	{
		if(article != NULL)
		{
			delete[] article;
			article = NULL;
		}
	}
};
class CVNExpressModel
{
public:
	CVNExpressModel();
	~CVNExpressModel();
	string IntToString(int iNumber);
	ListMenu *getMenuVNExpress();
	ListItem *getListVNExpress(string category_id, string limit, string offset);

};


#endif /* VNEXPRESSMODEL_H_ */
