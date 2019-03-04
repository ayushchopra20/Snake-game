#include<conio.h>
#include<stdlib.h>
#define height 40
#define width 40
 static int score=0;
typedef struct Node
{
    int X;
    int Y;
    char value;
    struct Node*next;
}Node;

typedef struct Food
{
    int X;
    int Y;
    char value;
}Food;


void setMatrix(char arr[height][width])
{
    //int height=40,width=40;
  char ch3='*',ch4=' ';
int i,j;

for(i=0;i<height;i++)
{
for(j=0;j<width;j++)
{

if(i==0||i==height-1||j==0||j==width-1)
  arr[i][j]=ch3;// printf("%c",ch1);
else
              arr[i][j]=ch4; // printf("%c",ch2);
          // printf("%c",arr[i][j]);
}
//printf("\n");
}

}

void moveSnaketoMatrix(char arr[height][width],Node*ptr,Food food)
{
    while(ptr)
    {
        arr[ptr->X][ptr->Y]=ptr->value;
        ptr=ptr->next;
    }
    arr[food.X][food.Y]=food.value;

}

void moveMatrixtoScreen(char arr[height][width])
{ int i,j;
    for(i=0;i<height;i++)
{
for(j=0;j<width;j++)
{
           printf("%c",arr[i][j]);
}
printf("\n");
}
}

Food generateFood(char arr[height][width],Node *ptr)
{
    Food food;
    food.X=rand()%(height-2)+1;
    food.Y=rand()%(width-2)+1;
    food.value='O';
    Node *temp=ptr;

    while(temp)
    {

        if(food.X==temp->X&&food.Y==temp->Y)
        {
            food=generateFood(arr,ptr);
        }
        else
                break;


        temp=temp->next;
    }
    return food;
}

void increaseLength(Node**tail)
{



Node*add=(Node*)malloc(sizeof(Node));
add->value='?';
add->next=NULL;
(*tail)->next=add;
add->X=(*tail)->X;
add->Y=(*tail)->Y;
(*tail)=add;
            score++;
            printf("\t\tSCORE:%d\n",score);
}

void checkOut(Node**head,int score)
{
    Node*ptr=*head;
    ptr=ptr->next;
    while(ptr)
    {

        if(ptr->X==(*head)->X && ptr->Y==(*head)->Y)
        {
            system("cls");
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t    GAME  OVER\n");
            printf("\n\t\t\t***Well  Played***\n");
            printf("\n\t\t\t  Total Score=%d",score);
            getch();
            exit(1);

        }
        ptr=ptr->next;
    }
}


Food eatFood(Node **head,char matrix[height][width],Food food,Node**tail)
{
    Node*ptr=*head;
    if(ptr->X==food.X && ptr->Y==food.Y)
    {
        food=generateFood(matrix,*head);
        increaseLength(tail);
        return food;
    }
    return food;

}

void swapValues(Node*ptr,int i,int j)
{
    if(ptr==NULL)
      return;

    int m=ptr->X;
    int n=ptr->Y;

    ptr->X=i;
    ptr->Y=j;
    swapValues(ptr->next,m,n);

}
void moveUp(Node **head)
{
    Node*ptr=*head;
    int m=(*head)->X;
    int n=(*head)->Y;
    (*head)->X=(*head)->X-1;
    if((*head)->X==0)
    {
        (*head)->X=height-2;
    }
    swapValues(ptr->next,m,n);

}

void moveDown(Node **head)
{
    Node*ptr=*head;
    int m=(*head)->X;
    int n=(*head)->Y;
    (*head)->X=(*head)->X+1;
    if((*head)->X==height-1)
    {
        (*head)->X=1;
    }
    swapValues(ptr->next,m,n);

}

void moveLeft(Node **head)
{
    Node*ptr=(*head);
    int m=(*head)->X;
    int n=(*head)->Y;
    (*head)->Y=(*head)->Y-1;
    if((*head)->Y==0)
    {
        (*head)->Y=width-2;
    }
    swapValues(ptr->next,m,n);

}

void moveRight(Node **head)
{
    Node*ptr=*head;
    int m=(*head)->X;
    int n=(*head)->Y;
    (*head)->Y=(*head)->Y+1;
    if((*head)->Y==width-1)
    {
        (*head)->Y=1;
    }
    swapValues(ptr->next,m,n);

}

void moveDefault(char ch,Node **head)
{
    switch(ch)
    {
    case 'w':
        moveUp(head);
        break;
    case 's':
        moveDown(head);
        break;
    case 'a':
        moveLeft(head);
        break;
    case 'd':
        moveRight(head);
        break;
    }
}

void presskey(Node**head,char matrix[height][width],Food food,Node**tail)
{
    char ch='a',ch1;
    while(1)
    {
        switch(ch1=getche())
        {
        case 'w':
        case 'W':
            if(ch!='s'||ch!='S')
            {   ch=ch1;
                moveUp(head);
                break;
            }

         case 's':
         case 'S':
            if(ch!='w'||ch!='W')
            {   ch=ch1;
                moveDown(head);
                break;}

         case 'a':
         case 'A':
            if(ch!='d'||ch!='D')
            {   ch=ch1;
                moveLeft(head);
                break;}

         case 'd':
         case 'D':
            if(ch!='a'||ch!='A')
            {   ch=ch1;
                moveRight(head);
                break;
            }
        }
        system("cls");
setMatrix(matrix);


food=eatFood(head,matrix,food,tail);
moveSnaketoMatrix(matrix,*head,food);
moveMatrixtoScreen(matrix);
checkOut(head,score);
    }
}

void createSnake(Node**head,Node**tail)
{

    Node*node1=(Node*)malloc(sizeof(Node));
    node1->X=6;
    node1->Y=10;
    node1->value='$';
    *head=node1;

    Node*node2=(Node*)malloc(sizeof(Node));
    node2->X=7;
    node2->Y=10;
    node2->value='?';
    node1->next=node2;

    Node*node3=(Node*)malloc(sizeof(Node));
    node3->X=8;
    node3->Y=10;
    node3->value='?';
    node2->next=node3;

    Node*node4=(Node*)malloc(sizeof(Node));
    node4->X=9;
    node4->Y=10;
    node4->value='?';
    node3->next=node4;

    Node*node5=(Node*)malloc(sizeof(Node));
    node5->X=10;
    node5->Y=10;
    node5->value='?';
    node4->next=node5;
    node5->next=NULL;
    *tail=node5;
}

int main()
{
    char ch;
    Node *head=NULL;
    Node *tail=NULL;
    Food food;

    char matrix[height][width];
    printf("Press N for new Game\n");
    while(1)

    {
        scanf("%c",&ch);

          if(ch=='N'||ch=='n')
       {
        setMatrix(matrix);
        createSnake(&head,&tail);

        food=generateFood(matrix,head);
        moveSnaketoMatrix(matrix,head,food);
        moveMatrixtoScreen(matrix);
        presskey(&head,matrix,food,&tail);
        break;

       }
         else
       {
          printf("press valid key\n");
        }
    }
    }
