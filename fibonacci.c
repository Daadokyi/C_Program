#include <stdio.h>
#include <stdlib.h>

typedef enum TypeTag {
    ADD,
    MUL,
    SUB,
    DIV,
    CONST,
    FIBO,
} TypeTag;

typedef struct Node {
    TypeTag type;
    int value;
    struct Node* left;
    struct Node* right;
} Node;

Node* makeNode(TypeTag type, int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->type = type;
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Node* makeFunc(TypeTag type) {
    Node* node = makeNode(type, 0);
    return node;
}

int calc(Node* node) {
    if (node == NULL) {
        return 0;
    }

    if (node->type == CONST) {
        return node->value;
    }

    int left = calc(node->left);
    int right = calc(node->right);

    switch (node->type) {
        case ADD:
            return left + right;
        case MUL:
            return left * right;
        case SUB:
            return left - right;
        case DIV:
            return left / right;
        case FIBO:
            if (left <= 1) {
                return left;
            } else {
                int prev = 0;
                int curr = 1;
                for (int i = 2; i <= left; i++) {
                    int next = prev + curr;
                    prev = curr;
                    curr = next;
                }
                return curr;
            }
        default:
            return 0;
    }
}

int main() {
    Node* add = (*makeFunc(ADD))(10, 6);
    Node* mul = (*makeFunc(MUL))(5, 4);
    Node* sub = (*makeFunc(SUB))(mul, add);
    Node* fibo = (*makeFunc(FIBO))(sub, NULL);

    printf("add : %d\n", calc(add));
    printf("mul : %d\n", calc(mul));
    printf("sub : %d\n", calc(sub));
    printf("fibo : %d\n", calc(fibo));

    free(add);
    free(mul);
    free(sub);
    free(fibo);

    return 0;
}
