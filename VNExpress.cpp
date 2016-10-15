#include <signal.h>
#include <stdio.h>
#include "requestdata.h"
#include "VNExpressModel.h"
 #include <directfb.h>
#include "FBGlobal.h"
#include <string.h>
#include <gstplayer.h>

int main(int argc, char *argv[])
{
	//CFBGlobal::FBSingletonGlobalInit();
	fprintf(stderr,"trung kienenenenen======================\n");
	//string text = CRequestData::postData("http://api.openfpt.vn/text2speech/v3?api_key=feedc4d1b6d94310a12e93efa794ca27","api_key:feedc4d1b6d94310a12e93efa794ca27","Cache-Control: no-cache","speed:0","ứng viên tổng thống đảng Cộng hòa");
	CVNExpressModel * vn = new CVNExpressModel();
	DetailItem *list = NULL;
	list = vn->getDetailVNExpress("3465014");
	fprintf(stderr,"trung kienenenenen======================\n");
	if(list != NULL)
	{
		fprintf(stderr,"trung kienenenenen===========1111111111111===========\n");
		for(int index = 0;index < list[0].size;index++)
		{
			//fprintf(stderr,"\ntrung kienenenenen===========aaaaaaaaaaaaaaaaaaaaaaaaa=========== : %s \n",list[index].thumbnail_url.c_str());
			//if(list[index].childMenu != NULL)
				//fprintf(stderr,"\ntrung kienenenenen============11111111111111111==========: %d ",list[index].childMenu->size);
		}
	}
	fprintf(stderr,"trung kienenenenen======================\n");
	sleep(10);
	//fprintf(stderr,"trung kienenenenen============11111111111111111==========: %s ",text.c_str());
	return 1;
}
