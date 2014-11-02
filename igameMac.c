#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>
#include <sys/time.h>
#include <string.h>

// キー入力
void init_keyboard();
void close_keyboard();
int kbhit();
int readkey();
static struct termios init_tio;     // kbhit用
// end キー入力

struct yusha{
	char* name; 
	int hp;
	int mp;
	int maxhp;
	int maxmp;
	int lv;
	int atk;
	int def;
	int exp;
	};
struct monsters{
	char* mname;
	int mhp;
	int mmp;
	int matk;
	int mdef;
	int mexp;
	};
char idou;
void mapart();
void move(char idou);
void sentou(struct monsters teki);
void create();
void lastart();
void lastmove(char idou);
struct yusha yush;
struct monsters teki;//sentouyou ni hitsuyou
struct monsters* enemy;
int road;
int lvup=40;
char command;
char skill=0;
char name[10];

char map[15][35]={
{'%','%','%','%','%','%','%','%','%','%','%','%','%','%','%','%','%','%','%','%','%','%','%','%','%','%','%','%','%','%','%','%','%',' ','%'},         
{'%',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','%'},
{'%',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','%'},
{'%',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','%'},
{'%',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','%'},
{'%',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','%'},
{'%',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','%'},
{'%',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','%'},
{'%',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','%'},
{'%',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','%'},
{'%',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','%'},
{'%',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','%'},
{'%',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','%'},
{'%',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','%'},
{'%','Y','%','%','%','%','%','%','%','%','%','%','%','%','%','%','%','%','%','%','%','%','%','%','%','%','%','%','%','%','%','%','%','%','%'}
};
char lastboss[15][21]={
{'%','%','%','%','%','%','%','%','%','%','%','%','%','%','%','%','%','%','%','%','%'},
{'%',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','%'},
{'%',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','%'},
{'%',' ',' ',' ',' ',' ',' ',' ','-',' ',' ',' ','-',' ',' ',' ',' ',' ',' ',' ','%'},
{'%',' ',' ',' ',' ',' ',' ',' ','.',' ',' ',' ','.',' ',' ',' ',' ',' ',' ',' ','%'},
{'%',' ',' ',' ',' ',' ',' ',' ',' ',' ','A',' ',' ',' ',' ',' ',' ',' ',' ',' ','%'},
{'%',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','%'},
{'%',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','%'},
{'%',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','%'},
{'%','%','%','%','%','%','%','%','%',' ',' ',' ','%','%','%','%','%','%','%','%','%'},
{' ',' ',' ',' ',' ',' ',' ',' ','%',' ',' ',' ','%',' ',' ',' ',' ',' ',' ',' ',' '},
{' ',' ',' ',' ',' ',' ',' ',' ','%',' ',' ',' ','%',' ',' ',' ',' ',' ',' ',' ',' '},
{' ',' ',' ',' ',' ',' ',' ',' ','%',' ',' ',' ','%',' ',' ',' ',' ',' ',' ',' ',' '},
{' ',' ',' ',' ',' ',' ',' ',' ','%',' ',' ',' ','%',' ',' ',' ',' ',' ',' ',' ',' '},
{' ',' ',' ',' ',' ',' ',' ',' ','%',' ','Y',' ','%',' ',' ',' ',' ',' ',' ',' ',' '}
};


char box=' ';
int m,p;
int ml,pl;

int encount;
int HPUP;
int MPUP;
int ATKUP;
int DEFUP;
int kihonti;
int damage;
int haba;
int mhaba;
int rndhaba;
int hantei;
int yaku=4;
int drop=0;
int count=0;
int soubi=1;
int daburu=0;
char next[20];
int ad=0;
int boss=0;
int consu=0;
int continu=3;
int mode=0;
int rndboss=0;
int tame;

int main(){

	int ch = 0;// キー入力

	srand(time(NULL));
	//yusha settei
	yush.maxhp=300;
	yush.maxmp=40;
	yush.lv=1;
	yush.atk=200;
	yush.def=80;
	yush.hp=yush.maxhp;
	yush.mp=yush.maxmp;
	yush.exp=0;

	//monster settei
	struct monsters a;
	a.mname="ドゥル";
	a.mhp=200;
	a.mmp=0;
	a.matk=80;
	a.mdef=30;
	a.mexp=15;

	struct monsters b;
	b.mname="マロク";
	b.mhp=400;
	b.mmp=100;
	b.matk=80;
	b.mdef=50;
	b.mexp=25;

	struct monsters c;
	c.mname="タイザー";
	c.mhp=200;
	c.mmp=0;
	c.matk=185;
	c.mdef=65;
	c.mexp=45;

	struct monsters d;
	d.mname="メタルドゥル";
	d.mhp=5;
	d.mmp=500;
	d.matk=120;
	d.mdef=10000;
	d.mexp=1000;

	struct monsters e;//ラスボス第6	
	e.mname="豆腐神 はせゆー";
	e.mhp=10000;
	e.mmp=1000;
	e.matk=340;
	e.mdef=150;
	e.mexp=0;

	struct monsters f;//ラスボス第5
	f.mname="トーフーキング　はせゆー";
	f.mhp=7500;
	f.mmp=500;
	f.matk=280;
	f.mdef=120;
	f.mexp=1500;

	struct monsters g;//ラスボス第4
	g.mname="はせゆーレジェンド";
	g.mhp=5000;
	g.mmp=0;
	g.matk=340;
	g.mdef=0;
	g.mexp=1200;

	struct monsters h;//ラスボス第3
	h.mname="らもす";
	h.mhp=1500;
	h.mmp=6000;
	h.matk=150;
	h.mdef=350;
	h.mexp=1000;

	struct monsters i;//ラスボス第2
	i.mname="はせゆかりん";
	i.mhp=1500;
	i.mmp=150;
	i.matk=230;
	i.mdef=60;
	i.mexp=600;

	struct monsters j;//ラスボス第1
	j.mname="おとうふ ♪";
	j.mhp=1000;
	j.mmp=100;
	j.matk=180;
	j.mdef=200;
	j.mexp=400;

	struct monsters s;/*short mode boss*/
	s.mname="豆腐神　はせゆー";
	s.mhp=1200;
	s.mmp=0;
	s.matk=200;
	s.mdef=60;
	s.mexp=0;


	m=14;
	p=1;

	char G[10];
	
printf("\n\n\n\n\n\n\n\n     　ーーーーーーーーーー\n     /　　　　　　　　　　/\n     ーーーーーーーーーー |\n     | 　　　　　　　　 | |\n     | おとうふクエスト | /\n     |  　　　　　　　　|/\n     ーーーーーーーーーー\n\n\n\n\n\n\n\n\n\n");
	printf("モードを選択してください\n１：ショートモード  :  適正時間　5分\n２：通常モード  :  適正時間15分〜20分\n\n");
	scanf("%d",&mode);
	printf("名前を入力してください。\n");
	scanf("%s",name);
	yush.name=name;

	if(mode==1){
		soubi=5;
		yaku=20;
		count=2;
	}

	if(strcmp(yush.name,"issa")==0){
		yush.hp=600;
		yush.maxhp=600;
		yush.atk=yush.atk+30;
		yush.def=0;
		soubi=5;
		yush.exp=yush.exp+4000;
	}	
kh:
ddd:
	create();
while(1){
	// printf("\a");
	if(count!=3){
		mapart();	
	}
	else{
		lastart();
	}
	init_keyboard();
	while(ch!='q'){
		if ( kbhit() ) {
            ch = readkey();

            switch(ch) {
                case 'w':
                	if(count!=3){
                		move('w');
						
                	}
                	else{
                		lastmove('w');
                	}goto label;
                    break;
                case 's':
                	if(count!=3){
                		move('s');
                    	
                	}
                	else{
                		lastmove('s');
                	}goto label;
                    break;
                case 'd':
                	if(count!=3){
                		move('d');
                		
                	}
                	else{
                		lastmove('d');
                	}goto label;
                    
                    break;
                case 'a':
                	if(count!=3){
                		move('a');
                    	
                	}
                	else{
                		lastmove('a');
                	}goto label;
                    break;
               	case 'p':
               		printf("\n\n");
               		create();
               		mapart();
               		break;
               	case 'y':
  					if(yaku<1){
  						printf("\n薬草が足りません\n");
  						goto label;
  						break;
  					}
               		else if(mode==2){
               			printf("\n%s は薬草を使った!\n%s はHPを%d回復した!\n",yush.name,yush.name,count*80+160);
						yush.hp=yush.hp+count*80+160;
						if(yush.hp>yush.maxhp){
						yush.hp=yush.maxhp;
						}
						yaku--;
					}
					else if(mode==1){
               			printf("\n%s は薬草を使った!\n%s はHPを200回復した!\n",yush.name,yush.name);
						yush.hp=yush.hp+200;
						if(yush.hp>yush.maxhp){
						yush.hp=yush.maxhp;
						}
						yaku--;
					}
					if(count!=3){
  						mapart();
  					}
  					else{
  						lastart();
  					}
          	}
       	}
   	}
label:		
	if(ad!=1){
	if(m==0){
		count++;
	if(mode==1){
		lastart();
		m=14;
		p=10;
		ad=1;
	}
	else{	
		 if(count==3){
			lastart();
			m=14;
			p=10;
			ad=1;
		}
		else{
			printf("NEXT MAP!\n");
			create();
			m=14;
			p=1;
		}
		continue;
	}
	}

	encount=rand()%100;

	if(encount>=93&&box==' '&&count<3){//kakuritsu ha atode kaeru
		encount=rand()%100;
		
		if(encount>=30){
			teki=a;
		}
		else{
			teki=b;
		}
		if(count==1&&mode==2){
			teki.mhp=teki.mhp*1.5;
			teki.mmp=teki.mmp*1.5;
			teki.matk=teki.matk*1.4;
			teki.mdef=teki.mdef*1.3;
			teki.mexp=teki.mexp*2;
		}
		else if(count==2&&mode==2){
			teki.mhp=teki.mhp*2;
			teki.mmp=teki.mmp*9999;
			teki.matk=teki.matk*1.7;
			teki.mdef=teki.mdef*2;
			teki.mexp=teki.mexp*3.2;
		}
		else if(mode==1){
			teki.mhp=teki.mhp*0.8;
			teki.mexp=teki.mexp*1.5;
		}
		if(strcmp(yush.name,"eno")!=0){
			sentou(teki);
			if(command=='9'){
				goto ddd;
			}
		}
	}
	else if(encount>=70&&box=='/'&&count<3){
		encount=rand()%100;

		if(encount>=84){
			teki=a;
		}
		else if(encount>=45){
			teki=b;
		}
		else if(encount>=8){
			teki=c;
		}
		else{
			teki=d;
		}
		if(count==1&&mode==2){
			teki.mhp=teki.mhp*1.5;
			teki.mmp=teki.mmp*1.5;
			teki.matk=teki.matk*1.4;
			teki.mdef=teki.mdef*1.3;
			teki.mexp=teki.mexp*2;
		}
		else if(count==2&&mode==2){
			teki.mhp=teki.mhp*2;
			teki.mmp=teki.mmp*9999;
			teki.matk=teki.matk*1.9;
			teki.mdef=teki.mdef*2;
			teki.mexp=teki.mexp*3.2;
		}
		if(strcmp(yush.name,"eno")!=0){
			sentou(teki);
			if(command=='9'){
				goto ddd;
			}
		}
		}
	}
	else if(count==3){
		if(m<=6){
			if(mode==1){
				teki=s;
				sentou(teki);
				printf(" \n\n\n\n\n\n\n\n\n\n\n           G   A   M   E\n\n\n         C   R   E   A   R\n\n\n\n\n\n\n\n\n                                   thank you for playing!\n\n\n");
				exit(0);
			}
			else{
				if(boss==0){
					teki=j;
					sentou(teki);
					printf("%s は薬草を手に入れた！\n",yush.name);
					yaku++;
					if(consu==1){
						consu=0;
						goto kh;
					}
					boss++;
				}
				if(boss==1){
					teki=i;
					sentou(teki);
					printf("%s は薬草を手に入れた！\n",yush.name);
					yaku++;
					if(consu==1){
						consu=0;
						goto kh;
					}
					boss++;
				}
				if(boss==2){
					teki=h;
					sentou(teki);
					printf("%s は薬草を手に入れた！\n",yush.name);
					yaku++;
					if(consu==1){
						consu=0;
						goto kh;
					}
					boss++;
				}
				if(boss==3){
					teki=g;
					sentou(teki);
					printf("%s は薬草を手に入れた！\n",yush.name);
					yaku++;
					if(consu==1){
						consu=0;
						goto kh;
					}
					boss++;
				}
				if(boss==4){
					teki=f;
					sentou(teki);
					printf("%s は薬草を手に入れた！\n",yush.name);
					yaku++;
					if(consu==1){
						consu=0;
						goto kh;
					}
					boss++;
				}
				if(boss==5){
					teki=e;
					sentou(teki);
					if(consu==1){
						consu=0;
						goto kh;
					}
					boss++;
					printf(" \n\n\n\n\n\n\n\n\n\n\n           G   A   M   E\n\n          C   R   E   A   R\n\n\n\n\n\n\n\n                                   thank you for playing!\n\n\n");
					exit(0);
				}


			}
			printf("\n\n");
	

		}
	}
}

	close_keyboard();	// キー入力用
	return 0;
}



void mapart(){		/*マップ表示*/
	int x,y;
	x=0;
	y=0;
	while(y<15){
		while(x<35){		
			putchar(map[y][x]);		
			if(lastboss[y][x]=='Y'){
				lastboss[y][x]=' ';
			}
			x++;				
		}
		y++;
		if(y==1){
			printf("    ----------------------");
		}
		else if(y==2){
			printf("    | %s",yush.name);
		}
		else if(y==3){
			printf("    |---------------------");
		}
		else if(y==4){
			printf("    | HP : %d/%d",yush.hp,yush.maxhp);
		}
		else if(y==5){
			printf("    | MP : %d/%d",yush.mp,yush.maxmp);
		}
		else if(y==6){
			printf("    | Lv . %d",yush.lv);
		}
		else if(y==7){
			printf("    |---------------------");
		}
		else if(y==8){
			printf("    |バッグ");
		}
		else if(y==9){
			printf("    | 薬草 × %d",yaku);
		}
		else if(y==10){
			printf("    ----------------------");
		} 
		else if(y==11&&soubi>=4){
			printf("    | 剣 : エクスカリバー");
		}
		else if(y==11&&soubi<=3){
			printf("    | 剣 : シャーペン");
		}
		else if(y==12&&soubi>=3){
			printf("    | 盾 : プリドゥエンの盾");
		}
		else if(y==12&&soubi<=2){
			printf("    | 盾 : なし");
		}
		else if(y==13&&soubi>=2){
			printf("    | 鎧 : ウィガールの鎧");
		}
		else if(y==13&&soubi==1){
			printf("    | 鎧 : なし");
		}
		else if(y==14){
			printf("    ----------------------");
		}
		x=0;
		printf("\n");
	}
	printf("\n\n\n");
}

void move(char idou){
	if(idou=='w'){				/*うえに移動*/
		m=m-1;
		if(map[m][p]!='%'){
			m=m+1;
			map[m][p]=box;
			m=m-1;
			box=map[m][p];
			map[m][p]='Y';
		}
		else{
			printf("これ以上いけません\n");
			m=m+1;
		}
	}

	else if(idou=='s'){				/*下に移動*/
		m=m+1;
		if(map[m][p]!='%'){
			m=m-1;
			map[m][p]=box;
			m=m+1;
			box=map[m][p];
			map[m][p]='Y';
		}
		else{
			printf("これ以上いけません\n");
			m=m-1;
		}
	}
	else if(idou=='d'){				/*右に移動*/
		p=p+1;
		if(map[m][p]!='%'){
			p=p-1;
			map[m][p]=box;
			p=p+1;
			box=map[m][p];
			map[m][p]='Y';
		}
		else{
			printf("これ以上いけません\n");
			p=p-1;
		}
	}
	else if(idou=='a'){				/*左に移動*/
		p=p-1;
		if(map[m][p]!='%'){
			p=p+1;
			map[m][p]=box;
			p=p-1;
			box=map[m][p];
			map[m][p]='Y';
		}
		else{
			printf("これ以上いけません\n");
			p=p+1;
		}
	}
	if(box=='H'){
		if(soubi==1){
			printf("%s は　を手に入れた\n%s は ウィガールの鎧 を装備した\n",yush.name,yush.name);
			yush.def=yush.def+40;
			soubi++;
		}
		else if(soubi==2){
			printf("%s は　を手に入れた\n%s は プリドゥウェンの盾 を装備した\n",yush.name,yush.name);
			yush.def=yush.def+60;
			soubi++;		
		}
		else if(soubi==3){
			printf("%s は　を手に入れた\n%s は エクスカリバー を装備した\n",yush.name,yush.name);
			yush.atk=yush.atk+100;
			soubi++;
		}
		else{
			printf("宝箱は空だった．．．．");
		}
		box=' ';
	}
	printf("\n");
}

// キーボード入力用
void init_keyboard()  { tcgetattr(0,&init_tio); }
void close_keyboard() { tcsetattr(0,TCSANOW,&init_tio); }


int kbhit()
{
    struct termios tio;
    struct timeval tv;
    fd_set rfds;
    memcpy(&tio,&init_tio,sizeof(struct termios));
    tio.c_lflag &= ~(ICANON);
    tcsetattr(0,TCSANOW,&tio);
    FD_ZERO(&rfds);
    FD_SET(0,&rfds);
    tv.tv_usec = 0;
    tv.tv_sec  = 0;
    select(1,&rfds,NULL,NULL,&tv);
    tcsetattr(0,TCSANOW,&init_tio);
    return (FD_ISSET(0,&rfds)?1:0);
}
int readkey()		/*キー入力*/
{
    int ch;
    struct termios tio;
    memcpy(&tio,&init_tio,sizeof(struct termios));
    tio.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO,TCSANOW,&tio);
    read(0,&ch,1);
    tcsetattr(0,TCSANOW,&init_tio);
    return ch;
}
void sentou(struct monsters teki){
			//rndboss=rand()%10;
			enemy=&teki;
			if(count==0||count==3||mode==1){
			printf("\n------------------------\n%s　が現れた!!\n\n\n\n",enemy->mname);
			}
			if(count==1){
			printf("\n------------------------\nスーパー%s が現れた!!\n\n\n\n",enemy->mname);
			}
			else if(count==2&&mode==2){
			printf("\n------------------------\n%sドラゴン　が現れた!!\n\n\n\n",enemy->mname);		
			}
			printf("(何かを入力してください)\n");
			scanf("%s",next);
			while(yush.hp>=0){
			printf("  ----------------------\n  | %s  \n  |---------------------\n  | HP : %d/%d \n  | MP : %d/%d \n  | Lv . %d  \n  |---------------------\n  | 薬草　×　%d\n  ----------------------\n",yush.name,yush.hp,yush.maxhp,yush.mp,yush.maxmp,yush.lv,yaku);
			printf("選択してください!\n");
			printf("1 : 攻撃\n2 : スキル\n3 : 薬草\n");
			if(soubi>=3){
				printf("4 : 防御\n");
			}	
				
				
				command=getchar();

				if(command!='1'||command!='2'||command!='3'||command!='4'){
					command=getchar();
				}
				if(command=='9'){
					break;
				}
				else if(command=='1'){		/*通常攻撃*/
					kihonti=yush.atk/2-enemy->mdef/4;
					haba=kihonti/16+1;
					rndhaba=rand()%haba*2+1;
					damage=kihonti-haba+rndhaba;
					if(damage<=0){
						hantei=rand()%100;
						if(hantei<70){
							damage=1;
						}
						else{
							damage=0;
						}
					}
					if(count==0||count==3||mode==1){
					printf("%s の攻撃\n%s に %d ダメージ!\n\n",yush.name,enemy->mname,damage);
					}
					else if(count==1){
						printf("%s の攻撃\nスーパー%s に %d ダメージ!\n\n",yush.name,enemy->mname,damage);
					}
					else if(count==2&&mode==2){
						printf("%s の攻撃\n%sドラゴン に %d ダメージ!\n\n",yush.name,enemy->mname,damage);
					} 
					enemy->mhp=enemy->mhp-damage;
					if(enemy->mhp<=0){
						break;					
					}		
				}	
				else if(command=='2'){		/*スキル*/
					printf("スキル を選択\n1 : クリティカルショット / MP 12 / 会心を狙って、一か八か大ダメージ！！\n2 : トゥワイスソード / MP 7 / 二回連続攻撃\n3 : ドレインブレード / MP 10 / 相手に攻撃,そして自分は回復\n4 : 戻る\n");
			hj:
					skill=getchar();
					if(skill=='1'){
						yush.mp=yush.mp-8;
						if(yush.mp<0){
							printf("MPがたりません\n");
							yush.mp=yush.mp+8;
							continue;
						}
						printf("%s は クリティカルショット を使った!\n",yush.name);
						rndhaba=rand()%3;
						if(rndhaba==1){
							damage=yush.atk*1.8;
							if(count==0||count==3){
							printf("会心の一撃!\n%s に %d のダメージ!\n",enemy->mname,damage);
							}
							else if(count==1){
								printf("会心の一撃!\nスーパー%s に %d のダメージ!\n",enemy->mname,damage);
							}
							else if(count==2&&mode==2){
								printf("会心の一撃!\n%sドラゴン に %d のダメージ!\n",enemy->mname,damage);
							}
							enemy->mhp=enemy->mhp-damage;
							if(enemy->mhp<=0){
								break;					
							}
						}
						else{
							printf("%s の攻撃ははずれた...\n",yush.name);
						}
						
						
						

					}
					else if(skill=='2'){
						yush.mp=yush.mp-5;
						if(yush.mp<0){
							printf("MPがたりません\n");
							yush.mp=yush.mp+5;
							continue;
						}
						printf("%s は トゥワイスソード を使った!\n",yush.name);
						while(daburu<=1){
							kihonti=yush.atk/2-enemy->mdef/4;
							mhaba=kihonti/16+1;
							rndhaba=rand()%mhaba*2+1;
							damage=kihonti-mhaba+rndhaba;
							damage=damage*0.7;
							if(damage<=0){
								hantei=rand()%10;
								if(hantei<7){damage=1;}
								else{damage=0;}
							}
							if(count==0||count==3||mode==1){
								printf("%s の攻撃\n%s に %d ダメージ!\n",yush.name,enemy->mname,damage);
							}
							else if(count==1){
								printf("%s の攻撃\nスーパー%s に %d ダメージ!\n",yush.name,enemy->mname,damage);
							}
							else if(count==2&&mode==2){
								printf("%s の攻撃\n%sドラゴン に %d ダメージ!\n",yush.name,enemy->mname,damage);
							} 	
							enemy->mhp=enemy->mhp-damage;
							if(enemy->mhp<=0){
								break;					
							}
							daburu++;
						}	

						daburu=0;		
					}


				
					else if(skill=='3'){
						yush.mp=yush.mp-6;
						if(yush.mp<0){
							printf("MPがたりません\n");
							yush.mp=yush.mp+6;
							continue;
						}
						printf("%s は ドレインブレード を使った!\n\n",yush.name);
						kihonti=yush.atk/2-enemy->mdef/4;
						haba=kihonti/16+1;
						rndhaba=rand()%haba*2+1;
						damage=kihonti-haba+rndhaba;
						damage=damage*0.75;
						if(damage<=0){
							hantei=rand()%100;
							if(hantei<70){
								damage=1;
							}
							else {damage=0;}
						}
						if(count==0||count==3||mode==1){
							printf("%s の攻撃\n%s に %d ダメージ!\n%s は %d 回復した。\n",yush.name,enemy->mname,damage,yush.name,2*damage/5);
						}
						else if(encount==1){
							printf("%s の攻撃\nスーパー%s に %d ダメージ!\n%s は %d 回復した。\n",yush.name,enemy->mname,damage,yush.name,2*damage/5);
						}
						else if(count==2&&mode==2){
							printf("%s の攻撃\n%sドラゴン に %d ダメージ!\n%s は %d 回復した。\n",yush.name,enemy->mname,damage,yush.name,2*damage/5);
						}
						enemy->mhp=enemy->mhp-damage;
						yush.hp=yush.hp+2*damage/5;
						if(yush.maxhp<=yush.hp){
							yush.hp=yush.maxhp;
						}
						if(enemy->mhp<=0){
							break;					
						}


						
					}
					else if(skill=='4'){
						continue;
					}
					else if(skill!='1'||skill!='2'||skill!='3'||skill!='4'){
						goto hj;
					}

					if(enemy->mhp<=0){
						break;
					}
				}
				else if(command=='3'){		/*薬草使用*/
					if(yaku>0&&mode==2){
					printf("%s は薬草を使った!\n%s はHPを%d回復した!\n",yush.name,yush.name,count*80+160);
					yush.hp=yush.hp+count*80+160;
					if(yush.hp>yush.maxhp){
						yush.hp=yush.maxhp;
					}
					yaku--;
					}
					else if(yaku>0&&mode==1){
					printf("%s は薬草を使った!\n%s はHPを200回復した!\n",yush.name,yush.name);
					yush.hp=yush.hp+200;
					if(yush.hp>yush.maxhp){
						yush.hp=yush.maxhp;
					}
					yaku--;
					}
					else{
						printf("薬草が足りません\n");
						continue;
					}
				

				}
				else if(command=='4'&&soubi>=3){
					printf("%s は防御している\n",yush.name);
				}
				else{
					continue;
				}
				if(strcmp(enemy->mname,"メタルドゥル")==0&&enemy->mhp>=3){	/*メタスラ逃げ率*/
					hantei=rand()%100;
					if(hantei<30){
						printf("メタルドゥル　は逃げ出した．．．\n\n");
						break;
					}
					else{
						kihonti=enemy->matk/2-yush.def/4;
					mhaba=kihonti/16+1;
					rndhaba=rand()%mhaba*2+1;
					damage=kihonti-mhaba+rndhaba;
					if(damage<=0){
						hantei=rand()%10;
						if(hantei<7){damage=1;}
						else{damage=0;}
					}
					if(tame==1){
						damage=damage*2.5;
						tame=0;
					}
					if(command=='4'&&soubi>=3){
						damage=damage/3;
					}
			
					if(count==0||count==3||mode==1){
						printf("%s の攻撃!\n%s に %d ダメージ\n\n",enemy->mname,yush.name,damage);		/*敵の攻撃*/
					}
					else if(count==1){
						printf("スーパー%s の攻撃!\n%s に %d ダメージ\n\n",enemy->mname,yush.name,damage);	
					}
					else if(count==2&&mode==2){
						printf("%sドラゴン の攻撃!\n%s に %d ダメージ\n\n",enemy->mname,yush.name,damage);	
					}
				
					}
				}
				else if(strcmp(enemy->mname,"はせゆかりん")==0&&enemy->mhp<=900&&enemy->mmp>=50){
					printf("ーーーーーーーーーーーーーー\n");
					rndboss=rand()%10;
					if(rndboss>=5){
						printf("はせゆかりん　は炎を吐いた\n");
						damage=enemy->matk*0.7+rndboss;
						if(command==4){
							damage=damage/3;
						}
						printf("%s は　%d のダメージ\n",yush.name,damage);
						enemy->mmp=enemy->mmp-50;
					}
					else{

					kihonti=enemy->matk/2-yush.def/4;
					mhaba=kihonti/16+1;
					rndhaba=rand()%mhaba*2+1;
					damage=kihonti-mhaba+rndhaba;
					if(damage<=0){
						hantei=rand()%10;
						if(hantei<7){damage=1;}
						else{damage=0;}
					}
					if(command=='4'&&soubi>=3){
						damage=damage/3;
					}
				
					if(count==0||count==3||mode==1){
						printf("%s の攻撃!\n%s に %d ダメージ\n\n",enemy->mname,yush.name,damage);		/*敵の攻撃*/
					}
					else if(count==1){
						printf("スーパー%s の攻撃!\n%s に %d ダメージ\n\n",enemy->mname,yush.name,damage);	
					}
					else if(count==2&&mode==2){
						printf("%sドラゴン の攻撃!\n%s に %d ダメージ\n\n",enemy->mname,yush.name,damage);	
					}
				
					}
				}
				else if(strcmp(enemy->mname,"らもす")==0&&enemy->mhp<=1300){
					rndboss=rand()%100;
					if(rndboss>=90){
						kihonti=enemy->matk/2-yush.def/4;
						mhaba=kihonti/16+1;
						rndhaba=rand()%mhaba*2+1;
						damage=kihonti-mhaba+rndhaba;
						if(damage<=0){
							hantei=rand()%10;
							if(hantei<7){damage=1;}
							else{damage=0;}
					}
					if(command=='4'&&soubi>=3){
						damage=damage/3;
					}
				
					if(count==0||count==3||mode==1){
						printf("%s の攻撃!\n%s に %d ダメージ\n\n",enemy->mname,yush.name,damage);		/*敵の攻撃*/
					}
					else if(count==1){
						printf("スーパー%s の攻撃!\n%s に %d ダメージ\n\n",enemy->mname,yush.name,damage);	
					}
					else if(count==2&&mode==2){
						printf("%sドラゴン の攻撃!\n%s に %d ダメージ\n\n",enemy->mname,yush.name,damage);	
					}
					}

					else if(rndboss>=0){
						mhaba=rand()%100;
						printf("らもす　は呪文を唱えた\n");
						if(mhaba>=65){
							printf("ショット！\n");
							kihonti=enemy->matk-60;
							mhaba=kihonti/16+1;
							rndhaba=rand()%mhaba*2+1;
							damage=kihonti-mhaba+rndhaba;	
							
							if(command=='4'&&soubi>=3){
								damage=damage/2;
							}
							printf("%s は　%d のダメージ\n",yush.name,damage);
						}
						else if(mhaba>=35){
							printf("ネフィルム！！\n");
							kihonti=enemy->matk-30;
							mhaba=kihonti/10+1;
							rndhaba=rand()%mhaba*2+1;
							damage=kihonti-mhaba+rndhaba;
							enemy->matk=enemy->matk*1.1;
							if(command=='4'&&soubi>=3){
								damage=damage/2;
							}
						printf("%s に　%d のダメージ\n",yush.name,damage);
						}
						
						else if(mhaba>=10&&enemy->mhp<=700){
							printf("アヴィス！！！\n");
							kihonti=enemy->matk;
							mhaba=kihonti/1+1;
							rndhaba=rand()%mhaba*3+1;
							damage=kihonti/2-mhaba+rndhaba;
							if(command=='4'&&soubi>=3){
								damage=damage/2;
							}
						printf("%s に　%d のダメージ\n",yush.name,damage);
						}
						else if(mhaba>=0){
							damage=0;
							printf("詠唱に失敗した\n");}
					}
			}
			else if(strcmp(enemy->mname,"豆腐神　はせゆー")==0&&enemy->mhp<=500&&tame==0){
				rndboss=rand()%10;
				if(rndboss<=5){
					goto gjd;
				}
				else {
					printf("豆腐神　はせゆー　は　力をためた\n");
					tame=1;
					damage=0;
				}		
			}



				else{
			gjd:
					kihonti=enemy->matk/2-yush.def/4;
					mhaba=kihonti/16+1;
					rndhaba=rand()%mhaba*2+1;
					damage=kihonti-mhaba+rndhaba;
					if(damage<=0){
						hantei=rand()%10;
						if(hantei<7){damage=1;}
						else{damage=0;}
					}
					if(tame==1){
						damage=damage*2.8;
						tame=0;
					}
					if(command=='4'&&soubi>=3){
						damage=damage/3;
					}
			
					if(count==0||count==3||mode==1){
						printf("%s の攻撃!\n%s に %d ダメージ\n\n",enemy->mname,yush.name,damage);		/*敵の攻撃*/
					}
					else if(count==1){
						printf("スーパー%s の攻撃!\n%s に %d ダメージ\n\n",enemy->mname,yush.name,damage);	
					}
					else if(count==2&&mode==2){
						printf("%sドラゴン の攻撃!\n%s に %d ダメージ\n\n",enemy->mname,yush.name,damage);	
					}
				}
				yush.hp=yush.hp-damage;
				
				if(yush.hp<=0&&mode==1){
					printf("GAME OVER\n");
					exit(0);
				}
				else if(yush.hp<=0&&count<=2){
					printf("%s　は倒れた．．．\n",yush.name);
				cons:
					printf("コンティニューしますか？　　残り%d回\n1 : YES\n2 : NO\n",continu);
					scanf("%d",&consu);
					if(continu>0&&consu==1){
						ad=0;
						continu--;
						yush.hp=yush.maxhp;
						yush.mp=yush.maxmp;
						break;
					}
					else if(continu==0||consu==2){
						if(continu==0){
							printf("コンティニューできません。");
						}
						printf("GAME OVER\n");
						exit(0);
						}
				
				else{
					printf("1 又は 2 を押してください。\n");
					goto cons;
				}
			}
				else if(yush.hp<=0&&count<=3){
					printf("%s　は倒れた．．．．．．\n",yush.name);
				con:
					printf("コンティニューしますか？　　残り%d回\n1 : YES\n2 : NO\n",continu);
					scanf("%d",&consu);
					if(continu>0&&consu==1){
						continu--;
						count--;
						yush.hp=yush.maxhp;
						yush.mp=yush.maxmp;
						ad=0;
						break;
					}
					else if(continu==0||consu==2){
						if(continu==0){
							printf("コンティニューできません。");
						}
						printf("GAME OVER\n");
						exit(0);

					}
					else{
						printf("1 又は 2 を押してください。 ");
						goto con;
					}

			}
		}
				if(enemy->mhp<=0){
				printf("%s を倒した！\n",enemy->mname);
				printf("%s は%d の経験値を手に入れた\n",yush.name,enemy->mexp);
				yush.exp=yush.exp+enemy->mexp;
				drop=rand()%10;
				if(drop>=8&&count<3){
					printf("%s は薬草を落とした\n",enemy->mname);
					yaku++;
				}
				printf("(何かを入力してください)\n\n");
				scanf("%s",next);
			}

			if(yush.lv<100){
				while(yush.exp>lvup){	//LV up 
					HPUP=rand()%14;
					MPUP=rand()%5;
					ATKUP=rand()%8;
					DEFUP=rand()%4;
					yush.lv=yush.lv+1;
					yush.maxmp=yush.maxmp+MPUP+2;
					yush.maxhp=yush.maxhp+HPUP+5;
					yush.atk=yush.atk+ATKUP+2;
					yush.def=yush.def+DEFUP+2;
					yush.hp=yush.maxhp;
					yush.mp=yush.maxmp;
					lvup=lvup+10+yush.lv*15+rand()%20;
					printf("%d\n",lvup);
					if(strcmp(yush.name,"issa")!=0){
						printf("   M M M M M M M M\n <      LV UP     > \n   W W W W W W W W\n\n");
						printf("-------------\n| %s  \n|------------\n|HP : %d/%d \n|MP : %d/%d \n|Lv . %d  \n-------------\n",yush.name,yush.hp,yush.maxhp,yush.mp,yush.maxmp,yush.lv);
						printf("(何かを入力してください)\n");
						scanf("%s",next);
					}
				}
			}
			
		printf("次のレベルまで　%d の経験値が必要です。\n----------------------\n",lvup-yush.exp+1);
	
}
void create(){			/*障害物生成*/
	int block=0;
	int w,q;
	m=14;
	p=1;
	box=' ';
	w=13;
	q=2;

	while(w!=0){
		while(q!=34){
				map[w][q]=' ';
			q++;
		}
	q=1;
	w--;
	}
	w=13;
	q=2;
	while(w!=0){
		while(q!=34){
			block=rand()%100;
			if(map[w][q]!='%'){
				if(block<=95&&map[w][q]!='/'){
					map[w][q]=' ';
				}
				else if(block==99){
					map[w][q]='/';
					w=w+1;
					q=q-1;
					if(map[w][q]!='%'){
						map[w][q]='/';
					}
					w=w-1;
					if(map[w][q]!='%'){
						map[w][q]='/';
					}
					w=w-1;
					if(map[w][q]!='%'){
						map[w][q]='/';
					}
					q=q+1;
					if(map[w][q]!='%'){
						map[w][q]='/';
					}
					q=q+1;
					if(map[w][q]!='%'){
						map[w][q]='/';
					}
					w=w+1;
					if(map[w][q]!='%'){
						map[w][q]='/';
					}
					w=w+1;
					if(map[w][q]!='%'){
						map[w][q]='/';
					}
					q=q-1;
					if(map[w][q]!='%'){
						map[w][q]='/';
					}
					w=w-1;
				}
				else if(block<=97){
					if(map[w][q]!='/'){
					map[w][q]='%';
					}
					w=w-1;
					if(map[w][q]!='/'){
					map[w][q]='%';
					}
					w=w+2;
					if(map[w][q]!='/'){
					map[w][q]='%';
					}
					w=w-1;
				}
				else{
					if(map[w][q]!='/'){
					map[w][q]='%';
					}
					q=q-1;
					if(map[w][q]!='/'){
					map[w][q]='%';
					}
					q=q+2;
					if(map[w][q]!='/'){
					map[w][q]='%';
					}
					q=q-1;
				}
			}
			q++;
		}
	q=1;
	w--;
	}
	map[13][1]=' ';
	map[14][1]='Y';
	map[0][33]=' ';
	if(count==0){
		map[1][1]='H';
	}
	else if(count==1){
		map[13][33]='H';
	}
	else if(count==2){
		map[1][15]='H';
	}
}

void lastart(){
	int x,y;
	x=0;
	y=0;
	printf("\n              トウフルーム\n\n");
	while(y<15){
		while(x<21){		
			putchar(lastboss[y][x]);
			x++;				
		}
		y++;
		if(y==1){
			printf("    ----------------------");
		}
		else if(y==2){
			printf("    | %s",yush.name);
		}
		else if(y==3){
			printf("    |---------------------");
		}
		else if(y==4){
			printf("    | HP : %d/%d",yush.hp,yush.maxhp);
		}
		else if(y==5){
			printf("    | MP : %d/%d",yush.mp,yush.maxmp);
		}
		else if(y==6){
			printf("    | Lv . %d",yush.lv);
		}
		else if(y==7){
			printf("    |---------------------");
		}
		else if(y==8){
			printf("    |バッグ");
		}
		else if(y==9){
			printf("    | 薬草 × %d",yaku);
		}
		else if(y==10){
			printf("    ----------------------");
		} 
		else if(y==11&&soubi>=4){
			printf("    | 剣 : エクスカリバー");
		}
		else if(y==11&&soubi<=3){
			printf("    | 剣 : シャーペン");
		}
		else if(y==12&&soubi>=3){
			printf("    | 盾 : プリドゥウェンの盾");
		}
		else if(y==12&&soubi<=2){
			printf("    | 盾 : なし");
		}
		else if(y==13&&soubi>=2){
			printf("    | 鎧 : ウィガールの鎧");
		}
		else if(y==13&&soubi==1){
			printf("    | 鎧 : なし");
		}
		else if(y==14){
			printf("    ----------------------");
		}
		x=0;
		printf("\n");
	}
	printf("\n\n\n");
}
void lastmove(char idou){
	if(idou=='w'){				/*うえに移動*/
		m=m-1;
		if(lastboss[m][p]!='%'){
			m=m+1;
			lastboss[m][p]=box;
			m=m-1;
			box=lastboss[m][p];
			lastboss[m][p]='Y';
		}
		else{
			printf("これ以上いけません\n");
			m=m+1;
		}
	}

	else if(idou=='s'){				/*下に移動*/
		m=m+1;
		if(lastboss[m][p]!='%'){
			m=m-1;
			lastboss[m][p]=box;
			m=m+1;
			box=lastboss[m][p];
			lastboss[m][p]='Y';
		}
		else{
			printf("これ以上いけません\n");
			m=m-1;
		}
	}
	else if(idou=='d'){				/*右に移動*/
		p=p+1;
		if(lastboss[m][p]!='%'){
			p=p-1;
			lastboss[m][p]=box;
			p=p+1;
			box=lastboss[m][p];
			lastboss[m][p]='Y';
		}
		else{
			printf("これ以上いけません\n");
			p=p-1;
		}
	}
	else if(idou=='a'){				/*左に移動*/
		p=p-1;
		if(lastboss[m][p]!='%'){
			p=p+1;
			lastboss[m][p]=box;
			p=p-1;
			box=lastboss[m][p];
			lastboss[m][p]='Y';
		}
		else{
			printf("これ以上いけません\n");
			p=p+1;
		}
	}
}