#include <stdio.h>
#include <ctype.h>

int main()
{
    FILE *fp;
    char ch;
    fp=fopen("input.txt","r");
    if (fp==NULL)
    {
        printf("no file found\n");
        return 0;
    }
    while (ch=fgetc(fp)!=EOF)
        {
            if(ch==' '|| ch=='\t'||ch=='\n')
            {
                continue;
            }
            if (isalpha(ch))
                { 
                    printf("identifier :%c",ch);
                    while(isalnum(ch=fgetc(fp)))
                        {
                            printf("%c",ch);
                        }
                    printf("\n");
                    if(ch!=EOF)
                    {
                        fseek(fp,-1,SEEK_CUR);
                    }
                
                }
            else if(isdigit(ch))
            {
                printf("number :%d",ch);
                while(isdigit(ch=fgetc(fp)))
                    {
                        printf("%c",ch);
                    }
                printf("\n");
                if (ch!=EOF)
                {
                    fseek(fp,-1,SEEK_CUR);
                }
            }
            else
            {
                printf("operators/special symbols : %c",ch);
            }
            
        }
    fclose(fp);
    return 0;
}