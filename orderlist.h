//orderlist.h
//�������̍ő�l�̐ݒ�
#define OUTPUTMAX 5000
#define WORDMAX 9999
#define ORDERMAX 500
#define HENSUMAX 999
#define OPTIONMAX 100
//�����܂�

//�o�[�W�����\��
char langname[80]=
/**********************************************************/
/**/			"E���� v0.0.1 by�Ƃ����̂�"				/**/
/**********************************************************/
;


int floatnum,enn=0;
int next=0;//�֐�����s�ŘA�������Ƃ���1�ɂ���
char output[OUTPUTMAX];//���C���v���O�����ɏo�͂��镶���������
int a=0,b=0,c=0,d=0,e=0,f=0,g=0,h=0,m,n,o,p,q;//���[�v�J�E���^
int forwin=0;
int err=0;
int ifkara=0;//if����~�����ɕK�v
int strlong;//������̒������ꎞ�I�ɕۑ�
int mode=0;//�֐��̎g�p���[�h��ۑ�
int hensukazu=0;//�Ǝ�������Œ�`�����ϐ��̐���ۑ�
int gotodo=0;//goto���g�p���ꂽ��1�ɂȂ�܂�
int reset=0,hikinum=0,checker=0;
int hensumode[HENSUMAX];//�z��ɂ͕ϐ��̔ԍ��A0=NULL,1=float,2=char
int hikikazu=0;//���ߖ����܂߂������̐������܂�
int errpoint;//�G���[�̏ꏊ���i�[���܂�
char option[OPTIONMAX][ORDERMAX],optionsave[OPTIONMAX][ORDERMAX];//�z��0���珇�ԂɈ�����ۑ����܂�
char optionyobi[OPTIONMAX];//�\���p�̃I�v�V�����ۑ��ϐ�
char name1[OPTIONMAX];
char hensuname[HENSUMAX][100];//�g�p�����ϐ�����ۑ�
char hiki[ORDERMAX],hikisave[ORDERMAX],hikihiki[ORDERMAX];//�������ꎞ�I�ɕۑ�
char outputword[ORDERMAX];//outputchange���߂ŃO���[�o���ŕK�v
char calc[5];//���Z�q���ꎞ�I�ɕۑ�
double floatint;//float�^�̒l���ꎞ�I�ɓ���Ă���
char cfilename[FULLPATHMAX];//C����o�̓t�@�C���̃p�X

void resetdata(void){//�ŏ��ɔz������Z�b�g����
	a=0;
	while(a!=HENSUMAX){
		hensumode[a]=0;//0=NULL,1=float,2=char
		a++;
	}
	a=0;
}

int optioncut(char wordin[ORDERMAX],char wordout[ORDERMAX],char kugiri){//optioncut(���X�̕�����,�ϊ���̕�����,��؂�ꏊ);
	int mojisu=strlen(wordin);
	int moji=0;
	while(moji!=mojisu){
		if((wordin[moji]==kugiri)&&(wordin[moji-1]!='@')){//@���O�ɂ���ꍇ�̓R���e�B�j���[
			strcpy(wordout,&wordin[moji+1]);
			wordin[moji]='\0';
			return 0;//��؂�ꏊ�����݂����0�ɂȂ�܂�
		}
		moji++;
	}
	return 1;
}

int ngword(char word[ORDERMAX]){//�֑����������邩���ׂ܂�
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

int strnum(char word[ORDERMAX]){//������̒��g���S�Đ����Ȃ�0��Ԃ��܂�
	int loop2;
	for(loop2=0;loop2<strlen(word)-1;loop2++){
		if(word[loop2]=='.')continue;
		if((isdigit(word[loop2]))==0){
			return 1;
		}
	}
	return 0;
}

int registercheck(char word[ORDERMAX]){//�ϐ���������ERROR=1,NULL=1,FLOAT=2,CHAR=3��Ԃ��܂�
	int loop,count001;
	sprintf(word,"%s_",word);//�� �� �� ��
	for(count001=0;count001<HENSUMAX;count001++){
		if((strcmp(word,hensuname[count001]))==0){//�ϐ�����S���ۑ����Ă���ϐ�����T���Ă���
			if(hensumode[count001]==1){//float=1
				return 2;
			}else if(hensumode[count001]==2){//char=2
				return 3;
			}
		}
	}
	return 1;
}

int outputchange(char word[ORDERMAX]){//������@��\�ɂ�镶���̕\�������܂�
	int mojimax=1,mojibasho=0,mojicount=0,mojicount2=0,hikinum=0;
	char mojisave[OPTIONMAX];
	hikikazu=0;
	while(mojimax!=mojibasho){//\���c����ɂ�����\\���o�͂���
		mojimax=strlen(word);
		if(word[mojibasho]=='\\'){
			strcpy(mojisave,&word[mojibasho+1]);
			word[mojibasho]='\\';
			word[mojibasho+1]='\\';
			word[mojibasho+2]='\0';
			sprintf(word,"%s%s",word,mojisave);
			mojibasho++;
		}
		if(word[mojibasho]=='%'){//%���c����ɂ�����%%���o�͂���
			strcpy(mojisave,&word[mojibasho+1]);
			word[mojibasho]='%';
			word[mojibasho+1]='%';
			word[mojibasho+2]='\0';
			sprintf(word,"%s%s",word,mojisave);
			mojibasho++;
		}
		if(word[mojibasho]=='\''){//'���c����ɂ�����\'���o�͂���
			strcpy(mojisave,&word[mojibasho+1]);
			word[mojibasho]='\\';
			word[mojibasho+1]='\'';
			word[mojibasho+2]='\0';
			sprintf(word,"%s%s",word,mojisave);
			mojibasho++;
		}
		if(word[mojibasho]=='\"'){//"���c����ɂ�����\"���o�͂���
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
	while(mojimax>=mojibasho){//��������G�X�P�[�v�V�[�P���X�I�Ȃ��Ƃ��o����
		mojicount=0;
		if(word[mojibasho]=='@'){//@���L�[�ɂ���
			if(word[mojibasho+1]=='n'){//@n�ŉ��s
				strcpy(&word[mojibasho+2],&word[mojibasho+2]);//strcpy(e+�g���ɕK�v�ȕ�����,e+�I���W�i�������Ŏg��������);
				word[mojibasho]='\\';
				word[mojibasho+1]='n';
			}else if(word[mojibasho+1]=='b'){//@b�ňꕶ������
				strcpy(&word[mojibasho+2],&word[mojibasho+2]);
				word[mojibasho]='\\';
				word[mojibasho+1]='b';
			}else if(word[mojibasho+1]=='r'){//@r�ōs���ɖ߂�
				strcpy(&word[mojibasho+2],&word[mojibasho+2]);
				word[mojibasho]='\\';
				word[mojibasho+1]='r';
			}else if(word[mojibasho+1]=='@'){//@@��@�̕\��
				strcpy(&word[mojibasho+1],&word[mojibasho+2]);
				word[mojibasho]='@';
			}else if(word[mojibasho+1]=='/'){//@/��/�̕\��
				strcpy(&word[mojibasho+1],&word[mojibasho+2]);
				word[mojibasho]='/';
			}else if(word[mojibasho+1]==','){//@,��,�̕\��
				strcpy(&word[mojibasho+1],&word[mojibasho+2]);
				word[mojibasho]=',';
			}else{
				printf("%3d�s��:Error:%d�����ڂ�@�̌�ɕs���ȕ����\\��������Ă��܂��I\n",enn,mojibasho+1);
				err=1;
				return 1;
			}
		}
			
			
		if(word[mojibasho]=='!'){//!���L�[�ɂ���
			if(word[mojibasho+1]!='!'){
				strcpy(hiki,&word[mojibasho+1]);//!�ϐ�!�ŕϐ���\��������
				while(hiki[mojicount]!='!'){
					mojicount++;
					if(mojicount==ORDERMAX)break;
				}
				hiki[mojicount]='\0';
				sprintf(hiki,"%s_",hiki);//�ϐ�����_�𑝂₵�Ă���̂ł��̕�
				hiki[mojicount+1]='\0';
				if(mojicount!=ORDERMAX){
					for(mojicount2=0;mojicount2<HENSUMAX;mojicount2++){
						if((strcmp(hiki,hensuname[mojicount2]))==0){//�ϐ��������邩�ǂ�������
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
						printf("%3d�s��:Error:�ϐ���%s�����݂��܂���I\n",enn,hiki);
						err=1;
						return 1;
					}else{
						mojimax=strlen(word);
						continue;
					}
				}else{
					printf("%3d�s��:Error:%d�����ڂɊԈႢ������܂��I\n",mojibasho);
					err=1;
					return 1;
				}
			}else{		//!!��!��\�����܂�
				strcpy(&word[mojibasho+1],&word[mojibasho+2]);
				word[mojibasho]='!';
				mojimax=strlen(word);
				mojibasho++;
				continue;
			}
			printf("%3d�s��:Error:%d�����ڂ�!�̌�ɕs���ȕ����\\��������Ă��܂��I\n",enn,mojibasho+1);
			err=1;
			return 1;
		}
		mojimax=strlen(word);
		mojibasho++;
	}
	strcpy(outputword,word);
	return 0;
}




//�������烁�C���̏���
int trans(char order[WORDMAX]){//��{�I�Ȗ��߂̏���
	FILE *cfp2;
	int loop0=0;
	transstart://�ꉞ���x����
	for(loop0=0;loop0<OPTIONMAX;loop0++){
		option[loop0][0]='\0';
	}
	loop0=0;
	for(reset=0;reset<ORDERMAX;reset++)option[0][reset]='\0';
	hikikazu=0;
	strcpy(option[0],order);
	while((optioncut(option[hikikazu],option[hikikazu+1],','))==0){//,������x��option�̔z���ς��đ�����Ă���
		hikikazu++;
	}
	strcpy(order,option[0]);
	
	
	
	//�������疽�߂̏���
	if((strcmp(order,"num"))==0){//num�֐�,�����^�̕ϐ�d
		if((optioncut(option[1],hiki,'='))==0){
			checker=1;
		}
		if(gotodo==1){
			printf("%3d�s��:Error:�ϐ���錾����O��go���߂�label���߂��g�p���Ȃ��ł��������I\n",enn);
			err=1;
			return 1;
		}
		if((ngword(option[1]))!=0){
			printf("%3d�s��:Error:�ϐ����Ɏg�p�ł��Ȃ��������܂܂�Ă��܂��I\n",enn);
			err=1;
			return 1;
		}
		floatint=atof(hiki);
		if(hensukazu==HENSUMAX){
			printf("%3d�s��:Error:�ϐ��̐����������܂��I\n",enn);
			err=1;
			return 1;
		}else{
			for(d=0;d<HENSUMAX;d++){
				if((strcmp(hensuname[d],option[1]))==0){
					printf("%3d�s��:Error:�ϐ������d�����Ă��܂��I\n",enn);
					err=1;
					return 1;
				}
			}
			sprintf(option[1],"%s_",option[1]);//�ϐ���_��t���邱�Ƃɂ����printf�ϐ��̍쐬
			strcpy(hensuname[hensukazu],option[1]);//�ϐ���o�^���܂�
			hensumode[hensukazu]=1;//num�^�Ȃ̂�1�Ɠo�^
			hensukazu++;
			sprintf(output,"float %s",option[1]);
			if(checker==1)
				sprintf(output,"%s=%g",output,floatint);
			}
			sprintf(output,"%s;\n",output);
		err=0;
	}else if((strcmp(order,"go"))==0){//go����,�D���ȏꏊ�ɃW�����v���܂�
		gotodo=1;
		sprintf(output,"goto %s;\n",option[1]);
		err=0;
	}else if((strcmp(order,"label"))==0){//label����,�W�����v���x���ł�
		gotodo=1;
		sprintf(output,"%s:\n",option[1]);
		err=0;
	}else if((strcmp(order,"str"))==0){//str�֐�,������̕ϐ�
		if(gotodo==1){
			printf("%3d�s��:Error:�ϐ���錾����O��go���߂�label���߂��g�p���Ȃ��ł��������I\n",enn);
			err=1;
			return 1;
		}
		if((optioncut(option[1],hiki,','))==0){
			hikinum=atoi(hiki);
		}
		if((ngword(option[1]))==1){
			printf("%3d�s��:Error:�ϐ����Ɏg�p�ł��Ȃ��������܂܂�Ă��܂��I\n",enn);
			err=1;
			return 1;
		}
		if(d==5){//�v�C��!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			printf("%3d�s��:Error:�ϐ����𐔎��݂̂ɂ͂ł��܂���I\n",enn);
			err=1;
			return 1;
		}else if(hensukazu==HENSUMAX){
			printf("%3d�s��:Error:�ϐ��̐����������܂��I\n",enn);
			err=1;
			return 1;
		}else{
			for(d=0;d<HENSUMAX;d++){
				if((strcmp(hensuname[d],option[1]))==0){
					printf("%3d�s��:Error:�ϐ������d�����Ă��܂��I\n",enn);
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
	}else if((strcmp(order,"put"))==0){//put�֐�,�W���o�͖���
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
	}else if((strcmp(order,"in"))==0){//in�֐�,�W�����͖���
		if(option[1][0]=='\0'){
			printf("%3d�s��:Error:����������܂���I\n",enn);
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
			printf("%3d�s��:Error:�ϐ���%s�����݂��܂���I\n",enn,option[1]);
			err=1;
			return 1;
		}
	}else if((strcmp(order,"exit"))==0){//exit�֐�,���ʂ�exit������
		e=atoi(option[1]);
		if((e<9999)&&(e>-9999)){
			sprintf(output,"exit (%d);\n",e);
		}else{
			printf("%3d�s��:Error:exit���߂̂��̒l�͖����ł��I\n",enn);
			err=1;
			return 1;
		}
		err=0;
	}else if((strcmp(order,"info"))==0){//info�֐�,��`����
		sprintf(output,"printf(\"%s\\n����ҘA����\\n Homepage\\thttps://jikantoki.jimdo.com\\n Twitter\\thttps://twitter.com/jikantoki\\n\");\n",langname);
		err=0;
	}else if((strcmp(order,"pause"))==0){//pause�֐�,����̓��͂�҂�
		sprintf(output,"getch();\n");
		err=0;
	}else if((strcmp(order,"if"))==0){//if�֐�,�������������
		if((ngword(option[1]))==2){//��������؂�ꏊ������ΐ����ĕԂ�
			if((option[1][errpoint]=='=')||(option[1][errpoint]=='<')||(option[1][errpoint]=='>')){//���̎O��
				if(option[1][errpoint+1]!='='){
					calc[0]=option[1][errpoint];
					calc[1]='\0';
					strcpy(hiki,&option[1][errpoint+1]);
				}else{
					goto if2saves;
				}
			}else{//<=�Ƃ�!=�Ƃ�
				if2saves:
				calc[0]=option[1][errpoint];
				calc[1]=option[1][errpoint+1];
				calc[2]='\0';
				strcpy(hiki,&option[1][errpoint+2]);
			}
			option[1][errpoint]='\0';
			if((hiki[strlen(hiki)-1])=='{'){//�Ōオ{�ŏI����Ă���ꍇ��mode��0�ɂ���
				hiki[strlen(hiki)-1]='\0';
				mode=0;
			}else mode=1;
			ifkara=0;
			optionyobi[0]='\0';
			hikisave[0]='\0';
			if((ngword(option[1]))==3){
				optioncut(option[1],optionyobi,'~');
				if((strnum(optionyobi))!=0){//�ϐ�������������Ȃ�������ϐ���T������
					if((registercheck(optionyobi))==1){
						printf("%3d�s��:Error:�ϐ���%s�����݂��܂���I\n",enn,optionyobi);
						err=1;
						return 1;
					}
				}
				ifkara=1;
			}
			if((ngword(hiki))==3){
				optioncut(hiki,hikisave,'~');
				if((strnum(hikisave))!=0){//�ϐ�������������Ȃ�������ϐ���T������
					if((registercheck(hikisave))==1){
						printf("%3d�s��:Error:�ϐ���%s�����݂��܂���I\n",enn,hikisave);
						err=1;
						return 1;
					}
				}
				ifkara=2;
			}
			if((strnum(hiki))!=0){//�ϐ�������������Ȃ�������ϐ���T������
				if((registercheck(hiki))==1){
					printf("%3d�s��:Error:�ϐ���%s�����݂��܂���I\n",enn,hiki);
					err=1;
					return 1;
				}
			}
			if((strnum(option[1]))!=0){//�ϐ�������������Ȃ�������ϐ���T������
				if((registercheck(option[1]))==1){
					printf("%3d�s��:Error:�ϐ���%s�����݂��܂���I\n",enn,option[1]);
					err=1;
					return 1;
				}
			}
			if(ifkara==1){//�������牉�Z�q�̕ϊ�
				if((strcmp(calc,"="))==0){
					sprintf(output,"if((%s<=%s)&&(%s>=%s))",option[1],hiki,optionyobi,hiki);
				}else if((strcmp(calc,"!="))==0){
					sprintf(output,"if!((%s<=%s)&&(%s>=%s))",option[1],hiki,optionyobi,hiki);
				}else{//���Z�q���䂾�����ꍇ
					printf("%3d�s��:Error:���Z�q�ɊԈႢ������܂��I\n",enn);
					err=1;
					return 1;
				}
			}else if(ifkara==2){//
				if((strcmp(calc,"="))==0){
					sprintf(output,"if((%s<=%s)&&(%s>=%s))",hiki,option[1],hikisave,option[1]);
				}else if((strcmp(calc,"!="))==0){
					sprintf(output,"if!((%s<=%s)&&(%s>=%s))",hiki,option[1],hikisave,option[1]);
				}else{//���Z�q���䂾�����ꍇ
					printf("%3d�s��:Error:���Z�q�ɊԈႢ������܂��I\n",enn);
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
				}else{//���Z�q���䂾�����ꍇ
					printf("%3d�s��:Error:���Z�q�ɊԈႢ������܂��I\n",enn);
					err=1;
					return 1;
				}
			}
			if(mode==0){
				sprintf(output,"%s{\n",output);
			}else{//if�̌�ɂ����߂��t���Ă���ꍇ
				order[0]='\0';
				for(d=2;d<12;d++){
					sprintf(order,"%s%s,",order,option[d]);
				}
				order[strlen(order)]='\0';//�Ōオ�J���}�ŏI����Ă���̂ŏC������
				next=1;
				cfp2=fopen(cfilename,"a");
				fprintf(cfp2,"%s",output);
				fclose(cfp2);
				goto transstart;
			}
		}else{
			printf("%3d�s��:Error:�����ɊԈႢ������܂��I\n",enn);
			err=1;
			return 1;
		}
	}else if((strcmp(order,"wait"))==0){//wait�֐��A�҂��܂�
		if((strnum(option[1]))==0){
			waitstart:
			if(forwin==1){//windows.h����`����Ă��邩�m�F
				sprintf(output,"Sleep(%s*1000);\n",option[1]);
			}else{
				printf("%3d�s��:Error:���̖��߂��g���ɂ̓v���O�����̐擪��#forwin���`���Ă��������I\n",enn);
				err=1;
				return 1;
			}
		}else{
			if((registercheck(option[1]))==2){
				goto waitstart;
			}else{
				printf("%3d�s��:Error:�ϐ���%s��num�ϐ��łȂ����͑��݂��܂���I\n",enn,option[1]);
				err=1;
				return 1;
			}
		}
	}else{//���̑�
		if(order[0]!='\0'){
			printf("%3d�s��:Error:%s���߂͒�`����Ă��Ȃ����m�̖��߂ł��I\n",enn,order);
		}else{
			printf("%3d�s��:Error:���@�ɊԈႢ������܂��I\n",enn);
		}
		err=1;
		return 1;
	}
	if(err==0)printf("%3d�s��:Log:%s���߂����s���܂�\n",enn,order);
	return 0;
}

int shape(char sword[OUTPUTMAX]){//#�Ŏn�܂閽�߂̐���
	int mojimax=strlen(sword);
	int mojibasho;
	int hikiall=0;//�����̌���ۑ����܂�
	if((optioncut(sword,hiki,','))==0){
		hikiall++;
		if((optioncut(hiki,hikihiki,','))==0){
			hikiall++;
			
		}
	}
	if((strcmp(sword,"#forwin"))==0){//#include<windows.h>�̒�`
		if(forwin==0){
			forwin=1;
			sprintf(output,"#include<windows.h>\n");
			err=0;
		}else{
			err=1;
			printf("%3d�s��:Error:������`���߂���d�ɏd�Ȃ��Ă��܂��I\n",enn);
			return 1;
		}
	}else if((strcmp(sword,"#define"))==0){//#define�iC����ʂ�j
		if((optioncut(sword,hiki,' '))==0){
			printf("%3d�s��:Error:#define���g�p���鎞�̓X�y�[�X�͎g�p���Ȃ��ł��������I");
			err=1;
			return 1;
		}
		if(hikiall!=2){
			err=1;
			printf("%3d�s��:Error:���@�ɊԈႢ������܂��I\n",enn);
			return 1;
		}
		sprintf(output,"#define %s %s\n",hiki,hikihiki);
		err=0;
	}
	if(err==0){
		printf("%3d�s��:Log:%s�̃Z�b�g���������܂���\n",enn,&sword[1]);
	}
	return 0;
}
