#include <stdio.h>
#include <stdlib.h>

// 定义多项式的结点结构
typedef struct PolyNode {
    int coef; // 系数
    int exp; // 指数
    struct PolyNode* next; // 指向下一个结点的指针
} PolyNode;

// 创建多项式的结点
PolyNode* createNode(int coef, int exp) {
    PolyNode* newNode = (PolyNode*)malloc(sizeof(PolyNode));
    if (newNode == NULL) {
        printf("内存分配失败\n");
        exit(1);
    }
    newNode->coef = coef;
    newNode->exp = exp;
    newNode->next = NULL;
    return newNode;
}

// 释放多项式链表的内存
void freePoly(PolyNode* poly) {
    PolyNode* current = poly;
    while (current != NULL) {
        PolyNode* temp = current;
        current = current->next;
        free(temp);
    }
}

// 打印多项式
void printPoly(PolyNode* poly) {
    if (poly == NULL) {
        printf("多项式为空\n");
        return;
    }

    PolyNode* current = poly;
    while (current != NULL) {
        printf("%dx^%d ", current->coef, current->exp);
        if (current->next != NULL) {
            printf("+ ");
        }
        current = current->next;
    }
    printf("\n");
}

// 多项式相加
PolyNode* addPoly(PolyNode* poly1, PolyNode* poly2) {
    if (poly1 == NULL) {
        return poly2;
    }
    if (poly2 == NULL) {
        return poly1;
    }

    PolyNode* head = NULL;
    PolyNode* tail = NULL;

    while (poly1 != NULL && poly2 != NULL) {
        int coef1 = poly1->coef;
        int exp1 = poly1->exp;
        int coef2 = poly2->coef;
        int exp2 = poly2->exp;

        if (exp1 == exp2) {
            int sum = coef1 + coef2;
            if (sum != 0) {
                PolyNode* newNode = createNode(sum, exp1);
                if (head == NULL) {
                    head = newNode;
                    tail = newNode;
                } else {
                    tail->next = newNode;
                    tail = newNode;
                }
            }
            poly1 = poly1->next;
            poly2 = poly2->next;
        } else if (exp1 > exp2) {
            PolyNode* newNode = createNode(coef1, exp1);
            if (head == NULL) {
                head = newNode;
                tail = newNode;
            } else {
                tail->next = newNode;
                tail = newNode;
            }
            poly1 = poly1->next;
        } else {
            PolyNode* newNode = createNode(coef2, exp2);
            if (head == NULL) {
                head = newNode;
                tail = newNode;
            } else {
                tail->next = newNode;
                tail = newNode;
            }
            poly2 = poly2->next;
        }
    }

    // 将剩余的节点连接到合并后的多项式尾部
    if (poly1 != NULL) {
        tail->next = poly1;
    }
    if (poly2 != NULL) {
        tail->next = poly2;
    }

    return head;
}
// 多项式相减
PolyNode* subtractPoly(PolyNode* poly1, PolyNode* poly2) {
    if (poly1 == NULL) {
        return poly2;
    }
    if (poly2 == NULL) {
        return poly1;
    }

    PolyNode* head = NULL;
    PolyNode* tail = NULL;

    while (poly1 != NULL && poly2 != NULL) {
        int coef1 = poly1->coef;
        int exp1 = poly1->exp;
        int coef2 = poly2->coef;
        int exp2 = poly2->exp;

        if (exp1 == exp2) {
            int diff = coef1 - coef2;
            if (diff != 0) {
                PolyNode* newNode = createNode(diff, exp1);
                if (head == NULL) {
                    head = newNode;
                    tail = newNode;
                } else {
                    tail->next = newNode;
                    tail = newNode;
                }
            }
            poly1 = poly1->next;
            poly2 = poly2->next;
        } else if (exp1 > exp2) {
            PolyNode* newNode = createNode(coef1, exp1);
            if (head == NULL) {
                head = newNode;
                tail = newNode;
            } else {
                tail->next = newNode;
                tail = newNode;
            }
            poly1 = poly1->next;
        } else {
            PolyNode* newNode = createNode(-coef2, exp2);
            if (head == NULL) {
                head = newNode;
                tail = newNode;
            } else {
                tail->next = newNode;
                tail = newNode;
            }
            poly2 = poly2->next;
        }
    }

    // 将剩余的节点连接到合并后的多项式尾部
    if (poly1 != NULL) {
        tail->next = poly1;
    }
    if (poly2 != NULL) {
        tail->next = poly2;
    }

    return head;
}

int main() {
    // 创建多项式1：3x^3 + 2x^2 + x^1 + 5
    PolyNode* poly1 = createNode(3, 3);
    poly1->next = createNode(2, 2);
    poly1->next->next = createNode(1, 1);
    poly1->next->next->next = createNode(5, 0);

    // 创建多项式2：2x^2 + 4x^1 + 1
    PolyNode* poly2 = createNode(2, 2);
    poly2->next = createNode(4, 1);
    poly2->next->next = createNode(1, 0);

    printf("多项式1：");
    printPoly(poly1);

    printf("多项式2：");
    printPoly(poly2);

    PolyNode* sum = addPoly(poly1, poly2);
    printf("多项式相加：");
    printPoly(sum);

    PolyNode* diff = subtractPoly(poly1, poly2);
    printf("多项式相减：");
    printPoly(diff);

    // 释放内存
    freePoly(poly1);
    freePoly(poly2);
    freePoly(sum);
    freePoly(diff);

    return 0;
}