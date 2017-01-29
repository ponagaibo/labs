#pragma once
#include <stdlib.h>
#include <time.h>
const char names[20][10]={"Jacob","Michael","Joshua","Matthew","Ethan","Andrew","Daniel","William","Joseph","John","Emily","Emma","Madison","Olivia",
"Hannah","Abigail","Isabella","Ashley","Samantha","Elizabeth"};
char inits[17][5]={"J.F" , "M.M","E.D","W.J","A.Q","E.A","V.P","W.A","L.A","D.C","M.A","R.V","E.L","N.E","W.Y","O.R","K.O"};

typedef struct Person{
	char name[10];
	char initial[5];
	char gen[2];
	int group;
	int marks[4];
}Person;
int cmp(char* a,char* b){
    int i;
	for(i=0;i<10;i++){
		if(a[i]=='\0' && b[i]==a[i]) return 1;
		if(a[i]!=b[i]) return 0;
	}
	return 1;
}

Person new_person(char* name,char* init,char* genn){
		Person p;
		//srand((unsigned) time(0) );
		int i;
		for(i=0;i<10;i++){
			p.name[i]=name[i];
		}
		for(i=0;i<5;i++){
			p.initial[i]=init[i];
			if(i<4){
				p.marks[i]=rand()%4+2;
			}
		}

		for(i=0;i<2;i++){
			p.gen[i]=genn[i];
		}
		p.group=rand()%8+1;

		return p;
}



void print_menu(){
	printf("|----------------------------------------------|\n");
	printf("|   		     Menu   	               |\n");
	printf("|----------------------------------------------|\n");
	printf("|1.     Create a base			       |\n"); //DONE
	printf("|2.     Add new elements		       |\n"); //DONE
	printf("|3.     Add new random elements		       |\n"); //DONE
	printf("|4.     Print the base		  	       |\n"); //DONE
	printf("|5.	Remove the N-th element		       |\n"); //DONE
	printf("|6.	Remove all element with the same name  |\n");//DONE
	printf("|7.	Option 18                              |\n");//DONE
	printf("|8.	Delete the base                        |\n"); //DONE
	printf("|9.     Quit                                   |\n");//DONE
	printf("|----------------------------------------------|\n");
}

void create_a_base(char* path){
	FILE* f;
	f=fopen(path,"wb");
	if(f){
		int a;
		printf("Please enter a number of elemts:\n");
		scanf("%d",&a);
		srand((unsigned) time(0) );
		int i;
		for(i=0;i<a;i++){
			int rand_names=rand()%20;
			int rand_init=rand()%17;
			char gen[2];
			if(rand_names<10)
				gen[0]='M';
			else
				gen[0]='F';
			gen[1]='\0';
			Person p=new_person(names[rand_names],inits[rand_init],&gen);
			fwrite(&p,sizeof(p),1,f);
		}
		fclose(f);
	}else{
		printf("I can not find or open the file.\n");
	}
}
void add_random_elements(char* path){
	FILE* f;
	f=fopen(path,"a+b");
	if(f){
		int a;
		printf("Please enter a number of elements:\n");
		scanf("%d",&a);
		srand((unsigned) time(0) );
		int i;
		for(i=0;i<a;i++){
			int rand_names=rand()%20;
			int rand_init=rand()%17;
			char gen[2];
			if(rand_names<10)
				gen[0]='M';
			else
				gen[0]='F';
			gen[1]='\0';
			Person p=new_person(names[rand_names],inits[rand_init],&gen);
			fwrite(&p,sizeof(p),1,f);
		}
	fclose(f);
	}else{
		printf("I can not find or open the file.\n");
	}
}
void add_new_elements(char* path){
	FILE* f;
	f=fopen(path,"a+b");
	if(f){
		Person p;
		int a;
		printf("Please enter a number of elements:\n");
		scanf("%d",&a);
		int i;
		for(i=0;i<a;i++){
			scanf("%s%s%s%d",&p.name,&p.initial,&p.gen,&p.group);
			int j;
			for(j=0;j<4;j++){
				scanf("%d",&p.marks[j]);
				if(p.marks[j]<2 || p.marks[j]>5) {
					p.marks[j]=2;
				}
			}
			fwrite(&p,sizeof(Person),1,f);
		}
		fclose(f);
	}else{
		printf("I can not find or open the file.\n");
	}
}
void print_a_base(char* path){
	FILE* f;
	f=fopen(path,"rb");
	if(f){
		Person q;
		int i=1;
		while(fread(&q,sizeof(Person),1,f)>0){
			printf("¹%d ",i);
			printf("%s %s %s\nGroup: %d\nMarks: ",q.name,q.initial,q.gen,q.group);
			int j;
			for(j=0;j<4;j++){
					printf("%d ",q.marks[j]);
			}
			printf("\n");
			i++;
		}
		fclose(f);
	}else{
		printf("I can not find or open the file.\n");
	}
}
void remove_nth_element(char* path,int n){
	FILE* f;
	FILE* temp;
	f=fopen(path,"rb");
	temp=fopen("temp.dat","w+b");
	if(f&&temp){
		int i=1;
		Person q;
		while(fread(&q,sizeof(Person),1,f)>0){
			if(i!=n){
				//fread(&q,sizeof(Person),1,f);
				fwrite(&q,sizeof(Person),1,temp);
				i++;
			}	else
			    	i++;
		}
		rewind(temp);
		fclose(f);
		f=fopen(path,"wb");

		while(fread(&q,sizeof(Person),1,temp)>0){
				fwrite(&q,sizeof(Person),1,f);
		}
		fclose(temp);
		fclose(f);
		//print_a_base("temp.dat");
		remove("temp.dat");
	}else{
		printf("I can not find or open the file.\n");
	}


}

void delete_with_same_name(char* path,char* name){
	FILE* f;
	FILE* temp;
	//printf("3\n");
	f=fopen(path,"rb");
	//printf("3\n");
	temp=fopen("temp2.dat","w+b");
	//printf("3\n");
	if(f&&temp){
		Person q;
		while(fread(&q,sizeof(Person),1,f)){
			//printf("%d\n",cmp(&q.name,name));
			if(!cmp(&q.name,name))
				fwrite(&q,sizeof(Person),1,temp);
		}
		rewind(temp);
		fclose(f);
		f=fopen(path,"wb");

		while(fread(&q,sizeof(Person),1,temp)>0){
				fwrite(&q,sizeof(Person),1,f);
		}
		fclose(temp);
		fclose(f);
		//print_a_base("temp.dat");
		remove("temp2.dat");
	}else{
		 printf("I can not find or open the file.\n");
	}


}
void solution_18(char* path){
	FILE* f;
	f=fopen(path,"rb");
	if(f){
		double mx[9],mn[9];
		for(int i=0;i<9;i++){
			mx[i]=-1;
			mn[i]=6;
		}
		Person q;
		while(fread(&q,sizeof(Person),1,f)){
				int sum=0;
				int i;
				for (i = 0; i < 4; i++) {
					sum+=q.marks[i];
				}
				double mean=sum/4.0;
				if(mean>mx[q.group]){
						mx[q.group]=mean;
				}
				if(mean<mn[q.group]){
						mn[q.group]=mean;
				}
		}
		int group=-1;
		double difference=-2;
		int i;
		for (i = 1; i < 9; i++) {
			 if(mx[i]-mn[i] > difference ){
				 	difference=mx[i]-mn[i];
					group=i;
			 }
		}
		if(group!=-1) printf("Group with maximum difference is %d-th with difference: %.2f \n",group,difference);
		else printf("There are no students\n" );
		fclose(f);
	}else{
		printf("I can not find or open the file.\n");
	}
}

void erase_the_base(char* path){
	FILE* f;
	f=fopen(path,"wb");
	if(f)
		fclose(f);
	else
		printf("I can not find or open the file.\n");
}
void quit(){
	exit(0);
}
