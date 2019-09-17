#include <stdio.h>

#define SMALL_OPEN_PAREN -1
#define SMALL_CLOSE_PAREN -2
#define BIG_OPEN_PAREN -3
#define BIG_CLOSE_PAREN -4
#define STACK_EMPTY_FLAG -5

struct stack
{
    int top = -1;
    int arr[35];
};

stack s;

void stackPush(int n)
{
    s.arr[++s.top] = n;
}

int stackPop()
{
    if (s.top == -1)
    {
        return STACK_EMPTY_FLAG;
    }
    return s.arr[s.top--];
}

int main(void)
{
    char inStr[500];
    int Answer = 0;

    scanf("%s", &inStr);

    for (int i = 0;; i++)
    {
        if (inStr[i] == '(')
        {
            stackPush(SMALL_OPEN_PAREN);
        }
        else if (inStr[i] == '[')
        {
            stackPush(BIG_OPEN_PAREN);
        }
        else if (inStr[i] == ')')
        {
            int pop;
            int numArr[500];
            int arrIdx = 0;

            while (1)
            {
                pop = stackPop();
                if (pop == STACK_EMPTY_FLAG || pop == BIG_OPEN_PAREN)
                {
                    Answer = 0;
                    printf("%d", Answer);
                    return 0;
                }
                else if (pop > 0)
                {
                    numArr[arrIdx++] = pop;
                    continue;
                }
                else
                {
                    int sum = 0;
                    for (int j = 0; j < arrIdx; j++)
                    {
                        sum += numArr[j];
                    }
                    if (!sum)
                        sum = 1;

                    stackPush(2 * sum);
                    break;
                }
            }
        }
        else if (inStr[i] == ']')
        {
            int pop;
            int numArr[500];
            int arrIdx = 0;

            while (1)
            {
                pop = stackPop();
                if (pop == STACK_EMPTY_FLAG || pop == SMALL_OPEN_PAREN)
                {
                    Answer = 0;
                    printf("%d", Answer);
                    return 0;
                }
                else if (pop > 0)
                {
                    numArr[arrIdx++] = pop;
                    continue;
                }
                else
                {
                    int sum = 0;
                    for (int j = 0; j < arrIdx; j++)
                    {
                        sum += numArr[j];
                    }
                    if (!sum)
                        sum = 1;

                    stackPush(3 * sum);
                    break;
                }
            }
        }
        else
        {
            int sum = 0;

            while (1)
            {
                int n = stackPop();
                if (n == STACK_EMPTY_FLAG)
                {
                    break;
                }
                else if (n < 0)
                {
                    printf("%d", 0);
                    return 0;
                }

                sum += n;
            }

            printf("%d", sum);
            break;
        }
    }
    return 0;
}