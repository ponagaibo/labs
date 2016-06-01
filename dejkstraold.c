Stack Dejkstra(struct elem* part, char* str)
{
    int i=0,state=1;
    char m,c,t;
    Stack res=NULL,temp=NULL;
    for (i=0;i<count;i++)
    {
        if(part[i].flag==0)
        {
            res=in_s(res,part[i].el.value);
        }
        /*if(part[i].flag==3)
        {
            if(part[i].el.op==0)
            {
                temp=in_s(temp,'+');
            } else if(part[i].el.op==1)
            {
                temp=in_s(temp,'-');
            } else if(part[i].el.op==2)
            {
                temp=in_s(temp,'*');
            } else if(part[i].el.op==3)
            {
                temp=in_s(temp,'/');
            } else if(part[i].el.op==4)
            {
                temp=in_s(temp,'^');
            }
        }*/

        if (part[i].flag==2 && part[i].el.br==0)
        {
            temp=in_s(temp,'(');
        }
        if (part[i].flag==2 && part[i].el.br==1)
        {
            while((c=first_s(temp))!='(')
            {
                if(!empty_s(temp))
                {
                    printf("Wrong quantity of brackets\n");
                    state=0;
                    return res;
                    break;
                }
                temp=out_s(temp,&m);
                res=in_s(res,m);
            }
            temp=out_s(temp,&m);
            if((c=first_s(temp))== '+' || c=='-' || c=='*' || c=='/' || c=='^')
            {
                temp=out_s(temp,&m);
                res=in_s(res,m);
            }
        }
        if(!state)
        {
            i=count;
            break;
        }
        if(part[i].flag==3)
        {
            switch(part[i].el.op)
            {
                case 0:
                    t='+';
                case 1:
                    t='-';
                case 2:
                    t='*';
                case 3:
                    t='/';
                case 4:
                    t='^';
            }
            if (temp!=NULL)
            {
                while(((t==0||t==1)&&((c=first_s(temp))=='+'||c=='-'||c=='*'||c=='/'||c=='^'))||((t==2||t==3)&&(c=='*'||c=='/'||c=='^'))||((t==5)&&(c=='^')))
                {
                    temp=out_s(temp,&m);
                    res=in_s(res,m);
                }
                temp=in_s(temp,t);
            } else {
                temp=in_s(temp,t);
            }
        }
    }

    while(empty_s(temp))
    {
        temp=out_s(temp,&m);
        res=in_s(res,m);
    }
    printf("top res %c",first_s(res));
    return res;
}
