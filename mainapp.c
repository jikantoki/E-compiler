//E�����C����ɂ���R���p�C��
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
int i,j,k;//���[�v�J�E���^
int filenum;
int cmerr=0;//�R���p�C�����ɃG���[����������1�ɂ���
int cmerrall=0;//�R���p�C�����̃G���[�̐���ۑ�
int len,sourceend=0,shapecheck=0,shapecheck1=0,enternum=0;
char ch;//�ꕶ�����������擾
char source[SOURCEMAX],filename[FILENAMEMAX],filename1[FILENAMEMAX],filename2[FILENAMEMAX],filedir[FILEDIRMAX],key=0,exefilename[FULLPATHMAX],command[FULLPATHMAX];
char *filepath,*word;//�t�@�C��������t���p�X���擾����p

int yesno(void){//getch��y��n�̓��͂𔻒肵�܂�,0=Y,1=N
	while(1){
		key=getch();
		if((key==121)||(key==89)){//Y�������ꂽ��
			return 0;
		}else if((key==110)||(key==78)){//N�������ꂽ��
			return 1;
		}
	}
}



//��������main
int main(int argc,char **argv){//�h���b�O�A���h�h���b�v�̒l�͈����œǂݍ��߂�
	
	resetdata();
	printf("E���ꁨC����ϊ���\n");
	
	//�t�@�C���|�C���^
	FILE *fp,*cfp;
	
	//�t�@�C���I�[�v��
	if(argc>1){//�h���b�O&�h���b�v���ꂽ���ǂ����̊m�F
		strcpy(filename,argv[1]);
		printf("\"%s\"���h���b�O&�h���b�v�œǂݍ��݂܂����B\n",filename);
	}else{
		printf("E����t�@�C���̑��΃p�X�܂��͐�΃p�X����͂��Ă�������(exit�Ɠ��͂���ƏI�����܂�)��");
		scanf("%s",filename);
	}
	if((strcmp(filename,"exit"))==0){
		printf("�v���O�������I�����܂��B\n");
		return 0;
	}
	fp=fopen(filename,"r");
	if(fp==NULL){
		sprintf(filename,"%s.e",filename);
		fclose(fp);
		fp=fopen(filename,"r");
	}
	
	//�t�@�C�����K�؂ɓǂݍ��܂�Ă��邩���m�F
	if(fp==NULL){
		perror("�t�@�C���̓ǂݍ��݂Ɏ��s���܂���");
		printf("\n�R���p�C�����I�����܂�\n");
		return 1;
	}
	if((filename[1]!=':')&&(filename[2]!='\\')){//���΃p�X�̏ꍇ�͐�΃p�X���擾
		strcpy(filename1,filename);
		filepath=getcwd(filedir,400);//��΃p�X�̎擾
		if(filepath==NULL){
			printf("�t�@�C�������������邩�f�B���N�g�����������ăt�@�C�����o�͂ł��܂���I\n�C�ӂ̃L�[�ŃR���p�C�����I�����܂�\n");
			getch();
			return 1;
		}
		sprintf(filename,"%s\\%s",filedir,filename1);
	}
	strcpy(filename1,filename);
	strcpy(filename2,filename);
	filenum=strlen(filename);//������̒������擾
	for(i=filenum;i>0;i--){//�t�@�C��������g���q������
		if(filename[i]=='.'){
			filename[i]=0;
			break;
		}
	}
	
	sprintf(cfilename,"%s.c",filename);
	sprintf(exefilename,"%s.exe",filename);
	strcpy(filename,filename2);//�t���p�X���擾�������̂�߂�
	
	if((cfp=fopen(cfilename,"r"))!=NULL){
		printf("�o�͗\\���c����t�@�C�������ɑ��݂��Ă��܂��B�㏑�����܂����H(y/n)\n");
		if((yesno())==0){
			fclose(cfp);
			cfp=fopen(cfilename,"w");
		}else{
			printf("�R���p�C�����I�����܂�\n");
			fclose(fp);
			fclose(cfp);
			return 1;
		}
	}
	
	printf("��΃p�X:%s\n",filename);
	
	//�e�L�X�g�̓ǂݍ��݂Əo��
	printf("��===== �\\�[�X�t�@�C���̓��e =====��\n");
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
	printf("\r\n��=========== �����܂� ===========��\n�R�[�h�͑S�̂�%d�s�ł��B\n�R���p�C�����J�n���܂��B\n",j);
	enternum=j;
	
	//��������R���p�C��
	i=0;
	fseek(fp,0L,SEEK_SET);//getc�̃��Z�b�g
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
	while(1){//��s���ǂݍ���
		i=0;
		while(((source[i]=fgetc(fp))!=EOF)&&(source[i]!='\n')){
			i++;
		}
		source[i]='\0';	
		j=0;
		while((source[0]==' ')||(source[0]=='\t')||(source[0]=='\v')){//�擪��tab�ƃX�y�[�X�̍폜
			len=strlen(source);
			strcpy(source,&source[1]);
			source[len]='\0';
		}
		if(source[0]=='\0'){//�����Ȃ��s�̏���
			printf("%3d�s��:�󔒍s�ł��B\n",enn);
			enn++;
			continue;
		}
		k=1;
		while(k!=i){//�r������R�����g�̂�p
			if((source[k-1]!='@')&&(source[k]=='/')&&(source[k+1]=='/')){
				source[k]='\0';
			}
			k++;
		}
		k=strlen(source);
		k--;
		while((source[k]==' ')||(source[k]=='\t')||(source[k]=='\v')){//�Ō�̃^�u�ƃX�y�[�X������
			source[k]='\0';
			k--;
		}
		if((source[0]=='}')&&(source[1]!='n')){//����ƃ��[�v�̏I���p
			printf("%3d�s��:����܂��̓��[�v�̏I�_�ł��B\n",enn);
			fprintf(cfp,"}\n");
			enn++;
			continue;
		}
		if(source[0]=='#'){//�n�b�V���^�O�Ŏn�܂邠��
			if(shapecheck1==0){
				cmerr=shape(source);
				fprintf(cfp,"%s",output);
			}else if(shapecheck1==1){//�r���n�b�V���^�O�����߂�����
				printf("%3d�s��:Error:#�Ŏn�܂镶�̓v���O�����̍ŏ��ɓ���Ă��������I\n",enn);
				cmerrall++;
			}
			cmerrall+=cmerr;
			if(enn==enternum)break;
			enn++;
			continue;
		}else if((source[0]=='/')&&(source[1]=='/')){//�R�����g�s�̖���
			printf("%3d�s��:�R�����g�s�ł��B\n",enn);
			if(enn==enternum)break;
			enn++;
			continue;
		}else if(shapecheck1==0){
			fprintf(cfp,"int main(int argc,char **argv){\n");
			shapecheck1=1;
		}
		cmerr=trans(source);//�����Ń��C���̃R���p�C�������܂��I
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
	
	//�R���p�C���I��
	fclose(cfp);
	if(cmerrall!=0){//�R���p�C���G���[�̌��𔻒�
		printf("�R���p�C������%d�̃G���[���������܂����B\n",cmerrall);
		fclose(fp);
		printf("�C�ӂ̃L�[�������ăv���O�������I�����܂��B\n");
		getch();
		return 1;
	}
	
	
	printf("�����C����t�@�C���ւ̕ϊ����������܂����B\n�R���p�C�����܂����H�i�O����gcc�R�}���h���g�p���܂��j(y/n)\n");
	if((yesno())==0){
		printf("�R���p�C�������s���܂��B\n");
		sprintf(command,"gcc %s -o %s",cfilename,exefilename);
		err=system(command);
		if(err==0){
			printf("����Ƀv���O�������������܂����B\n���s���܂����H(y/n)\n");
			if((yesno())==0){
				printf("=========================\n\n");
				err=system(exefilename);
				printf("\n\n=========================\n");
				printf("�v���O�����͖߂�l%d��",err);
				if(err==0)printf("�����");
				printf("�I�����܂����B\n");
			}
		}else{
			printf("�R���p�C���G���[���������܂����B\n�v���O�������I�����܂��B\n");
			return 1;
		}
	}
	
	printf("�v���O�������I�����܂��B\n");
	//�t�@�C���N���[�Y
	fclose(fp);
	
	
	return 0;
}