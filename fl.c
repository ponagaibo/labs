#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include <windows.h>
#define SEED (unsigned int)(time(NULL)*(rand()%10000))

const char names[20][11] = {"Targaryen", "Snow", "Stark", "Greyjoy", "Baratheon", "Lannister", "Bolton", "Tyrell",
"Baelish", "Mormont", "Naharis", "Clegane", "Martell", "Trant", "Selmy", "Payne", "H'ghar", "Seaworth", "Frey", "Tarly"};
const char initials[20][4] = {"D.E", "J.N", "A.R", "T.E", "R.O", "T.I", "R.A", "L.O", "P.E", "J.O", "D.A", "S.A", "O.B",
"M.E", "B.A", "I.L", "J.A", "D.V", "W.A", "S.M"};

typedef struct Person{
	char name[11];
	char initial[4];
	int total_w;
}Person;

Person random_person(char* name, char* init, int tw)
{
		Person p;
		int i;
		for(i=0;i<11;i++)
        {
			p.name[i]=name[i];
		}
		for(i=0;i<4;i++)
		{
			p.initial[i]=init[i];
		}
		p.total_w=tw;
		return p;
}

void create_b(char* filename)
{
    FILE* f;
	f=fopen(filename,"wb");
	if(f)
    {
		printf("������� ���������� ��������� ����: \n");
		int a, i=0;
		scanf("%d", &a);
		while (i<a)
		{
		    srand ( SEED );
            int rand_name = rand()%20;
            int rand_init = rand()%20;
            int rand_tw = rand()%26+3;
            Person q = random_person(names[rand_name], initials[rand_init], rand_tw);
            fwrite(&q, sizeof(q), 1, f);
            ++i;
        }
		fclose(f);
		printf("������� ���� �� %d ���������. ������� �������:\n",a);
	}
	else{
		printf("���������� ����� ��� ������� ����\n");
	}
}

void add_random_element(char* filename)
{
	FILE* f;
	f=fopen(filename,"ab");
    if (f)
    {
        srand( SEED );
        int rand_name = rand()%20;
        int rand_init = rand()%20;
        int rand_tw = rand()%26+3;
        Person q = random_person(names[rand_name], initials[rand_init], rand_tw);
        fwrite(&q, sizeof(q), 1, f);
        fclose(f);
        printf("�������� ��������� �������. ������� �������:\n");
    }
    else{
        printf("���������� ����� ��� ������� ����\n");
    }
}

void add_element(char* filename)
{
	FILE* f;
	f=fopen(filename,"ab");
    if (f)
    {
        Person s;
        printf("������� ���, �������� � ����� ��� �����\n");
        scanf("%s %s %d", &s.name, &s.initial, &s.total_w);
        fwrite(&s, sizeof(Person), 1, f);
        printf("�������� ������� %s %s %d ������� �������:\n",s.name, s.initial, s.total_w);
        fclose(f);
    }
    else{
        printf("���������� ����� ��� ������� ����\n");
    }
}

void print_b(char* filename)
{
	FILE* f;
	f=fopen(filename,"rb");
	if(f)
    {
		Person q;
		printf("      ���        ��������    ����� ��� �����\n");
		printf("_______________________________________________\n");
		while(fread(&q,sizeof(Person),1,f))
		{
			printf("%11s   |%9s   |%10d\n",q.name,q.initial,q.total_w);
		}
		fclose(f);
		printf("_______________________________________________\n");
		printf("������� �������:\n");
	}
	else{
		printf("���������� ����� ��� ������� ����\n");
	}
}

void remove_element(char* filename)
{
    FILE* f;
    FILE* file_new;
	f=fopen(filename,"rb");
	file_new=fopen("temp_file","wb");
    if (f&&file_new)
    {
        int n,i=1;
        printf("������� ����� ���������� ��������:\n");
        scanf("%d",&n);
        Person d;
        while(fread(&d, sizeof(Person),1,f))
        {
            if(i!=n){
                fwrite(&d,sizeof(Person),1,file_new);
                ++i;
            }
            else{
                ++i;
            }
        }
        fclose(f);
        fclose(file_new);
        f=fopen(filename,"wb");
        file_new=fopen("temp_file","rb");
        if (f&&file_new)
        {
            while(fread(&d,sizeof(Person),1,file_new))
            {
                fwrite(&d,sizeof(Person),1,f);
            }
        }
        else{
            printf("���������� ����� ��� ������� ����\n");
        }
        fclose(f);
        fclose(file_new);
        remove("temp_file");
        printf("������ %d �������. ������� �������:\n", n);
    }
    else{
        printf("���������� ����� ��� ������� ����\n");
    }
}

void delete_b(char* filename)
{
	FILE* f;
	f=fopen(filename,"wb");
	if(f)
    {
        fclose(f);
        remove(filename);
        printf("���� �������. ������� �������:\n");
    }
	else
		printf("I can not find or open the file.\n");
}
void quit()
{
	exit(0);
}

void task32(char* filename)
{
    FILE* f;
	f=fopen(filename,"rb");
	int max=0;
	Person t;
	if(f)
    {
        while(fread(&t,sizeof(Person),1,f))
        {
            if(t.total_w>max)
            {
                max=t.total_w;
            }
        }
        rewind(f);
        printf("������� ����� p:\n");
        int p;
        scanf("%d", &p);
        while(fread(&t,sizeof(Person),1,f))
        {
            if(t.total_w>(max-p))
            {
                printf("��� ������ %s %s ����� %d. ������������: %d\n",t.name, t.initial, t.total_w, max);
            }
        }
	}
	else{
		printf("���������� ����� ��� ������� ����\n");
	}
}

void print_menu(){
	printf("   ................................................\n");
	printf("   :   		     ����  	                  :\n");
	printf("   ................................................\n");
	printf("   :   1.        ������� ����                     :\n");
	printf("   :   2.        ���������� ����                  :\n");
	printf("   :   3.        �������� �������                 :\n");
    printf("   :   4.        �������� ��������� �������       :\n");
	printf("   :   5.        ������� ������� �� ������ 	  :\n");
	printf("   :   6.        ������� 32   	                  :\n");
	printf("   :   7.        �������� ����                    :\n");
	printf("   :   8.        �����                            :\n");
	printf("   ................................................\n");
}

int main()
{
    setlocale(LC_ALL, "Rus");
    print_menu();
    printf("������ ������ � �����? �� - 1, ��� - 0\n");
    int c,k,state=1;
    scanf("%d",&k);
    printf("������� �������:\n");
    while (state!=0)
    {
        c = getchar();
        if(c=='1')
        {
            create_b("newf");
        }else if(c=='2')
        {
            print_b("newf");
        }else if(c=='3')
        {
            add_element("newf");
        }else if(c=='4')
        {
            add_random_element("newf");
        }else if(c=='5')
        {
            remove_element("newf");
        }else if(c=='6')
        {
            task32("newf");
        }else if(c=='7')
        {
            delete_b("newf");
        }else if(c=='8')
        {
            state=0;
            quit();
        }else if ((c==' ')||(c=='\n'))
        {
            Sleep(0);
        } else
        {
            printf("������������ ����� �������\n");
        }
    }
}
