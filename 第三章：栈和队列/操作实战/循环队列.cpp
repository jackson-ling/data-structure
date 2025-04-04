/*

特点：先进先出，设置头指针front和尾指针rear，尾指针始终指向队尾元素的后一个位置

假溢出：当队头元素出队时，头指针上移，然而只能在队尾插入元素，空间大小一定的情况下，前面就会出现空位，空间利不完

为什么使用循环队列？为防止假溢出的情况，充分使用空间，用循环队列实现

注意?
（1）分配的是一段数组空间，指针指向的是数组的下标，实际上元素的物理位置=下标索引+1
（2）利用循环队列的特点，（重点）当分配n的空间大小的时候，“”我们认为当元素为n-1个的时候就是队满“”

记住以下几组公式

判断队空：q.front=q.rear
判断队满：(q.rear+1)%maxsize=q.front
求队列长度（计算元素个数）：(q.rear=q.front+maxqsize)%maxqsize

如何理解？
原本指针指的数组下标索引，加一就表示当前所指元素的物理位置，如果取模不为0，说明当前位置不是最后一个位置
（即maxqsize的值匹配，说明还可以继续添加元素），如果取模为0，就说明现在是队尾

对于队尾指针的自增表达：(q.rear+1)%maxqsize  ;   (q.front+1)%maxqsize

（1）如果取模不为0，那就指向当前位置，队尾指针始终指向队尾元素的上方
（2）如果取模为0，那队尾指针就回到下标索引为0的位置，实现循环队列

注意：在队列中访问元素的方式和栈的区别

（1）队列中由于只能在队头删除元素，在队尾插入元素的特点，使用指针的方式就没有直接通过下标索引访问来的方便，
    所以队列中采用下标索引来访问元素
（2）栈的特点是后进先出，操作都是在栈顶完成，操作简单，使用指针就很方便

*/

#include <stdio.h>
#include <stdlib.h>

typedef int status;
typedef int elemtype;

#define ok 1
#define error 0
#define overflow -1
#define maxqsize 100

// 队列的定义
typedef struct
{
    elemtype *data; // 采用动态内存分配
    // 注意这里不是指针类型，只是用来记录元素位置
    int front; // 队头指针
    int rear;  // 队尾指针
} sqqueue;

// 队列初始化
status sqqueueinit(sqqueue &q)
{
    q.data = (elemtype *)malloc(sizeof(elemtype) * maxqsize);
    if (!q.data)
    {
        printf("fail to init\n");
        return overflow;
    }
    q.front = q.rear = 0; // 注意初始化为0
    printf("init success\n");
    return ok;
}

// 打印队列元素
void printqueue(sqqueue q)
{
    printf("printqueue data below:\n");

    // 注意：不要直接对原有的指针进行修改，需要一个临时变量
    int temp = q.front;
    if (q.front == q.rear)
    {
        printf("the queue is empty\n");
    }
    while (temp != q.rear) // 打印的前提是队列不为空
    {
        printf("%d ", q.data[temp]); // 从队头元素开始打印
        temp = (temp + 1) % maxqsize;
    }
    printf("\n");
}

// 入队
status enqueue(sqqueue &q, elemtype e)
{
    if ((q.rear + 1) % maxqsize == q.front)
    {
        printf("the queue is full with data,enqueue fails\n");
        return error;
    }
    q.data[q.rear] = e;
    // 队尾指针自增1
    q.rear = (q.rear + 1) % maxqsize;
    printf("the enqueue data is :%d\n", e);
    printf("enqueue success\n");
    printf("\n");
    printqueue(q);
    printf("\n");
    return ok;
}

// 出队
status dequeue(sqqueue &q, elemtype &e)
{
    if (q.rear == q.front)
    {
        printf("the queue is empty,enqueue fails\n");
        return error;
    }
    e = q.data[q.front]; // 保存队头元素
    q.front = (q.front + 1) % maxqsize;
    printf("the enqueue data is : %d\n", e);
    printf("dequeue success\n");
    printf("\n");
    return ok;
}

// 求队列长度
status getlength(sqqueue q)
{
    int length = (q.rear - q.front + maxqsize) % maxqsize;
    printf("the queue length is : %d", length);
    return ok;
}

// 判断队列是否为空
status isempty(sqqueue q)
{
    if (q.front == q.rear)
    {
        printf("the squeue is empty\n");
        return ok;
    }
    else
    {
        printf("the squeue isn't empty,there have %d data in it\n", (q.rear - q.front + maxqsize) % maxqsize);
        return ok;
    }
}

int main()
{
    printf("1.queueinit\n");
    printf("2.enqueue\n");
    printf("3.dequeue\n");
    printf("4.getlength\n");
    printf("5.isempty\n");
    printf("6.printqueue\n");
    printf("0.exit\n");
    int choose, e, e1;
    sqqueue q;
    printf("\n");
    while (1)
    {
        printf("Please choose the function you want:");
        if (scanf("%d", &choose) != 1)
        {
            while (getchar() != '\n')
            {
                ;
            }
            printf("invalid input\n");
            continue;
        }
        switch (choose)
        {
        case 1:
            sqqueueinit(q);
            printf("\n");
            break;
        case 2:
            printf("input the data you want to enqueue:");
            scanf("%d", &e);
            enqueue(q, e);
            printf("\n");
            break;
        case 3:
            dequeue(q, e1);
            printf("\n");
            break;
        case 4:
            getlength(q);
            printf("\n");
            break;
        case 5:
            isempty(q);
            printf("\n");
            break;
        case 6:
            printqueue(q);
            printf("\n");
            break;
        case 0:
            return 0;
            break;
        }
    }
}