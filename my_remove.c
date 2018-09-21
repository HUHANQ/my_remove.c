#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <strings.h>
#include <string.h>
#include <sys/types.h>


int my_remove(const char* file)
{
	DIR* dirp = opendir(file);
	struct dirent* pde = NULL;
	char old[301];
	int cnt = 0;
	struct stat st;

	if(dirp == NULL)
	{
		printf("文件不存在打开失败！\n");
		return 1;
	}
	
	getcwd(old,sizeof(old));
	chdir(file);

	while(pde = readdir(dirp))
	{	
		if(0 == stat(pde->d_name,&st))
		{
			if(S_ISDIR(st.st_mode))
			{
				//说明是一个文件夹
				if(strcmp(pde->d_name,".") != 0 && strcmp(pde->d_name,"..") != 0)
				{
					my_remove(pde->d_name);
				}	
			}
			else
			{
				//说明是一个普通文件
				unlink(pde->d_name);
				cnt++;
			}

		}
		
	}
	chdir(old);
	rmdir(file);		
	closedir(dirp);
	return cnt;	
}

int main(int argc,char** argv)
{
	printf("%d个文件已经被删除！\n",my_remove(argv[1]));


	return 0;
}
