//E言語をC言語にするコンパイラ
//Powered by ENOKI
#define SOURCEMAX 9999
#define FILENAMEMAX 300
#define FILEDIRMAX 600
#define FULLPATHMAX 800
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<unistd.h>
#include<ctype.h>
#include"orderlist.h"
int i,j,k;//ループカウンタ
int filenum;
int cmerr=0;//コンパイル時にエラーがあったら1にする
int cmerrall=0;//コンパイル時のエラーの数を保存
int len,sourceend=0,shapecheck=0,shapecheck1=0,enternum=0;
char ch;//一文字ずつ文字を取得
char source[SOURCEMAX],filename[FILENAMEMAX],filename1[FILENAMEMAX],filename2[FILENAMEMAX],filedir[FILEDIRMAX],key=0,exefilename[FULLPATHMAX],command[FULLPATHMAX];
char *filepath,*word;//ファイル名からフルパスを取得する用

int yesno(void){//getchでyとnの入力を判定します,0=Y,1=N
	while(1){
		key=getch();
		if((key==121)||(key==89)){//Yが押された時
			return 0;
		}else if((key==110)||(key==78)){//Nが押された時
			return 1;
		}
	}
}



//ここからmain
int main(int argc,char **argv){//ドラッグアンドドロップの値は引数で読み込める
	
	resetdata();
	printf("E言語→C言語変換器\n");
	
	//ファイルポインタ
	FILE *fp,*cfp;
	
	//ファイルオープン
	if(argc>1){//ドラッグ&ドロップされたかどうかの確認
		strcpy(filename,argv[1]);
		printf("\"%s\"をドラッグ&ドロップで読み込みました。\n",filename);
	}else{
		printf("E言語ファイルの相対パスまたは絶対パスを入力してください(exitと入力すると終了します)→");
		scanf("%s",filename);
	}
	if((strcmp(filename,"exit"))==0){
		printf("プログラムを終了します。\n");
		return 0;
	}
	fp=fopen(filename,"r");
	if(fp==NULL){
		sprintf(filename,"%s.e",filename);
		fclose(fp);
		fp=fopen(filename,"r");
	}
	
	//ファイルが適切に読み込まれているかを確認
	if(fp==NULL){
		perror("ファイルの読み込みに失敗しました");
		printf("\nコンパイルを終了します\n");
		return 1;
	}
	if((filename[1]!=':')&&(filename[2]!='\\')){//相対パスの場合は絶対パスを取得
		strcpy(filename1,filename);
		filepath=getcwd(filedir,400);//絶対パスの取得
		if(filepath==NULL){
			printf("ファイル名が長すぎるかディレクトリが長すぎてファイルを出力できません！\n任意のキーでコンパイルを終了します\n");
			getch();
			return 1;
		}
		sprintf(filename,"%s\\%s",filedir,filename1);
	}
	strcpy(filename1,filename);
	strcpy(filename2,filename);
	filenum=strlen(filename);//文字列の長さを取得
	for(i=filenum;i>0;i--){//ファイル名から拡張子を消す
		if(filename[i]=='.'){
			filename[i]=0;
			break;
		}
	}
	
	sprintf(cfilename,"%s.c",filename);
	sprintf(exefilename,"%s.exe",filename);
	strcpy(filename,filename2);//フルパスを取得したものを戻す
	
	if((cfp=fopen(cfilename,"r"))!=NULL){
		printf("出力予\定のc言語ファイルが既に存在しています。上書きしますか？(y/n)\n");
		if((yesno())==0){
			fclose(cfp);
			cfp=fopen(cfilename,"w");
		}else{
			printf("コンパイルを終了します\n");
			fclose(fp);
			fclose(cfp);
			return 1;
		}
	}
	
	printf("絶対パス:%s\n",filename);
	
	//テキストの読み込みと出力
	printf("▼===== ソ\ースファイルの内容 =====▼\n");
	i=0;
	j=1;
	printf("%3d:",j);
	while((source[i]=fgetc(fp))!=EOF){
		printf("%c",source[i]);
		if(source[i]=='\n'){
			j++;
			printf("%3d:",j);
		}
		i++;
	}
	printf("\r\n▲=========== ここまで ===========▲\nコードは全体で%d行です。\nコンパイルを開始します。\n",j);
	enternum=j;
	
	//ここからコンパイル
	i=0;
	fseek(fp,0L,SEEK_SET);//getcのリセット
	fprintf(cfp,	"#include<stdio.h>\n"
					"#include<stdlib.h>\n"
					"#include<conio.h>\n"
					"#include<string.h>\n"
					"#include<math.h>\n"
					"#include<sys/stat.h>\n"
					"#include<direct.h>\n"
					"#include<ctype.h>\n"
					"#include<time.h>\n");
	enn=1;
	sourceend=0;
	while(1){//一行ずつ読み込む
		i=0;
		while(((source[i]=fgetc(fp))!=EOF)&&(source[i]!='\n')){
			i++;
		}
		source[i]='\0';	
		j=0;
		while((source[0]==' ')||(source[0]=='\t')||(source[0]=='\v')){//先頭のtabとスペースの削除
			len=strlen(source);
			strcpy(source,&source[1]);
			source[len]='\0';
		}
		if(source[0]=='\0'){//何もない行の処理
			printf("%3d行目:空白行です。\n",enn);
			enn++;
			continue;
		}
		k=1;
		while(k!=i){//途中からコメントのやつ用
			if((source[k-1]!='@')&&(source[k]=='/')&&(source[k+1]=='/')){
				source[k]='\0';
			}
			k++;
		}
		k=strlen(source);
		k--;
		while((source[k]==' ')||(source[k]=='\t')||(source[k]=='\v')){//最後のタブとスペースを消す
			source[k]='\0';
			k--;
		}
		if((source[0]=='}')&&(source[1]!='n')){//分岐とループの終了用
			printf("%3d行目:分岐またはループの終点です。\n",enn);
			fprintf(cfp,"}\n");
			enn++;
			continue;
		}
		if(source[0]=='#'){//ハッシュタグで始まるあれ
			if(shapecheck1==0){
				cmerr=shape(source);
				fprintf(cfp,"%s",output);
			}else if(shapecheck1==1){//途中ハッシュタグを辞めさせる
				printf("%3d行目:Error:#で始まる文はプログラムの最初に入れてください！\n",enn);
				cmerrall++;
			}
			cmerrall+=cmerr;
			if(enn==enternum)break;
			enn++;
			continue;
		}else if((source[0]=='/')&&(source[1]=='/')){//コメント行の無視
			printf("%3d行目:コメント行です。\n",enn);
			if(enn==enternum)break;
			enn++;
			continue;
		}else if(shapecheck1==0){
			fprintf(cfp,"int main(int argc,char **argv){\n");
			shapecheck1=1;
		}
		cmerr=trans(source);//ここでメインのコンパイルをします！
		if(cmerr!=0){
			cmerrall++;
		}else{
			fprintf(cfp,"%s",output);
		}
		if(enn==enternum)break;
		fclose(cfp);
		cfp=fopen(cfilename,"a");
		enn++;
	}
	fprintf(cfp,"}\n");
	
	//コンパイル終了
	fclose(cfp);
	if(cmerrall!=0){//コンパイルエラーの個数を判定
		printf("コンパイル時に%d個のエラーが発生しました。\n",cmerrall);
		fclose(fp);
		printf("任意のキーを押してプログラムを終了します。\n");
		getch();
		return 1;
	}
	
	
	printf("正常にC言語ファイルへの変換が完了しました。\nコンパイルしますか？（外部のgccコマンドを使用します）(y/n)\n");
	if((yesno())==0){
		printf("コンパイルを実行します。\n");
		sprintf(command,"gcc %s -o %s",cfilename,exefilename);
		err=system(command);
		if(err==0){
			printf("正常にプログラムが完成しました。\n実行しますか？(y/n)\n");
			if((yesno())==0){
				printf("=========================\n\n");
				err=system(exefilename);
				printf("\n\n=========================\n");
				printf("プログラムは戻り値%dで",err);
				if(err==0)printf("正常に");
				printf("終了しました。\n");
			}
		}else{
			printf("コンパイルエラーが発生しました。\nプログラムを終了します。\n");
			return 1;
		}
	}
	
	printf("プログラムを終了します。\n");
	//ファイルクローズ
	fclose(fp);
	
	
	return 0;
}