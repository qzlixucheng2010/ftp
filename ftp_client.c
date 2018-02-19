#include "header.h"





int clientSocket(char * ipaddr)   //客户端套接子封装
{
	int sockfd;
	int newsockfd;
	struct sockaddr_in addr;
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	addr.sin_family=AF_INET;
	addr.sin_addr.s_addr=inet_addr(ipaddr);
	addr.sin_port=htons(3339);
	newsockfd=connect(sockfd,(struct sockaddr*)&addr,sizeof(addr));
	if (newsockfd==-1)
	{
		perror("link fail");
		exit(1);
	}
	return sockfd;

}


void clientOptions()//客户端界面
{
printf("\n\n\n1.ls \n2.cd\n");
printf("3.cd .. \n4.get   \n5.update    \n6.close   \n\n");
printf("please input 1-6\n");
printf("which one do you chose:");
}

int main(int argc,char * argv[])
{
char buffer[1024];//文件传输是接受的缓存区
bzero(buffer,1024);
int length = 0;//文件传输的长度
int ok=0;
int sockfd;
char rebuf[1024];
char sendbuf[1024];
char scanfbuf[1024];
char choice[1024];
bzero(rebuf,1024);
bzero(sendbuf,1024);
bzero(scanfbuf,1024);
FILE * fp ;// 文件传输用
	if(argc<4)
	{
		printf("Usage:client ipaddr account  password/n");
		exit(1);
	}
sockfd=clientSocket(argv[1]);
//登录
strcpy(sendbuf,argv[2]);
strcat(sendbuf,"/");
strcat(sendbuf,argv[3]);
send(sockfd,sendbuf,strlen(sendbuf),0);
recv(sockfd,rebuf,1024,0);

printf("%s\n",rebuf);
//strcmp(rebuf,sendMessage(sockfd,sendbuf));
if(!strcmp(rebuf,"error"))
{
printf("error");
getchar();
exit(1);
}







	while(1)
	{
	
		bzero(scanfbuf,1024);
		bzero(choice,1024);
		bzero(sendbuf,1024);
		bzero(rebuf,1024);
		clientOptions();
		scanf("%s",choice);
		if(!strcmp(choice,"1"))
		{
			strcpy(sendbuf,"1");
			send(sockfd,sendbuf,strlen(sendbuf),0);
			recv(sockfd,rebuf,1024,0);
			printf("%s\n",rebuf);
		}
		else if(!strcmp(choice,"2"))
		{
			strcpy(sendbuf,"2");
			send(sockfd,sendbuf,strlen(sendbuf),0);
			recv(sockfd,rebuf,1024,0);
			printf("%s\n",rebuf);
			bzero(choice,1024);
			scanf("%s",choice);
			send(sockfd,choice,strlen(choice),0);
			recv(sockfd,rebuf,1024,0);
			printf("\n\n%s\n\n",rebuf);
			
			
		}
		else if(!strcmp(choice,"3"))
		{
			strcpy(sendbuf,"3");
			send(sockfd,sendbuf,strlen(sendbuf),0);
			recv(sockfd,rebuf,1024,0);
			printf("%s\n",rebuf);
		}
		else if(!strcmp(choice,"4"))
		{	
			strcpy(sendbuf,"4");
			send(sockfd,sendbuf,strlen(sendbuf),0);
			recv(sockfd,rebuf,1024,0);
			printf("%s\n",rebuf);
			bzero(choice,1024);
			scanf("%s",choice);
			send(sockfd,choice,strlen(choice),0);
			strcat(choice,"download");

			//打开文件
			fp = fopen(choice,"w");
   			 if(NULL == fp )
  				  {
       				 printf("File:\t%s Can Not Open To Write\n", scanfbuf);
					 close(sockfd);
      				  exit(1);
   				  }
  
  				  //从服务器接收数据到buffer中
		
    			bzero(buffer,1024);
  			  while( length = recv(sockfd,buffer,1024,0))
   				 {
			
      				  if(length < 0)
       						 {
       					     printf("Recieve Data From Server %s Failed!\n", argv[1]);
            					break;
     						}
        				 int write_length = fwrite(buffer,sizeof(char),length,fp);
   				     	 if (write_length<length)
        					{
            					printf("File:\t%s Write Failed\n", scanfbuf);
            					break;
        					}
      				  bzero(buffer,1024);
					if(length<1024)
						{
							break;
						}  
    				}
			fclose(fp);
   			 printf("Recieve File:\t %s From Server[%s] Finished\n",scanfbuf, argv[1]);
 
		}
		else if(!strcmp(choice,"5"))
		{
			strcpy(sendbuf,"5");
			send(sockfd,sendbuf,strlen(sendbuf),0);
			recv(sockfd,rebuf,1024,0);
			printf("%s\n",rebuf);      //please input name
			bzero(choice,1024);
			scanf("%s",choice);
			 if(NULL ==(fp=fopen(choice,"r")))
      		  		{
         		  		printf("\n\nnot found\n\n");
	     		  		continue;
       		 		}
			else
				{
				send(sockfd,choice,strlen(choice),0);
            		bzero(buffer, 1024);
            		int file_block_length = 0;
          		      while((file_block_length = fread(buffer,sizeof(char),1024,fp))>0)
         		   		{
						
             		    	     if(send(sockfd,buffer,file_block_length,0)<0)
                					{
                   			 		break;
               					 	}
                				bzero(buffer, 1024);
           				 }
				printf("\n\n\nupdate successful!!!!\n\n\n");
      				}
			fclose(fp);


		}
		else if(!strcmp(choice,"6"))
		{	
			
			strcpy(sendbuf,"6");
			send(sockfd,sendbuf,strlen(sendbuf),0);
			recv(sockfd,rebuf,1024,0);
			close(sockfd);
			break;
		}
		else 
			{
			printf("please input 1-6!!!!!\n");
			}
	}
	close(sockfd);
	return 0;
}
