// input 값 입력받기             arr[N]         -> O(N)
// input 값 퀵소트로 정렬.        sortedArr[N]  -> O(NlogN)
// sortedArr을 AVL에 삽입. 이 때, 앞의 값과 동일하면 삽입하지 않음. -> O(NlogN)
// arr의 값 순서대로 AVL을 탐색.
// AVL의 node의 visited 값이 false면 출력하고 visited 값을 true로 만들어줌. true면 출력X -> O(NlogN)
#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
#define MAX_NUM 100000

int arr[MAX_NUM];
int sortedArr[MAX_NUM];
// 노드 구조체를 정의합니다.
struct nodeAVL {
    int data;
    bool visited;
    struct nodeAVL* left;
    struct nodeAVL* right;
} * root;

// 클래스를 정의합니다.
class classAVL {
public:
    // 노드의 높이를 반환합니다.
    int height(nodeAVL*);
    // 균형인수(높이의 차이)를 반환합니다.
    int diff(nodeAVL*);
    // RR 회전 함수입니다.
    nodeAVL* rr(nodeAVL*);
    // LL 회전 함수입니다.
    nodeAVL* ll(nodeAVL*);
    // LR 회전 함수입니다.
    nodeAVL* lr(nodeAVL*);
    // RL 회전 함수입니다.
    nodeAVL* rl(nodeAVL*);
    // 트리의 균형을 맞추는 함수입니다.
    nodeAVL* balance(nodeAVL*);
    // AVL 트리에 새로운 원소를 삽입합니다.
    nodeAVL* insert(nodeAVL*, int);
    // 현재의 AVL 트리 내용을 보여주는 함수입니다.
    bool search(nodeAVL*, int);
    // 탐색.
    void display(nodeAVL*, int);
    // AVL 트리를 중위 순회합니다.
    void inorder(nodeAVL*);
    // AVL 트리를 전위 순회합니다.
    void preorder(nodeAVL*);
    // AVL 트리를 후위 순회합니다.
    void postorder(nodeAVL*);
    // classAVL의 생성자입니다.
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

// AVL 트리의 높이를 출력합니다.
int classAVL::height(nodeAVL* temp)
{
    int h = 0;
    if (temp != NULL) {
        // 재귀적으로 왼쪽 혹은 오른쪽으로 검색합니다.
        int left = height(temp->left);
        int right = height(temp->right);
        int maxHeight = max(left, right);
        h = maxHeight + 1;
    }
    return h;
}

// 균형인수(높이의 차이)를 반환합니다.
int classAVL::diff(nodeAVL* temp)
{
    // 왼쪽 자식의 높이와 오른쪽 자식의 높이 차이를 반환합니다.
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

// RR 회전 함수입니다.
nodeAVL* classAVL::rr(nodeAVL* parent)
{
    // 말이 회전이지 그냥 부모 노드의 오른쪽 자식노드와 데이터를 교환하는 것입니다.
    nodeAVL* temp;
    temp = parent->right;
    parent->right = temp->left;
    temp->left = parent;
    return temp;
}

// ll 회전 함수입니다.
nodeAVL* classAVL::ll(nodeAVL* parent)
{
    // RR 회전과 반대입니다.
    nodeAVL* temp;
    temp = parent->left;
    parent->left = temp->right;
    temp->right = parent;
    return temp;
}

// LR 회전 함수입니다.
nodeAVL* classAVL::lr(nodeAVL* parent)
{
    // LR 회전은 왼쪽 자식을 기준으로 RR, 본인을 기준으로 LL회전합니다.
    nodeAVL* temp;
    temp = parent->left;
    parent->left = rr(temp);
    return ll(parent);
}

// RL 회전 함수입니다.
nodeAVL* classAVL::rl(nodeAVL* parent)
{
    // LR 회전과 반대입니다.
    nodeAVL* temp;
    temp = parent->right;
    parent->right = ll(temp);
    return rr(parent);
}

// AVL 트리의 균형을 맞추는 함수입니다.
nodeAVL* classAVL::balance(nodeAVL* temp)
{
    int factor = diff(temp);
    // 왼쪽 서브트리쪽으로 삽입이 되어 균형이 깨진 경우입니다.
    if (factor > 1) {
        // 그 왼쪽 자식노드에 문제가 발생했습니다.
        if (diff(temp->left) > 0) {
            temp = ll(temp);
        }
        // 그 오른쪽 자식 노드에 문제가 발생했습니다.
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

// 트리에 원소를 삽입하는 함수입니다.
nodeAVL* classAVL::insert(nodeAVL* root, int value)
{
    // 현재 트리가 비었을 때
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
    // 크거나 같은 경우 오른쪽 서브트리에 삽입합니다.
    else if (value >= root->data) {
        root->right = insert(root->right, value);
        root = balance(root);
    }
    return root;
}

void classAVL::display(nodeAVL* ptr, int level)
{
    int i;
    // 현재 트리가 비어있지 않은 경우입니다.
    if (ptr != NULL) {
        display(ptr->right, level + 1);
        printf("\n");
        // 현재 루트 노드인 경우입니다.
        if (ptr == root) {
            cout << "Root -> ";
        }
        // i가 현레벨보다 낮고 루트가 아닌 경우일 때까지 입니다.
        for (i = 0; i < level && ptr != root; i++) {
            cout << "        ";
        }
        // 자신의 위치에 데이터를 출력합니다.
        if (ptr->visited) {
            cout << "[" << ptr->data << "]";
        } else {
            cout << "(" << ptr->data << ")";
        }
        // 왼쪽 노드도 출력해줍니다.
        display(ptr->left, level + 1);
    }
}