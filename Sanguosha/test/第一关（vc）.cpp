#include<stdio.h>
#include <graphics.h>
#include <time.h>
#include <math.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<windows.h>
#include <mmsystem.h> 
#pragma comment(lib,"Winmm.lib")
#define high 600
#define width 1000

IMAGE img_bk,img_ui,img_slash,img_jink,img_HeroUi,img_hp,img_EquipmentUi,img_peach;
IMAGE img_npcUi,img_firm,img_grayfirm,img_RoundOver,img_PromptBox,img_back,img_StagePlaycard,img_Stageplayer_discard,img_JinNangTiShi,img_zhuangbeitishi,img_propmt;
IMAGE img_NanMan,img_WanJian,img_QianYang,img_ChaiQiao,img_WuXie,img_TaoYuan,img_JueDou,img_WuZhong,img_WuGu,img_JieDao,img_ZhuGeLianNuShouPai,img_ZhuGeLianNuZhuangBei;
IMAGE img_next,img_restart,img_horse1,img_horse2,img_EquipHorse1,img_EquipHorse2,img_mirror,img_EquipMirror,img_start,img_level1,img_level2,img_level3,img_real;

const int ui_high=168,ui_width=639,player_high=130,player_width=93,heroui_high=187,heroui_width=187;
const int hp_high=30,hp_width=26,equipment_high=167,equipment_width=161;
const int npcui_high=246,npcui_width=174,firm_high=42,firm_width=125;
const int roundover_high=41,roundover_width=100,grayfirm_high=42,grayfirm_width=125;		//各种图片素材的尺寸
const int PromptBox_High=180,PromptBox_Width=630,StagePlaycard_high=18,StagePlaycard_width=141;

int ui_y,ui_x,player_x[6],player_y[6],HeroUi_x,HeroUi_y,HeroHp_x,HeroHp_y,grayfirm_x,grayfirm_y;
int equipment_x,equipment_y,npcUi_x,npcUi_y,npcHp_x,npcHp_y,firm_x,firm_y,roundover_x,roundover_y;	
int PromptBox_x,PromptBox_y,StagePlaycard_x,StagePlaycard_y,Stageplayer_discard_x,Stageplayer_discard_y,back_x,back_y,player_desktop_x,player_desktop_y,npc_desktop_x,npc_desktop_y;
int Weapon_x,Weapon_y,Armor_x,Armor_y,Horse1_x,Horse1_y,Horse2_x,Horse2_y;
int Prompt_x,Prompt_y,JiNangTiShi_x,JiNangTiShi_y,zhuangbeitishi_x,zhuangbeitishi_y;
int restart_x,restart_y,over_x,over_y,NpcWeapon_x,NpcWeapon_y,NpcArmor_x,NpcArmor_y,NpcHorse1_x,NpcHorse1_y,NpcHorse2_x,NpcHorse2_y;
	
//各种图片素材的坐标

int player_AbandonNum;   //所需弃牌数
int player_AbandonNum_once;//第一次以记录
int npc_AbandonNum;   //所需弃牌数

int isstart;             //是否开始游戏
int isselected;		   //是否选中某张牌
int isRoundover;	   //回合是否结束
int isAbletoPlaycard;  //被选定的牌能否打出
int isEffective;	   //是否打出手牌
int isplayer_discard;         //是否需要弃牌
int isPrompt;				//是否提示锦囊
int isPrompt1;				//是否提示装备
int isplayerh2;				//玩家是否装备加一马
int isplayerh1;				//玩家是否装备减一马
int isnpch2;				//npc是否装备加一马
int isnpch1;				//npc是否装备减一马
int isplayerzhuge;				//玩家是否装备诸葛连弩
int isnpcmirror;				//玩家是否装备诸葛连弩
int isplayermirror;				//玩家是否装备护心镜
int isnpczhuge;				//玩家是否装备护心镜
int answerover;			//是否应对结束
int OverValue=1;			//结束值决定下一步怎么办
int juedoupeople=0;			//标注决斗人，，1为npc

int i, j;
int paidui[57];  //定义牌堆
int player[8] = { 0 }, player_shoupai_num;  //玩家手牌,手牌数
char c_player[8][20];  //玩家手牌字符
int npc[8] = { 0 }, npc_shoupai_num;     //电脑手牌，手牌数
int player_out = -1; //玩家出牌号
int npc_out = -1; //电脑出牌号
int player_life, npc_life;  //玩家，电脑生命值
int npc_sha_num = 0;;//电脑出杀次数
int npc_shan_num = 0;   //npc出闪次数
int player_sha_num =0;//玩家出杀次数
int player_shan_num = 0;   //玩家出闪次数
int player_qipai_num = 0, npc_qipai_num = 0;
int player_weapon = 0, npc_weapon = 0;
int paihao = 0; //牌号
int tmp[2];
char c_tmp[2][20];
int player_desktop=-1,npc_desktop=-1;//打在桌面上的牌
int player_desktop2=-1,npc_desktop2=-1;//打在桌面上的牌
int isover=0;						//0为游戏未结束
int disnum=0;		//玩家已经弃牌数
int isjuedou;		//是否在决斗
int x_wanjiatonpc=1;		//玩家到npc的距离
int x_npctowanjia=1;		//npc到玩家的距离
					

char Promptplayer_discardContent[50]={"请弃掉  张牌来结束本回合..."};

//各种函数
void DataStartup();
void player_discard();
void npc_discard();
int CanPlaycard();
void ImgStartup();
void interactive();
void interactive_answer();
void getnew();
void player_zhengli();
void npc_zhengli();
void startup_1();
void startup_2();
void startup_3();
void startup_4();
void startup_5();
void show();
void player_panding();
void npc_panding();
void huihe_player();
void huihe_npc();
void gameover();
void player_answer();
void juedou();
void washcard();
void gamestart();

void gotoxy(int x, int y)     //清屏以更换数据
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

void DataStartup()
{
	int i;
	for (i=0;i<6;i++) //初始化手牌坐标
	{
		player_x[i]=equipment_width+(i*player_width);
		player_y[i]=high-player_high;
	}
	
	isplayerzhuge=0;
	isplayerh1=0;				
	isplayerh2=0;
	isplayermirror=0;
	isnpcmirror=0;
	isnpczhuge=0;	
	isnpch2=0;			
	isnpch1=0;
	isselected=0;
	isRoundover=0;
	answerover=0;
	isAbletoPlaycard=1;
	isplayer_discard=0;
	isPrompt=0;
	isPrompt1=0;
	isjuedou=0;
	isstart=0;
	equipment_x=0;
	equipment_y=high-equipment_high;
	ui_x=equipment_width;
	ui_y=high-ui_high;	
	HeroUi_x=width-heroui_width;
	HeroUi_y=high-heroui_high;
	HeroHp_x=HeroUi_x;
	HeroHp_y=HeroUi_y-hp_high;
	npcUi_x=0;
	npcUi_y=hp_high;
	npcHp_x=0;
	npcHp_y=0;
	firm_x=width/2-100;
	firm_y=ui_y-firm_high;
	roundover_x=HeroUi_x-roundover_width;
	roundover_y=firm_y;
	grayfirm_x=firm_x;
	grayfirm_y=firm_y;
	PromptBox_x=(width-PromptBox_Width)/2.0;
	PromptBox_y=(high-PromptBox_High)/2.0;
	StagePlaycard_x=0;
	StagePlaycard_y=equipment_y-StagePlaycard_high;
	Stageplayer_discard_x=StagePlaycard_x;
	Stageplayer_discard_y=StagePlaycard_y;
	back_x=0;
	back_y=npcUi_y+80;
	player_desktop_x=width/2+100;
	player_desktop_y=high/2;
	npc_desktop_x=npcui_width;
	npc_desktop_y=hp_high;
	Weapon_x=10;
	Armor_x=Weapon_x;
	Horse1_x=Armor_x;
	Horse2_x=Horse1_x;
	Weapon_y=equipment_y+45;
	Armor_y=Weapon_y+33;
	Horse1_y=Armor_y+33;
	Horse2_y=Horse1_y+33;
	JiNangTiShi_x=width-firm_width;
	JiNangTiShi_y=0;
	zhuangbeitishi_x=width-firm_width;
	zhuangbeitishi_y=firm_high;
	Prompt_x=PromptBox_x;
	Prompt_y=0;
	restart_x=firm_x-100;
	restart_y=firm_y;
	over_x=roundover_x-200;
	over_y=roundover_y;
	NpcWeapon_x=23;
	NpcWeapon_y=187;
	NpcArmor_x=NpcWeapon_x;
	NpcArmor_y=NpcWeapon_y+23;
	NpcHorse1_x=NpcArmor_x;
	NpcHorse1_y=NpcArmor_y+23;
	NpcHorse2_x=NpcHorse1_x;
	NpcHorse2_y=NpcHorse1_y+23;

	
}


void startup_1()       //第一局牌堆初始化
{
	paihao=0;
	mciSendString("close kaishimusic", NULL, 0, NULL);  //先关闭前一次
	mciSendString("open \"三国杀音频素材\\开始音频.mp3\" alias kaishimusic",NULL,0,NULL);//播放杀
	mciSendString("play kaishimusic", NULL, 0, NULL);  //仅播放一次
	paidui[0] = 1;
	paidui[1] = 1;
	paidui[2] = 1;
	paidui[3] = 1;
	paidui[4] = 1;
	paidui[5] = 1;
	paidui[6] = 1;
	paidui[7] = 1;
	paidui[8] = 1;
	paidui[9] = 1;

	player_life = 1; //要根据英雄选择判断
	player[0] = 1;//杀
	player[1] = 3;//桃
	player[2] = 2;//闪
	player[3] = 1;//杀
	player_shoupai_num = 4;
	
	npc_life = 1;
	npc[0] = 1;//杀
	npc[1] = 1;
	npc[2] = 1;
	npc[3] = 2;//闪
	npc_shoupai_num = 4;
}

void startup_2()
{
	paihao=0;
	mciSendString("close kaishimusic", NULL, 0, NULL);  //先关闭前一次
	mciSendString("open \"三国杀音频素材\\开始音频.mp3\" alias kaishimusic",NULL,0,NULL);//播放杀
	mciSendString("play kaishimusic", NULL, 0, NULL);  //仅播放一次
	player_sha_num=0;
	player_shan_num=0;
	npc_sha_num=0;
	npc_shan_num=0;
	paidui[0] = 11;	//无懈
	paidui[1] = 3;	//桃//玩家
	paidui[2] = 12;	//决斗
	paidui[3] = 2;	//npc
	paidui[4] = 4;
	paidui[5] = 13;//无中生有//玩家
	paidui[6] = 6;
	paidui[7] = 1;	//npc
	paidui[8] = 1;
	paidui[9] = 2;	//
	paidui[10] = 1;
	paidui[11] = 9;	//
	paidui[12] = 1;
	paidui[13] = 10;	//
	paidui[14] = 2;
	paidui[15] = 1;	//
	paidui[16] = 1;
	paidui[17] = 1;
	paidui[18] = 2;
	paidui[19] = 1;	//
	paidui[20] = 1;
	paidui[21] = 1;
	paidui[22] = 2;
	paidui[23] = 1;	//
	paidui[24] = 1;
	paidui[25] = 1;
	paidui[26]= 2;
	paidui[27] = 1;	//
	paidui[28] = 1;
	paidui[29] = 1;


	player_life = 3; //要根据英雄选择判断
	player[0] = 1;//杀
	player[1] = 2;//闪
	player[2] = 5;//顺手牵羊
	player[3] = 9;//南蛮入侵
	player_shoupai_num = 4;
	
	npc_life = 3;
	npc[0] = 2;//闪
	npc[1] = 10;//万箭齐发
	npc[2] = 1;
	npc[3] = 4;//过河拆桥
	npc_shoupai_num = 4;
}

void startup_3()
{
	paihao=0;
	x_npctowanjia=1;
	x_wanjiatonpc=1;
	isplayerzhuge=0;
	isplayerh1=0;				
	isplayerh2=0;
	isplayermirror=0;
	isnpcmirror=0;
	isnpczhuge=0;	
	isnpch2=0;			
	isnpch1=0;
	x_npctowanjia=1;
	x_wanjiatonpc=1;
	mciSendString("close kaishimusic", NULL, 0, NULL);  //先关闭前一次
	mciSendString("open \"三国杀音频素材\\开始音频.mp3\" alias kaishimusic",NULL,0,NULL);//播放杀
	mciSendString("play kaishimusic", NULL, 0, NULL);  //仅播放一次
	player_sha_num=0;
	player_shan_num=0;
	npc_sha_num=0;
	npc_shan_num=0;
	paidui[0] = 2;	
	paidui[1] = 3;	//桃//玩家
	paidui[2] = 7;	//+1马
	paidui[3] = 14;	//npc
	paidui[4] = 8;	//-1马
	paidui[5] = 13;	//无中生有//玩家
	paidui[6] = 6;
	paidui[7] = 1;	//npc
	paidui[8] = 1;
	paidui[9] = 14;	//诸葛连弩（玩家
	paidui[10] = 1;
	paidui[11] = 3;	//npc
	paidui[12] = 15;	//护心镜
	paidui[13] = 10;	//玩家
	paidui[14] = 1;
	paidui[15] = 1;	//npc
	paidui[16] = 1;
	paidui[17] = 1;		//玩家
	paidui[18] = 2;
	paidui[19] = 1;	//
	paidui[20] = 1;
	paidui[21] = 1;
	paidui[22] = 2;
	paidui[23] = 1;	//
	paidui[24] = 1;
	paidui[25] = 1;
	paidui[26]= 2;
	paidui[27] = 1;	//
	paidui[28] = 1;
	paidui[29] = 1;


	player_life = 2; //要根据英雄选择判断
	player[0] = 1;//杀
	player[1] = 2;//闪
	player[2] = 14;
	player[3] = 15;//南蛮入侵
	player_shoupai_num = 4;
	
	npc_life = 2;
	npc[0] = 8;//闪
	npc[1] = 10;//万箭齐发
	npc[2] = 1;
	npc[3] = 15;
	npc_shoupai_num = 4;

}
void startup_4()
{
	paihao=0;
	x_npctowanjia=1;
	x_wanjiatonpc=1;
	isplayerzhuge=0;
	isplayerh1=0;				
	isplayerh2=0;
	isplayermirror=0;
	isnpcmirror=0;
	isnpczhuge=0;	
	isnpch2=0;			
	isnpch1=0;
	while (1)
	{
		putimage(0,0,&img_bk);
		putimage(Prompt_x,Prompt_y+100,&img_propmt);
		setbkmode(TRANSPARENT);
		settextstyle(30, 0, _T("微软雅黑"));
		outtextxy(Prompt_x+30,Prompt_y+180,_T("恭喜你完成新手教程，下面你可以选择温习之前的关卡，"));
		outtextxy(Prompt_x+30,Prompt_y+220,_T("或是进入实战演练！准备好了吗？当然，你也可以选择退"));
		outtextxy(Prompt_x+30,Prompt_y+260,_T("出游戏，（温馨提示：注意游戏时间，绿色用眼哦！）"));


		putimage(150,restart_y+100,&img_level1);
		putimage(150+firm_width+50,restart_y+100,&img_level2);
		putimage(150+2*firm_width+100,restart_y+100,&img_level3);
		putimage(150+3*firm_width+150,restart_y+100,&img_real);
		putimage(0,0,&img_RoundOver);
		
		MOUSEMSG m;		
		m=GetMouseMsg();
		
		if (m.uMsg==WM_LBUTTONDOWN)
		{
			if ((m.x>=150)&&(m.x<=150+firm_width)&&(m.y>=restart_y+100)&&(m.y<=restart_y+100+firm_high))
			{
				OverValue=1;
				break;					
			}
			if ((m.x>=200+firm_width)&&(m.x<=200+2*firm_width)&&(m.y>=restart_y+100)&&(m.y<=restart_y+100+firm_high))
			{
				OverValue=2;
				break;					
			}
			if ((m.x>=250+2*firm_width)&&(m.x<=250+3*firm_width)&&(m.y>=restart_y+100)&&(m.y<=restart_y+100+firm_high))
			{
				OverValue=3;
				break;					
			}
			if ((m.x>=300+3*firm_width)&&(m.x<=300+4*firm_width)&&(m.y>=restart_y+100)&&(m.y<=restart_y+100+firm_high))
			{
				OverValue=5;
				break;					
			}
			if ((m.x>=0)&&(m.x<=firm_width)&&(m.y>=0)&&(m.y<=firm_high))
			{
				exit(0);
			}
		}
		
		
		
		FlushBatchDraw();
	}
}


void startup_5()
{
	paihao=0;
	player_life=4;
	npc_life=4;
	x_npctowanjia=1;
	x_wanjiatonpc=1;
	isplayerzhuge=0;
	isplayerh1=0;				
	isplayerh2=0;
	isplayermirror=0;
	isnpcmirror=0;
	isnpczhuge=0;	
	isnpch2=0;			
	isnpch1=0;
	mciSendString("close kaishimusic", NULL, 0, NULL);  //先关闭前一次
	mciSendString("open \"三国杀音频素材\\开始音频.mp3\" alias kaishimusic",NULL,0,NULL);//播放杀
	mciSendString("play kaishimusic", NULL, 0, NULL);  //仅播放一次
	//正式战斗
	player_sha_num=0;
	player_shan_num=0;
	npc_sha_num=0;
	npc_shan_num=0;
	washcard();
	paihao=0;
	player[0] = paidui[paihao];paihao++;
	player[1] = paidui[paihao];paihao++;
	player[2] = paidui[paihao];paihao++;
	player[3] = paidui[paihao];paihao++;
	player_shoupai_num=4;
	npc[0] = paidui[paihao];paihao++;
	npc[1] = paidui[paihao];paihao++;
	npc[2] = paidui[paihao];paihao++;
	npc[3] = paidui[paihao];paihao++;
	npc_shoupai_num=4;
}

void washcard()		//洗牌程序
{
	int temp;
	int i,j;
	for (i = 0; i < 15; i++)
	{
		paidui[i] = 1;//给牌堆赋值0-9为杀
	}
	for (i = 15; i < 30; i++)
	{
		paidui[i] = 2;//给牌堆赋值10-19为闪
	}
	for (i = 30; i < 33; i++)
	{
		paidui[i] = 3;//给牌堆赋值20-24为桃
	}
	for (i = 33; i < 35; i++)
	{
		paidui[i] = 4;//给牌堆赋值25-27为过河拆桥
	}
	for (i = 35; i < 37; i++)
	{
		paidui[i] = 5;//给牌堆赋值28-30为顺手牵羊
	}
	for (i = 37; i < 39; i++)
	{
		paidui[i] = 6;//给牌堆赋值31-33为桃园结义
	}
	for (i = 39; i < 41; i++)
	{
		paidui[i] = 7;//给牌堆赋值34-35为+1马 
	}
	for (i = 41; i < 43; i++)
	{
		paidui[i] = 8;//给牌堆赋值36-37为-1马 
	}
	for (i = 43; i < 45; i++)
	{
		paidui[i] = 14;//给牌堆赋值38诸葛连弩 
	}
	for (i = 45; i < 47; i++)
	{
		paidui[i] = 15;//给牌堆赋值39护心镜
	}
	for (i = 47; i < 49; i++)
	{
		paidui[i] = 9;//给牌堆赋值40-42为南蛮入侵
	}
	for (i = 49; i < 51; i++)
	{
		paidui[i] = 10;//给牌堆赋值43-45为万箭齐发
	}
	for (i = 51; i < 53; i++)
	{
		paidui[i] = 11;//给牌堆赋值46-47为无懈可击
	}
	for (i = 53; i < 55; i++)
	{
		paidui[i] = 12;//给牌堆赋值48-50为决斗
	}
	for (i = 55; i < 57; i++)
	{
		paidui[i] = 13;//给牌堆赋值51-53为无中生有
	}
	for (i = 0; i <57; i++)
	{
		j = rand() % 57;//随即打乱
		temp = paidui[i];
		paidui[i] = paidui[j];
		paidui[j] = temp;
	}
}


void player_discard()  //弃牌阶段
{
	if(disnum==0)		//仅每回合第一次弃牌时记录
	{
		player_AbandonNum=player_shoupai_num-player_life;
		player_AbandonNum_once=player_AbandonNum;
	}
	player_AbandonNum=player_shoupai_num-player_life;
	if (player_AbandonNum_once>0)
	{
		isplayer_discard=1;		
	}
	if (player_AbandonNum_once==0)
	{
		isplayer_discard=0;
	}
	if(disnum>=player_AbandonNum_once)//已经弃牌完成
	{
		isplayer_discard=0;
		player_out=-2;
	}
}

void npc_discard()
{
	int t=0;
	npc_AbandonNum=npc_shoupai_num-npc_life;
	while((npc_AbandonNum>0)&&(t<npc_AbandonNum))
	{
		npc[0]=0;
		npc_zhengli();
		npc_shoupai_num--;
		t++;
	}
	putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
	setbkmode(TRANSPARENT);
	settextstyle(30, 0, _T("微软雅黑"));
	outtextxy(PromptBox_x+20,PromptBox_y,_T("敌方弃牌中！"));
	FlushBatchDraw();
	Sleep(1000);

}

int CanPlaycard() //不能出牌的种种情况（配合确认按钮的色彩变化）
{
	
	
	
	return isAbletoPlaycard;
}

void ImgStartup()
{
	
	initgraph(width,high);
		
	loadimage(&img_bk,"三国杀图片素材\\background.jpg");
	loadimage(&img_ui,"三国杀图片素材\\ui.png");
	loadimage(&img_slash,"三国杀图片素材\\杀.png");
	loadimage(&img_jink,"三国杀图片素材\\闪.png");
	loadimage(&img_HeroUi,"三国杀图片素材\\heroui.png");
	loadimage(&img_hp,"三国杀图片素材\\hp.png");
	loadimage(&img_EquipmentUi,"三国杀图片素材\\equipmentui.png");
	loadimage(&img_npcUi,"三国杀图片素材\\npc_ui.png");
	loadimage(&img_RoundOver,"三国杀图片素材\\roundover.png");
	loadimage(&img_firm,"三国杀图片素材\\firm.png");
	loadimage(&img_grayfirm,"三国杀图片素材\\grayfirm.png");
	loadimage(&img_PromptBox,"三国杀图片素材\\promptbox.png");
	loadimage(&img_peach,"三国杀图片素材\\peach.png");
	loadimage(&img_back,"三国杀图片素材\\back.png");
	loadimage(&img_StagePlaycard,"三国杀图片素材\\stageplaycard.png");
	loadimage(&img_Stageplayer_discard,"三国杀图片素材\\stageplayer_discard.png");
	loadimage(&img_NanMan,"三国杀图片素材\\南蛮入侵.png");
	loadimage(&img_WanJian,"三国杀图片素材\\万箭齐发.png");
	loadimage(&img_WuZhong,"三国杀图片素材\\无中生有.png");
	loadimage(&img_JueDou,"三国杀图片素材\\决斗.png");
	loadimage(&img_TaoYuan,"三国杀图片素材\\桃园结义.png");
	loadimage(&img_QianYang,"三国杀图片素材\\顺手牵羊.png");
	loadimage(&img_ChaiQiao,"三国杀图片素材\\过河拆桥.png");
	loadimage(&img_WuXie,"三国杀图片素材\\无懈可击.png");
	loadimage(&img_ZhuGeLianNuShouPai,"三国杀图片素材\\手牌诸葛连弩.png");
	loadimage(&img_ZhuGeLianNuZhuangBei,"三国杀图片素材\\装备诸葛连弩.png");
	loadimage(&img_WuGu,"三国杀图片素材\\五谷丰登.png");
	loadimage(&img_JieDao,"三国杀图片素材\\借刀杀人.png");
	loadimage(&img_propmt,"三国杀图片素材\\prompt.png");
	loadimage(&img_JinNangTiShi,"三国杀图片素材\\锦囊提示.png");
	loadimage(&img_zhuangbeitishi,"三国杀图片素材\\装备提示.png");
	loadimage(&img_next,"三国杀图片素材\\next.png");
	loadimage(&img_restart,"三国杀图片素材\\restart.png");
	loadimage(&img_start,"三国杀图片素材\\start.png");
	loadimage(&img_horse1,"三国杀图片素材\\horse1.png");
	loadimage(&img_horse2,"三国杀图片素材\\horse2.png");
	loadimage(&img_EquipHorse1,"三国杀图片素材\\equiphorse1.png");
	loadimage(&img_EquipHorse2,"三国杀图片素材\\equiphorse2.png");
	loadimage(&img_mirror,"三国杀图片素材\\mirror.png");
	loadimage(&img_EquipMirror,"三国杀图片素材\\equipmirror.png");
	loadimage(&img_level1,"三国杀图片素材\\level1.png");
	loadimage(&img_level2,"三国杀图片素材\\level2.png");
	loadimage(&img_level3,"三国杀图片素材\\level3.png");
	loadimage(&img_real,"三国杀图片素材\\real.png");

	BeginBatchDraw();
}

/*void turn()         //用于数字换为汉字//现仅起注释作用！！！！！！
{
	int i;
	for (i = 0; player[i] != 0; i++)
	{
		if (player[i] == 1)
		{
			strcpy(c_player[i], "杀");
		}
		else if (player[i] == 2)
		{
			strcpy(c_player[i], "闪");
		}
		else if (player[i] == 3)
		{
			strcpy(c_player[i], "桃");
		}
		else if (player[i] == 4)
		{
			strcpy(c_player[i], "过河拆桥");
		}
		else if (player[i] == 5)
		{
			strcpy(c_player[i], "顺手牵羊");
		}
		else if (player[i] == 6)
		{
			strcpy(c_player[i], "桃园结义");
		}
		else if (player[i] == 7)
		{
			strcpy(c_player[i], "五谷丰登");
		}
		else if (player[i] == 8)
		{
			strcpy(c_player[i], "借刀杀人");
		}
		else if (player[i] == 9)
		{
			strcpy(c_player[i], "南蛮入侵");
		}
		else if (player[i] == 10)
		{
			strcpy(c_player[i], "万箭齐发");
		}
		else if (player[i] == 11)
		{
			strcpy(c_player[i], "无懈可击");
		}
		else if (player[i] == 12)
		{
			strcpy(c_player[i], "决斗");
		}
		else if (player[i] == 13)
		{
			strcpy(c_player[i], "无中生有");
		}
	}
}*/


void player_getnew()
{
	
	putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
	setbkmode(TRANSPARENT);
	settextstyle(30, 0, _T("微软雅黑"));
	outtextxy(PromptBox_x+20,PromptBox_y,_T("我方摸牌中！"));
	FlushBatchDraw();
	Sleep(1000);
	int t;
	int i,j;
	for (i = 0; player[i] != 0; i++)
	{ }//找到牌尾
	t = i;
	for (j = t; j < t+2; j++)
	{	
		if(paihao>55)	//考虑牌堆抽完
		{
			washcard();
			paihao=0;
		}
		player[j] = paidui[paihao];
		paidui[paihao] = 0;  //玩家抽两张牌，抽完牌堆处的数就清零
		paihao++;
	}
	player_shoupai_num+=2;//加二

}
void npc_getnew()
{
	
	putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
	setbkmode(TRANSPARENT);
	settextstyle(30, 0, _T("微软雅黑"));
	outtextxy(PromptBox_x+20,PromptBox_y,_T("敌方摸牌中！"));
	FlushBatchDraw();
	Sleep(1000);
	int t;
	int i,j;
	for (i = 0; npc[i] != 0; i++)
	{ }//找到牌尾
	t = i;
	for (j = t; j < t + 2; j++)
	{
		if(paihao>55)	//考虑牌堆抽完
		{
			washcard();
			paihao=0;
		}
		npc[j] = paidui[paihao];
		paidui[paihao] = 0;  //玩家抽两张牌，抽完牌堆处的数就清零
		paihao++;
	}
	npc_shoupai_num+=2;//加二
}



void player_zhengli()
{
	int k;
	for (k = 0; k < player_shoupai_num; k++)
	{
		if (player[k] == 0)
		{
			player[k] = player[k + 1];
			player[k + 1] = 0;
		}             //整理player手牌
	}
}

void npc_zhengli()
{
	int k;
	for (k = 0; k < npc_shoupai_num; k++)
	{
		if (npc[k] == 0)
		{
			npc[k] = npc[k + 1];
			npc[k + 1] = 0;
		}             //整理npc手牌
	}
}


void show()
{
	int i;

	putimage(0,0,&img_bk);
	putimage(ui_x,ui_y,&img_ui);
	putimage(HeroUi_x,HeroUi_y,&img_HeroUi);	
	putimage(equipment_x,equipment_y,&img_EquipmentUi);
	putimage(npcUi_x,npcUi_y,&img_npcUi);			
	putimage(back_x,back_y,&img_back);
	if(OverValue==2)
	{
		putimage(JiNangTiShi_x,JiNangTiShi_y,&img_JinNangTiShi);
	}
	if(OverValue==3)
	{
		putimage(JiNangTiShi_x,JiNangTiShi_y,&img_zhuangbeitishi);
	}
	if(OverValue==5)
	{
		putimage(JiNangTiShi_x,JiNangTiShi_y,&img_JinNangTiShi);
		putimage(zhuangbeitishi_x,zhuangbeitishi_y,&img_zhuangbeitishi);
	}
	setbkmode(TRANSPARENT);
	settextstyle(30, 0, _T("微软雅黑"));
	outtextxy(back_x+12,back_y+15,48+npc_shoupai_num);

	for (i=0;i<player_life;i++)
	{
		putimage(i*(hp_width+15)+HeroHp_x,HeroHp_y,&img_hp);
	}
	for (i=0;i<npc_life;i++)
	{
		putimage(i*(hp_width+20)+npcHp_x,npcHp_y,&img_hp);
	}                                //绘制血点
	
	if (isselected)
	{
		if (CanPlaycard())   //确认UI的颜色变化
		{
			putimage(firm_x,firm_y,&img_firm);
		}
		else
		{
			putimage(grayfirm_x,grayfirm_y,&img_grayfirm);			
		}
	}
	else if(!isover)
	{
		putimage(roundover_x,roundover_y,&img_RoundOver);
	}
	
	for (i=0;i<player_shoupai_num;i++)
	{		
		if (player[i]==1)
		{
			putimage(player_x[i],player_y[i],&img_slash);
			continue;//杀
		}
		if (player[i]==2)
		{
			putimage(player_x[i],player_y[i],&img_jink);
			continue;//闪
		}
		if (player[i]==3)
		{
			putimage(player_x[i],player_y[i],&img_peach);
			continue;//桃
		}
		if (player[i]==4)
		{
			putimage(player_x[i],player_y[i],&img_ChaiQiao);
			continue;//过河拆桥
		}
		if (player[i]==5)
		{
			putimage(player_x[i],player_y[i],&img_QianYang);
			continue;//顺手牵羊
		}
		if (player[i]==6)
		{
			putimage(player_x[i],player_y[i],&img_TaoYuan);
			continue;//桃园结义
		}
		if (player[i]==7)
		{
			putimage(player_x[i],player_y[i],&img_horse2);
			continue;//+1马
		}
		if (player[i]==8)
		{
			putimage(player_x[i],player_y[i],&img_horse1);
			continue;//-1马
		}
		if (player[i]==9)
		{
			putimage(player_x[i],player_y[i],&img_NanMan);
			continue;//南蛮入侵
		}
		if (player[i]==10)
		{
			putimage(player_x[i],player_y[i],&img_WanJian);
			continue;//万箭齐发
		}
		if (player[i]==11)
		{
			putimage(player_x[i],player_y[i],&img_WuXie);
			continue;//无懈可击
		}
		if (player[i]==12)
		{
			putimage(player_x[i],player_y[i],&img_JueDou);
			continue;//决斗
		}
		if (player[i]==13)
		{
			putimage(player_x[i],player_y[i],&img_WuZhong);
			continue;//无中生有
		}
		if (player[i]==14)
		{
			putimage(player_x[i],player_y[i],&img_ZhuGeLianNuShouPai);
			continue;//诸葛连弩
		}
		if (player[i]==15)
		{
			putimage(player_x[i],player_y[i],&img_mirror);
			continue;//护心镜
		}

	}
	if (!isRoundover)
	{
		putimage(StagePlaycard_x,StagePlaycard_y,&img_StagePlaycard);
	}

	if (isplayer_discard)
	{
		putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
		putimage(Stageplayer_discard_x,Stageplayer_discard_y,&img_Stageplayer_discard);
		setbkmode(TRANSPARENT);
		settextstyle(20, 0, _T("宋体"));
		outtextxy(PromptBox_x+20,PromptBox_y,_T(Promptplayer_discardContent));
		outtextxy(PromptBox_x+88,PromptBox_y,player_AbandonNum+48);
	}
		if (player_desktop2==1)
		{
			putimage(player_desktop_x,player_desktop_y,&img_slash);
			
		}
		if (player_desktop2==2)
		{
			putimage(player_desktop_x,player_desktop_y,&img_jink);
			
		}
		if (player_desktop2==3)
		{
			putimage(player_desktop_x,player_desktop_y,&img_peach);
		}
		if (player_desktop2==4)
		{
			putimage(player_desktop_x,player_desktop_y,&img_ChaiQiao);
		}
		if (player_desktop2==5)
		{
			putimage(player_desktop_x,player_desktop_y,&img_QianYang);
		}
		if (player_desktop2==6)
		{
			putimage(player_desktop_x,player_desktop_y,&img_TaoYuan);
		}
		if (player_desktop2==7)
		{
			putimage(player_desktop_x,player_desktop_y,&img_horse2);
		}
		if (player_desktop2==8)
		{
			putimage(player_desktop_x,player_desktop_y,&img_horse1);
		}
		if (player_desktop2==9)
		{
			putimage(player_desktop_x,player_desktop_y,&img_NanMan);
		}
		if (player_desktop2==10)
		{
			putimage(player_desktop_x,player_desktop_y,&img_WanJian);
		}
		if (player_desktop2==11)
		{
			putimage(player_desktop_x,player_desktop_y,&img_WuXie);
		}
		if (player_desktop2==12)
		{
			putimage(player_desktop_x,player_desktop_y,&img_JueDou);
		}
		if (player_desktop2==13)
		{
			putimage(player_desktop_x,player_desktop_y,&img_WuZhong);
		}
		if (player_desktop2==14)
		{
			putimage(player_desktop_x,player_desktop_y,&img_ZhuGeLianNuShouPai);
		}
		if (player_desktop2==15)
		{
			putimage(player_desktop_x,player_desktop_y,&img_mirror);
		}


		if (npc_desktop2==1)
		{
			putimage(npc_desktop_x,npc_desktop_y,&img_slash);
		}
		if (npc_desktop2==2)
		{
			putimage(npc_desktop_x,npc_desktop_y,&img_jink);
		}
		if (npc_desktop2==3)
		{
			putimage(npc_desktop_x,npc_desktop_y,&img_peach);
		}
		if (npc_desktop2==4)
		{
			putimage(npc_desktop_x,npc_desktop_y,&img_ChaiQiao);
		}
		if (npc_desktop2==5)
		{
			putimage(npc_desktop_x,npc_desktop_y,&img_QianYang);
		}
		if (npc_desktop2==6)
		{
			putimage(npc_desktop_x,npc_desktop_y,&img_TaoYuan);
		}
		if (npc_desktop2==7)
		{
			putimage(npc_desktop_x,npc_desktop_y,&img_horse2);
		}
		if (npc_desktop2==8)
		{
			putimage(npc_desktop_x,npc_desktop_y,&img_horse1);
		}
		if (npc_desktop2==9)
		{
			putimage(npc_desktop_x,npc_desktop_y,&img_NanMan);
		}
		if (npc_desktop2==10)
		{
			putimage(npc_desktop_x,npc_desktop_y,&img_WanJian);
		}
		if (npc_desktop2==11)
		{
			putimage(npc_desktop_x,npc_desktop_y,&img_WuXie);
		}
		if (npc_desktop2==12)
		{
			putimage(npc_desktop_x,npc_desktop_y,&img_JueDou);
		}
		if (npc_desktop2==13)
		{
			putimage(npc_desktop_x,npc_desktop_y,&img_WuZhong);
		}
		if (npc_desktop2==14)
		{
			putimage(npc_desktop_x,npc_desktop_y,&img_ZhuGeLianNuShouPai);
		}
		if (npc_desktop2==15)
		{
			putimage(npc_desktop_x,npc_desktop_y,&img_mirror);
		}
		if (isPrompt)
		{
			putimage(Prompt_x,Prompt_y,&img_propmt);
			setbkmode(TRANSPARENT);
			settextstyle(25, 0, _T("微软雅黑"));
			outtextxy(Prompt_x+20,Prompt_y,_T("过河拆桥：拆掉对方一张牌"));
			outtextxy(Prompt_x+20,Prompt_y+30,_T("顺手牵羊：选取对方一张牌加入自己手牌"));
			outtextxy(Prompt_x+20,Prompt_y+60,_T("万箭齐发：除你外所有其他角色需打出一张闪，否则受到一点伤害"));
			outtextxy(Prompt_x+20,Prompt_y+90,_T("南蛮入侵：除你外所有其他角色需打出一张杀，否则受到一点伤害"));
			outtextxy(Prompt_x+20,Prompt_y+120,_T("桃园结义：所有角色回复一点体力"));
			outtextxy(Prompt_x+20,Prompt_y+150,_T("无中生有：立即摸两张手牌"));
			outtextxy(Prompt_x+20,Prompt_y+180,_T("决斗：你和你指定的角色轮流出杀直到出现未出者，未出者受到一点伤害"));
			outtextxy(Prompt_x+20,Prompt_y+210,_T("五谷丰登：从牌堆中取出与在场人数相等的牌,从出牌者开始轮流选取获得"));
			outtextxy(Prompt_x+20,Prompt_y+240,_T("借刀杀人：选择一名角色对另一名出杀,若放弃出杀则其装备牌归你"));
			outtextxy(Prompt_x+20,Prompt_y+270,_T("无懈可击：某锦囊牌生效前可打出，使其无效"));	
		}
		if (isPrompt1)
		{
			putimage(Prompt_x,Prompt_y,&img_propmt);
			setbkmode(TRANSPARENT);
			settextstyle(25, 0, _T("微软雅黑"));
			outtextxy(Prompt_x+80,Prompt_y+60,_T("+1马：增加敌方到自己的距离，而不增加自己到敌方的距"));
			outtextxy(Prompt_x+80,Prompt_y+90,_T("离。注：正常杀的有效距离的1。"));
			outtextxy(Prompt_x+80,Prompt_y+120,_T("-1马：减少自己到敌方的距离，而不减少敌方到自己的距离。"));
			outtextxy(Prompt_x+80,Prompt_y+150,_T("诸葛连弩：单个回合可持续使用杀。"));
			outtextxy(Prompt_x+80,Prompt_y+180,_T("护心镜：濒死（血量为1）时主动失去护心镜，回血一滴。"));
		}
		if(isplayerh2==1)
		{
			putimage(Horse2_x,Horse2_y,&img_EquipHorse2);
		}
		if(isplayerh1==1)
		{
			putimage(Horse1_x,Horse1_y,&img_EquipHorse1);
		}
		if(isplayerzhuge==1)
		{
			putimage(Weapon_x,Weapon_y,&img_ZhuGeLianNuZhuangBei);
		}
		if(isplayermirror==1)
		{
			putimage(Armor_x,Armor_y,&img_EquipMirror);
		}
		if(isnpch2==1)
		{
			putimage(NpcHorse2_x,NpcHorse2_y,&img_EquipHorse2);
		}
		if(isnpch1==1)
		{
			putimage(NpcHorse1_x,NpcHorse1_y,&img_EquipHorse1);
		}
		if(isnpczhuge==1)
		{
			putimage(NpcWeapon_x,NpcWeapon_y,&img_ZhuGeLianNuZhuangBei);
		}
		if(isnpcmirror==1)
		{
			putimage(NpcArmor_x,NpcArmor_y,&img_EquipMirror);
		}
	
	
	
	FlushBatchDraw();
	
}

void player_answer()
{
	while(1)
	{
		interactive_answer();//鼠标交互
		show();//显示一次
		if((isjuedou==1)&&(juedoupeople==1))		//可无懈可击的决斗
		{
			if ((player[player_out] == 11)&&(isEffective==1))  //玩家出无懈可击
			{
				player_desktop=player[player_out];//记录桌面牌
				player_desktop2=player[player_out];//记录桌面牌
				mciSendString("close wuxiemusic", NULL, 0, NULL);  //先关闭前一次
				mciSendString("open \"三国杀音频素材\\无懈可击.mp3\" alias wuxiemusic",NULL,0,NULL);//播放杀
				mciSendString("play wuxiemusic", NULL, 0, NULL);  //仅播放一次
				Sleep(1000);
				player[player_out]=0;
				player_out = -1;				//出牌号清空
				player_zhengli();
				player_shoupai_num--;           //手牌数减一
				isEffective=0;
				npc_desktop = 0;
				show();
				juedoupeople=-1;				//返回值
				break;
			}
			if ((player[player_out] == 1)&&(isEffective==1))  //玩家出杀
			{
				player_desktop=player[player_out];//记录桌面牌
				player_desktop2=player[player_out];//记录桌面牌
				mciSendString("close shamusic", NULL, 0, NULL);  //先关闭前一次
				mciSendString("open \"三国杀音频素材\\杀.mp3\" alias shamusic",NULL,0,NULL);//播放杀
				mciSendString("play shamusic", NULL, 0, NULL);  //仅播放一次
				Sleep(500);
				player[player_out]=0;
				player_out = -1;				//出牌号清空
				player_zhengli();
				player_shoupai_num--;           //手牌数减一
				isEffective=0;
				show();
				juedoupeople=0;				//返回值
				break;
			}
			if(answerover==1)	//玩家点击结束
				{
					putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
					setbkmode(TRANSPARENT);
					settextstyle(30, 0, _T("微软雅黑"));
					outtextxy(PromptBox_x+20,PromptBox_y,_T("你决斗输了，受到一单位伤害！"));
					FlushBatchDraw();
					Sleep(1000);
					player_life--;		//扣血
					show();
					isEffective=0;
					answerover=0;//恢复
					isjuedou = 0;
					show();
					break;
				}


		}
		if((isjuedou==1)&&(juedoupeople==0))		//决斗
		{
			if ((player[player_out] == 1)&&(isEffective==1))  //玩家出杀
			{
				player_desktop=player[player_out];//记录桌面牌
				player_desktop2=player[player_out];//记录桌面牌
				mciSendString("close shamusic", NULL, 0, NULL);  //先关闭前一次
				mciSendString("open \"三国杀音频素材\\杀.mp3\" alias shamusic",NULL,0,NULL);//播放杀
				mciSendString("play shamusic", NULL, 0, NULL);  //仅播放一次
				Sleep(500);
				player[player_out]=0;
				player_out = -1;				//出牌号清空
				player_zhengli();
				player_shoupai_num--;           //手牌数减一
				isEffective=0;
				show();
				break;
			}
			if(answerover==1)	//玩家点击结束
				{
					putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
					setbkmode(TRANSPARENT);
					settextstyle(30, 0, _T("微软雅黑"));
					outtextxy(PromptBox_x+20,PromptBox_y,_T("你决斗输了，受到一单位伤害！"));
					FlushBatchDraw();
					Sleep(1000);
					player_life--;		//扣血
					show();
					isEffective=0;
					answerover=0;//恢复
					isjuedou = 0;
					show();
					break;
				}

		}
		if(npc_desktop==1)	//敌方出杀
		{
			if ((npc_desktop == 1)&&(npc_sha_num == 1)) //npc出有效杀且我方点击
			{
				if ((player[player_out] == 2)&&(isEffective==1))  //玩家出闪
				{
					player_desktop=player[player_out];//记录桌面牌
					player_desktop2=player[player_out];//记录桌面牌
					mciSendString("close shanmusic", NULL, 0, NULL);  //先关闭前一次
					mciSendString("open \"三国杀音频素材\\闪.mp3\" alias shanmusic",NULL,0,NULL);//播放闪
					mciSendString("play shanmusic", NULL, 0, NULL);  //仅播放一次
					Sleep(500);
					player[player_out]=0;
					player_out = -1;				//出牌号清空
					player_zhengli();
					player_shan_num++;				//玩家出闪次数加一
					player_shoupai_num--;           //手牌数减一
					isEffective=0;
					npc_desktop = 0;
					//printf("我方使用闪\n");
					show();
					break;
				}
				if(answerover==1)	//玩家点击结束
				{
					player_life--;
					isEffective=0;
					answerover=0;//恢复
					npc_desktop = 0;
					show();
					putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
					setbkmode(TRANSPARENT);
					settextstyle(30, 0, _T("微软雅黑"));
					outtextxy(PromptBox_x+20,PromptBox_y,_T("你受到一个单位伤害！"));
					FlushBatchDraw();
					Sleep(1000);
					break;
				}
				//npc_sha_num--;
			}
		}
		if(npc_desktop==4)	//敌方出过河拆桥
		{
			if ((player[player_out] == 11)&&(isEffective==1))  //玩家出无懈可击
			{
				player_desktop=player[player_out];//记录桌面牌
				player_desktop2=player[player_out];//记录桌面牌
				mciSendString("close wuxiemusic", NULL, 0, NULL);  //先关闭前一次
				mciSendString("open \"三国杀音频素材\\无懈可击.mp3\" alias wuxiemusic",NULL,0,NULL);//播放杀
				mciSendString("play wuxiemusic", NULL, 0, NULL);  //仅播放一次
				Sleep(1000);
				player[player_out]=0;
				player_out = -1;				//出牌号清空
				player_zhengli();
				player_shoupai_num--;           //手牌数减一
				isEffective=0;
				npc_desktop = 0;
				show();
				break;
			}
			if(answerover==1)	//玩家点击结束
				{
					int w=0;
					w=rand()%player_shoupai_num;	//随机抽一张玩家手牌
					putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
					setbkmode(TRANSPARENT);
					settextstyle(30, 0, _T("微软雅黑"));
					if(player[w]==1)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("对方拆了您的杀！"));
					}
					if(player[w]==2)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("对方拆了您的闪！"));
					}
					if(player[w]==3)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("对方拆了您的桃！"));
					}
					if(player[w]==4)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("对方拆了您的过河拆桥！"));
					}
					if(player[w]==5)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("对方拆了您的顺手牵羊！"));
					}
					if(player[w]==6)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("对方拆了您的桃园结义！"));
					}
					if(player[w]==7)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("对方拆了您的+1马！"));
					}
					if(player[w]==8)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("对方拆了您的-1马！"));
					}
					if(player[w]==9)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("对方拆了您的南蛮入侵！"));
					}
					if(player[w]==10)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("对方拆了您的万箭齐发！"));
					}
					if(player[w]==11)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("对方拆了您的无懈可击！"));
					}
					if(player[w]==12)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("对方拆了您的决斗！"));
					}
					if(player[w]==13)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("对方拆了您的无中生有！"));
					}
					if(player[w]==14)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("对方拆了您的诸葛连弩！"));
					}
					if(player[w]==15)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("对方拆了您的护心镜！"));
					}
					FlushBatchDraw();
					Sleep(1000);
					player[w]=0;
					player_zhengli();
					player_shoupai_num--;//玩家手牌减一
					show();
					isEffective=0;
					answerover=0;//恢复
					npc_desktop = 0;
					show();
					break;
				}
		}

		if(npc_desktop==5)	//敌方出顺手牵羊
		{
			if ((player[player_out] == 11)&&(isEffective==1))  //玩家出无懈可击
			{
				player_desktop=player[player_out];//记录桌面牌
				player_desktop2=player[player_out];//记录桌面牌
				mciSendString("close wuxiemusic", NULL, 0, NULL);  //先关闭前一次
				mciSendString("open \"三国杀音频素材\\无懈可击.mp3\" alias wuxiemusic",NULL,0,NULL);//播放杀
				mciSendString("play wuxiemusic", NULL, 0, NULL);  //仅播放一次
				Sleep(500);
				player[player_out]=0;
				player_out = -1;				//出牌号清空
				player_zhengli();
				player_shoupai_num--;           //手牌数减一
				isEffective=0;
				npc_desktop = 0;
				show();
				break;
			}
			if(answerover==1)	//玩家点击结束
				{
					int w=0;
					w=rand()%player_shoupai_num;	//随机抽一张玩家手牌
					putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
					setbkmode(TRANSPARENT);
					settextstyle(30, 0, _T("微软雅黑"));
					if(player[w]==1)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("对方顺了您的杀！"));
					}
					if(player[w]==2)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("对方顺了您的闪！"));
					}
					if(player[w]==3)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("对方顺了您的桃！"));
					}
					if(player[w]==4)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("对方顺了您的过河拆桥！"));
					}
					if(player[w]==5)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("对方顺了您的顺手牵羊！"));
					}
					if(player[w]==6)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("对方顺了您的桃园结义！"));
					}
					if(player[w]==7)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("对方顺了您的+1马！"));
					}
					if(player[w]==8)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("对方顺了您的-1马！"));
					}
					if(player[w]==9)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("对方顺了您的南蛮入侵！"));
					}
					if(player[w]==10)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("对方顺了您的万箭齐发！"));
					}
					if(player[w]==11)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("对方顺了您的无懈可击！"));
					}
					if(player[w]==12)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("对方顺了您的决斗！"));
					}
					if(player[w]==13)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("对方顺了您的无中生有！"));
					}
					if(player[w]==14)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("对方顺了您的诸葛连弩！"));
					}
					if(player[w]==15)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("对方顺了您的护心镜！"));
					}
					FlushBatchDraw();
					Sleep(1000);
					npc[npc_shoupai_num]=player[w];//npc得到这张牌
					npc_shoupai_num++;
					npc_zhengli();
					player[w]=0;
					player_zhengli();
					player_shoupai_num--;//玩家手牌减一
					show();
					isEffective=0;
					answerover=0;//恢复
					npc_desktop = 0;
					show();
					break;
				}
		}
		if(npc_desktop==6)	//敌方出桃园结义
		{
			if ((player[player_out] == 11)&&(isEffective==1))  //玩家出无懈可击
			{
				player_desktop=player[player_out];//记录桌面牌
				player_desktop2=player[player_out];//记录桌面牌
				mciSendString("close wuxiemusic", NULL, 0, NULL);  //先关闭前一次
				mciSendString("open \"三国杀音频素材\\无懈可击.mp3\" alias wuxiemusic",NULL,0,NULL);//播放杀
				mciSendString("play wuxiemusic", NULL, 0, NULL);  //仅播放一次
				Sleep(1000);
				player[player_out]=0;
				player_out = -1;				//出牌号清空
				player_zhengli();
				player_shoupai_num--;           //手牌数减一
				isEffective=0;
				npc_desktop = 0;
				show();
				break;
			}
			if(answerover==1)	//玩家点击结束
				{
					putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
					setbkmode(TRANSPARENT);
					settextstyle(30, 0, _T("微软雅黑"));
					outtextxy(PromptBox_x+20,PromptBox_y,_T("双方都加一滴血！"));
					FlushBatchDraw();
					Sleep(1000);
					if(npc_life<4)
					{
						npc_life++;
					}
					else			//满血提示
					{
						putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
						setbkmode(TRANSPARENT);
						settextstyle(30, 0, _T("微软雅黑"));
						outtextxy(PromptBox_x+20,PromptBox_y,_T("您的血是满的，奶不了了！"));
						FlushBatchDraw();
						Sleep(1000);
					}
					if(player_life<4)
					{
						player_life++;
					}
					show();
					isEffective=0;
					answerover=0;//恢复
					npc_desktop = 0;
					show();
					break;
				}
		}
		if(npc_desktop==9)	//敌方出南蛮入侵
		{
			if ((player[player_out] == 11)&&(isEffective==1))  //玩家出无懈可击
			{
				player_desktop=player[player_out];//记录桌面牌
				player_desktop2=player[player_out];//记录桌面牌
				mciSendString("close wuxiemusic", NULL, 0, NULL);  //先关闭前一次
				mciSendString("open \"三国杀音频素材\\无懈可击.mp3\" alias wuxiemusic",NULL,0,NULL);//播放杀
				mciSendString("play wuxiemusic", NULL, 0, NULL);  //仅播放一次
				Sleep(1000);
				player[player_out]=0;
				player_out = -1;				//出牌号清空
				player_zhengli();
				player_shoupai_num--;           //手牌数减一
				isEffective=0;
				npc_desktop = 0;
				show();
				break;
			}
			if((player[player_out] == 1)&&(isEffective==1))		//玩家出杀
			{
				player_desktop=player[player_out];//记录桌面牌
				player_desktop2=player[player_out];//记录桌面牌
				mciSendString("close shamusic", NULL, 0, NULL);  //先关闭前一次
				mciSendString("open \"三国杀音频素材\\杀.mp3\" alias shamusic",NULL,0,NULL);//播放杀
				mciSendString("play shamusic", NULL, 0, NULL);  //仅播放一次
				Sleep(500);
				player[player_out]=0;
				player_out = -1;				//出牌号清空
				player_zhengli();
				player_shoupai_num--;           //手牌数减一
				isEffective=0;
				npc_desktop = 0;
				show();
				break;
			}
			if(answerover==1)	//玩家点击结束
				{
					putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
					setbkmode(TRANSPARENT);
					settextstyle(30, 0, _T("微软雅黑"));
					outtextxy(PromptBox_x+20,PromptBox_y,_T("你受到一单位伤害！"));
					FlushBatchDraw();
					Sleep(1000);
					player_life--;	//玩家扣血
					show();
					isEffective=0;
					answerover=0;//恢复
					npc_desktop = 0;
					show();
					break;
				}
		}
		if(npc_desktop==10)	//敌方出万箭齐发
		{
			if ((player[player_out] == 11)&&(isEffective==1))  //玩家出无懈可击
			{
				player_desktop=player[player_out];//记录桌面牌
				player_desktop2=player[player_out];//记录桌面牌
				mciSendString("close wuxiemusic", NULL, 0, NULL);  //先关闭前一次
				mciSendString("open \"三国杀音频素材\\无懈可击.mp3\" alias wuxiemusic",NULL,0,NULL);//播放杀
				mciSendString("play wuxiemusic", NULL, 0, NULL);  //仅播放一次
				Sleep(1000);
				player[player_out]=0;
				player_out = -1;				//出牌号清空
				player_zhengli();
				player_shoupai_num--;           //手牌数减一
				isEffective=0;
				npc_desktop = 0;
				show();
				break;
			}
			if((player[player_out] == 2)&&(isEffective==1))		//玩家出闪
			{
				player_desktop=player[player_out];//记录桌面牌
				player_desktop2=player[player_out];//记录桌面牌
				mciSendString("close shanmusic", NULL, 0, NULL);  //先关闭前一次
				mciSendString("open \"三国杀音频素材\\闪.mp3\" alias shanmusic",NULL,0,NULL);//播放杀
				mciSendString("play shanmusic", NULL, 0, NULL);  //仅播放一次
				Sleep(500);
				player[player_out]=0;
				player_out = -1;				//出牌号清空
				player_zhengli();
				player_shoupai_num--;           //手牌数减一
				isEffective=0;
				npc_desktop = 0;
				show();
				break;
			}
			if(answerover==1)	//玩家点击结束
				{
					putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
					setbkmode(TRANSPARENT);
					settextstyle(30, 0, _T("微软雅黑"));
					outtextxy(PromptBox_x+20,PromptBox_y,_T("你受到一单位伤害！"));
					FlushBatchDraw();
					Sleep(1000);
					player_life--;	//玩家扣血
					show();
					isEffective=0;
					answerover=0;//恢复
					npc_desktop = 0;
					show();
					break;
				}
		}
		if(npc_desktop==13)	//敌方出无中生有
		{
			if ((player[player_out] == 11)&&(isEffective==1))  //玩家出无懈可击
			{
				player_desktop=player[player_out];//记录桌面牌
				player_desktop2=player[player_out];//记录桌面牌
				mciSendString("close wuxiemusic", NULL, 0, NULL);  //先关闭前一次
				mciSendString("open \"三国杀音频素材\\无懈可击.mp3\" alias wuxiemusic",NULL,0,NULL);//播放杀
				mciSendString("play wuxiemusic", NULL, 0, NULL);  //仅播放一次
				Sleep(1000);
				player[player_out]=0;
				player_out = -1;				//出牌号清空
				player_zhengli();
				player_shoupai_num--;           //手牌数减一
				isEffective=0;
				npc_desktop = 0;
				show();
				break;
			}
			if(answerover==1)	//玩家点击结束
				{
					putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
					setbkmode(TRANSPARENT);
					settextstyle(30, 0, _T("微软雅黑"));
					outtextxy(PromptBox_x+20,PromptBox_y,_T("敌方摸两张牌！"));
					FlushBatchDraw();
					Sleep(1000);
					npc_getnew();		//npc摸两张牌
					show();
					isEffective=0;
					answerover=0;//恢复
					npc_desktop = 0;
					show();
					break;
				}
		}
		isEffective=0;
	}
}

void player_panding()
{
	if((player_life==0)&&(isplayermirror==1))//濒死且有护心镜
	{
		isplayermirror=0;			//卸下护心镜
		player_life++;
		putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
		setbkmode(TRANSPARENT);
		settextstyle(30, 0, _T("微软雅黑"));
		outtextxy(PromptBox_x+20,PromptBox_y,_T("您的护心镜破裂，回一滴血！"));
		FlushBatchDraw();
		Sleep(1000);
		show();
	}
	if((npc_life<=0)||(player_life<=0))   //有人已死
	{
		isover = 1;
	}
	if (isRoundover == 0)   //玩家未结束回合，所点击的是有效牌
	{
		if ((player[player_out] == 1) &&((player_sha_num == 0)||(isplayerzhuge==1))&&(isEffective==1)&&(x_wanjiatonpc<=1))    //玩家出杀且是第一次出杀或有诸葛且在范围
		{
			player_desktop=player[player_out];//记录桌面牌
			player_desktop2=player[player_out];//记录桌面牌
			mciSendString("close shamusic", NULL, 0, NULL);  //先关闭前一次
			mciSendString("open \"三国杀音频素材\\杀.mp3\" alias shamusic",NULL,0,NULL);//播放杀
			mciSendString("play shamusic", NULL, 0, NULL);  //仅播放一次
			Sleep(1000);
			player[player_out] = 0;
			player_out = -1;        //出牌号清空
			player_zhengli();
			player_shoupai_num--;           //手牌数减一
			isEffective=0;
			player_sha_num++;
		}
		if ((player[player_out] == 1) && ((player_sha_num != 0)&&(isplayerzhuge==0))&&(isEffective==1)&&(x_wanjiatonpc<=1))   //玩家无连弩且第二次出杀
		{ 
			//player_sha_num++;
			player_out = -1;				//出牌号清空
			//printf("不可以出杀了哦!\n");      //禁止出杀
			putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
			setbkmode(TRANSPARENT);
			settextstyle(30, 0, _T("微软雅黑"));
			outtextxy(PromptBox_x+20,PromptBox_y,_T("无连弩不可以连续出杀哦！"));
			FlushBatchDraw();
			Sleep(1000);
			isEffective=0;
			return;  //退出判定
		}
		if ((player[player_out] == 1)&&(isEffective==1)&&(x_wanjiatonpc==2))   //玩家出杀不在范围
		{ 
			//player_sha_num++;
			player_out = -1;				//出牌号清空
			//printf("不可以出杀了哦!\n");      //禁止出杀
			putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
			setbkmode(TRANSPARENT);
			settextstyle(30, 0, _T("微软雅黑"));
			outtextxy(PromptBox_x+20,PromptBox_y,_T("杀不到他哦！"));
			FlushBatchDraw();
			Sleep(1000);
			isEffective=0;
			return;  //退出判定
		}

		if ((npc_desktop == 1)&&(npc_sha_num == 1)) //npc出有效杀且我方点击
		{
			if ((player[player_out] == 2)&&(isEffective==1))  //玩家出闪
			{
				player_desktop=player[player_out];//记录桌面牌
				player_desktop2=player[player_out];//记录桌面牌
				mciSendString("close shanmusic", NULL, 0, NULL);  //先关闭前一次
				mciSendString("open \"三国杀音频素材\\闪.mp3\" alias shanmusic",NULL,0,NULL);//播放闪
				mciSendString("play shanmusic", NULL, 0, NULL);  //仅播放一次
				Sleep(500);
				player[player_out]=0;
				player_out = -1;				//出牌号清空
				player_shan_num++;				//玩家出闪次数加一
				player_zhengli();
				player_shoupai_num--;           //手牌数减一
				isEffective=0;
				//printf("我方使用闪\n");
			}
			if((npc_desktop == 1)&&(player_shan_num == 0))	//npc出杀玩家没有闪
			{
				player_life--;
				isEffective=0;
			}
			npc_desktop = 0;
			player_shan_num = 0;
			npc_sha_num--;
			
		}
		if ((player[player_out] == 2) && (npc_desktop != 1)&&(isEffective==1))  //玩家出闪且电脑未出杀（或万箭齐发）
				{
					//printf("不可以出闪了哦！\n");   //禁止出闪
					putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
					setbkmode(TRANSPARENT);
					settextstyle(30, 0, _T("微软雅黑"));
					outtextxy(PromptBox_x+20,PromptBox_y,_T("不可以随意出闪哦！"));
					FlushBatchDraw();
					Sleep(1000);
					player_out = -1;				//出牌号清空
					isEffective=0;
					return;  //退出判定
				}
		
		if ((player[player_out] == 3) && (player_life < 4)&&(isEffective==1))
		{
			player_desktop=player[player_out];//记录桌面牌
			player_desktop2=player[player_out];//记录桌面牌
			player_life++;		//使用桃奶血
			mciSendString("close taomusic", NULL, 0, NULL);  //先关闭前一次
			mciSendString("open \"三国杀音频素材\\桃.mp3\" alias taomusic",NULL,0,NULL);//播放杀
			mciSendString("play taomusic", NULL, 0, NULL);  //仅播放一次
			Sleep(500);
			player[player_out]=0;
			player_out = -1;				//出牌号清空
			player_zhengli();
			player_shoupai_num--; //手牌减一
			isEffective=0;
		}
		if ((player[player_out] == 3) && (player_life==4)&&(isEffective==1))
		{

			putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
			setbkmode(TRANSPARENT);
			settextstyle(30, 0, _T("微软雅黑"));
			outtextxy(PromptBox_x+20,PromptBox_y,_T("您的血是满的，奶不了了！"));
			FlushBatchDraw();
			Sleep(1000);
			player_out = -1;				//出牌号清空
			isEffective=0;
			return;  //退出判定
		}
		if((player[player_out] == 4)&&(isEffective==1))				//打出过河拆桥
		{
			if(npc_shoupai_num==0)
			{
				putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
				setbkmode(TRANSPARENT);
				settextstyle(30, 0, _T("微软雅黑"));
				outtextxy(PromptBox_x+20,PromptBox_y,_T("敌方没有手牌哦，无法打出！"));
				FlushBatchDraw();
				Sleep(1000);

			}
			else
			{	
				mciSendString("close guohemusic", NULL, 0, NULL);  //先关闭前一次
				mciSendString("open \"三国杀音频素材\\过河拆桥.mp3\" alias guohemusic",NULL,0,NULL);//播放杀
				mciSendString("play guohemusic", NULL, 0, NULL);  //仅播放一次
				Sleep(1000);
				int k;
				int wuxienum=0;		//记录npc无懈次数
				player_desktop=player[player_out];//记录桌面牌
				player_desktop2=player[player_out];//记录桌面牌
				for (k = 0; k<npc_shoupai_num; k++)
				{
					if (npc[k] == 11)         //npc找到无懈可击
					{
						mciSendString("close wuxiemusic", NULL, 0, NULL);  //先关闭前一次
						mciSendString("open \"三国杀音频素材\\无懈可击.mp3\" alias wuxiemusic",NULL,0,NULL);//播放杀
						mciSendString("play wuxiemusic", NULL, 0, NULL);  //仅播放一次
						Sleep(1000);
						npc_desktop=npc[k];//记录npc桌面牌
						npc_desktop2=npc[k];//记录npc桌面牌
						npc[k] = 0;
						npc_zhengli();
						npc_shoupai_num--;  //手牌减一
						wuxienum++;
						break;
					}
				}
				if(wuxienum==0)	//npc没有无懈
				{
					//下为过河拆桥的作用
					
					k=rand()%npc_shoupai_num;	//随机抽一张npc手牌
					
					putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
					setbkmode(TRANSPARENT);
					settextstyle(30, 0, _T("微软雅黑"));
					if(npc[k]==1)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("您拆了对方的杀！"));
					}
					if(npc[k]==2)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("您拆了对方的闪！"));
					}
					if(npc[k]==3)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("您拆了对方的桃！"));
					}
					if(npc[k]==4)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("您拆了对方的过河拆桥！"));
					}
					if(npc[k]==5)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("您拆了对方的顺手牵羊！"));
					}
					if(npc[k]==6)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("您拆了对方的桃园结义！"));
					}
					if(npc[k]==7)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("您拆了对方的+1马！"));
					}
					if(npc[k]==8)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("您拆了对方的-1马！"));
					}
					if(npc[k]==9)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("您拆了对方的南蛮入侵！"));
					}
					if(npc[k]==10)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("您拆了对方的万箭齐发！"));
					}
					if(npc[k]==11)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("您拆了对方的无懈可击！"));
					}
					if(npc[k]==12)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("您拆了对方的决斗！"));
					}
					if(npc[k]==13)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("您拆了对方的无中生有！"));
					}
					if(npc[k]==14)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("您拆了对方的诸葛连弩！"));
					}
					if(npc[k]==15)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("您拆了对方的护心镜！"));
					}
					FlushBatchDraw();
					Sleep(1000);
					npc[k] = 0;			//清空拆去的牌
					npc_zhengli();
					npc_shoupai_num--;  //手牌减一

				}
				player[player_out]=0;
				player_out = -1;				//出牌号清空
				player_zhengli();
				player_shoupai_num--; //手牌减一
				isEffective=0;
			}
		}
	if((player[player_out] == 5)&&(isEffective==1))				//打出顺手牵羊
		{
			if(npc_shoupai_num==0)
			{
				putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
				setbkmode(TRANSPARENT);
				settextstyle(30, 0, _T("微软雅黑"));
				outtextxy(PromptBox_x+20,PromptBox_y,_T("敌方没有手牌哦，无法打出！"));
				FlushBatchDraw();
				Sleep(1000);

			}
			else
			{	
				mciSendString("close shunshoumusic", NULL, 0, NULL);  //先关闭前一次
				mciSendString("open \"三国杀音频素材\\顺手牵羊.mp3\" alias shunshoumusic",NULL,0,NULL);//播放杀
				mciSendString("play shunshoumusic", NULL, 0, NULL);  //仅播放一次
				Sleep(1000);
				int k;
				int wuxienum=0;		//记录npc无懈次数
				player_desktop=player[player_out];//记录桌面牌
				player_desktop2=player[player_out];//记录桌面牌
				for (k = 0; k<npc_shoupai_num; k++)
				{
					if (npc[k] == 11)         //npc找到无懈可击
					{
						mciSendString("close wuxiemusic", NULL, 0, NULL);  //先关闭前一次
						mciSendString("open \"三国杀音频素材\\无懈可击.mp3\" alias wuxiemusic",NULL,0,NULL);//播放杀
						mciSendString("play wuxiemusic", NULL, 0, NULL);  //仅播放一次
						Sleep(1000);
						npc_desktop=npc[k];//记录npc桌面牌
						npc_desktop2=npc[k];//记录npc桌面牌
						npc[k] = 0;
						npc_zhengli();
						npc_shoupai_num--;  //手牌减一
						wuxienum++;
						player[player_out]=0;
						player_out = -1;				//出牌号清空
						player_zhengli();
						player_shoupai_num--; //手牌减一
						show();
						break;
					}
				}
				if(wuxienum==0)	//npc没有无懈
				{
					//下为顺手牵羊的作用
					
					k=rand()%npc_shoupai_num;	//随机抽一张npc手牌
					
					putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
					setbkmode(TRANSPARENT);
					settextstyle(30, 0, _T("微软雅黑"));
					if(npc[k]==1)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("您顺了对方的杀！"));
					}
					if(npc[k]==2)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("您顺了对方的闪！"));
					}
					if(npc[k]==3)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("您顺了对方的桃！"));
					}
					if(npc[k]==4)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("您顺了对方的过河拆桥！"));
					}
					if(npc[k]==5)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("您顺了对方的顺手牵羊！"));
					}
					if(npc[k]==6)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("您顺了对方的桃园结义！"));
					}
					if(npc[k]==7)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("您顺了对方的+1马！"));
					}
					if(npc[k]==8)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("您顺了对方的-1马！"));
					}
					if(npc[k]==9)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("您顺了对方的南蛮入侵！"));
					}
					if(npc[k]==10)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("您顺了对方的万箭齐发！"));
					}
					if(npc[k]==11)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("您顺了对方的无懈可击！"));
					}
					if(npc[k]==12)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("您顺了对方的决斗！"));
					}
					if(npc[k]==13)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("您顺了对方的无中生有！"));
					}
					if(npc[k]==14)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("您顺了对方的诸葛连弩！"));
					}
					if(npc[k]==15)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("您顺了对方的护心镜！"));
					}
					FlushBatchDraw();
					Sleep(1000);
					player[player_out]=0;
					player_out = -1;				//出牌号清空
					player_zhengli();
					player_shoupai_num--; //手牌减一
					player[player_shoupai_num]=npc[k];	//得到这张牌
					player_shoupai_num++;//手牌数加一
					player_zhengli();
					npc[k] = 0;			//清空拆去的牌
					npc_zhengli();
					npc_shoupai_num--;  //手牌减一
					show();
				}
				isEffective=0;
			}
		}
	if((player[player_out] == 6)&&(isEffective==1))				//打出桃园结义
		{
			mciSendString("close taoyuanmusic", NULL, 0, NULL);  //先关闭前一次
			mciSendString("open \"三国杀音频素材\\桃园结义.mp3\" alias taoyuanmusic",NULL,0,NULL);//播放杀
			mciSendString("play taoyuanmusic", NULL, 0, NULL);  //仅播放一次
			Sleep(1000);
			int k;
			int wuxienum=0;		//记录npc无懈次数
			player_desktop=player[player_out];//记录桌面牌
			player_desktop2=player[player_out];//记录桌面牌
			if(player_life<npc_life)		//如果npc生命多就刚一点
			{
				for (k = 0; k<npc_shoupai_num; k++)
				{
					if (npc[k] == 11)         //npc找到无懈可击
					{
						mciSendString("close wuxiemusic", NULL, 0, NULL);  //先关闭前一次
						mciSendString("open \"三国杀音频素材\\无懈可击.mp3\" alias wuxiemusic",NULL,0,NULL);//播放杀
						mciSendString("play wuxiemusic", NULL, 0, NULL);  //仅播放一次
						Sleep(1000);
						npc_desktop=npc[k];//记录npc桌面牌
						npc_desktop2=npc[k];//记录npc桌面牌
						npc[k] = 0;
						npc_zhengli();
						npc_shoupai_num--;  //手牌减一
						wuxienum++;
						player[player_out]=0;
						player_out = -1;				//出牌号清空
						player_zhengli();
						player_shoupai_num--; //手牌减一
						break;
					}
				}
			}
			if(wuxienum==0)	//npc没有无懈
			{
				//下为桃园结义的作用
				putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
				setbkmode(TRANSPARENT);
				settextstyle(30, 0, _T("微软雅黑"));
				outtextxy(PromptBox_x+20,PromptBox_y,_T("双方增加生命！"));
				FlushBatchDraw();
				Sleep(1000);
				if(player_life<4)
				{
					player_life++;
				}
				else			//满血提示
				{
					putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
					setbkmode(TRANSPARENT);
					settextstyle(30, 0, _T("微软雅黑"));
					outtextxy(PromptBox_x+20,PromptBox_y,_T("您的血是满的，奶不了了！"));
					FlushBatchDraw();
					Sleep(1000);
				}
				if(npc_life<4)
				{
					npc_life++;
				}			//双方增加生命
				player[player_out]=0;
				player_out = -1;				//出牌号清空
				player_zhengli();
				player_shoupai_num--; //手牌减一
			}
			
			show();
			isEffective=0;
		}
	if((player[player_out] == 9)&&(isEffective==1))				//打出南蛮入侵
		{
			mciSendString("close nanmanmusic", NULL, 0, NULL);  //先关闭前一次
			mciSendString("open \"三国杀音频素材\\南蛮入侵.mp3\" alias nanmanmusic",NULL,0,NULL);//播放杀
			mciSendString("play nanmanmusic", NULL, 0, NULL);  //仅播放一次
			Sleep(1000);
			int k;
			int wuxienum=0;		//记录npc无懈次数
			int shanum=0;		//记录npc杀次数
			player_desktop=player[player_out];//记录桌面牌
			player_desktop2=player[player_out];//记录桌面牌
			for (k = 0; k<npc_shoupai_num; k++)
			{
				if (npc[k] == 1)      //npc找到杀
				{
					mciSendString("close shamusic", NULL, 0, NULL);  //先关闭前一次
					mciSendString("open \"三国杀音频素材\\杀.mp3\" alias shamusic",NULL,0,NULL);//播放杀
					mciSendString("play shamusic", NULL, 0, NULL);  //仅播放一次
					Sleep(500);
					npc_desktop=npc[k];//记录npc桌面牌
					npc_desktop2=npc[k];//记录npc桌面牌
					npc[k] = 0;
					npc_zhengli();
					npc_shoupai_num--;  //手牌减一
					shanum++;
					break;
				}
			}
			if(shanum==0)
			{
				for (k = 0; k<npc_shoupai_num; k++)
				{
					if (npc[k] == 11)      //npc找到无懈可击
					{
						mciSendString("close wuxiemusic", NULL, 0, NULL);  //先关闭前一次
						mciSendString("open \"三国杀音频素材\\无懈可击.mp3\" alias wuxiemusic",NULL,0,NULL);//播放杀
						mciSendString("play wuxiemusic", NULL, 0, NULL);  //仅播放一次
						Sleep(1000);
						npc_desktop=npc[k];//记录npc桌面牌
						npc_desktop2=npc[k];//记录npc桌面牌
						npc[k] = 0;
						npc_zhengli();
						npc_shoupai_num--;  //手牌减一
						wuxienum++;
						break;
					}
				}
			}
			if((wuxienum==0)&&(shanum==0))	//npc没有无懈和杀
			{
				//下为南蛮入侵的作用
				npc_life--;	//扣血
				show();
				putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
				setbkmode(TRANSPARENT);
				settextstyle(30, 0, _T("微软雅黑"));
				outtextxy(PromptBox_x+20,PromptBox_y,_T("敌方无杀或无懈，受到一单位伤害！"));
				FlushBatchDraw();
				Sleep(1000);
			}
			player[player_out]=0;
			player_out = -1;				//出牌号清空
			player_zhengli();
			player_shoupai_num--; //手牌减一
			show();
			isEffective=0;
		}
	if((player[player_out] == 10)&&(isEffective==1))				//打出万箭齐发
		{
			mciSendString("close wanjianmusic", NULL, 0, NULL);  //先关闭前一次
			mciSendString("open \"三国杀音频素材\\万箭齐发.mp3\" alias wanjianmusic",NULL,0,NULL);//播放杀
			mciSendString("play wanjianmusic", NULL, 0, NULL);  //仅播放一次
			Sleep(1000);
			int k;
			int wuxienum=0;		//记录npc无懈次数
			int shannum=0;		//记录npc闪次数
			player_desktop=player[player_out];//记录桌面牌
			player_desktop2=player[player_out];//记录桌面牌
			for (k = 0; k<npc_shoupai_num; k++)
			{
				if (npc[k] == 2)      //npc找到闪
				{
					mciSendString("close shanmusic", NULL, 0, NULL);  //先关闭前一次
					mciSendString("open \"三国杀音频素材\\闪.mp3\" alias shanmusic",NULL,0,NULL);//播放杀
					mciSendString("play shanmusic", NULL, 0, NULL);  //仅播放一次
					Sleep(500);
					npc_desktop=npc[k];//记录npc桌面牌
					npc_desktop2=npc[k];//记录npc桌面牌
					npc[k] = 0;
					npc_zhengli();
					npc_shoupai_num--;  //手牌减一
					shannum++;
					break;
				}
			}
			if(shannum==0)
			{
				for (k = 0; k<npc_shoupai_num; k++)
				{
					if (npc[k] == 11)      //npc找到无懈可击
					{
						mciSendString("close wuxiemusic", NULL, 0, NULL);  //先关闭前一次
						mciSendString("open \"三国杀音频素材\\无懈可击.mp3\" alias wuxiemusic",NULL,0,NULL);//播放杀
						mciSendString("play wuxiemusic", NULL, 0, NULL);  //仅播放一次
						Sleep(1000);
						npc_desktop=npc[k];//记录npc桌面牌
						npc_desktop2=npc[k];//记录npc桌面牌
						npc[k] = 0;
						npc_zhengli();
						npc_shoupai_num--;  //手牌减一
						wuxienum++;
						break;
					}
				}
			}
			if((wuxienum==0)&&(shannum==0))	//npc没有无懈和闪
			{
				//下为万箭齐发的作用
				npc_life--;	//扣血
				show();
				putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
				setbkmode(TRANSPARENT);
				settextstyle(30, 0, _T("微软雅黑"));
				outtextxy(PromptBox_x+20,PromptBox_y,_T("敌方无闪或无懈，受到一单位伤害！"));
				FlushBatchDraw();
				Sleep(1000);
			}
			player[player_out]=0;
			player_out = -1;				//出牌号清空
			player_zhengli();
			player_shoupai_num--; //手牌减一
			show();
			isEffective=0;
		}
	if((player[player_out] == 12)&&(isEffective==1))				//打出决斗
		{
			mciSendString("close juedoumusic", NULL, 0, NULL);  //先关闭前一次
			mciSendString("open \"三国杀音频素材\\决斗.mp3\" alias juedoumusic",NULL,0,NULL);//播放杀
			mciSendString("play juedoumusic", NULL, 0, NULL);  //仅播放一次
			Sleep(1000);
			int k;
			int wuxienum=0;		//记录npc无懈次数
			player_desktop=player[player_out];//记录桌面牌
			player_desktop2=player[player_out];//记录桌面牌
			for (k = 0; k<npc_shoupai_num; k++)
				{
					if (npc[k] == 11)         //npc找到无懈可击
					{
						mciSendString("close wuxiemusic", NULL, 0, NULL);  //先关闭前一次
						mciSendString("open \"三国杀音频素材\\无懈可击.mp3\" alias wuxiemusic",NULL,0,NULL);//播放杀
						mciSendString("play wuxiemusic", NULL, 0, NULL);  //仅播放一次
						Sleep(1000);
						npc_desktop=npc[k];//记录npc桌面牌
						npc_desktop2=npc[k];//记录npc桌面牌
						npc[k] = 0;
						npc_zhengli();
						npc_shoupai_num--;  //手牌减一
						wuxienum++;
						player[player_out]=0;
						player_out = -1;				//出牌号清空
						player_zhengli();
						player_shoupai_num--; //手牌减一
						break;
					}
				}
			if(wuxienum==0)	//npc没有无懈
			{
				//下为决斗的作用
				putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
				setbkmode(TRANSPARENT);
				settextstyle(30, 0, _T("微软雅黑"));
				outtextxy(PromptBox_x+20,PromptBox_y,_T("双方进入决斗！"));
				FlushBatchDraw();
				Sleep(1000);
				player[player_out]=0;
				player_out = -1;				//出牌号清空
				player_zhengli();
				player_shoupai_num--; //手牌减一
				show();
				juedou();
			}
			show();
			isEffective=0;
		}
	if((player[player_out] == 13)&&(isEffective==1))				//打出无中生有
		{
			mciSendString("close wuzhongmusic", NULL, 0, NULL);  //先关闭前一次
			mciSendString("open \"三国杀音频素材\\无中生有.mp3\" alias wuzhongmusic",NULL,0,NULL);//播放杀
			mciSendString("play wuzhongmusic", NULL, 0, NULL);  //仅播放一次
			Sleep(1000);
			int k;
			int wuxienum=0;		//记录npc无懈次数
			player_desktop=player[player_out];//记录桌面牌
			player_desktop2=player[player_out];//记录桌面牌
			for (k = 0; k<npc_shoupai_num; k++)
				{
					if (npc[k] == 11)         //npc找到无懈可击
					{
						mciSendString("close wuxiemusic", NULL, 0, NULL);  //先关闭前一次
						mciSendString("open \"三国杀音频素材\\无懈可击.mp3\" alias wuxiemusic",NULL,0,NULL);//播放杀
						mciSendString("play wuxiemusic", NULL, 0, NULL);  //仅播放一次
						Sleep(1000);
						npc_desktop=npc[k];//记录npc桌面牌
						npc_desktop2=npc[k];//记录npc桌面牌
						npc[k] = 0;
						npc_zhengli();
						npc_shoupai_num--;  //手牌减一
						wuxienum++;
						player[player_out]=0;
						player_out = -1;				//出牌号清空
						player_zhengli();
						player_shoupai_num--; //手牌减一
						break;
					}
				}
			if(wuxienum==0)	//npc没有无懈
			{
				//下为无中生有的作用
				putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
				setbkmode(TRANSPARENT);
				settextstyle(30, 0, _T("微软雅黑"));
				outtextxy(PromptBox_x+20,PromptBox_y,_T("您可摸两张牌！"));
				FlushBatchDraw();
				Sleep(1000);
				player[player_out]=0;
				player_out = -1;				//出牌号清空
				player_zhengli();
				player_shoupai_num--; //手牌减一
				player_getnew();
				show();
			}
			
			show();
			isEffective=0;
		}
	if((player[player_out] == 7)&&(isEffective==1))				//打出+1马
		{
			mciSendString("close horsemusic", NULL, 0, NULL);  //先关闭前一次
			mciSendString("open \"三国杀音频素材\\马.mp3\" alias horsemusic",NULL,0,NULL);//播放杀
			mciSendString("play horsemusic", NULL, 0, NULL);  //仅播放一次
			Sleep(1000);
			player_desktop=player[player_out];//记录桌面牌
			player_desktop2=player[player_out];//记录桌面牌
			if(isplayerh2==1)		//使用过加一马
			{
				player[player_out]=0;
				player_out = -1;				//出牌号清空
				isplayerh2=1;					//标记装备+1马
				player_zhengli();
				player_shoupai_num--; //手牌减一
			}
			if(isplayerh2==0)		//未使用过加一马
			{
				isplayerh2=1;			//标记装备+1马
				x_npctowanjia++;
				player[player_out]=0;
				player_out = -1;				//出牌号清空
				player_zhengli();
				player_shoupai_num--; //手牌减一
			}
			show();
			isEffective=0;
		}
	if((player[player_out] == 8)&&(isEffective==1))				//打出-1马
		{
			mciSendString("close horsemusic", NULL, 0, NULL);  //先关闭前一次
			mciSendString("open \"三国杀音频素材\\马.mp3\" alias horsemusic",NULL,0,NULL);//播放杀
			mciSendString("play horsemusic", NULL, 0, NULL);  //仅播放一次
			Sleep(1000);
			player_desktop=player[player_out];//记录桌面牌
			player_desktop2=player[player_out];//记录桌面牌
			if(isplayerh1==1)		//使用过减一马
			{
				player[player_out]=0;
				player_out = -1;				//出牌号清空
				isplayerh1=1;					//标记装备-1马
				player_zhengli();
				player_shoupai_num--; //手牌减一
			}
			if(isplayerh1==0)		//未使用过减一马
			{
				isplayerh1=1;			//标记装备-1马
				x_wanjiatonpc--;
				player[player_out]=0;
				player_out = -1;				//出牌号清空
				player_zhengli();
				player_shoupai_num--; //手牌减一
			}
			show();
			isEffective=0;
		}
	if((player[player_out] == 14)&&(isEffective==1))				//打出诸葛连弩
		{
			mciSendString("close liannumusic", NULL, 0, NULL);  //先关闭前一次
			mciSendString("open \"三国杀音频素材\\诸葛连弩.mp3\" alias liannumusic",NULL,0,NULL);//播放杀
			mciSendString("play liannumusic", NULL, 0, NULL);  //仅播放一次
			Sleep(1000);
			player_desktop=player[player_out];//记录桌面牌
			player_desktop2=player[player_out];//记录桌面牌
			if(isplayerzhuge==1)		//使用过诸葛连弩
			{
				player[player_out]=0;
				player_out = -1;				//出牌号清空
				isplayerzhuge=1;					//标记装备诸葛连弩
				player_zhengli();
				player_shoupai_num--; //手牌减一
			}
			if(isplayerzhuge==0)		//未使用过减诸葛连弩
			{
				isplayerzhuge=1;			//标记装备诸葛连弩
				player[player_out]=0;
				player_out = -1;				//出牌号清空
				player_zhengli();
				player_shoupai_num--; //手牌减一
			}
			show();
			isEffective=0;
		}
	if((player[player_out] == 15)&&(isEffective==1))				//打出护心镜
		{
			mciSendString("close huxinmusic", NULL, 0, NULL);  //先关闭前一次
			mciSendString("open \"三国杀音频素材\\护心镜.mp3\" alias huxinmusic",NULL,0,NULL);//播放杀
			mciSendString("play huxinmusic", NULL, 0, NULL);  //仅播放一次
			Sleep(1000);
			player_desktop=player[player_out];//记录桌面牌
			player_desktop2=player[player_out];//记录桌面牌
			if(isplayermirror==1)		//使用过护心镜
			{
				player[player_out]=0;
				player_out = -1;				//出牌号清空
				isplayermirror=1;					//标记装备护心镜
				player_zhengli();
				player_shoupai_num--; //手牌减一
			}
			if(isplayermirror==0)		//未使用过护心镜
			{
				isplayermirror=1;			//标记装备护心镜
				player[player_out]=0;
				player_out = -1;				//出牌号清空
				player_zhengli();
				player_shoupai_num--; //手牌减一
			}
			show();
			isEffective=0;
		}










	}

	if((isRoundover == 1)&&(isEffective==1))//玩家回合已结束出弃牌
	{
		player_desktop2=player[player_out];//记录以显示
		player[player_out]=0;
		player_zhengli();
		player_shoupai_num--;
		disnum++;						//已弃牌数加一
		isEffective=0;
	}
}

void npc_panding()
{
	int tempnpcshoupai=0;		//临时记录npc手牌数
	int k;
	if ((player_desktop == 1)&&((player_sha_num==1)||(isplayerzhuge==1)))   //玩家出有效杀电脑找闪否则扣血
	{
		for (k = 0; k<npc_shoupai_num; k++)
		{
			if (npc[k] == 2)         //找到闪
			{
				//printf("敌方‘英雄’使用闪！\n");
				mciSendString("close shanmusic", NULL, 0, NULL);  //先关闭前一次
				mciSendString("open \"三国杀音频素材\\闪.mp3\" alias shanmusic",NULL,0,NULL);//播放闪
				mciSendString("play shanmusic", NULL, 0, NULL);  //仅播放一次
				putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
				setbkmode(TRANSPARENT);
				settextstyle(30, 0, _T("微软雅黑"));
				outtextxy(PromptBox_x+20,PromptBox_y,_T("敌方出闪！"));
				FlushBatchDraw();
				Sleep(1000);
				npc_desktop=npc[k];//记录npc桌面牌
				npc_desktop2=npc[k];//记录npc桌面牌
				npc[k] = 0;
				npc_shoupai_num--;  //手牌减一
				npc_shan_num++;
				if((player_life==0)&&(isplayermirror==1))//濒死且有护心镜
				{
					isplayermirror=0;			//卸下护心镜
					player_life++;
					putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
					setbkmode(TRANSPARENT);
					settextstyle(30, 0, _T("微软雅黑"));
					outtextxy(PromptBox_x+20,PromptBox_y,_T("您的护心镜破裂，回一滴血！"));
					FlushBatchDraw();
					Sleep(1000);
					show();
				}
				if((npc_life==0)&&(isnpcmirror==1))//濒死且有护心镜
				{
					isnpcmirror=0;			//卸下护心镜
					npc_life++;
					putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
					setbkmode(TRANSPARENT);
					settextstyle(30, 0, _T("微软雅黑"));
					outtextxy(PromptBox_x+20,PromptBox_y,_T("敌方的护心镜破裂，回一滴血！"));
					FlushBatchDraw();
					Sleep(1000);
					show();
				}
				if((npc_life<=0)||(player_life<=0))   //有人已死
				{
					isover = 1;
					goto end;
				}
				break;
			}
		}
		if (npc_shan_num == 0)   //未使用闪。电脑扣血
		{
			npc_life--;
			//printf("敌方‘英雄’受到一单位伤害\n");
			putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
			setbkmode(TRANSPARENT);
			settextstyle(30, 0, _T("微软雅黑"));
			outtextxy(PromptBox_x+20,PromptBox_y,_T("敌方受到一单位伤害！"));
			FlushBatchDraw();
			Sleep(1000);
			if((player_life==0)&&(isplayermirror==1))//濒死且有护心镜
				{
					isplayermirror=0;			//卸下护心镜
					player_life++;
					putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
					setbkmode(TRANSPARENT);
					settextstyle(30, 0, _T("微软雅黑"));
					outtextxy(PromptBox_x+20,PromptBox_y,_T("您的护心镜破裂，回一滴血！"));
					FlushBatchDraw();
					Sleep(1000);
					show();
				}
				if((npc_life==0)&&(isnpcmirror==1))//濒死且有护心镜
				{
					isnpcmirror=0;			//卸下护心镜
					npc_life++;
					putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
					setbkmode(TRANSPARENT);
					settextstyle(30, 0, _T("微软雅黑"));
					outtextxy(PromptBox_x+20,PromptBox_y,_T("敌方的护心镜破裂，回一滴血！"));
					FlushBatchDraw();
					Sleep(1000);
					show();
				}
				if((npc_life<=0)||(player_life<=0))   //有人已死
				{
					isover = 1;
					goto end;
				}
			
		}
		player_desktop = 0;//玩家桌面牌清0
		npc_shan_num=0;//npc出闪次数清空
	}
	if (player_out == -2)//玩家回合结束，可主动出牌
	{
		tempnpcshoupai=npc_shoupai_num;
		int ss=0;	//记录npc有杀的张数
		for (k = 0; k<tempnpcshoupai; k++)		
		{
			if(npc[k]==7)	//找到+1马
			{
				npc_desktop = npc[k];//记录npc桌面牌
				npc_desktop2 =npc[k];//记录npc桌面牌
				//printf("‘英雄’使用马！\n");
				mciSendString("close horsemusic", NULL, 0, NULL);  //先关闭前一次
				mciSendString("open \"三国杀音频素材\\马.mp3\" alias horsemusic",NULL,0,NULL);//播放杀
				mciSendString("play horsemusic", NULL, 0, NULL);  //仅播放一次
				Sleep(1000);
				if(isnpch2==1)		//使用过加一马
				{
					isnpch2=1;
					npc[k] = 0;
					npc_zhengli();
					npc_shoupai_num--;  //npc手牌减一
				}
				if(isnpch2==0)		//未使用过加一马
				{
					isnpch2=1;			//标记装备+1马
					x_wanjiatonpc++;
					npc[k] = 0;
					npc_zhengli();
					npc_shoupai_num--;  //npc手牌减一
				}
				show();

			}
		}
		tempnpcshoupai=npc_shoupai_num;
		for (k = 0; k<tempnpcshoupai; k++)		
		{
			if(npc[k]==8)	//找到-1马
			{
				npc_desktop = npc[k];//记录npc桌面牌
				npc_desktop2 =npc[k];//记录npc桌面牌
				//printf("‘英雄’使用马！\n");
				mciSendString("close horsemusic", NULL, 0, NULL);  //先关闭前一次
				mciSendString("open \"三国杀音频素材\\马.mp3\" alias horsemusic",NULL,0,NULL);//播放杀
				mciSendString("play horsemusic", NULL, 0, NULL);  //仅播放一次
				Sleep(1000);
				if(isnpch1==1)		//使用过减一马
				{
					isnpch1=1;
					npc[k] = 0;
					npc_zhengli();
					npc_shoupai_num--;  //npc手牌减一
				}
				if(isnpch1==0)		//未使用过减一马
				{
					isnpch1=1;			//标记装备+1马
					x_npctowanjia--;
					npc[k] = 0;
					npc_zhengli();
					npc_shoupai_num--;  //npc手牌减一
				}
				show();

			}
		}
		tempnpcshoupai=npc_shoupai_num;
		for (k = 0; k<tempnpcshoupai; k++)		
		{
			if(npc[k]==14)	//找到诸葛连弩
			{
				npc_desktop = npc[k];//记录npc桌面牌
				npc_desktop2 =npc[k];//记录npc桌面牌
				//printf("‘英雄’使用诸葛连弩！\n");
				mciSendString("close zhugemusic", NULL, 0, NULL);  //先关闭前一次
				mciSendString("open \"三国杀音频素材\\诸葛连弩.mp3\" alias zhugemusic",NULL,0,NULL);//播放诸葛连弩
				mciSendString("play zhugemusic", NULL, 0, NULL);  //仅播放一次
				Sleep(1000);
				if(isnpczhuge==1)		//使用过诸葛连弩
				{
					isnpczhuge=1;
					npc[k] = 0;
					npc_zhengli();
					npc_shoupai_num--;  //npc手牌减一
				}
				if(isnpczhuge==0)		//未使用过诸葛连弩
				{
					isnpczhuge=1;			//标记装备诸葛连弩
					npc[k] = 0;
					npc_zhengli();
					npc_shoupai_num--;  //npc手牌减一
				}
				show();
			}
		}
		tempnpcshoupai=npc_shoupai_num;
		for (k = 0; k<tempnpcshoupai; k++)		
		{
			if(npc[k]==15)	//找到护心镜
			{
				npc_desktop = npc[k];//记录npc桌面牌
				npc_desktop2 =npc[k];//记录npc桌面牌
				//printf("‘英雄’使用护心镜！\n");
				mciSendString("close huxinmusic", NULL, 0, NULL);  //先关闭前一次
				mciSendString("open \"三国杀音频素材\\护心镜.mp3\" alias huxinmusic",NULL,0,NULL);//播放护心镜
				mciSendString("play huxinmusic", NULL, 0, NULL);  //仅播放一次
				Sleep(1000);
				if(isnpcmirror==1)		//使用过护心镜
				{
					isnpcmirror=1;
					npc[k] = 0;
					npc_zhengli();
					npc_shoupai_num--;  //npc手牌减一
				}
				if(isnpcmirror==0)		//未使用过护心镜
				{
					isnpcmirror=1;			//标记装备护心镜
					npc[k] = 0;
					npc_zhengli();
					npc_shoupai_num--;  //npc手牌减一
				}
				show();
			}
		}
		tempnpcshoupai=npc_shoupai_num;
		for (k = 0; k<tempnpcshoupai; k++)		
		{
			if(npc[k]==13)	//找到无中生有
			{
				npc_desktop = npc[k];//记录npc桌面牌
				npc_desktop2 =npc[k];//记录npc桌面牌
				//printf("‘英雄’使用无中生有！\n");
				mciSendString("close wuzhongmusic", NULL, 0, NULL);  //先关闭前一次
				mciSendString("open \"三国杀音频素材\\无中生有.mp3\" alias wuzhongmusic",NULL,0,NULL);//播放杀
				mciSendString("play wuzhongmusic", NULL, 0, NULL);  //仅播放一次
				Sleep(1000);
				putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
				setbkmode(TRANSPARENT);
				settextstyle(30, 0, _T("微软雅黑"));
				outtextxy(PromptBox_x+20,PromptBox_y,_T("选择出无懈可击或是结束！"));
				FlushBatchDraw();
				Sleep(1000);
				npc[k] = 0;
				npc_zhengli();
				npc_shoupai_num--;  //npc手牌减一
				player_answer();
				show();

			}
		}
		tempnpcshoupai=npc_shoupai_num;
		for (k = 0; k<tempnpcshoupai; k++)		
		{
			if((npc_life<4)&&(npc[k] == 3))   //先找桃奶自己一口
			{
				npc_desktop = npc[k];//记录npc桌面牌
				npc_desktop2 =npc[k];//记录npc桌面牌
				mciSendString("close taomusic", NULL, 0, NULL);  //先关闭前一次
				mciSendString("open \"三国杀音频素材\\桃.mp3\" alias taomusic",NULL,0,NULL);//播放桃
				mciSendString("play taomusic", NULL, 0, NULL);  //仅播放一次
				Sleep(500);
				npc[k] = 0;
				npc_life++;			//生命加一
				npc_shoupai_num--;  //手牌减一
			}
		}
		tempnpcshoupai=npc_shoupai_num;
		for (k = 0; k<tempnpcshoupai; k++)		
		{

			if(((npc_life<player_life)||(npc_life==1))&&(player_life!=1))	//劣势
			{
				if (npc[k] == 6)       //找到桃园结义
				{
					npc_desktop = npc[k];//记录npc桌面牌
					npc_desktop2 =npc[k];//记录npc桌面牌
					//printf("‘英雄’使用桃园结义！\n");
					mciSendString("close taoyuanmusic", NULL, 0, NULL);  //先关闭前一次
					mciSendString("open \"三国杀音频素材\\桃园结义.mp3\" alias taoyuanmusic",NULL,0,NULL);//播放杀
					mciSendString("play taoyuanmusic", NULL, 0, NULL);  //仅播放一次
					Sleep(1000);
					putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
					setbkmode(TRANSPARENT);
					settextstyle(30, 0, _T("微软雅黑"));
					outtextxy(PromptBox_x+20,PromptBox_y,_T("选择出无懈可击或是结束！"));
					FlushBatchDraw();
					Sleep(1000);
					npc[k] = 0;
					npc_zhengli();
					npc_shoupai_num--;  //npc手牌减一
					player_answer();
					show();
				}
			}
		}
		tempnpcshoupai=npc_shoupai_num;
		for (k = 0; k<tempnpcshoupai; k++)		
		{

			if ((npc[k] == 5)&&(player_shoupai_num>0))     //找到顺手牵羊且有牌可顺
			{
				npc_desktop = npc[k];//记录npc桌面牌
				npc_desktop2 =npc[k];//记录npc桌面牌
				//printf("‘英雄’使用顺手牵羊！\n");
				mciSendString("close shunshoumusic", NULL, 0, NULL);  //先关闭前一次
				mciSendString("open \"三国杀音频素材\\顺手牵羊.mp3\" alias shunshoumusic",NULL,0,NULL);//播放杀
				mciSendString("play shunshoumusic", NULL, 0, NULL);  //仅播放一次
				Sleep(1000);
				putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
				setbkmode(TRANSPARENT);
				settextstyle(30, 0, _T("微软雅黑"));
				outtextxy(PromptBox_x+20,PromptBox_y,_T("选择出无懈可击或是结束！"));
				FlushBatchDraw();
				Sleep(1000);
				npc[k] = 0;
				npc_zhengli();
				npc_shoupai_num--;  //npc手牌减一
				player_answer();
				show();
			}
		}
		tempnpcshoupai=npc_shoupai_num;
		for (k = 0; k<tempnpcshoupai; k++)		
		{
			if ((npc[k] == 4)&&(player_shoupai_num>0))      //找到过河拆桥且有东西可拆
			{
				npc_desktop = npc[k];//记录npc桌面牌
				npc_desktop2 =npc[k];//记录npc桌面牌
				//printf("‘英雄’使用过河拆桥！\n");
				mciSendString("close guohemusic", NULL, 0, NULL);  //先关闭前一次
				mciSendString("open \"三国杀音频素材\\过河拆桥.mp3\" alias guohemusic",NULL,0,NULL);//播放杀
				mciSendString("play guohemusic", NULL, 0, NULL);  //仅播放一次
				Sleep(1000);
				putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
				setbkmode(TRANSPARENT);
				settextstyle(30, 0, _T("微软雅黑"));
				outtextxy(PromptBox_x+20,PromptBox_y,_T("选择出无懈可击或是结束！"));
				FlushBatchDraw();
				Sleep(1000);
				player_answer();
				npc[k] = 0;
				npc_zhengli();
				npc_shoupai_num--;  //npc手牌减一
				show();
			}
		}
		tempnpcshoupai=npc_shoupai_num;
		for (k = 0; k<tempnpcshoupai; k++)		
		{

			if (npc[k] == 9)      //找到南蛮入侵
			{
				npc_desktop = npc[k];//记录npc桌面牌
				npc_desktop2 =npc[k];//记录npc桌面牌
				//printf("‘英雄’使用南蛮入侵！\n");
				mciSendString("close nanmanmusic", NULL, 0, NULL);  //先关闭前一次
				mciSendString("open \"三国杀音频素材\\南蛮入侵.mp3\" alias nanmanmusic",NULL,0,NULL);//播放杀
				mciSendString("play nanmanmusic", NULL, 0, NULL);  //仅播放一次
				Sleep(1000);
				putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
				setbkmode(TRANSPARENT);
				settextstyle(30, 0, _T("微软雅黑"));
				outtextxy(PromptBox_x+20,PromptBox_y,_T("选择出无懈可击或是出杀或是结束！"));
				FlushBatchDraw();
				Sleep(1000);
				npc[k] = 0;
				npc_zhengli();
				npc_shoupai_num--;  //npc手牌减一
				player_answer();
				if((player_life==0)&&(isplayermirror==1))//濒死且有护心镜
				{
					isplayermirror=0;			//卸下护心镜
					player_life++;
					putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
					setbkmode(TRANSPARENT);
					settextstyle(30, 0, _T("微软雅黑"));
					outtextxy(PromptBox_x+20,PromptBox_y,_T("您的护心镜破裂，回一滴血！"));
					FlushBatchDraw();
					Sleep(1000);
					show();
				}
				if((npc_life==0)&&(isnpcmirror==1))//濒死且有护心镜
				{
					isnpcmirror=0;			//卸下护心镜
					npc_life++;
					putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
					setbkmode(TRANSPARENT);
					settextstyle(30, 0, _T("微软雅黑"));
					outtextxy(PromptBox_x+20,PromptBox_y,_T("敌方的护心镜破裂，回一滴血！"));
					FlushBatchDraw();
					Sleep(1000);
					show();
				}
				if((npc_life<=0)||(player_life<=0))   //有人已死
				{
					isover = 1;
					goto end;
				}
				show();
			}
		}
		tempnpcshoupai=npc_shoupai_num;
		for (k = 0; k<tempnpcshoupai; k++)		
		{
			if (npc[k] == 10)      //找到万箭齐发
			{
				npc_desktop = npc[k];//记录npc桌面牌
				npc_desktop2 =npc[k];//记录npc桌面牌
				//printf("‘英雄’使用万箭齐发！\n");
				mciSendString("close wanjianmusic", NULL, 0, NULL);  //先关闭前一次
				mciSendString("open \"三国杀音频素材\\万箭齐发.mp3\" alias wanjianmusic",NULL,0,NULL);//播放杀
				mciSendString("play wanjianmusic", NULL, 0, NULL);  //仅播放一次
				Sleep(1000);
				putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
				setbkmode(TRANSPARENT);
				settextstyle(30, 0, _T("微软雅黑"));
				outtextxy(PromptBox_x+20,PromptBox_y,_T("选择出无懈可击或是出闪或是结束！"));
				FlushBatchDraw();
				Sleep(1000);
				npc[k] = 0;
				npc_zhengli();
				npc_shoupai_num--;  //npc手牌减一
				player_answer();
				if((player_life==0)&&(isplayermirror==1))//濒死且有护心镜
				{
					isplayermirror=0;			//卸下护心镜
					player_life++;
					putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
					setbkmode(TRANSPARENT);
					settextstyle(30, 0, _T("微软雅黑"));
					outtextxy(PromptBox_x+20,PromptBox_y,_T("您的护心镜破裂，回一滴血！"));
					FlushBatchDraw();
					Sleep(1000);
					show();
				}
				if((npc_life==0)&&(isnpcmirror==1))//濒死且有护心镜
				{
					isnpcmirror=0;			//卸下护心镜
					npc_life++;
					putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
					setbkmode(TRANSPARENT);
					settextstyle(30, 0, _T("微软雅黑"));
					outtextxy(PromptBox_x+20,PromptBox_y,_T("敌方的护心镜破裂，回一滴血！"));
					FlushBatchDraw();
					Sleep(1000);
					show();
				}
				if((npc_life<=0)||(player_life<=0))   //有人已死
				{
					isover = 1;
					goto end;
				}
				show();
			}
		}
		tempnpcshoupai=npc_shoupai_num;
		for (k = 0; k<tempnpcshoupai; k++)		
		{
			if(npc[k] == 1)
			{
				ss++;		//记录有一张杀
			}
			
			if ((npc[k] == 1) &&((npc_sha_num==0)||(isnpczhuge==1))&&(x_npctowanjia<=1))        //找到杀且本回合第一次使用或有连弩且在范围
			{
				npc_desktop = npc[k];//记录npc桌面牌
				npc_desktop2 =npc[k];//记录npc桌面牌
				//printf("‘英雄’使用杀！\n");
				mciSendString("close shamusic", NULL, 0, NULL);  //先关闭前一次
				mciSendString("open \"三国杀音频素材\\杀.mp3\" alias shamusic",NULL,0,NULL);//播放杀
				mciSendString("play shamusic", NULL, 0, NULL);  //仅播放一次
				Sleep(500);
				npc[k] = 0;
				npc_zhengli();
				npc_shoupai_num--;  //手牌减一
				npc_sha_num++;
				show();
				putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
				setbkmode(TRANSPARENT);
				settextstyle(30, 0, _T("微软雅黑"));
				outtextxy(PromptBox_x+20,PromptBox_y,_T("选择出闪或是结束！"));
				FlushBatchDraw();
				Sleep(1000);
				player_answer();
				if((player_life==0)&&(isplayermirror==1))//濒死且有护心镜
				{
					isplayermirror=0;			//卸下护心镜
					player_life++;
					putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
					setbkmode(TRANSPARENT);
					settextstyle(30, 0, _T("微软雅黑"));
					outtextxy(PromptBox_x+20,PromptBox_y,_T("您的护心镜破裂，回一滴血！"));
					FlushBatchDraw();
					Sleep(1000);
					show();
				}
				if((npc_life==0)&&(isnpcmirror==1))//濒死且有护心镜
				{
					isnpcmirror=0;			//卸下护心镜
					npc_life++;
					putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
					setbkmode(TRANSPARENT);
					settextstyle(30, 0, _T("微软雅黑"));
					outtextxy(PromptBox_x+20,PromptBox_y,_T("敌方的护心镜破裂，回一滴血！"));
					FlushBatchDraw();
					Sleep(1000);
					show();
				}
				if((npc_life<=0)||(player_life<=0))   //有人已死
				{
					isover = 1;
					goto end;
				}

			}

		}
		if((npc_life==0)&&(isnpcmirror==1))//濒死且有护心镜
		{
			isnpcmirror=0;			//卸下护心镜
			npc_life++;
			putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
			setbkmode(TRANSPARENT);
			settextstyle(30, 0, _T("微软雅黑"));
			outtextxy(PromptBox_x+20,PromptBox_y,_T("敌方的护心镜破裂，回一滴血！"));
			FlushBatchDraw();
			Sleep(1000);
			show();
		}
		if((npc_life<=0)||(player_life<=0))   //有人已死
		{
			isover = 1;
		}
		if((ss>1)||((ss==1)&&(player_shoupai_num<4)))		//优化npc出决斗的时机
		{
			for(k=0;k<npc_shoupai_num;k++)
			{
				if (npc[k] == 12)      //找到决斗
				{
					npc_desktop = npc[k];//记录npc桌面牌
					npc_desktop2 =npc[k];//记录npc桌面牌
					//printf("‘英雄’使用决斗！\n");
					mciSendString("close juedoumusic", NULL, 0, NULL);  //先关闭前一次
					mciSendString("open \"三国杀音频素材\\决斗.mp3\" alias juedoumusic",NULL,0,NULL);//播放杀
					mciSendString("play juedoumusic", NULL, 0, NULL);  //仅播放一次
					Sleep(500);
					putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
					setbkmode(TRANSPARENT);
					settextstyle(30, 0, _T("微软雅黑"));
					outtextxy(PromptBox_x+20,PromptBox_y,_T("选择出无懈可击或是出杀或是结束！"));
					FlushBatchDraw();
					Sleep(1000);
					npc[k] = 0;
					npc_zhengli();
					npc_shoupai_num--;  //npc手牌减一
					juedoupeople=1;
					juedou();			//进入决斗
					show();
					break;
				}
			}
		}


	}
	if((npc_life==0)&&(isnpcmirror==1))//濒死且有护心镜
	{
		isnpcmirror=0;			//卸下护心镜
		npc_life++;
		putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
		setbkmode(TRANSPARENT);
		settextstyle(30, 0, _T("微软雅黑"));
		outtextxy(PromptBox_x+20,PromptBox_y,_T("敌方的护心镜破裂，回一滴血！"));
		FlushBatchDraw();
		Sleep(1000);
		show();
	}
	if((npc_life<=0)||(player_life<=0))   //有人已死
	{
		isover = 1;
	}

end:;
}

void juedou()
{
	isjuedou=1;		//开始决斗
	if(juedoupeople==0)	//玩家主动决斗
	{
		while(1)
		{
			int k;
			int pp=0;//记录临时决斗中单一回合杀的次数
			for (k = 0; k<npc_shoupai_num; k++)
			{
				if(npc[k]==1)	//找到杀
				{
					npc_desktop = npc[k];//记录npc桌面牌
					npc_desktop2 =npc[k];//记录npc桌面牌
					mciSendString("close shamusic", NULL, 0, NULL);  //先关闭前一次
					mciSendString("open \"三国杀音频素材\\杀.mp3\" alias shamusic",NULL,0,NULL);//播放杀
					mciSendString("play shamusic", NULL, 0, NULL);  //仅播放一次
					Sleep(500);
					pp++;
					npc[k] = 0;
					npc_zhengli();
					npc_shoupai_num--;  //手牌减一
					show();
					putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
					setbkmode(TRANSPARENT);
					settextstyle(30, 0, _T("微软雅黑"));
					outtextxy(PromptBox_x+20,PromptBox_y,_T("请您出杀！"));
					FlushBatchDraw();
					Sleep(1000);
					player_answer();
					if((player_life==0)&&(isplayermirror==1))//濒死且有护心镜
					{
						isplayermirror=0;			//卸下护心镜
						player_life++;
						putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
						setbkmode(TRANSPARENT);
						settextstyle(30, 0, _T("微软雅黑"));
						outtextxy(PromptBox_x+20,PromptBox_y,_T("您的护心镜破裂，回一滴血！"));
						FlushBatchDraw();
						Sleep(1000);
						show();
					}
					if((npc_life==0)&&(isnpcmirror==1))//濒死且有护心镜
					{
						isnpcmirror=0;			//卸下护心镜
						npc_life++;
						putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
						setbkmode(TRANSPARENT);
						settextstyle(30, 0, _T("微软雅黑"));
						outtextxy(PromptBox_x+20,PromptBox_y,_T("敌方的护心镜破裂，回一滴血！"));
						FlushBatchDraw();
						Sleep(1000);
						show();
					}
					if((npc_life<=0)||(player_life<=0))   //有人已死
					{
						isover = 1;
						goto end;
					}
					break;
				}
			}
			if(pp==0)		//说明单一回合电脑无杀
			{
				putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
				setbkmode(TRANSPARENT);
				settextstyle(30, 0, _T("微软雅黑"));
				outtextxy(PromptBox_x+20,PromptBox_y,_T("敌方未出杀，决斗你赢了，敌方受到一单位伤害！"));
				FlushBatchDraw();
				Sleep(1000);
				npc_life--;		//扣血
				show();
				isjuedou=0;		//
				break;		//决斗以我方赢结束
			}
			if(isjuedou==0)
			{
				break;		//决斗以我方输结束
			}
		}
	}
	if(juedoupeople==1)	//npc主动决斗
	{
		player_answer();
		if((player_life==0)&&(isplayermirror==1))//濒死且有护心镜
		{
			isplayermirror=0;			//卸下护心镜
			player_life++;
			putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
			setbkmode(TRANSPARENT);
			settextstyle(30, 0, _T("微软雅黑"));
			outtextxy(PromptBox_x+20,PromptBox_y,_T("您的护心镜破裂，回一滴血！"));
			FlushBatchDraw();
			Sleep(1000);
			show();
		}
		if((npc_life<=0)||(player_life<=0))   //有人已死
		{
			isover = 1;
		}
		if(juedoupeople==-1)		//表示被无懈了
		{
			juedoupeople=0;
		}
		else if(isjuedou==0)		//玩家决斗输了
		{
		}
		else if(juedoupeople==0)		//表示出杀了
		{
			while(1)
			{
				int k;
				int pp=0;//记录临时决斗中单一回合杀的次数
				for (k = 0; k<npc_shoupai_num; k++)
				{
					if(npc[k]==1)	//找到杀
					{
						npc_desktop = npc[k];//记录npc桌面牌
						npc_desktop2 =npc[k];//记录npc桌面牌
						mciSendString("close shamusic", NULL, 0, NULL);  //先关闭前一次
						mciSendString("open \"三国杀音频素材\\杀.mp3\" alias shamusic",NULL,0,NULL);//播放杀
						mciSendString("play shamusic", NULL, 0, NULL);  //仅播放一次
						Sleep(500);
						pp++;
						npc[k] = 0;
						npc_zhengli();
						npc_shoupai_num--;  //手牌减一
						show();
						putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
						setbkmode(TRANSPARENT);
						settextstyle(30, 0, _T("微软雅黑"));
						outtextxy(PromptBox_x+20,PromptBox_y,_T("请您出杀！"));
						FlushBatchDraw();
						Sleep(1000);
								player_answer();
						if((player_life==0)&&(isplayermirror==1))//濒死且有护心镜
						{
							isplayermirror=0;			//卸下护心镜
							player_life++;
							putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
							setbkmode(TRANSPARENT);
							settextstyle(30, 0, _T("微软雅黑"));
							outtextxy(PromptBox_x+20,PromptBox_y,_T("您的护心镜破裂，回一滴血！"));
							FlushBatchDraw();
							Sleep(1000);
							show();
						}
						if((npc_life==0)&&(isnpcmirror==1))//濒死且有护心镜
						{
							isnpcmirror=0;			//卸下护心镜
							npc_life++;
							putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
							setbkmode(TRANSPARENT);
							settextstyle(30, 0, _T("微软雅黑"));
							outtextxy(PromptBox_x+20,PromptBox_y,_T("敌方的护心镜破裂，回一滴血！"));
							FlushBatchDraw();
							Sleep(1000);
							show();
						}
						if((npc_life<=0)||(player_life<=0))   //有人已死
						{
							isover = 1;
							goto end;
						}
						break;
					}
				}
				if(pp==0)		//说明单一回合电脑无杀
				{
					putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
					setbkmode(TRANSPARENT);
					settextstyle(30, 0, _T("微软雅黑"));
					outtextxy(PromptBox_x+20,PromptBox_y,_T("敌方未出杀，决斗你赢了，敌方受到一单位伤害！"));
					FlushBatchDraw();
					Sleep(1000);
					npc_life--;		//扣血
					show();
					isjuedou=0;		//
					break;		//决斗以我方赢结束
				}
				if(isjuedou==0)
				{
					break;		//决斗以我方输结束
				}

			}
		}
		
	}
end:;
}


void interactive()
{
	int i;
	MOUSEMSG m;
	if (MouseHit()) //有鼠标消息时执行
	{
		m=GetMouseMsg();

		
			if (m.uMsg==WM_LBUTTONDOWN)
			{
				for (i=0;(i<player_shoupai_num)&&(!isselected);i++)
				{
					if ((m.x>=player_x[i]&&m.x<=player_x[i]+player_width)&&(m.y>=player_y[i]&&m.y<=player_y[i]+player_high))
					{
						player_out=i;
						player_y[i]-=20;//突出
						isselected=1;
						goto end0;
					}
				
				}
				
				if ((isselected)&&(m.x>=player_x[player_out]&&m.x<=player_x[player_out]+player_width)&&(m.y>=player_y[player_out]&&m.y<=player_y[player_out]+player_high))
				{
					player_y[player_out]+=20;//缩回
					player_out=-1;
					isselected=0;
				}
				if ((isselected)&&(isAbletoPlaycard)&&(m.x>=firm_x&&m.x<=firm_x+firm_width)&&(m.y>=firm_y&&m.y<=firm_y+firm_high))
				{
					isEffective=1;
					player_y[player_out]+=20;
					isselected=0;
				}
				if ((m.x>=roundover_x&&m.x<=roundover_x+roundover_width)&&(m.y>=roundover_y&&m.y<=roundover_y+roundover_high))
				{
					if(isRoundover==0)
					{
						isselected=0;
						isRoundover=1;
							//回合结束
					}
					else if((isRoundover==1)&&(disnum==0))	//不想弃牌了
					{
						isplayer_discard=0;				//不弃牌，图框消失
						isselected=0;
						isRoundover=0;
					}
					
				}
				if(OverValue==2)			//第二关才有
				{
					if (((!isPrompt)&&(!isPrompt1))&&(m.x>=JiNangTiShi_x&&m.x<=JiNangTiShi_x+firm_width)&&(m.y>=JiNangTiShi_y&&m.y<=JiNangTiShi_y+firm_high))
					{
						isPrompt=1;
						goto end0;
					}
					if ((isPrompt)&&(m.x>=JiNangTiShi_x&&m.x<=JiNangTiShi_x+firm_width)&&(m.y>=JiNangTiShi_y&&m.y<=JiNangTiShi_y+firm_high))
					{
						isPrompt=0;
					
					}
					
				}
				if(OverValue==3)			//第二关才有
				{
					if (((!isPrompt)&&(!isPrompt1))&&(m.x>=JiNangTiShi_x&&m.x<=JiNangTiShi_x+firm_width)&&(m.y>=JiNangTiShi_y&&m.y<=JiNangTiShi_y+firm_high))
					{
						isPrompt1=1;
						goto end0;
					}
					if ((isPrompt1)&&(m.x>=JiNangTiShi_x&&m.x<=JiNangTiShi_x+firm_width)&&(m.y>=JiNangTiShi_y&&m.y<=JiNangTiShi_y+firm_high))
					{
						isPrompt1=0;
					
					}
				}
				if(OverValue==5)			//最后都有
				{
					if (((!isPrompt)&&(!isPrompt1))&&(m.x>=JiNangTiShi_x&&m.x<=JiNangTiShi_x+firm_width)&&(m.y>=JiNangTiShi_y&&m.y<=JiNangTiShi_y+firm_high))
					{
						isPrompt=1;
						goto end0;
					}
					if ((isPrompt)&&(m.x>=JiNangTiShi_x&&m.x<=JiNangTiShi_x+firm_width)&&(m.y>=JiNangTiShi_y&&m.y<=JiNangTiShi_y+firm_high))
					{
						isPrompt=0;
					
					}
					if (((!isPrompt)&&(!isPrompt1))&&(m.x>=zhuangbeitishi_x&&m.x<=zhuangbeitishi_x+firm_width)&&(m.y>=zhuangbeitishi_y&&m.y<=zhuangbeitishi_y+firm_high))
					{
						isPrompt1=1;
						goto end0;
					}
					if ((isPrompt1)&&(m.x>=zhuangbeitishi_x&&m.x<=zhuangbeitishi_x+firm_width)&&(m.y>=zhuangbeitishi_y&&m.y<=zhuangbeitishi_y+firm_high))
					{
						isPrompt1=0;
					
					}
				}
				

	
			}
end0:;
	
	
	
	}
}


void interactive_answer()
{
	int i;
	MOUSEMSG m;
	if (MouseHit()) //有鼠标消息时执行
	{
		m=GetMouseMsg();

		
			if (m.uMsg==WM_LBUTTONDOWN)
			{
				for (i=0;(i<player_shoupai_num)&&(!isselected);i++)
				{
					if ((m.x>=player_x[i]&&m.x<=player_x[i]+player_width)&&(m.y>=player_y[i]&&m.y<=player_y[i]+player_high))
					{
						player_out=i;
						player_y[i]-=20;//突出
						isselected=1;
						goto end0;
					}
				
				}
				
				if ((isselected)&&(m.x>=player_x[player_out]&&m.x<=player_x[player_out]+player_width)&&(m.y>=player_y[player_out]&&m.y<=player_y[player_out]+player_high))
				{
					player_y[player_out]+=20;//缩回
					player_out=-1;
					isselected=0;
				}
				if ((isselected)&&(isAbletoPlaycard)&&(m.x>=firm_x&&m.x<=firm_x+firm_width)&&(m.y>=firm_y&&m.y<=firm_y+firm_high))
				{
					isEffective=1;
					player_y[player_out]+=20;
					isselected=0;
				}
				if ((m.x>=roundover_x&&m.x<=roundover_x+roundover_width)&&(m.y>=roundover_y&&m.y<=roundover_y+roundover_high))
				{		
					answerover=1;			//点击结束，而不反应
				}

	
			}
end0:;
	
	
	
	}

}

void huihe_player()   //玩家回合
{
	while (1)
	{
		if(isover == 1)	//有人死，游戏结束了
		{
			break;
		}
		interactive();//鼠标交互
		if(isRoundover==0)			//非弃牌点击
		{
			player_panding();  //判定
			player_zhengli();   //整理
			show();
			npc_panding();//交给电脑判定
			npc_zhengli();//npc整理手牌
		}
		if(isRoundover==1)   //玩家回合结束弃牌
		{
			player_discard();
			player_panding();  //判定
			player_zhengli();   //整理
		}
		if(player_out==-2)
		{
			break;
		}
		show();     //清屏显示
		isEffective=0;
	}
}

void huihe_npc()      //电脑回合
{
	npc_panding();
	npc_zhengli();
	npc_discard();	//弃牌
	player_sha_num=0;			//为新回合做准备
	npc_sha_num = 0;
	player_shan_num=0;			//为新回合做准备
	npc_shan_num = 0;
	player_out=-1;
	isRoundover=0;
	//player_desktop2=0;
	//npc_desktop2=0;
	disnum=0;
	show();
}

void gameover()
{
		while(1)
	{											
		putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
		putimage(over_x,over_y,&img_RoundOver);
		setbkmode(TRANSPARENT);
		settextstyle(30, 0, _T("微软雅黑"));
		if(npc_life<=0)
		{
			if (OverValue!=5)
			{
			putimage(restart_x,restart_y,&img_next);
			outtextxy(PromptBox_x+20,PromptBox_y,_T("你赢了！"));
			outtextxy(PromptBox_x+20,PromptBox_y+20,_T("本局结束！"));
			}
			else
			{
			putimage(restart_x,restart_y,&img_restart);
			outtextxy(PromptBox_x+20,PromptBox_y,_T("你赢了！"));
			outtextxy(PromptBox_x+20,PromptBox_y+20,_T("本局结束！"));
			}
		}
		if(player_life<=0)
		{
			putimage(restart_x,restart_y,&img_restart);
			outtextxy(PromptBox_x+20,PromptBox_y,_T("你输了！"));
			outtextxy(PromptBox_x+20,PromptBox_y+20,_T("本局结束！"));
		}
		MOUSEMSG m;
		
			
				m=GetMouseMsg();
				if (m.uMsg==WM_LBUTTONDOWN)
				{
			
					if ((!player_life)&&(m.x>=restart_x&&m.x<=restart_x+firm_width)&&(m.y>=restart_y&&m.y<=restart_y+firm_high))
					{
						isover=0;
						if(OverValue==5)
						{
							OverValue--;
						}
						break;
					}
					if ((m.x>=restart_x&&m.x<=restart_x+firm_width)&&(m.y>=restart_y&&m.y<=restart_y+firm_high))
					{
						isover=0;
						
						if (OverValue!=5)
						{
							OverValue++;
						}
						
						

						break;
					}    //下一关
					if ((m.x>=over_x&&m.x<=over_x+roundover_width)&&(m.y>=over_y&&m.y<=over_y+roundover_high))
					{
						isover=0;
						OverValue=0;
						break;
					}	//结束游戏			
				}
			
		//}
		
		EndBatchDraw();
	
		
		
		
		//exit(0);		//现阶段直接退出
	}
}

void gamestart()
{
	while (1)
	{
		putimage(0,0,&img_bk);
		putimage(Prompt_x,Prompt_y+100,&img_propmt);
		putimage(width/2-firm_width/2,restart_y+100,&img_start);
		setbkmode(TRANSPARENT);
		settextstyle(30, 0, _T("微软雅黑"));
		outtextxy(Prompt_x+60,Prompt_y+160,_T("声明：本游戏为《三国杀》新手教程，会教会你基"));
		outtextxy(Prompt_x+60,Prompt_y+200,_T("础手牌的使用，常见锦囊牌的使用以及装备牌的简"));
		outtextxy(Prompt_x+60,Prompt_y+240,_T("单介绍。本游戏一共有三个关卡，通关后才可随意"));
		outtextxy(Prompt_x+60,Prompt_y+280,_T("选择哦！开始游戏请点击下方按钮，让我们一起开"));
		outtextxy(Prompt_x+60,Prompt_y+320,_T("始奇妙的三国之旅吧！准备好了吗？"));
		outtextxy(Prompt_x+30,Prompt_y+380,_T("开发人员：泉水组组长：杨飞缘，组员：葛雨凡，黄立力"));
		outtextxy(Prompt_x+190,Prompt_y+420,_T("河海大学19级计科二班"));
		MOUSEMSG m;		
		m=GetMouseMsg();
		
			if (m.uMsg==WM_LBUTTONDOWN)
			{
				if ((m.x>=width/2-firm_width/2)&&(m.x<=width/2+firm_width/2)&&(m.y>=restart_y+100)&&(m.y<=restart_y+100+firm_high))
				{
					OverValue=1;
					break;					
				}			
			}		
		FlushBatchDraw();
	}
}


int main()
{	
	initgraph(width,high);
	DataStartup(); //数据初始化
	ImgStartup();  // 图像初始化
	gamestart();   //游戏开始
	mciSendString("open \"三国杀音频素材\\背景音乐.mp3\" alias bk1music",NULL,0,NULL);  //播放背景音乐
	mciSendString("play bk1music repeat",NULL,0,NULL);  //循环播放
	while(1)
	{
		BeginBatchDraw();
		if(OverValue==4)
		{
			startup_4();	//弹出提示：新手教程结束
		}
		if(OverValue==0)
		{
			exit(0);	//结束
		}
		if(OverValue==1)
		{
			startup_1();	//第一关
		}
		if(OverValue==2)
		{
			startup_2();	//第二关
		}
		if(OverValue==3)
		{
			startup_3();	//第三关
		}
	
		if(OverValue==5)
		{
			startup_5();	//正式战斗
		}
		while (1)  //  游戏循环执行
		{
			 
			show();  // 显示画面
			player_getnew();//玩家摸牌
			huihe_player();   //玩家回合
			if(isover == 1)		//游戏结束
			{
				break;
			}
			putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
			setbkmode(TRANSPARENT);
			settextstyle(30, 0, _T("微软雅黑"));
			outtextxy(PromptBox_x+20,PromptBox_y,_T("敌方回合！"));
			FlushBatchDraw();
			Sleep(500);
			npc_getnew();//电脑摸牌
			huihe_npc();      //电脑回合
			if(isover == 1)		//游戏结束
			{
				break;
			}
		
		}
		gameover();     // 游戏结束、后续处理
	}

	
	return 0;
}