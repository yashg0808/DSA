#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// 1. Reverse a linked list
ListNode* reverseList(ListNode* head) {
    ListNode* prev = nullptr;
    ListNode* current = head;
    while (current) {
        ListNode* nextNode = current->next;
        current->next = prev;
        prev = current;
        current = nextNode;
    }
    return prev;
}

// 2. Detect a cycle in a linked list
bool hasCycle(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;
    }
    return false;
}

// 3. Merge two sorted linked lists
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    if (!l1) return l2;
    if (!l2) return l1;

    if (l1->val < l2->val) {
        l1->next = mergeTwoLists(l1->next, l2);
        return l1;
    } else {
        l2->next = mergeTwoLists(l1, l2->next);
        return l2;
    }
}

// 4. Find the middle of a linked list
ListNode* middleNode(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

// 5. Remove Nth node from the end of a linked list
ListNode* removeNthFromEnd(ListNode* head, int n) {
    ListNode* dummy = new ListNode(0, head);
    ListNode* slow = dummy;
    ListNode* fast = dummy;
    for (int i = 0; i < n; i++) {
        fast = fast->next;
    }
    while (fast->next) {
        slow = slow->next;
        fast = fast->next;
    }
    slow->next = slow->next->next;
    return dummy->next;
}

// 6. Remove duplicates from a sorted linked list
ListNode* deleteDuplicates(ListNode* head) {
    ListNode* current = head;
    while (current && current->next) {
        if (current->val == current->next->val) {
            current->next = current->next->next;
        } else {
            current = current->next;
        }
    }
    return head;
}

// 7. Detect and remove a cycle in a linked list
void removeCycle(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            slow = head;
            while (slow->next != fast->next) {
                slow = slow->next;
                fast = fast->next;
            }
            fast->next = nullptr;
            return;
        }
    }
}

// 8. Check if a linked list is palindrome
bool isPalindrome(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;
    std::stack<int> s;

    while (fast && fast->next) {
        s.push(slow->val);
        slow = slow->next;
        fast = fast->next->next;
    }

    if (fast) slow = slow->next;

    while (slow) {
        int top = s.top();
        s.pop();
        if (top != slow->val) return false;
        slow = slow->next;
    }
    return true;
}

// 9. Rotate a linked list
ListNode* rotateRight(ListNode* head, int k) {
    if (!head || k == 0) return head;

    int length = 1;
    ListNode* tail = head;
    while (tail->next) {
        tail = tail->next;
        length++;
    }

    k = k % length;
    if (k == 0) return head;

    tail->next = head;
    for (int i = 0; i < length-k; ++i) {
        tail = tail->next;
    }

    ListNode* newHead = tail->next;
    tail->next = nullptr;
    return newHead;
}

int main() {
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);
    ListNode* ans=rotateRight(head, 2);
    while (ans) {
        cout << ans->val << " ";
        ans = ans->next;
    }
    return 0;
}