#include "header.h"
#include <pthread.h>


void *  judgeClient(int * arg);

int main() 
{
char path[1024];   // 初始化路径用
int socket_fd[10];
int s_fd;
int b; //线程计数
struct sockaddr_in addr1;
char  rebuf[1024];
pthread_t id;
int c_fd;
char *addr;
struct sockaddr_in c_addr;
int c_len;
c_len=sizeof(c_addr);

pid_t pid=fork();    //作为守护进程
	if(pid<0)
		return 1;
	if(pid>0)
		{
		exit(0);       //中止父进程
		
		}


umask(0);
s_fd=socket(AF_INET,SOCK_STREAM,0);                //服务器端的套接字
addr1.sin_family=AF_INET;
addr1.sin_addr.s_addr=inet_addr("127.0.0.1");
addr1.sin_port=htons(3339);
bind(s_fd,(struct sockaddr *)&addr1,sizeof(addr1));
listen(s_fd,10);
bzero(rebuf,1024);
bzero(path,1024);//获取当前路径
getcwd(path,1024);
int i;
//初始化sock_fd
for(i=0;i<10;i++)
{
socket_fd[i]=-1;
}
		i=0;
	while(1)
	{
		c_fd=accept(s_fd,(struct sockaddr*)&c_addr,&c_len);
				recv(c_fd,rebuf,1024,0);
				printf("%s",rebuf);
				while(socket_fd[i]!=-1)
					i=(i+1)%10;
				socket_fd[i]=c_fd;
				if(!strcmp(rebuf,"3140704117/123"))
					{
					send(c_fd,"login successful\n",16,0);
					bzero(rebuf,1024);
					chdir(path);
					pthread_create(&id,NULL,judgeClient,(int *)c_fd);
					
					}
					else 
					{
					send(c_fd,"error",6,0);
					close(c_fd);
					continue;
					}
				
					
		
		
	}
return 0;
} 
