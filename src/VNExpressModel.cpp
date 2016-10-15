/*
 * requestdata.cpp
 *
 *  Created on: Oct 15, 2016
 *      Author: SONY
 */

#include <VNExpressModel.h>

CVNExpressModel::CVNExpressModel()
{
}
CVNExpressModel::~CVNExpressModel()
{
}
string CVNExpressModel::IntToString(int iNumber)
{
	 ostringstream oss;
	 oss<< iNumber;
	 return oss.str();
}
ListMenu* CVNExpressModel::getMenuVNExpress()
{
	 Json::Value root;
	Json::Reader reader;
	ListMenu *listItems = NULL;
	string response = CRequestData::getData("http://api.openfpt.vn/vne/category?api_key=feedc4d1b6d94310a12e93efa794ca27");
	bool bParsingSuccessful = reader.parse(response.c_str(), root);
	bool checkJson = root.isObject();
	if (!bParsingSuccessful || !checkJson)
	{
			return listItems;
	}
	else
	{
			Json::Value menu_items = root.get("data", Json::arrayValue);
			int iSizeMenu = menu_items.size();
			if(iSizeMenu > 0)
			{
				listItems = new ListMenu[iSizeMenu];
				for(int index_menu = 0;index_menu<iSizeMenu;index_menu++)
				{
					listItems[index_menu].size = iSizeMenu;
					listItems[index_menu].parent_id = menu_items[index_menu].get("parent_id", "").asString();
					listItems[index_menu].catename = menu_items[index_menu].get("catename", "").asString();
					listItems[index_menu].catecode = menu_items[index_menu].get("catecode", "").asString();
					listItems[index_menu].full_parent = menu_items[index_menu].get("full_parent", "").asString();
					listItems[index_menu].show_folder = menu_items[index_menu].get("show_folder", "").asString();
					listItems[index_menu].level = menu_items[index_menu].get("level", "").asString();
					listItems[index_menu].category_id = menu_items[index_menu].get("category_id", "").asString();
					listItems[index_menu].display_order = menu_items[index_menu].get("display_order", "").asString();
					Json::Value child = menu_items[index_menu].get("child", Json::arrayValue);
					if(child.size() > 0)
					{
						listItems[index_menu].childMenu = new ListMenu[child.size()+1];
						for(int index = 0;index<child.size();index++)
						{
							listItems[index_menu].childMenu[index].size = child.size();
							listItems[index_menu].childMenu[index].parent_id = child[index].get("parent_id", "").asString();
							listItems[index_menu].childMenu[index].catename = child[index].get("catename", "").asString();
							listItems[index_menu].childMenu[index].catecode = child[index].get("catecode", "").asString();
							listItems[index_menu].childMenu[index].full_parent = child[index].get("full_parent", "").asString();
							listItems[index_menu].childMenu[index].show_folder = child[index].get("show_folder", "").asString();
							listItems[index_menu].childMenu[index].level = child[index].get("level", "").asString();
							listItems[index_menu].childMenu[index].category_id = child[index].get("category_id", "").asString();
							listItems[index_menu].childMenu[index].display_order = child[index].get("display_order", "").asString();
							listItems[index_menu].childMenu[index].parent_id = child[index].get("parent_id", "").asString();
						}
					}
					else
					{
						listItems[index_menu].childMenu = NULL;
					}

				}
			}
	}
	return listItems;
}
ListItem* CVNExpressModel::getListVNExpress(string category_id, string limit, string offset)
{
	 Json::Value root;
	Json::Reader reader;
	ListItem *listItems = NULL;
	string response = CRequestData::getData("http://api.openfpt.vn/vne/categoryarticle?api_key=feedc4d1b6d94310a12e93efa794ca27&category_id="+category_id+"&limit="+limit+"&offset="+offset);
	bool bParsingSuccessful = reader.parse(response.c_str(), root);
	bool checkJson = root.isObject();
	if (!bParsingSuccessful || !checkJson)
	{
			return listItems;
	}
	else
	{
			Json::Value root_items = root.get("data", Json::arrayValue);
			Json::Value list_items = root_items.get(category_id, Json::arrayValue);
			int iSizeItem = list_items.size();
			fprintf(stderr,"\n==============:3333333333336666666666677777777: %d \n",iSizeItem);
			if(iSizeItem > 0)
			{
				listItems = new ListItem[iSizeItem];
				for(int index_menu = 0;index_menu<iSizeItem;index_menu++)
				{
					listItems[index_menu].size = iSizeItem;
					listItems[index_menu].original_cate = list_items[index_menu].get("original_cate", "").asString();
					listItems[index_menu].title = list_items[index_menu].get("title", "").asString();
					listItems[index_menu].lead = list_items[index_menu].get("lead", "").asString();
					listItems[index_menu].share_url = list_items[index_menu].get("share_url", "").asString();
					listItems[index_menu].thumbnail_url = list_items[index_menu].get("thumbnail_url", "").asString();
					listItems[index_menu].publish_time = list_items[index_menu].get("publish_time", "").asString();
					listItems[index_menu].article_id = list_items[index_menu].get("article_id", "").asString();
					Json::Value list_reference = list_items.get("list_reference", Json::arrayValue);
					fprintf(stderr,"==========222222222===list_reference : %d \n",list_reference);
					if(list_reference.size() > 0)
					{
						Json::Value arti = list_reference.get("article", Json::arrayValue);
						fprintf(stderr,"========111111111111=====article : %d \n",arti);
						if(arti.size() > 0)
						{
							listItems[index_menu].article = new string[arti.size()];
							for(int index = 0;index < arti.size();index++)
							{
								listItems[index_menu].article[index] = arti[index].get("article", "").asString();
								fprintf(stderr,"=============trungggggggggg : %s \n",listItems[index_menu].article[index].c_str());
							}
						}
					}
				}
			}
			fprintf(stderr,"\ntrung kienenenenen====================== %d \n", iSizeItem);
	}
	return listItems;
}



