#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX_BUFF_SIZE 2000

char *HEX_VAL[]={"30","31","32","33","34","35","36","37","38","39",
				"41","42","43","44","45","46","47","48","49","4A",
				"4B","4C","4D","4E","4F","50","51","52","53","54",
				"55","56","57","58","59","5A","61","62","63","64",
				"65","66","67","68","69","6A","6B","6C","6D","6E",
				"6F","70","71","72","73","74","75","76","77","78",
				"79","7A","20","3D"};

char CHAR_VAL[]={'0','1','2','3','4','5','6','7','8','9',
			     'A','B','C','D','E','F','G','H','I','J',
			     'K','L','M','N','O','P','Q','R','S','T',
				 'U','V','W','X','Y','Z','a','b','c','d',
				 'e','f','g','h','i','j','k','l','m','n',
				 'o','p','q','r','s','t','u','v','w','x',
				 'y','z',' ','='};

int ISO97_SIZE[]={8,19,6,12,12,12,10,8,8,8,
				  6,12,4,4,2,4,4,4,3,3,
				  3,12,3,3,2,2,1,8,8,8,
				  8,11,11,28,37,104,12,6,2,3,
				  8,15,42,25,76,999,999,999,3,3,
				  3,16,41,120,999,999,999,999,999,7,
				  999,999,999,4,8,1,2,3,3,3,
				  4,999,6,10,10,10,10,10,10,10,
				  10,12,12,12,12,15,15,15,15,42,
				  1,2,5,7,42,8,16,25,11,11,
				  17,28,28,100,999,999,999,999,999,999,
				  999,999,11,999,999,999,999,999,999,999,
				  999,999,999,255,50,999,999,4};
				  
void CONVERT_HEX_TO_CHAR(char *BUFF,char *OUTPUT)
{
	char conv[3];int FLAG=1,k=0;OUTPUT[0]='\0';
	for(size_t i=0;i<strlen(BUFF);i+=3)
	{
		conv[0]=BUFF[i];conv[1]=BUFF[i+1];conv[2]='\0';
		FLAG=1;
		for(int j=0;j<(sizeof(HEX_VAL)/sizeof(HEX_VAL[0]));j++)
		{
			if(memcmp(strupr(conv),HEX_VAL[j],sizeof(conv))==0)
			{
				OUTPUT[k++]=CHAR_VAL[j];FLAG=0;
			}
			
		}
		if(FLAG==1)
			OUTPUT[k++]='.';
				
	}
}

char * HEX_TO_BINARY(char *str)
{
	char *out;
	strupr(str);
	//printf("\nHEX :%s\n",str);
	out=(char *)malloc(sizeof(char)*(strlen(str)-7)*4+2);out[0]='\0';
    for(int i=0;i<strlen(str);i++)
	{
		//printf("%c %d ",str[i],i);
		switch(str[i])
		{
			case '0':
				strcat(out,"0000");break;
			case '1':
				strcat(out,"0001");break;
			case '2':
				strcat(out,"0010");break;
			case '3':
				strcat(out,"0011");break;
			case '4':
				strcat(out,"0100");break;
			case '5':
				strcat(out,"0101");break;
			case '6':
				strcat(out,"0110");break;
			case '7':
				strcat(out,"0111");break;
			case '8':
				strcat(out,"1000");break;
			case '9':
				strcat(out,"1001");break;
			case 'A':
				strcat(out,"1010");break;
			case 'B':
				strcat(out,"1011");break;
			case 'C':
				strcat(out,"1100");break;
			case 'D':
				strcat(out,"1101");break;
			case 'E':
				strcat(out,"1110");break;
			case 'F':		  
			  	strcat(out,"1111");break;
			default :
					break;
		}		
	}
	return out;
}


int main()
{
	char str[MAX_BUFF_SIZE],*out, OUTPUT[1000];//out[500]="";
	char BUFF[MAX_BUFF_SIZE],TEMP[5];int i=0,val=0,MTI=0,CHAR_COUNTER=0,ISO_FIELD[128],cnt=1;
 	printf("Enter HEX dump : ");
	scanf("%[A-Za-z0-9 ]s",BUFF);
	printf("\n");
	ISO_FIELD[0]=0;
	for(;i<12;i++)
	{	str[val++]=BUFF[i];MTI=1;}
		
	if(MTI==1)
	{	CHAR_COUNTER=i;
		CONVERT_HEX_TO_CHAR(str, OUTPUT);
		printf("\nMTI :%s\n",OUTPUT);
	}
	
	if(i<35)
	{
		val=0;
		for(;i<((ISO97_SIZE[ISO_FIELD[0]]*2)+(ISO97_SIZE[ISO_FIELD[0]]-1)+CHAR_COUNTER+1);i++)
			str[val++]=BUFF[i];
		CHAR_COUNTER=i;
		out=HEX_TO_BINARY(str);
		for(int j=1;j<strlen(out);j++)
			if(out[j]=='1')
				ISO_FIELD[cnt++]=(j+1);
				
		if(out[0]=='1')
		{
			val=0;
			for(;i<((ISO97_SIZE[ISO_FIELD[0]]*2)+(ISO97_SIZE[ISO_FIELD[0]]-1)+CHAR_COUNTER+1);i++)
				str[val++]=BUFF[i];
			CHAR_COUNTER=i;
			out=HEX_TO_BINARY(str);
			for(int j=0;j<strlen(out);j++)
				if(out[j]=='1')
					ISO_FIELD[cnt++]=(j+65);			
		}
	}
	//printf("\n ISO FIELDS :");
	val=0;
	for(;BUFF[i]!='\0';i++)
	    str[val++]=BUFF[i];
		
	CONVERT_HEX_TO_CHAR(str, OUTPUT);
	printf("\nBODY :%s\n",OUTPUT);
	i=0;
	for(int j=1;j<cnt && OUTPUT[i]!='\0';j++)
	{
		if(ISO_FIELD[j]==2 || ISO_FIELD[j]==32 || ISO_FIELD[j]==33 || ISO_FIELD[j]==34 || ISO_FIELD[j]==35 || ISO_FIELD[j]==44 || ISO_FIELD[j]==45 || 
		   ISO_FIELD[j]==99 || ISO_FIELD[j]==100 || ISO_FIELD[j]==102 || ISO_FIELD[j]==103 || ISO_FIELD[j]==113 || ISO_FIELD[j]==125)
		{
			TEMP[0]=OUTPUT[i++];TEMP[1]=OUTPUT[i++];TEMP[2]='\0';
			CHAR_COUNTER=atoi(TEMP);
			printf("\n ISO : %d : LENGTH : [%d] ---> ",ISO_FIELD[j],CHAR_COUNTER);
			for(int k=0;k<CHAR_COUNTER && CHAR_COUNTER<=ISO97_SIZE[ISO_FIELD[j]-1] && OUTPUT[i]!='\0';k++)
				if(ISO_FIELD[j]==2 && i<15 && i>7)
				{	printf("%c",'X');i++;}
				else
					printf("%c",OUTPUT[i++]);
		}
		else if(ISO_FIELD[j]==36 || ISO_FIELD[j]==46 || ISO_FIELD[j]==47 || ISO_FIELD[j]==48 || ISO_FIELD[j]==54 || ISO_FIELD[j]==55 || ISO_FIELD[j]==56
		        || ISO_FIELD[j]==57 || ISO_FIELD[j]==58 || ISO_FIELD[j]==59 || ISO_FIELD[j]==61 || ISO_FIELD[j]==62 || ISO_FIELD[j]==63 || ISO_FIELD[j]==72
				|| ISO_FIELD[j]==104 || ISO_FIELD[j]==105 || ISO_FIELD[j]==106 || ISO_FIELD[j]==107 || ISO_FIELD[j]==108 || ISO_FIELD[j]==109 ||
				ISO_FIELD[j]==110 || ISO_FIELD[j]==111 || ISO_FIELD[j]==112 || ISO_FIELD[j]==114 || ISO_FIELD[j]==115 || ISO_FIELD[j]==116 || ISO_FIELD[j]==117
				|| ISO_FIELD[j]==118 || ISO_FIELD[j]==119 || ISO_FIELD[j]==120 || ISO_FIELD[j]==121 || ISO_FIELD[j]==122 || ISO_FIELD[j]==123 || ISO_FIELD[j]==124
				|| ISO_FIELD[j]==126 || ISO_FIELD[j]==127)
		{
			TEMP[0]=OUTPUT[i++];TEMP[1]=OUTPUT[i++];TEMP[2]=OUTPUT[i++];TEMP[3]='\0';
			CHAR_COUNTER=atoi(TEMP);
			printf("\n ISO : %d : LENGTH : [%d] ---> ",ISO_FIELD[j],CHAR_COUNTER);
			for(int k=0;k<CHAR_COUNTER && CHAR_COUNTER<=ISO97_SIZE[ISO_FIELD[j]-1] && OUTPUT[i]!='\0';k++)
				printf("%c",OUTPUT[i++]);
		}
		else
		{
			printf("\n ISO : %d : LENGTH : [%d] ---> ",ISO_FIELD[j],ISO97_SIZE[ISO_FIELD[j]-1]);
			for(int k=0;k<ISO97_SIZE[ISO_FIELD[j]-1] && OUTPUT[i]!='\0';k++)
				printf("%c",OUTPUT[i++]);
		}
		if (ISO_FIELD[j]==17)//Added to avoid same entry in Field 18
		{
		  for(int k=0;k<ISO97_SIZE[ISO_FIELD[j+1]-1] && OUTPUT[i]!='\0';k++)
				i++;
		}
		//printf(" %d",ISO_FIELD[j]);
	}
	
		
	/*for(size_t i=0;i<strlen(BUFF);i+=3)
	{
		conv[0]=BUFF[i];conv[1]=BUFF[i+1];conv[2]='\0';
		FLAG=1;
		for(int j=0;j<(sizeof(HEX_VAL)/sizeof(HEX_VAL[0]));j++)
		{
			if(memcmp(conv,HEX_VAL[j],sizeof(conv))==0)
			{
				printf("%c",CHAR_VAL[j]);FLAG=0;break;
			}
			
		}
		if(FLAG==1)
			printf("%c",'.');
				
	}*/

	/*printf("\nFinal Bitmap Binary :%s\n",out);
        for(int i=0;i<strlen(out);i++)
	{
		if(out[i]=='1')
			printf(" %d",i+1);
	}
	printf("\n");*/	
	return 0;
}
