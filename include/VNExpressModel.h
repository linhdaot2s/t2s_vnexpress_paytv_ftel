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
	int sizepage;
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
struct ListItem
{
	int size;
	int sizepage;
	string original_cate;
	string title;
	string lead;
	string share_url;
	string thumbnail_url;
	string publish_time;
	string article_id;
	ListItem()
	{
	}
	~ListItem()
	{
	}
};
struct DetailItem
{
	int size;
	string original_cate;
	string title;
	string lead;
	string share_url;
	string thumbnail_url;
	string publish_time;
	string article_id;
	string content;
	DetailItem()
	{
	}
	~DetailItem()
	{
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
	DetailItem *getDetailVNExpress(string article_id);

};


#endif /* VNEXPRESSMODEL_H_ */
