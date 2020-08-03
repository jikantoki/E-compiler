//orderlist.h
//文字数の最大値の設定
#define OUTPUTMAX 5000
#define WORDMAX 9999
#define ORDERMAX 500
#define HENSUMAX 999
#define OPTIONMAX 100
//ここまで

//バージョン表示
char langname[80]=
/**********************************************************/
/**/			"E言語 v0.0.1 byときえのき"				/**/
/**********************************************************/
;


int floatnum,enn=0;
int next=0;//関数が一行で連続したときに1にする
char output[OUTPUTMAX];//メインプログラムに出力する文字をいれる
int a=0,b=0,c=0,d=0,e=0,f=0,g=0,h=0,m,n,o,p,q;//ループカウンタ
int forwin=0;
int err=0;
int ifkara=0;//if文の~処理に必要
int strlong;//文字列の長さを一時的に保存
int mode=0;//関数の使用モードを保存
int hensukazu=0;//独自言語内で定義した変数の数を保存
int gotodo=0;//gotoが使用されたら1になります
int reset=0,hikinum=0,checker=0;
int hensumode[HENSUMAX];//配列には変数の番号、0=NULL,1=float,2=char
int hikikazu=0;//命令名を含めた引数の数を入れます
int errpoint;//エラーの場所を格納します
char option[OPTIONMAX][ORDERMAX],optionsave[OPTIONMAX][ORDERMAX];//配列0から順番に引数を保存します
char optionyobi[OPTIONMAX];//予備用のオプション保存変数
char name1[OPTIONMAX];
char hensuname[HENSUMAX][100];//使用した変数名を保存
char hiki[ORDERMAX],hikisave[ORDERMAX],hikihiki[ORDERMAX];//引数を一時的に保存
char outputword[ORDERMAX];//outputchange命令でグローバルで必要
char calc[5];//演算子を一時的に保存
double floatint;//float型の値を一時的に入れておく
char cfilename[FULLPATHMAX];//C言語出力ファイルのパス

void resetdata(void){//最初に配列をリセットする
	a=0;
	while(a!=HENSUMAX){
		hensumode[a]=0;//0=NULL,1=float,2=char
		a++;
	}
	a=0;
}

int optioncut(char wordin[ORDERMAX],char wordout[ORDERMAX],char kugiri){//optioncut(元々の文字列,変換先の文字列,区切る場所);
	int mojisu=strlen(wordin);
	int moji=0;
	while(moji!=mojisu){
		if((wordin[moji]==kugiri)&&(wordin[moji-1]!='@')){//@が前にある場合はコンティニュー
			strcpy(wordout,&wordin[moji+1]);
			wordin[moji]='\0';
			return 0;//区切る場所が存在すれば0になります
		}
		moji++;
	}
	return 1;
}

int ngword(char word[ORDERMAX]){//禁則文字があるか調べます
	int wordmax=strlen(word);
	int wordbasho=0;
	while(wordmax!=wordbasho){
		errpoint=wordbasho;
		if(word[wordbasho]=='\\')return 1;
		if(word[wordbasho]=='&')return 1;
		if(word[wordbasho]=='(')return 1;
		if(word[wordbasho]==')')return 1;
		if(word[wordbasho]=='<')return 1;
		if(word[wordbasho]=='>')return 1;
		if(word[wordbasho]=='{')return 1;
		if(word[wordbasho]=='}')return 1;
		if(word[wordbasho]=='\"')return 1;
		if(word[wordbasho]=='?')return 1;
		if(word[wordbasho]=='#')return 1;
		if(word[wordbasho]=='$')return 1;
		if(word[wordbasho]=='\'')return 1;
		if(word[wordbasho]=='^')return 1;
		if(word[wordbasho]=='|')return 1;
		if(word[wordbasho]=='`')return 1;
		if(word[wordbasho]=='>')return 2;
		if(word[wordbasho]=='<')return 2;
		if(word[wordbasho]=='=')return 2;
		if(word[wordbasho]=='!')return 2;
		if(word[wordbasho]=='+')return 2;
		if(word[wordbasho]=='-')return 2;
		if(word[wordbasho]=='*')return 2;
		if(word[wordbasho]=='/')return 2;
		wordbasho++;
	}
	wordbasho=0;
	while(wordmax!=wordbasho){
		errpoint=wordbasho;
		if(word[wordbasho]=='~')return 3;
		wordbasho++;
	}
	errpoint=0;
	return 0;
}

int strnum(char word[ORDERMAX]){//文字列の中身が全て数字なら0を返します
	int loop2;
	for(loop2=0;loop2<strlen(word)-1;loop2++){
		if(word[loop2]=='.')continue;
		if((isdigit(word[loop2]))==0){
			return 1;
		}
	}
	return 0;
}

int registercheck(char word[ORDERMAX]){//変数名を入れてERROR=1,NULL=1,FLOAT=2,CHAR=3を返します
	int loop,count001;
	sprintf(word,"%s_",word);//い つ も の
	for(count001=0;count001<HENSUMAX;count001++){
		if((strcmp(word,hensuname[count001]))==0){//変数名を全部保存してある変数から探していく
			if(hensumode[count001]==1){//float=1
				return 2;
			}else if(hensumode[count001]==2){//char=2
				return 3;
			}
		}
	}
	return 1;
}

int outputchange(char word[ORDERMAX]){//文字の@や\による文字の表現をします
	int mojimax=1,mojibasho=0,mojicount=0,mojicount2=0,hikinum=0;
	char mojisave[OPTIONMAX];
	hikikazu=0;
	while(mojimax!=mojibasho){//\一つでc言語における\\を出力する
		mojimax=strlen(word);
		if(word[mojibasho]=='\\'){
			strcpy(mojisave,&word[mojibasho+1]);
			word[mojibasho]='\\';
			word[mojibasho+1]='\\';
			word[mojibasho+2]='\0';
			sprintf(word,"%s%s",word,mojisave);
			mojibasho++;
		}
		if(word[mojibasho]=='%'){//%一つでc言語における%%を出力する
			strcpy(mojisave,&word[mojibasho+1]);
			word[mojibasho]='%';
			word[mojibasho+1]='%';
			word[mojibasho+2]='\0';
			sprintf(word,"%s%s",word,mojisave);
			mojibasho++;
		}
		if(word[mojibasho]=='\''){//'一つでc言語における\'を出力する
			strcpy(mojisave,&word[mojibasho+1]);
			word[mojibasho]='\\';
			word[mojibasho+1]='\'';
			word[mojibasho+2]='\0';
			sprintf(word,"%s%s",word,mojisave);
			mojibasho++;
		}
		if(word[mojibasho]=='\"'){//"一つでc言語における\"を出力する
			strcpy(mojisave,&word[mojibasho+1]);
			word[mojibasho]='\\';
			word[mojibasho+1]='\"';
			word[mojibasho+2]='\0';
			sprintf(word,"%s%s",word,mojisave);
			mojibasho++;
		}
		mojibasho++;
	}
	mojimax=1;
	mojibasho=0;
	while(mojimax>=mojibasho){//ここからエスケープシーケンス的なことが出来る
		mojicount=0;
		if(word[mojibasho]=='@'){//@をキーにする
			if(word[mojibasho+1]=='n'){//@nで改行
				strcpy(&word[mojibasho+2],&word[mojibasho+2]);//strcpy(e+拡張に必要な文字数,e+オリジナル書式で使う文字数);
				word[mojibasho]='\\';
				word[mojibasho+1]='n';
			}else if(word[mojibasho+1]=='b'){//@bで一文字消す
				strcpy(&word[mojibasho+2],&word[mojibasho+2]);
				word[mojibasho]='\\';
				word[mojibasho+1]='b';
			}else if(word[mojibasho+1]=='r'){//@rで行頭に戻る
				strcpy(&word[mojibasho+2],&word[mojibasho+2]);
				word[mojibasho]='\\';
				word[mojibasho+1]='r';
			}else if(word[mojibasho+1]=='@'){//@@で@の表示
				strcpy(&word[mojibasho+1],&word[mojibasho+2]);
				word[mojibasho]='@';
			}else if(word[mojibasho+1]=='/'){//@/で/の表示
				strcpy(&word[mojibasho+1],&word[mojibasho+2]);
				word[mojibasho]='/';
			}else if(word[mojibasho+1]==','){//@,で,の表示
				strcpy(&word[mojibasho+1],&word[mojibasho+2]);
				word[mojibasho]=',';
			}else{
				printf("%3d行目:Error:%d文字目で@の後に不明な文字表\現がされています！\n",enn,mojibasho+1);
				err=1;
				return 1;
			}
		}
			
			
		if(word[mojibasho]=='!'){//!をキーにする
			if(word[mojibasho+1]!='!'){
				strcpy(hiki,&word[mojibasho+1]);//!変数!で変数を表示させる
				while(hiki[mojicount]!='!'){
					mojicount++;
					if(mojicount==ORDERMAX)break;
				}
				hiki[mojicount]='\0';
				sprintf(hiki,"%s_",hiki);//変数名に_を増やしているのでその分
				hiki[mojicount+1]='\0';
				if(mojicount!=ORDERMAX){
					for(mojicount2=0;mojicount2<HENSUMAX;mojicount2++){
						if((strcmp(hiki,hensuname[mojicount2]))==0){//変数名があるかどうか検索
							for(m=0;m<=mojibasho;m++){
								hikihiki[m]=word[m];
							}
							hikihiki[mojibasho]='\0';
							strcpy(mojisave,&word[mojibasho+mojicount+2]);
							word[mojibasho]='\0';
							if(hensumode[mojicount2]==1){
								sprintf(word,"%s%%g%s",hikihiki,mojisave);
							}else if(hensumode[mojicount2]==2){
								sprintf(word,"%s%%s%s",hikihiki,mojisave);
							}
							strcpy(option[hikikazu+2],hiki);
							hikikazu++;
							mojibasho-=mojicount;
							break;
						}
					}
					if((mojicount>HENSUMAX)||(mojicount2>=HENSUMAX)){
						printf("%3d行目:Error:変数名%sが存在しません！\n",enn,hiki);
						err=1;
						return 1;
					}else{
						mojimax=strlen(word);
						continue;
					}
				}else{
					printf("%3d行目:Error:%d文字目に間違いがあります！\n",mojibasho);
					err=1;
					return 1;
				}
			}else{		//!!で!を表示します
				strcpy(&word[mojibasho+1],&word[mojibasho+2]);
				word[mojibasho]='!';
				mojimax=strlen(word);
				mojibasho++;
				continue;
			}
			printf("%3d行目:Error:%d文字目で!の後に不明な文字表\現がされています！\n",enn,mojibasho+1);
			err=1;
			return 1;
		}
		mojimax=strlen(word);
		mojibasho++;
	}
	strcpy(outputword,word);
	return 0;
}




//ここからメインの処理
int trans(char order[WORDMAX]){//基本的な命令の処理
	FILE *cfp2;
	int loop0=0;
	transstart://一応ラベルを
	for(loop0=0;loop0<OPTIONMAX;loop0++){
		option[loop0][0]='\0';
	}
	loop0=0;
	for(reset=0;reset<ORDERMAX;reset++)option[0][reset]='\0';
	hikikazu=0;
	strcpy(option[0],order);
	while((optioncut(option[hikikazu],option[hikikazu+1],','))==0){//,がある度にoptionの配列を変えて代入していく
		hikikazu++;
	}
	strcpy(order,option[0]);
	
	
	
	//ここから命令の処理
	if((strcmp(order,"num"))==0){//num関数,実数型の変数d
		if((optioncut(option[1],hiki,'='))==0){
			checker=1;
		}
		if(gotodo==1){
			printf("%3d行目:Error:変数を宣言する前にgo命令やlabel命令を使用しないでください！\n",enn);
			err=1;
			return 1;
		}
		if((ngword(option[1]))!=0){
			printf("%3d行目:Error:変数名に使用できない文字が含まれています！\n",enn);
			err=1;
			return 1;
		}
		floatint=atof(hiki);
		if(hensukazu==HENSUMAX){
			printf("%3d行目:Error:変数の数が多すぎます！\n",enn);
			err=1;
			return 1;
		}else{
			for(d=0;d<HENSUMAX;d++){
				if((strcmp(hensuname[d],option[1]))==0){
					printf("%3d行目:Error:変数名が重複しています！\n",enn);
					err=1;
					return 1;
				}
			}
			sprintf(option[1],"%s_",option[1]);//変数に_を付けることによってprintf変数の作成
			strcpy(hensuname[hensukazu],option[1]);//変数を登録します
			hensumode[hensukazu]=1;//num型なので1と登録
			hensukazu++;
			sprintf(output,"float %s",option[1]);
			if(checker==1)
				sprintf(output,"%s=%g",output,floatint);
			}
			sprintf(output,"%s;\n",output);
		err=0;
	}else if((strcmp(order,"go"))==0){//go命令,好きな場所にジャンプします
		gotodo=1;
		sprintf(output,"goto %s;\n",option[1]);
		err=0;
	}else if((strcmp(order,"label"))==0){//label命令,ジャンプラベルです
		gotodo=1;
		sprintf(output,"%s:\n",option[1]);
		err=0;
	}else if((strcmp(order,"str"))==0){//str関数,文字列の変数
		if(gotodo==1){
			printf("%3d行目:Error:変数を宣言する前にgo命令やlabel命令を使用しないでください！\n",enn);
			err=1;
			return 1;
		}
		if((optioncut(option[1],hiki,','))==0){
			hikinum=atoi(hiki);
		}
		if((ngword(option[1]))==1){
			printf("%3d行目:Error:変数名に使用できない文字が含まれています！\n",enn);
			err=1;
			return 1;
		}
		if(d==5){//要修正!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			printf("%3d行目:Error:変数名を数字のみにはできません！\n",enn);
			err=1;
			return 1;
		}else if(hensukazu==HENSUMAX){
			printf("%3d行目:Error:変数の数が多すぎます！\n",enn);
			err=1;
			return 1;
		}else{
			for(d=0;d<HENSUMAX;d++){
				if((strcmp(hensuname[d],option[1]))==0){
					printf("%3d行目:Error:変数名が重複しています！\n",enn);
					err=1;
					return 1;
				}
			}
			strcpy(hensuname[hensukazu],option[1]);
			hensukazu++;
			sprintf(output,"char %s",option[1]);
			if(hikinum!=0){
				sprintf(output,"%s[%d]",output,hikinum);
			}
			sprintf(output,"%s;\n",output);
		}
		err=0;
	}else if((strcmp(order,"put"))==0){//put関数,標準出力命令
		if((outputchange(option[1]))==0){
			sprintf(output,"printf(\"%s\"",outputword);
			for(loop0=2;loop0<=hikikazu+1;loop0++){
				sprintf(output,"%s,%s",output,option[loop0]);
			}
			sprintf(output,"%s);\n",output);
			err=0;
		}else{
			err=1;
			return 1;
		}
	}else if((strcmp(order,"in"))==0){//in関数,標準入力命令
		if(option[1][0]=='\0'){
			printf("%3d行目:Error:引数がありません！\n",enn);
			err=1;
			return 1;
		}
		sprintf(option[1],"%s_",option[1]);
		for(d=0;d<HENSUMAX;d++){
			if((strcmp(hensuname[d],option[1]))==0){
				sprintf(output,"scanf(\"");
				if(hensumode[d]==1){
					sprintf(output,"%s%%g\",&",output);
				}else if(hensumode[d]==2){
					sprintf(output,"%s%%s\",",output);
				}
				sprintf(output,"%s%s);\n",output,option[1]);
				break;
			}
		}
		if(d>=HENSUMAX){
			printf("%3d行目:Error:変数名%sが存在しません！\n",enn,option[1]);
			err=1;
			return 1;
		}
	}else if((strcmp(order,"exit"))==0){//exit関数,普通にexitをする
		e=atoi(option[1]);
		if((e<9999)&&(e>-9999)){
			sprintf(output,"exit (%d);\n",e);
		}else{
			printf("%3d行目:Error:exit命令のこの値は無効です！\n",enn);
			err=1;
			return 1;
		}
		err=0;
	}else if((strcmp(order,"info"))==0){//info関数,宣伝する
		sprintf(output,"printf(\"%s\\n製作者連絡先\\n Homepage\\thttps://jikantoki.jimdo.com\\n Twitter\\thttps://twitter.com/jikantoki\\n\");\n",langname);
		err=0;
	}else if((strcmp(order,"pause"))==0){//pause関数,相手の入力を待つ
		sprintf(output,"getch();\n");
		err=0;
	}else if((strcmp(order,"if"))==0){//if関数,条件分岐をする
		if((ngword(option[1]))==2){//文字を区切る場所があれば数えて返す
			if((option[1][errpoint]=='=')||(option[1][errpoint]=='<')||(option[1][errpoint]=='>')){//この三つ
				if(option[1][errpoint+1]!='='){
					calc[0]=option[1][errpoint];
					calc[1]='\0';
					strcpy(hiki,&option[1][errpoint+1]);
				}else{
					goto if2saves;
				}
			}else{//<=とか!=とか
				if2saves:
				calc[0]=option[1][errpoint];
				calc[1]=option[1][errpoint+1];
				calc[2]='\0';
				strcpy(hiki,&option[1][errpoint+2]);
			}
			option[1][errpoint]='\0';
			if((hiki[strlen(hiki)-1])=='{'){//最後が{で終わっている場合はmodeを0にする
				hiki[strlen(hiki)-1]='\0';
				mode=0;
			}else mode=1;
			ifkara=0;
			optionyobi[0]='\0';
			hikisave[0]='\0';
			if((ngword(option[1]))==3){
				optioncut(option[1],optionyobi,'~');
				if((strnum(optionyobi))!=0){//変数欄が数字じゃなかったら変数を探させる
					if((registercheck(optionyobi))==1){
						printf("%3d行目:Error:変数名%sが存在しません！\n",enn,optionyobi);
						err=1;
						return 1;
					}
				}
				ifkara=1;
			}
			if((ngword(hiki))==3){
				optioncut(hiki,hikisave,'~');
				if((strnum(hikisave))!=0){//変数欄が数字じゃなかったら変数を探させる
					if((registercheck(hikisave))==1){
						printf("%3d行目:Error:変数名%sが存在しません！\n",enn,hikisave);
						err=1;
						return 1;
					}
				}
				ifkara=2;
			}
			if((strnum(hiki))!=0){//変数欄が数字じゃなかったら変数を探させる
				if((registercheck(hiki))==1){
					printf("%3d行目:Error:変数名%sが存在しません！\n",enn,hiki);
					err=1;
					return 1;
				}
			}
			if((strnum(option[1]))!=0){//変数欄が数字じゃなかったら変数を探させる
				if((registercheck(option[1]))==1){
					printf("%3d行目:Error:変数名%sが存在しません！\n",enn,option[1]);
					err=1;
					return 1;
				}
			}
			if(ifkara==1){//ここから演算子の変換
				if((strcmp(calc,"="))==0){
					sprintf(output,"if((%s<=%s)&&(%s>=%s))",option[1],hiki,optionyobi,hiki);
				}else if((strcmp(calc,"!="))==0){
					sprintf(output,"if!((%s<=%s)&&(%s>=%s))",option[1],hiki,optionyobi,hiki);
				}else{//演算子が謎だった場合
					printf("%3d行目:Error:演算子に間違いがあります！\n",enn);
					err=1;
					return 1;
				}
			}else if(ifkara==2){//
				if((strcmp(calc,"="))==0){
					sprintf(output,"if((%s<=%s)&&(%s>=%s))",hiki,option[1],hikisave,option[1]);
				}else if((strcmp(calc,"!="))==0){
					sprintf(output,"if!((%s<=%s)&&(%s>=%s))",hiki,option[1],hikisave,option[1]);
				}else{//演算子が謎だった場合
					printf("%3d行目:Error:演算子に間違いがあります！\n",enn);
					err=1;
					return 1;
				}
			}else{
				if((strcmp(calc,"="))==0){
					sprintf(output,"if(%s==%s)",option[1],hiki);
				}else if((strcmp(calc,"!="))==0){
					sprintf(output,"if(%s!=%s)",option[1],hiki);
				}else if((strcmp(calc,"<"))==0){
					sprintf(output,"if(%s<%s)",option[1],hiki);
				}else if((strcmp(calc,">"))==0){
					sprintf(output,"if(%s>%s)",option[1],hiki);
				}else if((strcmp(calc,"<="))==0){
					sprintf(output,"if(%s<=%s)",option[1],hiki);
				}else if((strcmp(calc,">="))==0){
					sprintf(output,"if(%s>=%s)",option[1],hiki);
				}else{//演算子が謎だった場合
					printf("%3d行目:Error:演算子に間違いがあります！\n",enn);
					err=1;
					return 1;
				}
			}
			if(mode==0){
				sprintf(output,"%s{\n",output);
			}else{//ifの後にも命令が付いている場合
				order[0]='\0';
				for(d=2;d<12;d++){
					sprintf(order,"%s%s,",order,option[d]);
				}
				order[strlen(order)]='\0';//最後がカンマで終わっているので修正する
				next=1;
				cfp2=fopen(cfilename,"a");
				fprintf(cfp2,"%s",output);
				fclose(cfp2);
				goto transstart;
			}
		}else{
			printf("%3d行目:Error:引数に間違いがあります！\n",enn);
			err=1;
			return 1;
		}
	}else if((strcmp(order,"wait"))==0){//wait関数、待ちます
		if((strnum(option[1]))==0){
			waitstart:
			if(forwin==1){//windows.hが定義されているか確認
				sprintf(output,"Sleep(%s*1000);\n",option[1]);
			}else{
				printf("%3d行目:Error:この命令を使うにはプログラムの先頭で#forwinを定義してください！\n",enn);
				err=1;
				return 1;
			}
		}else{
			if((registercheck(option[1]))==2){
				goto waitstart;
			}else{
				printf("%3d行目:Error:変数名%sがnum変数でない又は存在しません！\n",enn,option[1]);
				err=1;
				return 1;
			}
		}
	}else{//その他
		if(order[0]!='\0'){
			printf("%3d行目:Error:%s命令は定義されていない未知の命令です！\n",enn,order);
		}else{
			printf("%3d行目:Error:文法に間違いがあります！\n",enn);
		}
		err=1;
		return 1;
	}
	if(err==0)printf("%3d行目:Log:%s命令を実行します\n",enn,order);
	return 0;
}

int shape(char sword[OUTPUTMAX]){//#で始まる命令の整備
	int mojimax=strlen(sword);
	int mojibasho;
	int hikiall=0;//引数の個数を保存します
	if((optioncut(sword,hiki,','))==0){
		hikiall++;
		if((optioncut(hiki,hikihiki,','))==0){
			hikiall++;
			
		}
	}
	if((strcmp(sword,"#forwin"))==0){//#include<windows.h>の定義
		if(forwin==0){
			forwin=1;
			sprintf(output,"#include<windows.h>\n");
			err=0;
		}else{
			err=1;
			printf("%3d行目:Error:同じ定義命令が二重に重なっています！\n",enn);
			return 1;
		}
	}else if((strcmp(sword,"#define"))==0){//#define（C言語通り）
		if((optioncut(sword,hiki,' '))==0){
			printf("%3d行目:Error:#defineを使用する時はスペースは使用しないでください！");
			err=1;
			return 1;
		}
		if(hikiall!=2){
			err=1;
			printf("%3d行目:Error:文法に間違いがあります！\n",enn);
			return 1;
		}
		sprintf(output,"#define %s %s\n",hiki,hikihiki);
		err=0;
	}
	if(err==0){
		printf("%3d行目:Log:%sのセットが完了しました\n",enn,&sword[1]);
	}
	return 0;
}
