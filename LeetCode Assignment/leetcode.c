#include <stdio.h>
#include <stdlib.h>

// Definition of ListNode structure for linked list
struct ListNode {
    int val;
    struct ListNode* next;
};

// Function to find the town judge
int findTownJudge(int N, int trust[][2], int trustSize) {
    // Initialize arrays to count incoming and outgoing trusts
    int incoming[N + 1];
    int outgoing[N + 1];
    for (int i = 0; i <= N; i++) {
        incoming[i] = 0;
        outgoing[i] = 0;
    }

    // Count incoming and outgoing trusts for each person
    for (int i = 0; i < trustSize; i++) {
        int a = trust[i][0];
        int b = trust[i][1];
        outgoing[a]++;
        incoming[b]++;
    }

    // Find the person who satisfies properties 1 and 2
    for (int i = 1; i <= N; i++) {
        if (incoming[i] == N - 1 && outgoing[i] == 0) {
            return i;
        }
    }

    // If no such person exists, return -1
    return -1;
}

// Function to get the intersection node of two linked lists
struct ListNode* getIntersectionNode(struct ListNode* headA, struct ListNode* headB) {
    // Helper function to get the length of a linked list
    int getLength(struct ListNode* head) {
        int length = 0;
        while (head) {
            length++;
            head = head->next;
        }
        return length;
    }

    // Get the lengths of both linked lists
    int lengthA = getLength(headA);
    int lengthB = getLength(headB);

    // Reset pointers to the heads of the linked lists
    struct ListNode* ptrA = headA;
    struct ListNode* ptrB = headB;

    // Adjust the longer linked list's pointer to match the length of the shorter linked list
    while (lengthA > lengthB) {
        ptrA = ptrA->next;
        lengthA--;
    }

    while (lengthB > lengthA) {
        ptrB = ptrB->next;
        lengthB--;
    }

    // Move both pointers until they intersect or reach the end
    while (ptrA != ptrB) {
        ptrA = ptrA->next;
        ptrB = ptrB->next;
    }

    // Return the intersection node or NULL if no intersection exists
    return ptrA;
}

int main() {
    // Example usage for finding the town judge
    int N = 4;
    int trust[][2] = {{1, 3}, {1, 4}, {2, 3}, {2, 4}, {4, 3}};
    int trustSize = sizeof(trust) / sizeof(trust[0]);
    int town_judge = findTownJudge(N, trust, trustSize);
    printf("Town Judge: %d\n", town_judge);

    // Example usage for finding the intersection point of two linked lists
    // Construct linked lists for demonstration
    // Intersection point at node with value 8
    struct ListNode* intersect_node = (struct ListNode*)malloc(sizeof(struct ListNode));
    intersect_node->val = 8;
    intersect_node->next = (struct ListNode*)malloc(sizeof(struct ListNode));
    intersect_node->next->val = 4;
    intersect_node->next->next = (struct ListNode*)malloc(sizeof(struct ListNode));
    intersect_node->next->next->val = 5;
    intersect_node->next->next->next = NULL;

    struct ListNode* headA = (struct ListNode*)malloc(sizeof(struct ListNode));
    headA->val = 4;
    headA->next = (struct ListNode*)malloc(sizeof(struct ListNode));
    headA->next->val = 1;
    headA->next->next = intersect_node;

    struct ListNode* headB = (struct ListNode*)malloc(sizeof(struct ListNode));
    headB->val = 5;
    headB->next = (struct ListNode*)malloc(sizeof(struct ListNode));
    headB->next->val = 6;
    headB->next->next = (struct ListNode*)malloc(sizeof(struct ListNode));
    headB->next->next->val = 1;
    headB->next->next->next = intersect_node;

    struct ListNode* intersection_node = getIntersectionNode(headA, headB);
    if (intersection_node) {
        printf("Intersection Node Value: %d\n", intersection_node->val);
    } else {
        printf("No Intersection Node Found\n");
    }

    // Free dynamically allocated memory
    free(intersect_node->next->next);
    free(intersect_node->next);
    free(intersect_node);
    free(headA->next->next);
    free(headA->next);
    free(headA);
    free(headB->next->next);
    free(headB->next);
    free(headB);

    return 0;
}
