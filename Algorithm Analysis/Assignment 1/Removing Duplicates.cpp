// input �� �Է¹ޱ�             arr[N]         -> O(N)
// input �� ����Ʈ�� ����.        sortedArr[N]  -> O(NlogN)
// sortedArr�� AVL�� ����. �� ��, ���� ���� �����ϸ� �������� ����. -> O(NlogN)
// arr�� �� ������� AVL�� Ž��.
// AVL�� node�� visited ���� false�� ����ϰ� visited ���� true�� �������. true�� ���X -> O(NlogN)
#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
#define MAX_NUM 100000

int arr[MAX_NUM];
int sortedArr[MAX_NUM];
// ��� ����ü�� �����մϴ�.
struct nodeAVL {
    int data;
    bool visited;
    struct nodeAVL* left;
    struct nodeAVL* right;
} * root;

// Ŭ������ �����մϴ�.
class classAVL {
public:
    // ����� ���̸� ��ȯ�մϴ�.
    int height(nodeAVL*);
    // �����μ�(������ ����)�� ��ȯ�մϴ�.
    int diff(nodeAVL*);
    // RR ȸ�� �Լ��Դϴ�.
    nodeAVL* rr(nodeAVL*);
    // LL ȸ�� �Լ��Դϴ�.
    nodeAVL* ll(nodeAVL*);
    // LR ȸ�� �Լ��Դϴ�.
    nodeAVL* lr(nodeAVL*);
    // RL ȸ�� �Լ��Դϴ�.
    nodeAVL* rl(nodeAVL*);
    // Ʈ���� ������ ���ߴ� �Լ��Դϴ�.
    nodeAVL* balance(nodeAVL*);
    // AVL Ʈ���� ���ο� ���Ҹ� �����մϴ�.
    nodeAVL* insert(nodeAVL*, int);
    // ������ AVL Ʈ�� ������ �����ִ� �Լ��Դϴ�.
    bool search(nodeAVL*, int);
    // Ž��.
    void display(nodeAVL*, int);
    // AVL Ʈ���� ���� ��ȸ�մϴ�.
    void inorder(nodeAVL*);
    // AVL Ʈ���� ���� ��ȸ�մϴ�.
    void preorder(nodeAVL*);
    // AVL Ʈ���� ���� ��ȸ�մϴ�.
    void postorder(nodeAVL*);
    // classAVL�� �������Դϴ�.
    classAVL()
    {
        root = NULL;
    }
};

int main(void)
{
    classAVL AVL;
    int N;
    scanf("%d", &N);

    // input values
    for (int i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
    }

    // copy values
    for (int i = 0; i < N; i++) {
        sortedArr[i] = arr[i];
    }

    // sort using Quick Sort Method
    sort(sortedArr, sortedArr + N);

    // insert smallest value into AVL tree
    root = AVL.insert(root, sortedArr[0]);

    // traverse index 1 ~ N-1
    for (int i = 1; i < N; i++) {
        if (sortedArr[i - 1] == sortedArr[i])
            continue;

        // insert only different numbers into AVL tree
        root = AVL.insert(root, sortedArr[i]);
    }

    int Answer[N];
    int answerCnt = 0;

    // traverse index 0 ~ N-1 in inputArr[] array.
    for (int i = 0; i < N; i++) {
        if (!AVL.search(root, arr[i])) { // if only first visit, add numbers into Answer
            Answer[answerCnt++] = arr[i];
        }
    }

    for (int i = 0; i < answerCnt; i++) {
        printf("%d ", Answer[i]);
    }

    return 0;
}

// AVL Ʈ���� ���̸� ����մϴ�.
int classAVL::height(nodeAVL* temp)
{
    int h = 0;
    if (temp != NULL) {
        // ��������� ���� Ȥ�� ���������� �˻��մϴ�.
        int left = height(temp->left);
        int right = height(temp->right);
        int maxHeight = max(left, right);
        h = maxHeight + 1;
    }
    return h;
}

// �����μ�(������ ����)�� ��ȯ�մϴ�.
int classAVL::diff(nodeAVL* temp)
{
    // ���� �ڽ��� ���̿� ������ �ڽ��� ���� ���̸� ��ȯ�մϴ�.
    int left = height(temp->left);
    int right = height(temp->right);
    int factor = left - right;
    return factor;
}

bool classAVL::search(nodeAVL* temp, int num)
{
    if (num == temp->data) {
        if (temp->visited) {
            return true;
        } else {
            temp->visited = true;
            return false;
        }
    } else if (num > temp->data) {
        return search(temp->right, num);
    } else {
        return search(temp->left, num);
    }
}

// RR ȸ�� �Լ��Դϴ�.
nodeAVL* classAVL::rr(nodeAVL* parent)
{
    // ���� ȸ������ �׳� �θ� ����� ������ �ڽĳ��� �����͸� ��ȯ�ϴ� ���Դϴ�.
    nodeAVL* temp;
    temp = parent->right;
    parent->right = temp->left;
    temp->left = parent;
    return temp;
}

// ll ȸ�� �Լ��Դϴ�.
nodeAVL* classAVL::ll(nodeAVL* parent)
{
    // RR ȸ���� �ݴ��Դϴ�.
    nodeAVL* temp;
    temp = parent->left;
    parent->left = temp->right;
    temp->right = parent;
    return temp;
}

// LR ȸ�� �Լ��Դϴ�.
nodeAVL* classAVL::lr(nodeAVL* parent)
{
    // LR ȸ���� ���� �ڽ��� �������� RR, ������ �������� LLȸ���մϴ�.
    nodeAVL* temp;
    temp = parent->left;
    parent->left = rr(temp);
    return ll(parent);
}

// RL ȸ�� �Լ��Դϴ�.
nodeAVL* classAVL::rl(nodeAVL* parent)
{
    // LR ȸ���� �ݴ��Դϴ�.
    nodeAVL* temp;
    temp = parent->right;
    parent->right = ll(temp);
    return rr(parent);
}

// AVL Ʈ���� ������ ���ߴ� �Լ��Դϴ�.
nodeAVL* classAVL::balance(nodeAVL* temp)
{
    int factor = diff(temp);
    // ���� ����Ʈ�������� ������ �Ǿ� ������ ���� ����Դϴ�.
    if (factor > 1) {
        // �� ���� �ڽĳ�忡 ������ �߻��߽��ϴ�.
        if (diff(temp->left) > 0) {
            temp = ll(temp);
        }
        // �� ������ �ڽ� ��忡 ������ �߻��߽��ϴ�.
        else {
            temp = lr(temp);
        }
    } else if (factor < -1) {
        if (diff(temp->right) > 0) {
            temp = rl(temp);
        } else {
            temp = rr(temp);
        }
    }
    return temp;
}

// Ʈ���� ���Ҹ� �����ϴ� �Լ��Դϴ�.
nodeAVL* classAVL::insert(nodeAVL* root, int value)
{
    // ���� Ʈ���� ����� ��
    if (root == NULL) {
        root = new nodeAVL;
        root->data = value;
        root->visited = false;
        root->left = NULL;
        root->right = NULL;
        return root;
    } else if (value < root->data) {
        root->left = insert(root->left, value);
        root = balance(root);
    }
    // ũ�ų� ���� ��� ������ ����Ʈ���� �����մϴ�.
    else if (value >= root->data) {
        root->right = insert(root->right, value);
        root = balance(root);
    }
    return root;
}

void classAVL::display(nodeAVL* ptr, int level)
{
    int i;
    // ���� Ʈ���� ������� ���� ����Դϴ�.
    if (ptr != NULL) {
        display(ptr->right, level + 1);
        printf("\n");
        // ���� ��Ʈ ����� ����Դϴ�.
        if (ptr == root) {
            cout << "Root -> ";
        }
        // i�� ���������� ���� ��Ʈ�� �ƴ� ����� ������ �Դϴ�.
        for (i = 0; i < level && ptr != root; i++) {
            cout << "        ";
        }
        // �ڽ��� ��ġ�� �����͸� ����մϴ�.
        if (ptr->visited) {
            cout << "[" << ptr->data << "]";
        } else {
            cout << "(" << ptr->data << ")";
        }
        // ���� ��嵵 ������ݴϴ�.
        display(ptr->left, level + 1);
    }
}