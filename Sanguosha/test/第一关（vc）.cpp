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
const int roundover_high=41,roundover_width=100,grayfirm_high=42,grayfirm_width=125;		//����ͼƬ�زĵĳߴ�
const int PromptBox_High=180,PromptBox_Width=630,StagePlaycard_high=18,StagePlaycard_width=141;

int ui_y,ui_x,player_x[6],player_y[6],HeroUi_x,HeroUi_y,HeroHp_x,HeroHp_y,grayfirm_x,grayfirm_y;
int equipment_x,equipment_y,npcUi_x,npcUi_y,npcHp_x,npcHp_y,firm_x,firm_y,roundover_x,roundover_y;	
int PromptBox_x,PromptBox_y,StagePlaycard_x,StagePlaycard_y,Stageplayer_discard_x,Stageplayer_discard_y,back_x,back_y,player_desktop_x,player_desktop_y,npc_desktop_x,npc_desktop_y;
int Weapon_x,Weapon_y,Armor_x,Armor_y,Horse1_x,Horse1_y,Horse2_x,Horse2_y;
int Prompt_x,Prompt_y,JiNangTiShi_x,JiNangTiShi_y,zhuangbeitishi_x,zhuangbeitishi_y;
int restart_x,restart_y,over_x,over_y,NpcWeapon_x,NpcWeapon_y,NpcArmor_x,NpcArmor_y,NpcHorse1_x,NpcHorse1_y,NpcHorse2_x,NpcHorse2_y;
	
//����ͼƬ�زĵ�����

int player_AbandonNum;   //����������
int player_AbandonNum_once;//��һ���Լ�¼
int npc_AbandonNum;   //����������

int isstart;             //�Ƿ�ʼ��Ϸ
int isselected;		   //�Ƿ�ѡ��ĳ����
int isRoundover;	   //�غ��Ƿ����
int isAbletoPlaycard;  //��ѡ�������ܷ���
int isEffective;	   //�Ƿ�������
int isplayer_discard;         //�Ƿ���Ҫ����
int isPrompt;				//�Ƿ���ʾ����
int isPrompt1;				//�Ƿ���ʾװ��
int isplayerh2;				//����Ƿ�װ����һ��
int isplayerh1;				//����Ƿ�װ����һ��
int isnpch2;				//npc�Ƿ�װ����һ��
int isnpch1;				//npc�Ƿ�װ����һ��
int isplayerzhuge;				//����Ƿ�װ���������
int isnpcmirror;				//����Ƿ�װ���������
int isplayermirror;				//����Ƿ�װ�����ľ�
int isnpczhuge;				//����Ƿ�װ�����ľ�
int answerover;			//�Ƿ�Ӧ�Խ���
int OverValue=1;			//����ֵ������һ����ô��
int juedoupeople=0;			//��ע�����ˣ���1Ϊnpc

int i, j;
int paidui[57];  //�����ƶ�
int player[8] = { 0 }, player_shoupai_num;  //�������,������
char c_player[8][20];  //��������ַ�
int npc[8] = { 0 }, npc_shoupai_num;     //�������ƣ�������
int player_out = -1; //��ҳ��ƺ�
int npc_out = -1; //���Գ��ƺ�
int player_life, npc_life;  //��ң���������ֵ
int npc_sha_num = 0;;//���Գ�ɱ����
int npc_shan_num = 0;   //npc��������
int player_sha_num =0;//��ҳ�ɱ����
int player_shan_num = 0;   //��ҳ�������
int player_qipai_num = 0, npc_qipai_num = 0;
int player_weapon = 0, npc_weapon = 0;
int paihao = 0; //�ƺ�
int tmp[2];
char c_tmp[2][20];
int player_desktop=-1,npc_desktop=-1;//���������ϵ���
int player_desktop2=-1,npc_desktop2=-1;//���������ϵ���
int isover=0;						//0Ϊ��Ϸδ����
int disnum=0;		//����Ѿ�������
int isjuedou;		//�Ƿ��ھ���
int x_wanjiatonpc=1;		//��ҵ�npc�ľ���
int x_npctowanjia=1;		//npc����ҵľ���
					

char Promptplayer_discardContent[50]={"������  �������������غ�..."};

//���ֺ���
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

void gotoxy(int x, int y)     //�����Ը�������
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
	for (i=0;i<6;i++) //��ʼ����������
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


void startup_1()       //��һ���ƶѳ�ʼ��
{
	paihao=0;
	mciSendString("close kaishimusic", NULL, 0, NULL);  //�ȹر�ǰһ��
	mciSendString("open \"����ɱ��Ƶ�ز�\\��ʼ��Ƶ.mp3\" alias kaishimusic",NULL,0,NULL);//����ɱ
	mciSendString("play kaishimusic", NULL, 0, NULL);  //������һ��
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

	player_life = 1; //Ҫ����Ӣ��ѡ���ж�
	player[0] = 1;//ɱ
	player[1] = 3;//��
	player[2] = 2;//��
	player[3] = 1;//ɱ
	player_shoupai_num = 4;
	
	npc_life = 1;
	npc[0] = 1;//ɱ
	npc[1] = 1;
	npc[2] = 1;
	npc[3] = 2;//��
	npc_shoupai_num = 4;
}

void startup_2()
{
	paihao=0;
	mciSendString("close kaishimusic", NULL, 0, NULL);  //�ȹر�ǰһ��
	mciSendString("open \"����ɱ��Ƶ�ز�\\��ʼ��Ƶ.mp3\" alias kaishimusic",NULL,0,NULL);//����ɱ
	mciSendString("play kaishimusic", NULL, 0, NULL);  //������һ��
	player_sha_num=0;
	player_shan_num=0;
	npc_sha_num=0;
	npc_shan_num=0;
	paidui[0] = 11;	//��и
	paidui[1] = 3;	//��//���
	paidui[2] = 12;	//����
	paidui[3] = 2;	//npc
	paidui[4] = 4;
	paidui[5] = 13;//��������//���
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


	player_life = 3; //Ҫ����Ӣ��ѡ���ж�
	player[0] = 1;//ɱ
	player[1] = 2;//��
	player[2] = 5;//˳��ǣ��
	player[3] = 9;//��������
	player_shoupai_num = 4;
	
	npc_life = 3;
	npc[0] = 2;//��
	npc[1] = 10;//����뷢
	npc[2] = 1;
	npc[3] = 4;//���Ӳ���
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
	mciSendString("close kaishimusic", NULL, 0, NULL);  //�ȹر�ǰһ��
	mciSendString("open \"����ɱ��Ƶ�ز�\\��ʼ��Ƶ.mp3\" alias kaishimusic",NULL,0,NULL);//����ɱ
	mciSendString("play kaishimusic", NULL, 0, NULL);  //������һ��
	player_sha_num=0;
	player_shan_num=0;
	npc_sha_num=0;
	npc_shan_num=0;
	paidui[0] = 2;	
	paidui[1] = 3;	//��//���
	paidui[2] = 7;	//+1��
	paidui[3] = 14;	//npc
	paidui[4] = 8;	//-1��
	paidui[5] = 13;	//��������//���
	paidui[6] = 6;
	paidui[7] = 1;	//npc
	paidui[8] = 1;
	paidui[9] = 14;	//����������
	paidui[10] = 1;
	paidui[11] = 3;	//npc
	paidui[12] = 15;	//���ľ�
	paidui[13] = 10;	//���
	paidui[14] = 1;
	paidui[15] = 1;	//npc
	paidui[16] = 1;
	paidui[17] = 1;		//���
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


	player_life = 2; //Ҫ����Ӣ��ѡ���ж�
	player[0] = 1;//ɱ
	player[1] = 2;//��
	player[2] = 14;
	player[3] = 15;//��������
	player_shoupai_num = 4;
	
	npc_life = 2;
	npc[0] = 8;//��
	npc[1] = 10;//����뷢
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
		settextstyle(30, 0, _T("΢���ź�"));
		outtextxy(Prompt_x+30,Prompt_y+180,_T("��ϲ��������ֽ̳̣����������ѡ����ϰ֮ǰ�Ĺؿ���"));
		outtextxy(Prompt_x+30,Prompt_y+220,_T("���ǽ���ʵս������׼�������𣿵�Ȼ����Ҳ����ѡ����"));
		outtextxy(Prompt_x+30,Prompt_y+260,_T("����Ϸ������ܰ��ʾ��ע����Ϸʱ�䣬��ɫ����Ŷ����"));


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
	mciSendString("close kaishimusic", NULL, 0, NULL);  //�ȹر�ǰһ��
	mciSendString("open \"����ɱ��Ƶ�ز�\\��ʼ��Ƶ.mp3\" alias kaishimusic",NULL,0,NULL);//����ɱ
	mciSendString("play kaishimusic", NULL, 0, NULL);  //������һ��
	//��ʽս��
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

void washcard()		//ϴ�Ƴ���
{
	int temp;
	int i,j;
	for (i = 0; i < 15; i++)
	{
		paidui[i] = 1;//���ƶѸ�ֵ0-9Ϊɱ
	}
	for (i = 15; i < 30; i++)
	{
		paidui[i] = 2;//���ƶѸ�ֵ10-19Ϊ��
	}
	for (i = 30; i < 33; i++)
	{
		paidui[i] = 3;//���ƶѸ�ֵ20-24Ϊ��
	}
	for (i = 33; i < 35; i++)
	{
		paidui[i] = 4;//���ƶѸ�ֵ25-27Ϊ���Ӳ���
	}
	for (i = 35; i < 37; i++)
	{
		paidui[i] = 5;//���ƶѸ�ֵ28-30Ϊ˳��ǣ��
	}
	for (i = 37; i < 39; i++)
	{
		paidui[i] = 6;//���ƶѸ�ֵ31-33Ϊ��԰����
	}
	for (i = 39; i < 41; i++)
	{
		paidui[i] = 7;//���ƶѸ�ֵ34-35Ϊ+1�� 
	}
	for (i = 41; i < 43; i++)
	{
		paidui[i] = 8;//���ƶѸ�ֵ36-37Ϊ-1�� 
	}
	for (i = 43; i < 45; i++)
	{
		paidui[i] = 14;//���ƶѸ�ֵ38������� 
	}
	for (i = 45; i < 47; i++)
	{
		paidui[i] = 15;//���ƶѸ�ֵ39���ľ�
	}
	for (i = 47; i < 49; i++)
	{
		paidui[i] = 9;//���ƶѸ�ֵ40-42Ϊ��������
	}
	for (i = 49; i < 51; i++)
	{
		paidui[i] = 10;//���ƶѸ�ֵ43-45Ϊ����뷢
	}
	for (i = 51; i < 53; i++)
	{
		paidui[i] = 11;//���ƶѸ�ֵ46-47Ϊ��и�ɻ�
	}
	for (i = 53; i < 55; i++)
	{
		paidui[i] = 12;//���ƶѸ�ֵ48-50Ϊ����
	}
	for (i = 55; i < 57; i++)
	{
		paidui[i] = 13;//���ƶѸ�ֵ51-53Ϊ��������
	}
	for (i = 0; i <57; i++)
	{
		j = rand() % 57;//�漴����
		temp = paidui[i];
		paidui[i] = paidui[j];
		paidui[j] = temp;
	}
}


void player_discard()  //���ƽ׶�
{
	if(disnum==0)		//��ÿ�غϵ�һ������ʱ��¼
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
	if(disnum>=player_AbandonNum_once)//�Ѿ��������
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
	settextstyle(30, 0, _T("΢���ź�"));
	outtextxy(PromptBox_x+20,PromptBox_y,_T("�з������У�"));
	FlushBatchDraw();
	Sleep(1000);

}

int CanPlaycard() //���ܳ��Ƶ�������������ȷ�ϰ�ť��ɫ�ʱ仯��
{
	
	
	
	return isAbletoPlaycard;
}

void ImgStartup()
{
	
	initgraph(width,high);
		
	loadimage(&img_bk,"����ɱͼƬ�ز�\\background.jpg");
	loadimage(&img_ui,"����ɱͼƬ�ز�\\ui.png");
	loadimage(&img_slash,"����ɱͼƬ�ز�\\ɱ.png");
	loadimage(&img_jink,"����ɱͼƬ�ز�\\��.png");
	loadimage(&img_HeroUi,"����ɱͼƬ�ز�\\heroui.png");
	loadimage(&img_hp,"����ɱͼƬ�ز�\\hp.png");
	loadimage(&img_EquipmentUi,"����ɱͼƬ�ز�\\equipmentui.png");
	loadimage(&img_npcUi,"����ɱͼƬ�ز�\\npc_ui.png");
	loadimage(&img_RoundOver,"����ɱͼƬ�ز�\\roundover.png");
	loadimage(&img_firm,"����ɱͼƬ�ز�\\firm.png");
	loadimage(&img_grayfirm,"����ɱͼƬ�ز�\\grayfirm.png");
	loadimage(&img_PromptBox,"����ɱͼƬ�ز�\\promptbox.png");
	loadimage(&img_peach,"����ɱͼƬ�ز�\\peach.png");
	loadimage(&img_back,"����ɱͼƬ�ز�\\back.png");
	loadimage(&img_StagePlaycard,"����ɱͼƬ�ز�\\stageplaycard.png");
	loadimage(&img_Stageplayer_discard,"����ɱͼƬ�ز�\\stageplayer_discard.png");
	loadimage(&img_NanMan,"����ɱͼƬ�ز�\\��������.png");
	loadimage(&img_WanJian,"����ɱͼƬ�ز�\\����뷢.png");
	loadimage(&img_WuZhong,"����ɱͼƬ�ز�\\��������.png");
	loadimage(&img_JueDou,"����ɱͼƬ�ز�\\����.png");
	loadimage(&img_TaoYuan,"����ɱͼƬ�ز�\\��԰����.png");
	loadimage(&img_QianYang,"����ɱͼƬ�ز�\\˳��ǣ��.png");
	loadimage(&img_ChaiQiao,"����ɱͼƬ�ز�\\���Ӳ���.png");
	loadimage(&img_WuXie,"����ɱͼƬ�ز�\\��и�ɻ�.png");
	loadimage(&img_ZhuGeLianNuShouPai,"����ɱͼƬ�ز�\\�����������.png");
	loadimage(&img_ZhuGeLianNuZhuangBei,"����ɱͼƬ�ز�\\װ���������.png");
	loadimage(&img_WuGu,"����ɱͼƬ�ز�\\��ȷ��.png");
	loadimage(&img_JieDao,"����ɱͼƬ�ز�\\�赶ɱ��.png");
	loadimage(&img_propmt,"����ɱͼƬ�ز�\\prompt.png");
	loadimage(&img_JinNangTiShi,"����ɱͼƬ�ز�\\������ʾ.png");
	loadimage(&img_zhuangbeitishi,"����ɱͼƬ�ز�\\װ����ʾ.png");
	loadimage(&img_next,"����ɱͼƬ�ز�\\next.png");
	loadimage(&img_restart,"����ɱͼƬ�ز�\\restart.png");
	loadimage(&img_start,"����ɱͼƬ�ز�\\start.png");
	loadimage(&img_horse1,"����ɱͼƬ�ز�\\horse1.png");
	loadimage(&img_horse2,"����ɱͼƬ�ز�\\horse2.png");
	loadimage(&img_EquipHorse1,"����ɱͼƬ�ز�\\equiphorse1.png");
	loadimage(&img_EquipHorse2,"����ɱͼƬ�ز�\\equiphorse2.png");
	loadimage(&img_mirror,"����ɱͼƬ�ز�\\mirror.png");
	loadimage(&img_EquipMirror,"����ɱͼƬ�ز�\\equipmirror.png");
	loadimage(&img_level1,"����ɱͼƬ�ز�\\level1.png");
	loadimage(&img_level2,"����ɱͼƬ�ز�\\level2.png");
	loadimage(&img_level3,"����ɱͼƬ�ز�\\level3.png");
	loadimage(&img_real,"����ɱͼƬ�ز�\\real.png");

	BeginBatchDraw();
}

/*void turn()         //�������ֻ�Ϊ����//�ֽ���ע�����ã�����������
{
	int i;
	for (i = 0; player[i] != 0; i++)
	{
		if (player[i] == 1)
		{
			strcpy(c_player[i], "ɱ");
		}
		else if (player[i] == 2)
		{
			strcpy(c_player[i], "��");
		}
		else if (player[i] == 3)
		{
			strcpy(c_player[i], "��");
		}
		else if (player[i] == 4)
		{
			strcpy(c_player[i], "���Ӳ���");
		}
		else if (player[i] == 5)
		{
			strcpy(c_player[i], "˳��ǣ��");
		}
		else if (player[i] == 6)
		{
			strcpy(c_player[i], "��԰����");
		}
		else if (player[i] == 7)
		{
			strcpy(c_player[i], "��ȷ��");
		}
		else if (player[i] == 8)
		{
			strcpy(c_player[i], "�赶ɱ��");
		}
		else if (player[i] == 9)
		{
			strcpy(c_player[i], "��������");
		}
		else if (player[i] == 10)
		{
			strcpy(c_player[i], "����뷢");
		}
		else if (player[i] == 11)
		{
			strcpy(c_player[i], "��и�ɻ�");
		}
		else if (player[i] == 12)
		{
			strcpy(c_player[i], "����");
		}
		else if (player[i] == 13)
		{
			strcpy(c_player[i], "��������");
		}
	}
}*/


void player_getnew()
{
	
	putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
	setbkmode(TRANSPARENT);
	settextstyle(30, 0, _T("΢���ź�"));
	outtextxy(PromptBox_x+20,PromptBox_y,_T("�ҷ������У�"));
	FlushBatchDraw();
	Sleep(1000);
	int t;
	int i,j;
	for (i = 0; player[i] != 0; i++)
	{ }//�ҵ���β
	t = i;
	for (j = t; j < t+2; j++)
	{	
		if(paihao>55)	//�����ƶѳ���
		{
			washcard();
			paihao=0;
		}
		player[j] = paidui[paihao];
		paidui[paihao] = 0;  //��ҳ������ƣ������ƶѴ�����������
		paihao++;
	}
	player_shoupai_num+=2;//�Ӷ�

}
void npc_getnew()
{
	
	putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
	setbkmode(TRANSPARENT);
	settextstyle(30, 0, _T("΢���ź�"));
	outtextxy(PromptBox_x+20,PromptBox_y,_T("�з������У�"));
	FlushBatchDraw();
	Sleep(1000);
	int t;
	int i,j;
	for (i = 0; npc[i] != 0; i++)
	{ }//�ҵ���β
	t = i;
	for (j = t; j < t + 2; j++)
	{
		if(paihao>55)	//�����ƶѳ���
		{
			washcard();
			paihao=0;
		}
		npc[j] = paidui[paihao];
		paidui[paihao] = 0;  //��ҳ������ƣ������ƶѴ�����������
		paihao++;
	}
	npc_shoupai_num+=2;//�Ӷ�
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
		}             //����player����
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
		}             //����npc����
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
	settextstyle(30, 0, _T("΢���ź�"));
	outtextxy(back_x+12,back_y+15,48+npc_shoupai_num);

	for (i=0;i<player_life;i++)
	{
		putimage(i*(hp_width+15)+HeroHp_x,HeroHp_y,&img_hp);
	}
	for (i=0;i<npc_life;i++)
	{
		putimage(i*(hp_width+20)+npcHp_x,npcHp_y,&img_hp);
	}                                //����Ѫ��
	
	if (isselected)
	{
		if (CanPlaycard())   //ȷ��UI����ɫ�仯
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
			continue;//ɱ
		}
		if (player[i]==2)
		{
			putimage(player_x[i],player_y[i],&img_jink);
			continue;//��
		}
		if (player[i]==3)
		{
			putimage(player_x[i],player_y[i],&img_peach);
			continue;//��
		}
		if (player[i]==4)
		{
			putimage(player_x[i],player_y[i],&img_ChaiQiao);
			continue;//���Ӳ���
		}
		if (player[i]==5)
		{
			putimage(player_x[i],player_y[i],&img_QianYang);
			continue;//˳��ǣ��
		}
		if (player[i]==6)
		{
			putimage(player_x[i],player_y[i],&img_TaoYuan);
			continue;//��԰����
		}
		if (player[i]==7)
		{
			putimage(player_x[i],player_y[i],&img_horse2);
			continue;//+1��
		}
		if (player[i]==8)
		{
			putimage(player_x[i],player_y[i],&img_horse1);
			continue;//-1��
		}
		if (player[i]==9)
		{
			putimage(player_x[i],player_y[i],&img_NanMan);
			continue;//��������
		}
		if (player[i]==10)
		{
			putimage(player_x[i],player_y[i],&img_WanJian);
			continue;//����뷢
		}
		if (player[i]==11)
		{
			putimage(player_x[i],player_y[i],&img_WuXie);
			continue;//��и�ɻ�
		}
		if (player[i]==12)
		{
			putimage(player_x[i],player_y[i],&img_JueDou);
			continue;//����
		}
		if (player[i]==13)
		{
			putimage(player_x[i],player_y[i],&img_WuZhong);
			continue;//��������
		}
		if (player[i]==14)
		{
			putimage(player_x[i],player_y[i],&img_ZhuGeLianNuShouPai);
			continue;//�������
		}
		if (player[i]==15)
		{
			putimage(player_x[i],player_y[i],&img_mirror);
			continue;//���ľ�
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
		settextstyle(20, 0, _T("����"));
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
			settextstyle(25, 0, _T("΢���ź�"));
			outtextxy(Prompt_x+20,Prompt_y,_T("���Ӳ��ţ�����Է�һ����"));
			outtextxy(Prompt_x+20,Prompt_y+30,_T("˳��ǣ��ѡȡ�Է�һ���Ƽ����Լ�����"));
			outtextxy(Prompt_x+20,Prompt_y+60,_T("����뷢������������������ɫ����һ�����������ܵ�һ���˺�"));
			outtextxy(Prompt_x+20,Prompt_y+90,_T("�������֣�����������������ɫ����һ��ɱ�������ܵ�һ���˺�"));
			outtextxy(Prompt_x+20,Prompt_y+120,_T("��԰���壺���н�ɫ�ظ�һ������"));
			outtextxy(Prompt_x+20,Prompt_y+150,_T("�������У���������������"));
			outtextxy(Prompt_x+20,Prompt_y+180,_T("�����������ָ���Ľ�ɫ������ɱֱ������δ���ߣ�δ�����ܵ�һ���˺�"));
			outtextxy(Prompt_x+20,Prompt_y+210,_T("��ȷ�ǣ����ƶ���ȡ�����ڳ�������ȵ���,�ӳ����߿�ʼ����ѡȡ���"));
			outtextxy(Prompt_x+20,Prompt_y+240,_T("�赶ɱ�ˣ�ѡ��һ����ɫ����һ����ɱ,��������ɱ����װ���ƹ���"));
			outtextxy(Prompt_x+20,Prompt_y+270,_T("��и�ɻ���ĳ��������Чǰ�ɴ����ʹ����Ч"));	
		}
		if (isPrompt1)
		{
			putimage(Prompt_x,Prompt_y,&img_propmt);
			setbkmode(TRANSPARENT);
			settextstyle(25, 0, _T("΢���ź�"));
			outtextxy(Prompt_x+80,Prompt_y+60,_T("+1�����ӵз����Լ��ľ��룬���������Լ����з��ľ�"));
			outtextxy(Prompt_x+80,Prompt_y+90,_T("�롣ע������ɱ����Ч�����1��"));
			outtextxy(Prompt_x+80,Prompt_y+120,_T("-1�������Լ����з��ľ��룬�������ٵз����Լ��ľ��롣"));
			outtextxy(Prompt_x+80,Prompt_y+150,_T("������󣺵����غϿɳ���ʹ��ɱ��"));
			outtextxy(Prompt_x+80,Prompt_y+180,_T("���ľ���������Ѫ��Ϊ1��ʱ����ʧȥ���ľ�����Ѫһ�Ρ�"));
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
		interactive_answer();//��꽻��
		show();//��ʾһ��
		if((isjuedou==1)&&(juedoupeople==1))		//����и�ɻ��ľ���
		{
			if ((player[player_out] == 11)&&(isEffective==1))  //��ҳ���и�ɻ�
			{
				player_desktop=player[player_out];//��¼������
				player_desktop2=player[player_out];//��¼������
				mciSendString("close wuxiemusic", NULL, 0, NULL);  //�ȹر�ǰһ��
				mciSendString("open \"����ɱ��Ƶ�ز�\\��и�ɻ�.mp3\" alias wuxiemusic",NULL,0,NULL);//����ɱ
				mciSendString("play wuxiemusic", NULL, 0, NULL);  //������һ��
				Sleep(1000);
				player[player_out]=0;
				player_out = -1;				//���ƺ����
				player_zhengli();
				player_shoupai_num--;           //��������һ
				isEffective=0;
				npc_desktop = 0;
				show();
				juedoupeople=-1;				//����ֵ
				break;
			}
			if ((player[player_out] == 1)&&(isEffective==1))  //��ҳ�ɱ
			{
				player_desktop=player[player_out];//��¼������
				player_desktop2=player[player_out];//��¼������
				mciSendString("close shamusic", NULL, 0, NULL);  //�ȹر�ǰһ��
				mciSendString("open \"����ɱ��Ƶ�ز�\\ɱ.mp3\" alias shamusic",NULL,0,NULL);//����ɱ
				mciSendString("play shamusic", NULL, 0, NULL);  //������һ��
				Sleep(500);
				player[player_out]=0;
				player_out = -1;				//���ƺ����
				player_zhengli();
				player_shoupai_num--;           //��������һ
				isEffective=0;
				show();
				juedoupeople=0;				//����ֵ
				break;
			}
			if(answerover==1)	//��ҵ������
				{
					putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
					setbkmode(TRANSPARENT);
					settextstyle(30, 0, _T("΢���ź�"));
					outtextxy(PromptBox_x+20,PromptBox_y,_T("��������ˣ��ܵ�һ��λ�˺���"));
					FlushBatchDraw();
					Sleep(1000);
					player_life--;		//��Ѫ
					show();
					isEffective=0;
					answerover=0;//�ָ�
					isjuedou = 0;
					show();
					break;
				}


		}
		if((isjuedou==1)&&(juedoupeople==0))		//����
		{
			if ((player[player_out] == 1)&&(isEffective==1))  //��ҳ�ɱ
			{
				player_desktop=player[player_out];//��¼������
				player_desktop2=player[player_out];//��¼������
				mciSendString("close shamusic", NULL, 0, NULL);  //�ȹر�ǰһ��
				mciSendString("open \"����ɱ��Ƶ�ز�\\ɱ.mp3\" alias shamusic",NULL,0,NULL);//����ɱ
				mciSendString("play shamusic", NULL, 0, NULL);  //������һ��
				Sleep(500);
				player[player_out]=0;
				player_out = -1;				//���ƺ����
				player_zhengli();
				player_shoupai_num--;           //��������һ
				isEffective=0;
				show();
				break;
			}
			if(answerover==1)	//��ҵ������
				{
					putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
					setbkmode(TRANSPARENT);
					settextstyle(30, 0, _T("΢���ź�"));
					outtextxy(PromptBox_x+20,PromptBox_y,_T("��������ˣ��ܵ�һ��λ�˺���"));
					FlushBatchDraw();
					Sleep(1000);
					player_life--;		//��Ѫ
					show();
					isEffective=0;
					answerover=0;//�ָ�
					isjuedou = 0;
					show();
					break;
				}

		}
		if(npc_desktop==1)	//�з���ɱ
		{
			if ((npc_desktop == 1)&&(npc_sha_num == 1)) //npc����Чɱ���ҷ����
			{
				if ((player[player_out] == 2)&&(isEffective==1))  //��ҳ���
				{
					player_desktop=player[player_out];//��¼������
					player_desktop2=player[player_out];//��¼������
					mciSendString("close shanmusic", NULL, 0, NULL);  //�ȹر�ǰһ��
					mciSendString("open \"����ɱ��Ƶ�ز�\\��.mp3\" alias shanmusic",NULL,0,NULL);//������
					mciSendString("play shanmusic", NULL, 0, NULL);  //������һ��
					Sleep(500);
					player[player_out]=0;
					player_out = -1;				//���ƺ����
					player_zhengli();
					player_shan_num++;				//��ҳ���������һ
					player_shoupai_num--;           //��������һ
					isEffective=0;
					npc_desktop = 0;
					//printf("�ҷ�ʹ����\n");
					show();
					break;
				}
				if(answerover==1)	//��ҵ������
				{
					player_life--;
					isEffective=0;
					answerover=0;//�ָ�
					npc_desktop = 0;
					show();
					putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
					setbkmode(TRANSPARENT);
					settextstyle(30, 0, _T("΢���ź�"));
					outtextxy(PromptBox_x+20,PromptBox_y,_T("���ܵ�һ����λ�˺���"));
					FlushBatchDraw();
					Sleep(1000);
					break;
				}
				//npc_sha_num--;
			}
		}
		if(npc_desktop==4)	//�з������Ӳ���
		{
			if ((player[player_out] == 11)&&(isEffective==1))  //��ҳ���и�ɻ�
			{
				player_desktop=player[player_out];//��¼������
				player_desktop2=player[player_out];//��¼������
				mciSendString("close wuxiemusic", NULL, 0, NULL);  //�ȹر�ǰһ��
				mciSendString("open \"����ɱ��Ƶ�ز�\\��и�ɻ�.mp3\" alias wuxiemusic",NULL,0,NULL);//����ɱ
				mciSendString("play wuxiemusic", NULL, 0, NULL);  //������һ��
				Sleep(1000);
				player[player_out]=0;
				player_out = -1;				//���ƺ����
				player_zhengli();
				player_shoupai_num--;           //��������һ
				isEffective=0;
				npc_desktop = 0;
				show();
				break;
			}
			if(answerover==1)	//��ҵ������
				{
					int w=0;
					w=rand()%player_shoupai_num;	//�����һ���������
					putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
					setbkmode(TRANSPARENT);
					settextstyle(30, 0, _T("΢���ź�"));
					if(player[w]==1)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("�Է���������ɱ��"));
					}
					if(player[w]==2)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("�Է�������������"));
					}
					if(player[w]==3)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("�Է����������ң�"));
					}
					if(player[w]==4)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("�Է��������Ĺ��Ӳ��ţ�"));
					}
					if(player[w]==5)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("�Է���������˳��ǣ��"));
					}
					if(player[w]==6)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("�Է�����������԰���壡"));
					}
					if(player[w]==7)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("�Է���������+1��"));
					}
					if(player[w]==8)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("�Է���������-1��"));
					}
					if(player[w]==9)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("�Է����������������֣�"));
					}
					if(player[w]==10)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("�Է�������������뷢��"));
					}
					if(player[w]==11)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("�Է�����������и�ɻ���"));
					}
					if(player[w]==12)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("�Է��������ľ�����"));
					}
					if(player[w]==13)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("�Է����������������У�"));
					}
					if(player[w]==14)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("�Է����������������"));
					}
					if(player[w]==15)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("�Է��������Ļ��ľ���"));
					}
					FlushBatchDraw();
					Sleep(1000);
					player[w]=0;
					player_zhengli();
					player_shoupai_num--;//������Ƽ�һ
					show();
					isEffective=0;
					answerover=0;//�ָ�
					npc_desktop = 0;
					show();
					break;
				}
		}

		if(npc_desktop==5)	//�з���˳��ǣ��
		{
			if ((player[player_out] == 11)&&(isEffective==1))  //��ҳ���и�ɻ�
			{
				player_desktop=player[player_out];//��¼������
				player_desktop2=player[player_out];//��¼������
				mciSendString("close wuxiemusic", NULL, 0, NULL);  //�ȹر�ǰһ��
				mciSendString("open \"����ɱ��Ƶ�ز�\\��и�ɻ�.mp3\" alias wuxiemusic",NULL,0,NULL);//����ɱ
				mciSendString("play wuxiemusic", NULL, 0, NULL);  //������һ��
				Sleep(500);
				player[player_out]=0;
				player_out = -1;				//���ƺ����
				player_zhengli();
				player_shoupai_num--;           //��������һ
				isEffective=0;
				npc_desktop = 0;
				show();
				break;
			}
			if(answerover==1)	//��ҵ������
				{
					int w=0;
					w=rand()%player_shoupai_num;	//�����һ���������
					putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
					setbkmode(TRANSPARENT);
					settextstyle(30, 0, _T("΢���ź�"));
					if(player[w]==1)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("�Է�˳������ɱ��"));
					}
					if(player[w]==2)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("�Է�˳����������"));
					}
					if(player[w]==3)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("�Է�˳�������ң�"));
					}
					if(player[w]==4)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("�Է�˳�����Ĺ��Ӳ��ţ�"));
					}
					if(player[w]==5)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("�Է�˳������˳��ǣ��"));
					}
					if(player[w]==6)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("�Է�˳��������԰���壡"));
					}
					if(player[w]==7)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("�Է�˳������+1��"));
					}
					if(player[w]==8)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("�Է�˳������-1��"));
					}
					if(player[w]==9)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("�Է�˳�������������֣�"));
					}
					if(player[w]==10)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("�Է�˳����������뷢��"));
					}
					if(player[w]==11)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("�Է�˳��������и�ɻ���"));
					}
					if(player[w]==12)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("�Է�˳�����ľ�����"));
					}
					if(player[w]==13)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("�Է�˳�������������У�"));
					}
					if(player[w]==14)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("�Է�˳�������������"));
					}
					if(player[w]==15)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("�Է�˳�����Ļ��ľ���"));
					}
					FlushBatchDraw();
					Sleep(1000);
					npc[npc_shoupai_num]=player[w];//npc�õ�������
					npc_shoupai_num++;
					npc_zhengli();
					player[w]=0;
					player_zhengli();
					player_shoupai_num--;//������Ƽ�һ
					show();
					isEffective=0;
					answerover=0;//�ָ�
					npc_desktop = 0;
					show();
					break;
				}
		}
		if(npc_desktop==6)	//�з�����԰����
		{
			if ((player[player_out] == 11)&&(isEffective==1))  //��ҳ���и�ɻ�
			{
				player_desktop=player[player_out];//��¼������
				player_desktop2=player[player_out];//��¼������
				mciSendString("close wuxiemusic", NULL, 0, NULL);  //�ȹر�ǰһ��
				mciSendString("open \"����ɱ��Ƶ�ز�\\��и�ɻ�.mp3\" alias wuxiemusic",NULL,0,NULL);//����ɱ
				mciSendString("play wuxiemusic", NULL, 0, NULL);  //������һ��
				Sleep(1000);
				player[player_out]=0;
				player_out = -1;				//���ƺ����
				player_zhengli();
				player_shoupai_num--;           //��������һ
				isEffective=0;
				npc_desktop = 0;
				show();
				break;
			}
			if(answerover==1)	//��ҵ������
				{
					putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
					setbkmode(TRANSPARENT);
					settextstyle(30, 0, _T("΢���ź�"));
					outtextxy(PromptBox_x+20,PromptBox_y,_T("˫������һ��Ѫ��"));
					FlushBatchDraw();
					Sleep(1000);
					if(npc_life<4)
					{
						npc_life++;
					}
					else			//��Ѫ��ʾ
					{
						putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
						setbkmode(TRANSPARENT);
						settextstyle(30, 0, _T("΢���ź�"));
						outtextxy(PromptBox_x+20,PromptBox_y,_T("����Ѫ�����ģ��̲����ˣ�"));
						FlushBatchDraw();
						Sleep(1000);
					}
					if(player_life<4)
					{
						player_life++;
					}
					show();
					isEffective=0;
					answerover=0;//�ָ�
					npc_desktop = 0;
					show();
					break;
				}
		}
		if(npc_desktop==9)	//�з�����������
		{
			if ((player[player_out] == 11)&&(isEffective==1))  //��ҳ���и�ɻ�
			{
				player_desktop=player[player_out];//��¼������
				player_desktop2=player[player_out];//��¼������
				mciSendString("close wuxiemusic", NULL, 0, NULL);  //�ȹر�ǰһ��
				mciSendString("open \"����ɱ��Ƶ�ز�\\��и�ɻ�.mp3\" alias wuxiemusic",NULL,0,NULL);//����ɱ
				mciSendString("play wuxiemusic", NULL, 0, NULL);  //������һ��
				Sleep(1000);
				player[player_out]=0;
				player_out = -1;				//���ƺ����
				player_zhengli();
				player_shoupai_num--;           //��������һ
				isEffective=0;
				npc_desktop = 0;
				show();
				break;
			}
			if((player[player_out] == 1)&&(isEffective==1))		//��ҳ�ɱ
			{
				player_desktop=player[player_out];//��¼������
				player_desktop2=player[player_out];//��¼������
				mciSendString("close shamusic", NULL, 0, NULL);  //�ȹر�ǰһ��
				mciSendString("open \"����ɱ��Ƶ�ز�\\ɱ.mp3\" alias shamusic",NULL,0,NULL);//����ɱ
				mciSendString("play shamusic", NULL, 0, NULL);  //������һ��
				Sleep(500);
				player[player_out]=0;
				player_out = -1;				//���ƺ����
				player_zhengli();
				player_shoupai_num--;           //��������һ
				isEffective=0;
				npc_desktop = 0;
				show();
				break;
			}
			if(answerover==1)	//��ҵ������
				{
					putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
					setbkmode(TRANSPARENT);
					settextstyle(30, 0, _T("΢���ź�"));
					outtextxy(PromptBox_x+20,PromptBox_y,_T("���ܵ�һ��λ�˺���"));
					FlushBatchDraw();
					Sleep(1000);
					player_life--;	//��ҿ�Ѫ
					show();
					isEffective=0;
					answerover=0;//�ָ�
					npc_desktop = 0;
					show();
					break;
				}
		}
		if(npc_desktop==10)	//�з�������뷢
		{
			if ((player[player_out] == 11)&&(isEffective==1))  //��ҳ���и�ɻ�
			{
				player_desktop=player[player_out];//��¼������
				player_desktop2=player[player_out];//��¼������
				mciSendString("close wuxiemusic", NULL, 0, NULL);  //�ȹر�ǰһ��
				mciSendString("open \"����ɱ��Ƶ�ز�\\��и�ɻ�.mp3\" alias wuxiemusic",NULL,0,NULL);//����ɱ
				mciSendString("play wuxiemusic", NULL, 0, NULL);  //������һ��
				Sleep(1000);
				player[player_out]=0;
				player_out = -1;				//���ƺ����
				player_zhengli();
				player_shoupai_num--;           //��������һ
				isEffective=0;
				npc_desktop = 0;
				show();
				break;
			}
			if((player[player_out] == 2)&&(isEffective==1))		//��ҳ���
			{
				player_desktop=player[player_out];//��¼������
				player_desktop2=player[player_out];//��¼������
				mciSendString("close shanmusic", NULL, 0, NULL);  //�ȹر�ǰһ��
				mciSendString("open \"����ɱ��Ƶ�ز�\\��.mp3\" alias shanmusic",NULL,0,NULL);//����ɱ
				mciSendString("play shanmusic", NULL, 0, NULL);  //������һ��
				Sleep(500);
				player[player_out]=0;
				player_out = -1;				//���ƺ����
				player_zhengli();
				player_shoupai_num--;           //��������һ
				isEffective=0;
				npc_desktop = 0;
				show();
				break;
			}
			if(answerover==1)	//��ҵ������
				{
					putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
					setbkmode(TRANSPARENT);
					settextstyle(30, 0, _T("΢���ź�"));
					outtextxy(PromptBox_x+20,PromptBox_y,_T("���ܵ�һ��λ�˺���"));
					FlushBatchDraw();
					Sleep(1000);
					player_life--;	//��ҿ�Ѫ
					show();
					isEffective=0;
					answerover=0;//�ָ�
					npc_desktop = 0;
					show();
					break;
				}
		}
		if(npc_desktop==13)	//�з�����������
		{
			if ((player[player_out] == 11)&&(isEffective==1))  //��ҳ���и�ɻ�
			{
				player_desktop=player[player_out];//��¼������
				player_desktop2=player[player_out];//��¼������
				mciSendString("close wuxiemusic", NULL, 0, NULL);  //�ȹر�ǰһ��
				mciSendString("open \"����ɱ��Ƶ�ز�\\��и�ɻ�.mp3\" alias wuxiemusic",NULL,0,NULL);//����ɱ
				mciSendString("play wuxiemusic", NULL, 0, NULL);  //������һ��
				Sleep(1000);
				player[player_out]=0;
				player_out = -1;				//���ƺ����
				player_zhengli();
				player_shoupai_num--;           //��������һ
				isEffective=0;
				npc_desktop = 0;
				show();
				break;
			}
			if(answerover==1)	//��ҵ������
				{
					putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
					setbkmode(TRANSPARENT);
					settextstyle(30, 0, _T("΢���ź�"));
					outtextxy(PromptBox_x+20,PromptBox_y,_T("�з��������ƣ�"));
					FlushBatchDraw();
					Sleep(1000);
					npc_getnew();		//npc��������
					show();
					isEffective=0;
					answerover=0;//�ָ�
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
	if((player_life==0)&&(isplayermirror==1))//�������л��ľ�
	{
		isplayermirror=0;			//ж�»��ľ�
		player_life++;
		putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
		setbkmode(TRANSPARENT);
		settextstyle(30, 0, _T("΢���ź�"));
		outtextxy(PromptBox_x+20,PromptBox_y,_T("���Ļ��ľ����ѣ���һ��Ѫ��"));
		FlushBatchDraw();
		Sleep(1000);
		show();
	}
	if((npc_life<=0)||(player_life<=0))   //��������
	{
		isover = 1;
	}
	if (isRoundover == 0)   //���δ�����غϣ������������Ч��
	{
		if ((player[player_out] == 1) &&((player_sha_num == 0)||(isplayerzhuge==1))&&(isEffective==1)&&(x_wanjiatonpc<=1))    //��ҳ�ɱ���ǵ�һ�γ�ɱ����������ڷ�Χ
		{
			player_desktop=player[player_out];//��¼������
			player_desktop2=player[player_out];//��¼������
			mciSendString("close shamusic", NULL, 0, NULL);  //�ȹر�ǰһ��
			mciSendString("open \"����ɱ��Ƶ�ز�\\ɱ.mp3\" alias shamusic",NULL,0,NULL);//����ɱ
			mciSendString("play shamusic", NULL, 0, NULL);  //������һ��
			Sleep(1000);
			player[player_out] = 0;
			player_out = -1;        //���ƺ����
			player_zhengli();
			player_shoupai_num--;           //��������һ
			isEffective=0;
			player_sha_num++;
		}
		if ((player[player_out] == 1) && ((player_sha_num != 0)&&(isplayerzhuge==0))&&(isEffective==1)&&(x_wanjiatonpc<=1))   //����������ҵڶ��γ�ɱ
		{ 
			//player_sha_num++;
			player_out = -1;				//���ƺ����
			//printf("�����Գ�ɱ��Ŷ!\n");      //��ֹ��ɱ
			putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
			setbkmode(TRANSPARENT);
			settextstyle(30, 0, _T("΢���ź�"));
			outtextxy(PromptBox_x+20,PromptBox_y,_T("�����󲻿���������ɱŶ��"));
			FlushBatchDraw();
			Sleep(1000);
			isEffective=0;
			return;  //�˳��ж�
		}
		if ((player[player_out] == 1)&&(isEffective==1)&&(x_wanjiatonpc==2))   //��ҳ�ɱ���ڷ�Χ
		{ 
			//player_sha_num++;
			player_out = -1;				//���ƺ����
			//printf("�����Գ�ɱ��Ŷ!\n");      //��ֹ��ɱ
			putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
			setbkmode(TRANSPARENT);
			settextstyle(30, 0, _T("΢���ź�"));
			outtextxy(PromptBox_x+20,PromptBox_y,_T("ɱ������Ŷ��"));
			FlushBatchDraw();
			Sleep(1000);
			isEffective=0;
			return;  //�˳��ж�
		}

		if ((npc_desktop == 1)&&(npc_sha_num == 1)) //npc����Чɱ���ҷ����
		{
			if ((player[player_out] == 2)&&(isEffective==1))  //��ҳ���
			{
				player_desktop=player[player_out];//��¼������
				player_desktop2=player[player_out];//��¼������
				mciSendString("close shanmusic", NULL, 0, NULL);  //�ȹر�ǰһ��
				mciSendString("open \"����ɱ��Ƶ�ز�\\��.mp3\" alias shanmusic",NULL,0,NULL);//������
				mciSendString("play shanmusic", NULL, 0, NULL);  //������һ��
				Sleep(500);
				player[player_out]=0;
				player_out = -1;				//���ƺ����
				player_shan_num++;				//��ҳ���������һ
				player_zhengli();
				player_shoupai_num--;           //��������һ
				isEffective=0;
				//printf("�ҷ�ʹ����\n");
			}
			if((npc_desktop == 1)&&(player_shan_num == 0))	//npc��ɱ���û����
			{
				player_life--;
				isEffective=0;
			}
			npc_desktop = 0;
			player_shan_num = 0;
			npc_sha_num--;
			
		}
		if ((player[player_out] == 2) && (npc_desktop != 1)&&(isEffective==1))  //��ҳ����ҵ���δ��ɱ��������뷢��
				{
					//printf("�����Գ�����Ŷ��\n");   //��ֹ����
					putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
					setbkmode(TRANSPARENT);
					settextstyle(30, 0, _T("΢���ź�"));
					outtextxy(PromptBox_x+20,PromptBox_y,_T("�������������Ŷ��"));
					FlushBatchDraw();
					Sleep(1000);
					player_out = -1;				//���ƺ����
					isEffective=0;
					return;  //�˳��ж�
				}
		
		if ((player[player_out] == 3) && (player_life < 4)&&(isEffective==1))
		{
			player_desktop=player[player_out];//��¼������
			player_desktop2=player[player_out];//��¼������
			player_life++;		//ʹ������Ѫ
			mciSendString("close taomusic", NULL, 0, NULL);  //�ȹر�ǰһ��
			mciSendString("open \"����ɱ��Ƶ�ز�\\��.mp3\" alias taomusic",NULL,0,NULL);//����ɱ
			mciSendString("play taomusic", NULL, 0, NULL);  //������һ��
			Sleep(500);
			player[player_out]=0;
			player_out = -1;				//���ƺ����
			player_zhengli();
			player_shoupai_num--; //���Ƽ�һ
			isEffective=0;
		}
		if ((player[player_out] == 3) && (player_life==4)&&(isEffective==1))
		{

			putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
			setbkmode(TRANSPARENT);
			settextstyle(30, 0, _T("΢���ź�"));
			outtextxy(PromptBox_x+20,PromptBox_y,_T("����Ѫ�����ģ��̲����ˣ�"));
			FlushBatchDraw();
			Sleep(1000);
			player_out = -1;				//���ƺ����
			isEffective=0;
			return;  //�˳��ж�
		}
		if((player[player_out] == 4)&&(isEffective==1))				//������Ӳ���
		{
			if(npc_shoupai_num==0)
			{
				putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
				setbkmode(TRANSPARENT);
				settextstyle(30, 0, _T("΢���ź�"));
				outtextxy(PromptBox_x+20,PromptBox_y,_T("�з�û������Ŷ���޷������"));
				FlushBatchDraw();
				Sleep(1000);

			}
			else
			{	
				mciSendString("close guohemusic", NULL, 0, NULL);  //�ȹر�ǰһ��
				mciSendString("open \"����ɱ��Ƶ�ز�\\���Ӳ���.mp3\" alias guohemusic",NULL,0,NULL);//����ɱ
				mciSendString("play guohemusic", NULL, 0, NULL);  //������һ��
				Sleep(1000);
				int k;
				int wuxienum=0;		//��¼npc��и����
				player_desktop=player[player_out];//��¼������
				player_desktop2=player[player_out];//��¼������
				for (k = 0; k<npc_shoupai_num; k++)
				{
					if (npc[k] == 11)         //npc�ҵ���и�ɻ�
					{
						mciSendString("close wuxiemusic", NULL, 0, NULL);  //�ȹر�ǰһ��
						mciSendString("open \"����ɱ��Ƶ�ز�\\��и�ɻ�.mp3\" alias wuxiemusic",NULL,0,NULL);//����ɱ
						mciSendString("play wuxiemusic", NULL, 0, NULL);  //������һ��
						Sleep(1000);
						npc_desktop=npc[k];//��¼npc������
						npc_desktop2=npc[k];//��¼npc������
						npc[k] = 0;
						npc_zhengli();
						npc_shoupai_num--;  //���Ƽ�һ
						wuxienum++;
						break;
					}
				}
				if(wuxienum==0)	//npcû����и
				{
					//��Ϊ���Ӳ��ŵ�����
					
					k=rand()%npc_shoupai_num;	//�����һ��npc����
					
					putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
					setbkmode(TRANSPARENT);
					settextstyle(30, 0, _T("΢���ź�"));
					if(npc[k]==1)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("�����˶Է���ɱ��"));
					}
					if(npc[k]==2)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("�����˶Է�������"));
					}
					if(npc[k]==3)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("�����˶Է����ң�"));
					}
					if(npc[k]==4)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("�����˶Է��Ĺ��Ӳ��ţ�"));
					}
					if(npc[k]==5)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("�����˶Է���˳��ǣ��"));
					}
					if(npc[k]==6)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("�����˶Է�����԰���壡"));
					}
					if(npc[k]==7)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("�����˶Է���+1��"));
					}
					if(npc[k]==8)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("�����˶Է���-1��"));
					}
					if(npc[k]==9)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("�����˶Է����������֣�"));
					}
					if(npc[k]==10)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("�����˶Է�������뷢��"));
					}
					if(npc[k]==11)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("�����˶Է�����и�ɻ���"));
					}
					if(npc[k]==12)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("�����˶Է��ľ�����"));
					}
					if(npc[k]==13)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("�����˶Է����������У�"));
					}
					if(npc[k]==14)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("�����˶Է����������"));
					}
					if(npc[k]==15)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("�����˶Է��Ļ��ľ���"));
					}
					FlushBatchDraw();
					Sleep(1000);
					npc[k] = 0;			//��ղ�ȥ����
					npc_zhengli();
					npc_shoupai_num--;  //���Ƽ�һ

				}
				player[player_out]=0;
				player_out = -1;				//���ƺ����
				player_zhengli();
				player_shoupai_num--; //���Ƽ�һ
				isEffective=0;
			}
		}
	if((player[player_out] == 5)&&(isEffective==1))				//���˳��ǣ��
		{
			if(npc_shoupai_num==0)
			{
				putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
				setbkmode(TRANSPARENT);
				settextstyle(30, 0, _T("΢���ź�"));
				outtextxy(PromptBox_x+20,PromptBox_y,_T("�з�û������Ŷ���޷������"));
				FlushBatchDraw();
				Sleep(1000);

			}
			else
			{	
				mciSendString("close shunshoumusic", NULL, 0, NULL);  //�ȹر�ǰһ��
				mciSendString("open \"����ɱ��Ƶ�ز�\\˳��ǣ��.mp3\" alias shunshoumusic",NULL,0,NULL);//����ɱ
				mciSendString("play shunshoumusic", NULL, 0, NULL);  //������һ��
				Sleep(1000);
				int k;
				int wuxienum=0;		//��¼npc��и����
				player_desktop=player[player_out];//��¼������
				player_desktop2=player[player_out];//��¼������
				for (k = 0; k<npc_shoupai_num; k++)
				{
					if (npc[k] == 11)         //npc�ҵ���и�ɻ�
					{
						mciSendString("close wuxiemusic", NULL, 0, NULL);  //�ȹر�ǰһ��
						mciSendString("open \"����ɱ��Ƶ�ز�\\��и�ɻ�.mp3\" alias wuxiemusic",NULL,0,NULL);//����ɱ
						mciSendString("play wuxiemusic", NULL, 0, NULL);  //������һ��
						Sleep(1000);
						npc_desktop=npc[k];//��¼npc������
						npc_desktop2=npc[k];//��¼npc������
						npc[k] = 0;
						npc_zhengli();
						npc_shoupai_num--;  //���Ƽ�һ
						wuxienum++;
						player[player_out]=0;
						player_out = -1;				//���ƺ����
						player_zhengli();
						player_shoupai_num--; //���Ƽ�һ
						show();
						break;
					}
				}
				if(wuxienum==0)	//npcû����и
				{
					//��Ϊ˳��ǣ�������
					
					k=rand()%npc_shoupai_num;	//�����һ��npc����
					
					putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
					setbkmode(TRANSPARENT);
					settextstyle(30, 0, _T("΢���ź�"));
					if(npc[k]==1)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("��˳�˶Է���ɱ��"));
					}
					if(npc[k]==2)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("��˳�˶Է�������"));
					}
					if(npc[k]==3)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("��˳�˶Է����ң�"));
					}
					if(npc[k]==4)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("��˳�˶Է��Ĺ��Ӳ��ţ�"));
					}
					if(npc[k]==5)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("��˳�˶Է���˳��ǣ��"));
					}
					if(npc[k]==6)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("��˳�˶Է�����԰���壡"));
					}
					if(npc[k]==7)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("��˳�˶Է���+1��"));
					}
					if(npc[k]==8)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("��˳�˶Է���-1��"));
					}
					if(npc[k]==9)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("��˳�˶Է����������֣�"));
					}
					if(npc[k]==10)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("��˳�˶Է�������뷢��"));
					}
					if(npc[k]==11)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("��˳�˶Է�����и�ɻ���"));
					}
					if(npc[k]==12)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("��˳�˶Է��ľ�����"));
					}
					if(npc[k]==13)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("��˳�˶Է����������У�"));
					}
					if(npc[k]==14)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("��˳�˶Է����������"));
					}
					if(npc[k]==15)
					{
						outtextxy(PromptBox_x+20,PromptBox_y,_T("��˳�˶Է��Ļ��ľ���"));
					}
					FlushBatchDraw();
					Sleep(1000);
					player[player_out]=0;
					player_out = -1;				//���ƺ����
					player_zhengli();
					player_shoupai_num--; //���Ƽ�һ
					player[player_shoupai_num]=npc[k];	//�õ�������
					player_shoupai_num++;//��������һ
					player_zhengli();
					npc[k] = 0;			//��ղ�ȥ����
					npc_zhengli();
					npc_shoupai_num--;  //���Ƽ�һ
					show();
				}
				isEffective=0;
			}
		}
	if((player[player_out] == 6)&&(isEffective==1))				//�����԰����
		{
			mciSendString("close taoyuanmusic", NULL, 0, NULL);  //�ȹر�ǰһ��
			mciSendString("open \"����ɱ��Ƶ�ز�\\��԰����.mp3\" alias taoyuanmusic",NULL,0,NULL);//����ɱ
			mciSendString("play taoyuanmusic", NULL, 0, NULL);  //������һ��
			Sleep(1000);
			int k;
			int wuxienum=0;		//��¼npc��и����
			player_desktop=player[player_out];//��¼������
			player_desktop2=player[player_out];//��¼������
			if(player_life<npc_life)		//���npc������͸�һ��
			{
				for (k = 0; k<npc_shoupai_num; k++)
				{
					if (npc[k] == 11)         //npc�ҵ���и�ɻ�
					{
						mciSendString("close wuxiemusic", NULL, 0, NULL);  //�ȹر�ǰһ��
						mciSendString("open \"����ɱ��Ƶ�ز�\\��и�ɻ�.mp3\" alias wuxiemusic",NULL,0,NULL);//����ɱ
						mciSendString("play wuxiemusic", NULL, 0, NULL);  //������һ��
						Sleep(1000);
						npc_desktop=npc[k];//��¼npc������
						npc_desktop2=npc[k];//��¼npc������
						npc[k] = 0;
						npc_zhengli();
						npc_shoupai_num--;  //���Ƽ�һ
						wuxienum++;
						player[player_out]=0;
						player_out = -1;				//���ƺ����
						player_zhengli();
						player_shoupai_num--; //���Ƽ�һ
						break;
					}
				}
			}
			if(wuxienum==0)	//npcû����и
			{
				//��Ϊ��԰���������
				putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
				setbkmode(TRANSPARENT);
				settextstyle(30, 0, _T("΢���ź�"));
				outtextxy(PromptBox_x+20,PromptBox_y,_T("˫������������"));
				FlushBatchDraw();
				Sleep(1000);
				if(player_life<4)
				{
					player_life++;
				}
				else			//��Ѫ��ʾ
				{
					putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
					setbkmode(TRANSPARENT);
					settextstyle(30, 0, _T("΢���ź�"));
					outtextxy(PromptBox_x+20,PromptBox_y,_T("����Ѫ�����ģ��̲����ˣ�"));
					FlushBatchDraw();
					Sleep(1000);
				}
				if(npc_life<4)
				{
					npc_life++;
				}			//˫����������
				player[player_out]=0;
				player_out = -1;				//���ƺ����
				player_zhengli();
				player_shoupai_num--; //���Ƽ�һ
			}
			
			show();
			isEffective=0;
		}
	if((player[player_out] == 9)&&(isEffective==1))				//�����������
		{
			mciSendString("close nanmanmusic", NULL, 0, NULL);  //�ȹر�ǰһ��
			mciSendString("open \"����ɱ��Ƶ�ز�\\��������.mp3\" alias nanmanmusic",NULL,0,NULL);//����ɱ
			mciSendString("play nanmanmusic", NULL, 0, NULL);  //������һ��
			Sleep(1000);
			int k;
			int wuxienum=0;		//��¼npc��и����
			int shanum=0;		//��¼npcɱ����
			player_desktop=player[player_out];//��¼������
			player_desktop2=player[player_out];//��¼������
			for (k = 0; k<npc_shoupai_num; k++)
			{
				if (npc[k] == 1)      //npc�ҵ�ɱ
				{
					mciSendString("close shamusic", NULL, 0, NULL);  //�ȹر�ǰһ��
					mciSendString("open \"����ɱ��Ƶ�ز�\\ɱ.mp3\" alias shamusic",NULL,0,NULL);//����ɱ
					mciSendString("play shamusic", NULL, 0, NULL);  //������һ��
					Sleep(500);
					npc_desktop=npc[k];//��¼npc������
					npc_desktop2=npc[k];//��¼npc������
					npc[k] = 0;
					npc_zhengli();
					npc_shoupai_num--;  //���Ƽ�һ
					shanum++;
					break;
				}
			}
			if(shanum==0)
			{
				for (k = 0; k<npc_shoupai_num; k++)
				{
					if (npc[k] == 11)      //npc�ҵ���и�ɻ�
					{
						mciSendString("close wuxiemusic", NULL, 0, NULL);  //�ȹر�ǰһ��
						mciSendString("open \"����ɱ��Ƶ�ز�\\��и�ɻ�.mp3\" alias wuxiemusic",NULL,0,NULL);//����ɱ
						mciSendString("play wuxiemusic", NULL, 0, NULL);  //������һ��
						Sleep(1000);
						npc_desktop=npc[k];//��¼npc������
						npc_desktop2=npc[k];//��¼npc������
						npc[k] = 0;
						npc_zhengli();
						npc_shoupai_num--;  //���Ƽ�һ
						wuxienum++;
						break;
					}
				}
			}
			if((wuxienum==0)&&(shanum==0))	//npcû����и��ɱ
			{
				//��Ϊ�������ֵ�����
				npc_life--;	//��Ѫ
				show();
				putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
				setbkmode(TRANSPARENT);
				settextstyle(30, 0, _T("΢���ź�"));
				outtextxy(PromptBox_x+20,PromptBox_y,_T("�з���ɱ����и���ܵ�һ��λ�˺���"));
				FlushBatchDraw();
				Sleep(1000);
			}
			player[player_out]=0;
			player_out = -1;				//���ƺ����
			player_zhengli();
			player_shoupai_num--; //���Ƽ�һ
			show();
			isEffective=0;
		}
	if((player[player_out] == 10)&&(isEffective==1))				//�������뷢
		{
			mciSendString("close wanjianmusic", NULL, 0, NULL);  //�ȹر�ǰһ��
			mciSendString("open \"����ɱ��Ƶ�ز�\\����뷢.mp3\" alias wanjianmusic",NULL,0,NULL);//����ɱ
			mciSendString("play wanjianmusic", NULL, 0, NULL);  //������һ��
			Sleep(1000);
			int k;
			int wuxienum=0;		//��¼npc��и����
			int shannum=0;		//��¼npc������
			player_desktop=player[player_out];//��¼������
			player_desktop2=player[player_out];//��¼������
			for (k = 0; k<npc_shoupai_num; k++)
			{
				if (npc[k] == 2)      //npc�ҵ���
				{
					mciSendString("close shanmusic", NULL, 0, NULL);  //�ȹر�ǰһ��
					mciSendString("open \"����ɱ��Ƶ�ز�\\��.mp3\" alias shanmusic",NULL,0,NULL);//����ɱ
					mciSendString("play shanmusic", NULL, 0, NULL);  //������һ��
					Sleep(500);
					npc_desktop=npc[k];//��¼npc������
					npc_desktop2=npc[k];//��¼npc������
					npc[k] = 0;
					npc_zhengli();
					npc_shoupai_num--;  //���Ƽ�һ
					shannum++;
					break;
				}
			}
			if(shannum==0)
			{
				for (k = 0; k<npc_shoupai_num; k++)
				{
					if (npc[k] == 11)      //npc�ҵ���и�ɻ�
					{
						mciSendString("close wuxiemusic", NULL, 0, NULL);  //�ȹر�ǰһ��
						mciSendString("open \"����ɱ��Ƶ�ز�\\��и�ɻ�.mp3\" alias wuxiemusic",NULL,0,NULL);//����ɱ
						mciSendString("play wuxiemusic", NULL, 0, NULL);  //������һ��
						Sleep(1000);
						npc_desktop=npc[k];//��¼npc������
						npc_desktop2=npc[k];//��¼npc������
						npc[k] = 0;
						npc_zhengli();
						npc_shoupai_num--;  //���Ƽ�һ
						wuxienum++;
						break;
					}
				}
			}
			if((wuxienum==0)&&(shannum==0))	//npcû����и����
			{
				//��Ϊ����뷢������
				npc_life--;	//��Ѫ
				show();
				putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
				setbkmode(TRANSPARENT);
				settextstyle(30, 0, _T("΢���ź�"));
				outtextxy(PromptBox_x+20,PromptBox_y,_T("�з���������и���ܵ�һ��λ�˺���"));
				FlushBatchDraw();
				Sleep(1000);
			}
			player[player_out]=0;
			player_out = -1;				//���ƺ����
			player_zhengli();
			player_shoupai_num--; //���Ƽ�һ
			show();
			isEffective=0;
		}
	if((player[player_out] == 12)&&(isEffective==1))				//�������
		{
			mciSendString("close juedoumusic", NULL, 0, NULL);  //�ȹر�ǰһ��
			mciSendString("open \"����ɱ��Ƶ�ز�\\����.mp3\" alias juedoumusic",NULL,0,NULL);//����ɱ
			mciSendString("play juedoumusic", NULL, 0, NULL);  //������һ��
			Sleep(1000);
			int k;
			int wuxienum=0;		//��¼npc��и����
			player_desktop=player[player_out];//��¼������
			player_desktop2=player[player_out];//��¼������
			for (k = 0; k<npc_shoupai_num; k++)
				{
					if (npc[k] == 11)         //npc�ҵ���и�ɻ�
					{
						mciSendString("close wuxiemusic", NULL, 0, NULL);  //�ȹر�ǰһ��
						mciSendString("open \"����ɱ��Ƶ�ز�\\��и�ɻ�.mp3\" alias wuxiemusic",NULL,0,NULL);//����ɱ
						mciSendString("play wuxiemusic", NULL, 0, NULL);  //������һ��
						Sleep(1000);
						npc_desktop=npc[k];//��¼npc������
						npc_desktop2=npc[k];//��¼npc������
						npc[k] = 0;
						npc_zhengli();
						npc_shoupai_num--;  //���Ƽ�һ
						wuxienum++;
						player[player_out]=0;
						player_out = -1;				//���ƺ����
						player_zhengli();
						player_shoupai_num--; //���Ƽ�һ
						break;
					}
				}
			if(wuxienum==0)	//npcû����и
			{
				//��Ϊ����������
				putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
				setbkmode(TRANSPARENT);
				settextstyle(30, 0, _T("΢���ź�"));
				outtextxy(PromptBox_x+20,PromptBox_y,_T("˫�����������"));
				FlushBatchDraw();
				Sleep(1000);
				player[player_out]=0;
				player_out = -1;				//���ƺ����
				player_zhengli();
				player_shoupai_num--; //���Ƽ�һ
				show();
				juedou();
			}
			show();
			isEffective=0;
		}
	if((player[player_out] == 13)&&(isEffective==1))				//�����������
		{
			mciSendString("close wuzhongmusic", NULL, 0, NULL);  //�ȹر�ǰһ��
			mciSendString("open \"����ɱ��Ƶ�ز�\\��������.mp3\" alias wuzhongmusic",NULL,0,NULL);//����ɱ
			mciSendString("play wuzhongmusic", NULL, 0, NULL);  //������һ��
			Sleep(1000);
			int k;
			int wuxienum=0;		//��¼npc��и����
			player_desktop=player[player_out];//��¼������
			player_desktop2=player[player_out];//��¼������
			for (k = 0; k<npc_shoupai_num; k++)
				{
					if (npc[k] == 11)         //npc�ҵ���и�ɻ�
					{
						mciSendString("close wuxiemusic", NULL, 0, NULL);  //�ȹر�ǰһ��
						mciSendString("open \"����ɱ��Ƶ�ز�\\��и�ɻ�.mp3\" alias wuxiemusic",NULL,0,NULL);//����ɱ
						mciSendString("play wuxiemusic", NULL, 0, NULL);  //������һ��
						Sleep(1000);
						npc_desktop=npc[k];//��¼npc������
						npc_desktop2=npc[k];//��¼npc������
						npc[k] = 0;
						npc_zhengli();
						npc_shoupai_num--;  //���Ƽ�һ
						wuxienum++;
						player[player_out]=0;
						player_out = -1;				//���ƺ����
						player_zhengli();
						player_shoupai_num--; //���Ƽ�һ
						break;
					}
				}
			if(wuxienum==0)	//npcû����и
			{
				//��Ϊ�������е�����
				putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
				setbkmode(TRANSPARENT);
				settextstyle(30, 0, _T("΢���ź�"));
				outtextxy(PromptBox_x+20,PromptBox_y,_T("�����������ƣ�"));
				FlushBatchDraw();
				Sleep(1000);
				player[player_out]=0;
				player_out = -1;				//���ƺ����
				player_zhengli();
				player_shoupai_num--; //���Ƽ�һ
				player_getnew();
				show();
			}
			
			show();
			isEffective=0;
		}
	if((player[player_out] == 7)&&(isEffective==1))				//���+1��
		{
			mciSendString("close horsemusic", NULL, 0, NULL);  //�ȹر�ǰһ��
			mciSendString("open \"����ɱ��Ƶ�ز�\\��.mp3\" alias horsemusic",NULL,0,NULL);//����ɱ
			mciSendString("play horsemusic", NULL, 0, NULL);  //������һ��
			Sleep(1000);
			player_desktop=player[player_out];//��¼������
			player_desktop2=player[player_out];//��¼������
			if(isplayerh2==1)		//ʹ�ù���һ��
			{
				player[player_out]=0;
				player_out = -1;				//���ƺ����
				isplayerh2=1;					//���װ��+1��
				player_zhengli();
				player_shoupai_num--; //���Ƽ�һ
			}
			if(isplayerh2==0)		//δʹ�ù���һ��
			{
				isplayerh2=1;			//���װ��+1��
				x_npctowanjia++;
				player[player_out]=0;
				player_out = -1;				//���ƺ����
				player_zhengli();
				player_shoupai_num--; //���Ƽ�һ
			}
			show();
			isEffective=0;
		}
	if((player[player_out] == 8)&&(isEffective==1))				//���-1��
		{
			mciSendString("close horsemusic", NULL, 0, NULL);  //�ȹر�ǰһ��
			mciSendString("open \"����ɱ��Ƶ�ز�\\��.mp3\" alias horsemusic",NULL,0,NULL);//����ɱ
			mciSendString("play horsemusic", NULL, 0, NULL);  //������һ��
			Sleep(1000);
			player_desktop=player[player_out];//��¼������
			player_desktop2=player[player_out];//��¼������
			if(isplayerh1==1)		//ʹ�ù���һ��
			{
				player[player_out]=0;
				player_out = -1;				//���ƺ����
				isplayerh1=1;					//���װ��-1��
				player_zhengli();
				player_shoupai_num--; //���Ƽ�һ
			}
			if(isplayerh1==0)		//δʹ�ù���һ��
			{
				isplayerh1=1;			//���װ��-1��
				x_wanjiatonpc--;
				player[player_out]=0;
				player_out = -1;				//���ƺ����
				player_zhengli();
				player_shoupai_num--; //���Ƽ�һ
			}
			show();
			isEffective=0;
		}
	if((player[player_out] == 14)&&(isEffective==1))				//����������
		{
			mciSendString("close liannumusic", NULL, 0, NULL);  //�ȹر�ǰһ��
			mciSendString("open \"����ɱ��Ƶ�ز�\\�������.mp3\" alias liannumusic",NULL,0,NULL);//����ɱ
			mciSendString("play liannumusic", NULL, 0, NULL);  //������һ��
			Sleep(1000);
			player_desktop=player[player_out];//��¼������
			player_desktop2=player[player_out];//��¼������
			if(isplayerzhuge==1)		//ʹ�ù��������
			{
				player[player_out]=0;
				player_out = -1;				//���ƺ����
				isplayerzhuge=1;					//���װ���������
				player_zhengli();
				player_shoupai_num--; //���Ƽ�һ
			}
			if(isplayerzhuge==0)		//δʹ�ù����������
			{
				isplayerzhuge=1;			//���װ���������
				player[player_out]=0;
				player_out = -1;				//���ƺ����
				player_zhengli();
				player_shoupai_num--; //���Ƽ�һ
			}
			show();
			isEffective=0;
		}
	if((player[player_out] == 15)&&(isEffective==1))				//������ľ�
		{
			mciSendString("close huxinmusic", NULL, 0, NULL);  //�ȹر�ǰһ��
			mciSendString("open \"����ɱ��Ƶ�ز�\\���ľ�.mp3\" alias huxinmusic",NULL,0,NULL);//����ɱ
			mciSendString("play huxinmusic", NULL, 0, NULL);  //������һ��
			Sleep(1000);
			player_desktop=player[player_out];//��¼������
			player_desktop2=player[player_out];//��¼������
			if(isplayermirror==1)		//ʹ�ù����ľ�
			{
				player[player_out]=0;
				player_out = -1;				//���ƺ����
				isplayermirror=1;					//���װ�����ľ�
				player_zhengli();
				player_shoupai_num--; //���Ƽ�һ
			}
			if(isplayermirror==0)		//δʹ�ù����ľ�
			{
				isplayermirror=1;			//���װ�����ľ�
				player[player_out]=0;
				player_out = -1;				//���ƺ����
				player_zhengli();
				player_shoupai_num--; //���Ƽ�һ
			}
			show();
			isEffective=0;
		}










	}

	if((isRoundover == 1)&&(isEffective==1))//��һغ��ѽ���������
	{
		player_desktop2=player[player_out];//��¼����ʾ
		player[player_out]=0;
		player_zhengli();
		player_shoupai_num--;
		disnum++;						//����������һ
		isEffective=0;
	}
}

void npc_panding()
{
	int tempnpcshoupai=0;		//��ʱ��¼npc������
	int k;
	if ((player_desktop == 1)&&((player_sha_num==1)||(isplayerzhuge==1)))   //��ҳ���Чɱ�������������Ѫ
	{
		for (k = 0; k<npc_shoupai_num; k++)
		{
			if (npc[k] == 2)         //�ҵ���
			{
				//printf("�з���Ӣ�ۡ�ʹ������\n");
				mciSendString("close shanmusic", NULL, 0, NULL);  //�ȹر�ǰһ��
				mciSendString("open \"����ɱ��Ƶ�ز�\\��.mp3\" alias shanmusic",NULL,0,NULL);//������
				mciSendString("play shanmusic", NULL, 0, NULL);  //������һ��
				putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
				setbkmode(TRANSPARENT);
				settextstyle(30, 0, _T("΢���ź�"));
				outtextxy(PromptBox_x+20,PromptBox_y,_T("�з�������"));
				FlushBatchDraw();
				Sleep(1000);
				npc_desktop=npc[k];//��¼npc������
				npc_desktop2=npc[k];//��¼npc������
				npc[k] = 0;
				npc_shoupai_num--;  //���Ƽ�һ
				npc_shan_num++;
				if((player_life==0)&&(isplayermirror==1))//�������л��ľ�
				{
					isplayermirror=0;			//ж�»��ľ�
					player_life++;
					putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
					setbkmode(TRANSPARENT);
					settextstyle(30, 0, _T("΢���ź�"));
					outtextxy(PromptBox_x+20,PromptBox_y,_T("���Ļ��ľ����ѣ���һ��Ѫ��"));
					FlushBatchDraw();
					Sleep(1000);
					show();
				}
				if((npc_life==0)&&(isnpcmirror==1))//�������л��ľ�
				{
					isnpcmirror=0;			//ж�»��ľ�
					npc_life++;
					putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
					setbkmode(TRANSPARENT);
					settextstyle(30, 0, _T("΢���ź�"));
					outtextxy(PromptBox_x+20,PromptBox_y,_T("�з��Ļ��ľ����ѣ���һ��Ѫ��"));
					FlushBatchDraw();
					Sleep(1000);
					show();
				}
				if((npc_life<=0)||(player_life<=0))   //��������
				{
					isover = 1;
					goto end;
				}
				break;
			}
		}
		if (npc_shan_num == 0)   //δʹ���������Կ�Ѫ
		{
			npc_life--;
			//printf("�з���Ӣ�ۡ��ܵ�һ��λ�˺�\n");
			putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
			setbkmode(TRANSPARENT);
			settextstyle(30, 0, _T("΢���ź�"));
			outtextxy(PromptBox_x+20,PromptBox_y,_T("�з��ܵ�һ��λ�˺���"));
			FlushBatchDraw();
			Sleep(1000);
			if((player_life==0)&&(isplayermirror==1))//�������л��ľ�
				{
					isplayermirror=0;			//ж�»��ľ�
					player_life++;
					putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
					setbkmode(TRANSPARENT);
					settextstyle(30, 0, _T("΢���ź�"));
					outtextxy(PromptBox_x+20,PromptBox_y,_T("���Ļ��ľ����ѣ���һ��Ѫ��"));
					FlushBatchDraw();
					Sleep(1000);
					show();
				}
				if((npc_life==0)&&(isnpcmirror==1))//�������л��ľ�
				{
					isnpcmirror=0;			//ж�»��ľ�
					npc_life++;
					putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
					setbkmode(TRANSPARENT);
					settextstyle(30, 0, _T("΢���ź�"));
					outtextxy(PromptBox_x+20,PromptBox_y,_T("�з��Ļ��ľ����ѣ���һ��Ѫ��"));
					FlushBatchDraw();
					Sleep(1000);
					show();
				}
				if((npc_life<=0)||(player_life<=0))   //��������
				{
					isover = 1;
					goto end;
				}
			
		}
		player_desktop = 0;//�����������0
		npc_shan_num=0;//npc�����������
	}
	if (player_out == -2)//��һغϽ���������������
	{
		tempnpcshoupai=npc_shoupai_num;
		int ss=0;	//��¼npc��ɱ������
		for (k = 0; k<tempnpcshoupai; k++)		
		{
			if(npc[k]==7)	//�ҵ�+1��
			{
				npc_desktop = npc[k];//��¼npc������
				npc_desktop2 =npc[k];//��¼npc������
				//printf("��Ӣ�ۡ�ʹ����\n");
				mciSendString("close horsemusic", NULL, 0, NULL);  //�ȹر�ǰһ��
				mciSendString("open \"����ɱ��Ƶ�ز�\\��.mp3\" alias horsemusic",NULL,0,NULL);//����ɱ
				mciSendString("play horsemusic", NULL, 0, NULL);  //������һ��
				Sleep(1000);
				if(isnpch2==1)		//ʹ�ù���һ��
				{
					isnpch2=1;
					npc[k] = 0;
					npc_zhengli();
					npc_shoupai_num--;  //npc���Ƽ�һ
				}
				if(isnpch2==0)		//δʹ�ù���һ��
				{
					isnpch2=1;			//���װ��+1��
					x_wanjiatonpc++;
					npc[k] = 0;
					npc_zhengli();
					npc_shoupai_num--;  //npc���Ƽ�һ
				}
				show();

			}
		}
		tempnpcshoupai=npc_shoupai_num;
		for (k = 0; k<tempnpcshoupai; k++)		
		{
			if(npc[k]==8)	//�ҵ�-1��
			{
				npc_desktop = npc[k];//��¼npc������
				npc_desktop2 =npc[k];//��¼npc������
				//printf("��Ӣ�ۡ�ʹ����\n");
				mciSendString("close horsemusic", NULL, 0, NULL);  //�ȹر�ǰһ��
				mciSendString("open \"����ɱ��Ƶ�ز�\\��.mp3\" alias horsemusic",NULL,0,NULL);//����ɱ
				mciSendString("play horsemusic", NULL, 0, NULL);  //������һ��
				Sleep(1000);
				if(isnpch1==1)		//ʹ�ù���һ��
				{
					isnpch1=1;
					npc[k] = 0;
					npc_zhengli();
					npc_shoupai_num--;  //npc���Ƽ�һ
				}
				if(isnpch1==0)		//δʹ�ù���һ��
				{
					isnpch1=1;			//���װ��+1��
					x_npctowanjia--;
					npc[k] = 0;
					npc_zhengli();
					npc_shoupai_num--;  //npc���Ƽ�һ
				}
				show();

			}
		}
		tempnpcshoupai=npc_shoupai_num;
		for (k = 0; k<tempnpcshoupai; k++)		
		{
			if(npc[k]==14)	//�ҵ��������
			{
				npc_desktop = npc[k];//��¼npc������
				npc_desktop2 =npc[k];//��¼npc������
				//printf("��Ӣ�ۡ�ʹ���������\n");
				mciSendString("close zhugemusic", NULL, 0, NULL);  //�ȹر�ǰһ��
				mciSendString("open \"����ɱ��Ƶ�ز�\\�������.mp3\" alias zhugemusic",NULL,0,NULL);//�����������
				mciSendString("play zhugemusic", NULL, 0, NULL);  //������һ��
				Sleep(1000);
				if(isnpczhuge==1)		//ʹ�ù��������
				{
					isnpczhuge=1;
					npc[k] = 0;
					npc_zhengli();
					npc_shoupai_num--;  //npc���Ƽ�һ
				}
				if(isnpczhuge==0)		//δʹ�ù��������
				{
					isnpczhuge=1;			//���װ���������
					npc[k] = 0;
					npc_zhengli();
					npc_shoupai_num--;  //npc���Ƽ�һ
				}
				show();
			}
		}
		tempnpcshoupai=npc_shoupai_num;
		for (k = 0; k<tempnpcshoupai; k++)		
		{
			if(npc[k]==15)	//�ҵ����ľ�
			{
				npc_desktop = npc[k];//��¼npc������
				npc_desktop2 =npc[k];//��¼npc������
				//printf("��Ӣ�ۡ�ʹ�û��ľ���\n");
				mciSendString("close huxinmusic", NULL, 0, NULL);  //�ȹر�ǰһ��
				mciSendString("open \"����ɱ��Ƶ�ز�\\���ľ�.mp3\" alias huxinmusic",NULL,0,NULL);//���Ż��ľ�
				mciSendString("play huxinmusic", NULL, 0, NULL);  //������һ��
				Sleep(1000);
				if(isnpcmirror==1)		//ʹ�ù����ľ�
				{
					isnpcmirror=1;
					npc[k] = 0;
					npc_zhengli();
					npc_shoupai_num--;  //npc���Ƽ�һ
				}
				if(isnpcmirror==0)		//δʹ�ù����ľ�
				{
					isnpcmirror=1;			//���װ�����ľ�
					npc[k] = 0;
					npc_zhengli();
					npc_shoupai_num--;  //npc���Ƽ�һ
				}
				show();
			}
		}
		tempnpcshoupai=npc_shoupai_num;
		for (k = 0; k<tempnpcshoupai; k++)		
		{
			if(npc[k]==13)	//�ҵ���������
			{
				npc_desktop = npc[k];//��¼npc������
				npc_desktop2 =npc[k];//��¼npc������
				//printf("��Ӣ�ۡ�ʹ���������У�\n");
				mciSendString("close wuzhongmusic", NULL, 0, NULL);  //�ȹر�ǰһ��
				mciSendString("open \"����ɱ��Ƶ�ز�\\��������.mp3\" alias wuzhongmusic",NULL,0,NULL);//����ɱ
				mciSendString("play wuzhongmusic", NULL, 0, NULL);  //������һ��
				Sleep(1000);
				putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
				setbkmode(TRANSPARENT);
				settextstyle(30, 0, _T("΢���ź�"));
				outtextxy(PromptBox_x+20,PromptBox_y,_T("ѡ�����и�ɻ����ǽ�����"));
				FlushBatchDraw();
				Sleep(1000);
				npc[k] = 0;
				npc_zhengli();
				npc_shoupai_num--;  //npc���Ƽ�һ
				player_answer();
				show();

			}
		}
		tempnpcshoupai=npc_shoupai_num;
		for (k = 0; k<tempnpcshoupai; k++)		
		{
			if((npc_life<4)&&(npc[k] == 3))   //���������Լ�һ��
			{
				npc_desktop = npc[k];//��¼npc������
				npc_desktop2 =npc[k];//��¼npc������
				mciSendString("close taomusic", NULL, 0, NULL);  //�ȹر�ǰһ��
				mciSendString("open \"����ɱ��Ƶ�ز�\\��.mp3\" alias taomusic",NULL,0,NULL);//������
				mciSendString("play taomusic", NULL, 0, NULL);  //������һ��
				Sleep(500);
				npc[k] = 0;
				npc_life++;			//������һ
				npc_shoupai_num--;  //���Ƽ�һ
			}
		}
		tempnpcshoupai=npc_shoupai_num;
		for (k = 0; k<tempnpcshoupai; k++)		
		{

			if(((npc_life<player_life)||(npc_life==1))&&(player_life!=1))	//����
			{
				if (npc[k] == 6)       //�ҵ���԰����
				{
					npc_desktop = npc[k];//��¼npc������
					npc_desktop2 =npc[k];//��¼npc������
					//printf("��Ӣ�ۡ�ʹ����԰���壡\n");
					mciSendString("close taoyuanmusic", NULL, 0, NULL);  //�ȹر�ǰһ��
					mciSendString("open \"����ɱ��Ƶ�ز�\\��԰����.mp3\" alias taoyuanmusic",NULL,0,NULL);//����ɱ
					mciSendString("play taoyuanmusic", NULL, 0, NULL);  //������һ��
					Sleep(1000);
					putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
					setbkmode(TRANSPARENT);
					settextstyle(30, 0, _T("΢���ź�"));
					outtextxy(PromptBox_x+20,PromptBox_y,_T("ѡ�����и�ɻ����ǽ�����"));
					FlushBatchDraw();
					Sleep(1000);
					npc[k] = 0;
					npc_zhengli();
					npc_shoupai_num--;  //npc���Ƽ�һ
					player_answer();
					show();
				}
			}
		}
		tempnpcshoupai=npc_shoupai_num;
		for (k = 0; k<tempnpcshoupai; k++)		
		{

			if ((npc[k] == 5)&&(player_shoupai_num>0))     //�ҵ�˳��ǣ�������ƿ�˳
			{
				npc_desktop = npc[k];//��¼npc������
				npc_desktop2 =npc[k];//��¼npc������
				//printf("��Ӣ�ۡ�ʹ��˳��ǣ��\n");
				mciSendString("close shunshoumusic", NULL, 0, NULL);  //�ȹر�ǰһ��
				mciSendString("open \"����ɱ��Ƶ�ز�\\˳��ǣ��.mp3\" alias shunshoumusic",NULL,0,NULL);//����ɱ
				mciSendString("play shunshoumusic", NULL, 0, NULL);  //������һ��
				Sleep(1000);
				putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
				setbkmode(TRANSPARENT);
				settextstyle(30, 0, _T("΢���ź�"));
				outtextxy(PromptBox_x+20,PromptBox_y,_T("ѡ�����и�ɻ����ǽ�����"));
				FlushBatchDraw();
				Sleep(1000);
				npc[k] = 0;
				npc_zhengli();
				npc_shoupai_num--;  //npc���Ƽ�һ
				player_answer();
				show();
			}
		}
		tempnpcshoupai=npc_shoupai_num;
		for (k = 0; k<tempnpcshoupai; k++)		
		{
			if ((npc[k] == 4)&&(player_shoupai_num>0))      //�ҵ����Ӳ������ж����ɲ�
			{
				npc_desktop = npc[k];//��¼npc������
				npc_desktop2 =npc[k];//��¼npc������
				//printf("��Ӣ�ۡ�ʹ�ù��Ӳ��ţ�\n");
				mciSendString("close guohemusic", NULL, 0, NULL);  //�ȹر�ǰһ��
				mciSendString("open \"����ɱ��Ƶ�ز�\\���Ӳ���.mp3\" alias guohemusic",NULL,0,NULL);//����ɱ
				mciSendString("play guohemusic", NULL, 0, NULL);  //������һ��
				Sleep(1000);
				putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
				setbkmode(TRANSPARENT);
				settextstyle(30, 0, _T("΢���ź�"));
				outtextxy(PromptBox_x+20,PromptBox_y,_T("ѡ�����и�ɻ����ǽ�����"));
				FlushBatchDraw();
				Sleep(1000);
				player_answer();
				npc[k] = 0;
				npc_zhengli();
				npc_shoupai_num--;  //npc���Ƽ�һ
				show();
			}
		}
		tempnpcshoupai=npc_shoupai_num;
		for (k = 0; k<tempnpcshoupai; k++)		
		{

			if (npc[k] == 9)      //�ҵ���������
			{
				npc_desktop = npc[k];//��¼npc������
				npc_desktop2 =npc[k];//��¼npc������
				//printf("��Ӣ�ۡ�ʹ���������֣�\n");
				mciSendString("close nanmanmusic", NULL, 0, NULL);  //�ȹر�ǰһ��
				mciSendString("open \"����ɱ��Ƶ�ز�\\��������.mp3\" alias nanmanmusic",NULL,0,NULL);//����ɱ
				mciSendString("play nanmanmusic", NULL, 0, NULL);  //������һ��
				Sleep(1000);
				putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
				setbkmode(TRANSPARENT);
				settextstyle(30, 0, _T("΢���ź�"));
				outtextxy(PromptBox_x+20,PromptBox_y,_T("ѡ�����и�ɻ����ǳ�ɱ���ǽ�����"));
				FlushBatchDraw();
				Sleep(1000);
				npc[k] = 0;
				npc_zhengli();
				npc_shoupai_num--;  //npc���Ƽ�һ
				player_answer();
				if((player_life==0)&&(isplayermirror==1))//�������л��ľ�
				{
					isplayermirror=0;			//ж�»��ľ�
					player_life++;
					putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
					setbkmode(TRANSPARENT);
					settextstyle(30, 0, _T("΢���ź�"));
					outtextxy(PromptBox_x+20,PromptBox_y,_T("���Ļ��ľ����ѣ���һ��Ѫ��"));
					FlushBatchDraw();
					Sleep(1000);
					show();
				}
				if((npc_life==0)&&(isnpcmirror==1))//�������л��ľ�
				{
					isnpcmirror=0;			//ж�»��ľ�
					npc_life++;
					putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
					setbkmode(TRANSPARENT);
					settextstyle(30, 0, _T("΢���ź�"));
					outtextxy(PromptBox_x+20,PromptBox_y,_T("�з��Ļ��ľ����ѣ���һ��Ѫ��"));
					FlushBatchDraw();
					Sleep(1000);
					show();
				}
				if((npc_life<=0)||(player_life<=0))   //��������
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
			if (npc[k] == 10)      //�ҵ�����뷢
			{
				npc_desktop = npc[k];//��¼npc������
				npc_desktop2 =npc[k];//��¼npc������
				//printf("��Ӣ�ۡ�ʹ������뷢��\n");
				mciSendString("close wanjianmusic", NULL, 0, NULL);  //�ȹر�ǰһ��
				mciSendString("open \"����ɱ��Ƶ�ز�\\����뷢.mp3\" alias wanjianmusic",NULL,0,NULL);//����ɱ
				mciSendString("play wanjianmusic", NULL, 0, NULL);  //������һ��
				Sleep(1000);
				putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
				setbkmode(TRANSPARENT);
				settextstyle(30, 0, _T("΢���ź�"));
				outtextxy(PromptBox_x+20,PromptBox_y,_T("ѡ�����и�ɻ����ǳ������ǽ�����"));
				FlushBatchDraw();
				Sleep(1000);
				npc[k] = 0;
				npc_zhengli();
				npc_shoupai_num--;  //npc���Ƽ�һ
				player_answer();
				if((player_life==0)&&(isplayermirror==1))//�������л��ľ�
				{
					isplayermirror=0;			//ж�»��ľ�
					player_life++;
					putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
					setbkmode(TRANSPARENT);
					settextstyle(30, 0, _T("΢���ź�"));
					outtextxy(PromptBox_x+20,PromptBox_y,_T("���Ļ��ľ����ѣ���һ��Ѫ��"));
					FlushBatchDraw();
					Sleep(1000);
					show();
				}
				if((npc_life==0)&&(isnpcmirror==1))//�������л��ľ�
				{
					isnpcmirror=0;			//ж�»��ľ�
					npc_life++;
					putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
					setbkmode(TRANSPARENT);
					settextstyle(30, 0, _T("΢���ź�"));
					outtextxy(PromptBox_x+20,PromptBox_y,_T("�з��Ļ��ľ����ѣ���һ��Ѫ��"));
					FlushBatchDraw();
					Sleep(1000);
					show();
				}
				if((npc_life<=0)||(player_life<=0))   //��������
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
				ss++;		//��¼��һ��ɱ
			}
			
			if ((npc[k] == 1) &&((npc_sha_num==0)||(isnpczhuge==1))&&(x_npctowanjia<=1))        //�ҵ�ɱ�ұ��غϵ�һ��ʹ�û����������ڷ�Χ
			{
				npc_desktop = npc[k];//��¼npc������
				npc_desktop2 =npc[k];//��¼npc������
				//printf("��Ӣ�ۡ�ʹ��ɱ��\n");
				mciSendString("close shamusic", NULL, 0, NULL);  //�ȹر�ǰһ��
				mciSendString("open \"����ɱ��Ƶ�ز�\\ɱ.mp3\" alias shamusic",NULL,0,NULL);//����ɱ
				mciSendString("play shamusic", NULL, 0, NULL);  //������һ��
				Sleep(500);
				npc[k] = 0;
				npc_zhengli();
				npc_shoupai_num--;  //���Ƽ�һ
				npc_sha_num++;
				show();
				putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
				setbkmode(TRANSPARENT);
				settextstyle(30, 0, _T("΢���ź�"));
				outtextxy(PromptBox_x+20,PromptBox_y,_T("ѡ��������ǽ�����"));
				FlushBatchDraw();
				Sleep(1000);
				player_answer();
				if((player_life==0)&&(isplayermirror==1))//�������л��ľ�
				{
					isplayermirror=0;			//ж�»��ľ�
					player_life++;
					putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
					setbkmode(TRANSPARENT);
					settextstyle(30, 0, _T("΢���ź�"));
					outtextxy(PromptBox_x+20,PromptBox_y,_T("���Ļ��ľ����ѣ���һ��Ѫ��"));
					FlushBatchDraw();
					Sleep(1000);
					show();
				}
				if((npc_life==0)&&(isnpcmirror==1))//�������л��ľ�
				{
					isnpcmirror=0;			//ж�»��ľ�
					npc_life++;
					putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
					setbkmode(TRANSPARENT);
					settextstyle(30, 0, _T("΢���ź�"));
					outtextxy(PromptBox_x+20,PromptBox_y,_T("�з��Ļ��ľ����ѣ���һ��Ѫ��"));
					FlushBatchDraw();
					Sleep(1000);
					show();
				}
				if((npc_life<=0)||(player_life<=0))   //��������
				{
					isover = 1;
					goto end;
				}

			}

		}
		if((npc_life==0)&&(isnpcmirror==1))//�������л��ľ�
		{
			isnpcmirror=0;			//ж�»��ľ�
			npc_life++;
			putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
			setbkmode(TRANSPARENT);
			settextstyle(30, 0, _T("΢���ź�"));
			outtextxy(PromptBox_x+20,PromptBox_y,_T("�з��Ļ��ľ����ѣ���һ��Ѫ��"));
			FlushBatchDraw();
			Sleep(1000);
			show();
		}
		if((npc_life<=0)||(player_life<=0))   //��������
		{
			isover = 1;
		}
		if((ss>1)||((ss==1)&&(player_shoupai_num<4)))		//�Ż�npc��������ʱ��
		{
			for(k=0;k<npc_shoupai_num;k++)
			{
				if (npc[k] == 12)      //�ҵ�����
				{
					npc_desktop = npc[k];//��¼npc������
					npc_desktop2 =npc[k];//��¼npc������
					//printf("��Ӣ�ۡ�ʹ�þ�����\n");
					mciSendString("close juedoumusic", NULL, 0, NULL);  //�ȹر�ǰһ��
					mciSendString("open \"����ɱ��Ƶ�ز�\\����.mp3\" alias juedoumusic",NULL,0,NULL);//����ɱ
					mciSendString("play juedoumusic", NULL, 0, NULL);  //������һ��
					Sleep(500);
					putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
					setbkmode(TRANSPARENT);
					settextstyle(30, 0, _T("΢���ź�"));
					outtextxy(PromptBox_x+20,PromptBox_y,_T("ѡ�����и�ɻ����ǳ�ɱ���ǽ�����"));
					FlushBatchDraw();
					Sleep(1000);
					npc[k] = 0;
					npc_zhengli();
					npc_shoupai_num--;  //npc���Ƽ�һ
					juedoupeople=1;
					juedou();			//�������
					show();
					break;
				}
			}
		}


	}
	if((npc_life==0)&&(isnpcmirror==1))//�������л��ľ�
	{
		isnpcmirror=0;			//ж�»��ľ�
		npc_life++;
		putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
		setbkmode(TRANSPARENT);
		settextstyle(30, 0, _T("΢���ź�"));
		outtextxy(PromptBox_x+20,PromptBox_y,_T("�з��Ļ��ľ����ѣ���һ��Ѫ��"));
		FlushBatchDraw();
		Sleep(1000);
		show();
	}
	if((npc_life<=0)||(player_life<=0))   //��������
	{
		isover = 1;
	}

end:;
}

void juedou()
{
	isjuedou=1;		//��ʼ����
	if(juedoupeople==0)	//�����������
	{
		while(1)
		{
			int k;
			int pp=0;//��¼��ʱ�����е�һ�غ�ɱ�Ĵ���
			for (k = 0; k<npc_shoupai_num; k++)
			{
				if(npc[k]==1)	//�ҵ�ɱ
				{
					npc_desktop = npc[k];//��¼npc������
					npc_desktop2 =npc[k];//��¼npc������
					mciSendString("close shamusic", NULL, 0, NULL);  //�ȹر�ǰһ��
					mciSendString("open \"����ɱ��Ƶ�ز�\\ɱ.mp3\" alias shamusic",NULL,0,NULL);//����ɱ
					mciSendString("play shamusic", NULL, 0, NULL);  //������һ��
					Sleep(500);
					pp++;
					npc[k] = 0;
					npc_zhengli();
					npc_shoupai_num--;  //���Ƽ�һ
					show();
					putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
					setbkmode(TRANSPARENT);
					settextstyle(30, 0, _T("΢���ź�"));
					outtextxy(PromptBox_x+20,PromptBox_y,_T("������ɱ��"));
					FlushBatchDraw();
					Sleep(1000);
					player_answer();
					if((player_life==0)&&(isplayermirror==1))//�������л��ľ�
					{
						isplayermirror=0;			//ж�»��ľ�
						player_life++;
						putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
						setbkmode(TRANSPARENT);
						settextstyle(30, 0, _T("΢���ź�"));
						outtextxy(PromptBox_x+20,PromptBox_y,_T("���Ļ��ľ����ѣ���һ��Ѫ��"));
						FlushBatchDraw();
						Sleep(1000);
						show();
					}
					if((npc_life==0)&&(isnpcmirror==1))//�������л��ľ�
					{
						isnpcmirror=0;			//ж�»��ľ�
						npc_life++;
						putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
						setbkmode(TRANSPARENT);
						settextstyle(30, 0, _T("΢���ź�"));
						outtextxy(PromptBox_x+20,PromptBox_y,_T("�з��Ļ��ľ����ѣ���һ��Ѫ��"));
						FlushBatchDraw();
						Sleep(1000);
						show();
					}
					if((npc_life<=0)||(player_life<=0))   //��������
					{
						isover = 1;
						goto end;
					}
					break;
				}
			}
			if(pp==0)		//˵����һ�غϵ�����ɱ
			{
				putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
				setbkmode(TRANSPARENT);
				settextstyle(30, 0, _T("΢���ź�"));
				outtextxy(PromptBox_x+20,PromptBox_y,_T("�з�δ��ɱ��������Ӯ�ˣ��з��ܵ�һ��λ�˺���"));
				FlushBatchDraw();
				Sleep(1000);
				npc_life--;		//��Ѫ
				show();
				isjuedou=0;		//
				break;		//�������ҷ�Ӯ����
			}
			if(isjuedou==0)
			{
				break;		//�������ҷ������
			}
		}
	}
	if(juedoupeople==1)	//npc��������
	{
		player_answer();
		if((player_life==0)&&(isplayermirror==1))//�������л��ľ�
		{
			isplayermirror=0;			//ж�»��ľ�
			player_life++;
			putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
			setbkmode(TRANSPARENT);
			settextstyle(30, 0, _T("΢���ź�"));
			outtextxy(PromptBox_x+20,PromptBox_y,_T("���Ļ��ľ����ѣ���һ��Ѫ��"));
			FlushBatchDraw();
			Sleep(1000);
			show();
		}
		if((npc_life<=0)||(player_life<=0))   //��������
		{
			isover = 1;
		}
		if(juedoupeople==-1)		//��ʾ����и��
		{
			juedoupeople=0;
		}
		else if(isjuedou==0)		//��Ҿ�������
		{
		}
		else if(juedoupeople==0)		//��ʾ��ɱ��
		{
			while(1)
			{
				int k;
				int pp=0;//��¼��ʱ�����е�һ�غ�ɱ�Ĵ���
				for (k = 0; k<npc_shoupai_num; k++)
				{
					if(npc[k]==1)	//�ҵ�ɱ
					{
						npc_desktop = npc[k];//��¼npc������
						npc_desktop2 =npc[k];//��¼npc������
						mciSendString("close shamusic", NULL, 0, NULL);  //�ȹر�ǰһ��
						mciSendString("open \"����ɱ��Ƶ�ز�\\ɱ.mp3\" alias shamusic",NULL,0,NULL);//����ɱ
						mciSendString("play shamusic", NULL, 0, NULL);  //������һ��
						Sleep(500);
						pp++;
						npc[k] = 0;
						npc_zhengli();
						npc_shoupai_num--;  //���Ƽ�һ
						show();
						putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
						setbkmode(TRANSPARENT);
						settextstyle(30, 0, _T("΢���ź�"));
						outtextxy(PromptBox_x+20,PromptBox_y,_T("������ɱ��"));
						FlushBatchDraw();
						Sleep(1000);
								player_answer();
						if((player_life==0)&&(isplayermirror==1))//�������л��ľ�
						{
							isplayermirror=0;			//ж�»��ľ�
							player_life++;
							putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
							setbkmode(TRANSPARENT);
							settextstyle(30, 0, _T("΢���ź�"));
							outtextxy(PromptBox_x+20,PromptBox_y,_T("���Ļ��ľ����ѣ���һ��Ѫ��"));
							FlushBatchDraw();
							Sleep(1000);
							show();
						}
						if((npc_life==0)&&(isnpcmirror==1))//�������л��ľ�
						{
							isnpcmirror=0;			//ж�»��ľ�
							npc_life++;
							putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
							setbkmode(TRANSPARENT);
							settextstyle(30, 0, _T("΢���ź�"));
							outtextxy(PromptBox_x+20,PromptBox_y,_T("�з��Ļ��ľ����ѣ���һ��Ѫ��"));
							FlushBatchDraw();
							Sleep(1000);
							show();
						}
						if((npc_life<=0)||(player_life<=0))   //��������
						{
							isover = 1;
							goto end;
						}
						break;
					}
				}
				if(pp==0)		//˵����һ�غϵ�����ɱ
				{
					putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
					setbkmode(TRANSPARENT);
					settextstyle(30, 0, _T("΢���ź�"));
					outtextxy(PromptBox_x+20,PromptBox_y,_T("�з�δ��ɱ��������Ӯ�ˣ��з��ܵ�һ��λ�˺���"));
					FlushBatchDraw();
					Sleep(1000);
					npc_life--;		//��Ѫ
					show();
					isjuedou=0;		//
					break;		//�������ҷ�Ӯ����
				}
				if(isjuedou==0)
				{
					break;		//�������ҷ������
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
	if (MouseHit()) //�������Ϣʱִ��
	{
		m=GetMouseMsg();

		
			if (m.uMsg==WM_LBUTTONDOWN)
			{
				for (i=0;(i<player_shoupai_num)&&(!isselected);i++)
				{
					if ((m.x>=player_x[i]&&m.x<=player_x[i]+player_width)&&(m.y>=player_y[i]&&m.y<=player_y[i]+player_high))
					{
						player_out=i;
						player_y[i]-=20;//ͻ��
						isselected=1;
						goto end0;
					}
				
				}
				
				if ((isselected)&&(m.x>=player_x[player_out]&&m.x<=player_x[player_out]+player_width)&&(m.y>=player_y[player_out]&&m.y<=player_y[player_out]+player_high))
				{
					player_y[player_out]+=20;//����
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
							//�غϽ���
					}
					else if((isRoundover==1)&&(disnum==0))	//����������
					{
						isplayer_discard=0;				//�����ƣ�ͼ����ʧ
						isselected=0;
						isRoundover=0;
					}
					
				}
				if(OverValue==2)			//�ڶ��ز���
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
				if(OverValue==3)			//�ڶ��ز���
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
				if(OverValue==5)			//�����
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
	if (MouseHit()) //�������Ϣʱִ��
	{
		m=GetMouseMsg();

		
			if (m.uMsg==WM_LBUTTONDOWN)
			{
				for (i=0;(i<player_shoupai_num)&&(!isselected);i++)
				{
					if ((m.x>=player_x[i]&&m.x<=player_x[i]+player_width)&&(m.y>=player_y[i]&&m.y<=player_y[i]+player_high))
					{
						player_out=i;
						player_y[i]-=20;//ͻ��
						isselected=1;
						goto end0;
					}
				
				}
				
				if ((isselected)&&(m.x>=player_x[player_out]&&m.x<=player_x[player_out]+player_width)&&(m.y>=player_y[player_out]&&m.y<=player_y[player_out]+player_high))
				{
					player_y[player_out]+=20;//����
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
					answerover=1;			//���������������Ӧ
				}

	
			}
end0:;
	
	
	
	}

}

void huihe_player()   //��һغ�
{
	while (1)
	{
		if(isover == 1)	//����������Ϸ������
		{
			break;
		}
		interactive();//��꽻��
		if(isRoundover==0)			//�����Ƶ��
		{
			player_panding();  //�ж�
			player_zhengli();   //����
			show();
			npc_panding();//���������ж�
			npc_zhengli();//npc��������
		}
		if(isRoundover==1)   //��һغϽ�������
		{
			player_discard();
			player_panding();  //�ж�
			player_zhengli();   //����
		}
		if(player_out==-2)
		{
			break;
		}
		show();     //������ʾ
		isEffective=0;
	}
}

void huihe_npc()      //���Իغ�
{
	npc_panding();
	npc_zhengli();
	npc_discard();	//����
	player_sha_num=0;			//Ϊ�»غ���׼��
	npc_sha_num = 0;
	player_shan_num=0;			//Ϊ�»غ���׼��
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
		settextstyle(30, 0, _T("΢���ź�"));
		if(npc_life<=0)
		{
			if (OverValue!=5)
			{
			putimage(restart_x,restart_y,&img_next);
			outtextxy(PromptBox_x+20,PromptBox_y,_T("��Ӯ�ˣ�"));
			outtextxy(PromptBox_x+20,PromptBox_y+20,_T("���ֽ�����"));
			}
			else
			{
			putimage(restart_x,restart_y,&img_restart);
			outtextxy(PromptBox_x+20,PromptBox_y,_T("��Ӯ�ˣ�"));
			outtextxy(PromptBox_x+20,PromptBox_y+20,_T("���ֽ�����"));
			}
		}
		if(player_life<=0)
		{
			putimage(restart_x,restart_y,&img_restart);
			outtextxy(PromptBox_x+20,PromptBox_y,_T("�����ˣ�"));
			outtextxy(PromptBox_x+20,PromptBox_y+20,_T("���ֽ�����"));
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
					}    //��һ��
					if ((m.x>=over_x&&m.x<=over_x+roundover_width)&&(m.y>=over_y&&m.y<=over_y+roundover_high))
					{
						isover=0;
						OverValue=0;
						break;
					}	//������Ϸ			
				}
			
		//}
		
		EndBatchDraw();
	
		
		
		
		//exit(0);		//�ֽ׶�ֱ���˳�
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
		settextstyle(30, 0, _T("΢���ź�"));
		outtextxy(Prompt_x+60,Prompt_y+160,_T("����������ϷΪ������ɱ�����ֽ̳̣���̻����"));
		outtextxy(Prompt_x+60,Prompt_y+200,_T("�����Ƶ�ʹ�ã����������Ƶ�ʹ���Լ�װ���Ƶļ�"));
		outtextxy(Prompt_x+60,Prompt_y+240,_T("�����ܡ�����Ϸһ���������ؿ���ͨ�غ�ſ�����"));
		outtextxy(Prompt_x+60,Prompt_y+280,_T("ѡ��Ŷ����ʼ��Ϸ�����·���ť��������һ��"));
		outtextxy(Prompt_x+60,Prompt_y+320,_T("ʼ���������֮�ðɣ�׼��������"));
		outtextxy(Prompt_x+30,Prompt_y+380,_T("������Ա��Ȫˮ���鳤�����Ե����Ա�����귲��������"));
		outtextxy(Prompt_x+190,Prompt_y+420,_T("�Ӻ���ѧ19���ƿƶ���"));
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
	DataStartup(); //���ݳ�ʼ��
	ImgStartup();  // ͼ���ʼ��
	gamestart();   //��Ϸ��ʼ
	mciSendString("open \"����ɱ��Ƶ�ز�\\��������.mp3\" alias bk1music",NULL,0,NULL);  //���ű�������
	mciSendString("play bk1music repeat",NULL,0,NULL);  //ѭ������
	while(1)
	{
		BeginBatchDraw();
		if(OverValue==4)
		{
			startup_4();	//������ʾ�����ֽ̳̽���
		}
		if(OverValue==0)
		{
			exit(0);	//����
		}
		if(OverValue==1)
		{
			startup_1();	//��һ��
		}
		if(OverValue==2)
		{
			startup_2();	//�ڶ���
		}
		if(OverValue==3)
		{
			startup_3();	//������
		}
	
		if(OverValue==5)
		{
			startup_5();	//��ʽս��
		}
		while (1)  //  ��Ϸѭ��ִ��
		{
			 
			show();  // ��ʾ����
			player_getnew();//�������
			huihe_player();   //��һغ�
			if(isover == 1)		//��Ϸ����
			{
				break;
			}
			putimage(PromptBox_x,PromptBox_y,&img_PromptBox);
			setbkmode(TRANSPARENT);
			settextstyle(30, 0, _T("΢���ź�"));
			outtextxy(PromptBox_x+20,PromptBox_y,_T("�з��غϣ�"));
			FlushBatchDraw();
			Sleep(500);
			npc_getnew();//��������
			huihe_npc();      //���Իغ�
			if(isover == 1)		//��Ϸ����
			{
				break;
			}
		
		}
		gameover();     // ��Ϸ��������������
	}

	
	return 0;
}