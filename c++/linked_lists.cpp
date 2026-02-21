#include <iostream>

using namespace std;


struct Node {
    int data; 
    Node *next; 
};


struct List {
    Node *first; 
};


struct ListData {
    int *data; 
    size_t len; 
};



void appendNode(List *list, const int val) {
    Node *newNode = new Node;
    newNode->data = val;
    newNode->next = nullptr;

    if (list->first == nullptr) {
        list->first = newNode;
        return;
    }

    Node *curr = list->first;
    while (curr->next != nullptr) {
        curr = curr->next;
    }
    curr->next = newNode;
}


List *createList(const ListData *listData) {
    List *list = new List;
    list->first = nullptr;

    if (listData->len == 0) {
        return list;
    }

    for (int i = 0; i < listData->len; i++) {
        appendNode(list, listData->data[i]);

    }
    return list;
}


void insertNode(List *sortedList, const int val) {

    Node *newNode = new Node;
    newNode->data = val;
    newNode->next = nullptr;

    if (sortedList->first == nullptr) {
        sortedList->first = newNode;
        return;
    }

    if (val <= sortedList->first->data) {
        newNode->next = sortedList->first;
        sortedList->first = newNode;
        return;
    }

    Node *curr = sortedList->first;
    while (curr->next != nullptr && curr->next->data < val) {
        curr = curr->next;
    }

    newNode->next = curr->next;
    curr->next = newNode;
}


List *joinLists(List *list1, List *list2) {
    List *list = new List;
    list->first = nullptr;

    Node *curr = list1->first;
    while (curr != nullptr) {
        appendNode(list, curr->data);
        curr = curr->next;
    }

    curr = list2->first;
    while (curr != nullptr) {
        appendNode(list, curr->data);
        curr = curr->next;
    }


    return list;
}

void removeLastNode(List *list) {

    if (list->first == nullptr) {
        return;
    }

    if (list->first->next == nullptr) {
        delete list->first;
        list->first = nullptr;
        return;
    }

    Node *curr = list->first;
    while (curr->next->next != nullptr) {
        curr = curr->next;
    }

    delete curr->next;
    curr->next = nullptr;
}


bool isPalindrome(const List *list) {
    if (list->first == nullptr || list->first->next == nullptr) {
        return true;
    }

    Node *curr = list->first;
    size_t len = 0;
    while (curr != nullptr) {
        len++;
        curr = curr->next;
    }

    int *arr = new int[len];
    curr = list->first;
    for (size_t i = 0; i < len; i++) {
        arr[i] = curr->data;
        curr = curr->next;
    }

    for (size_t i = 0; i < len / 2; i++) {
        if (arr[i] != arr[len - i - 1]) {
            delete[] arr;
            return false;
        }
    }

    delete[] arr;
    return true;
}


int sumNodes(const List *list, const size_t n) {
    if (list->first == nullptr || n == 0) {
        return 0;
    }
    int sum = 0;
    Node *curr = list->first;
    for (size_t i = 0; i < n; i++) {
        sum += curr->data;
        curr = curr->next;
    }
    return sum;
}


bool contains(const List *list1, const List *list2) {
    if (list2->first == nullptr) {
        return true;
    }
    if (list1->first == nullptr) {
        return false;
    }

    for (Node *node2 = list2->first; node2 != nullptr; node2 = node2->next) {
        bool found = false;
        for (Node *node1 = list1->first; node1 != nullptr; node1 = node1->next) {
            if (node1->data == node2->data) {
                found = true;
                break;
            }
        }

        if (!found) {
            return false;
        }
    }
    return true;
}


List *deepCopyList(const List *list) {
    List *deep_list = new List;
    deep_list->first = nullptr;

    if (list->first == nullptr) {
        return deep_list;
    }

    Node *curr = list->first;
    while (curr != nullptr) {
        appendNode(deep_list, curr->data);
        curr = curr->next;
    }

    return deep_list; // tento riadok zmente podla zadania, je tu len kvoli kompilacii
}



Node *findLastNodeOccurrence(const List *list, const int val) {
    if (list->first == nullptr) {
        return nullptr;
    }

    Node *curr = list->first;
    Node *last_occ = nullptr;
    while (curr != nullptr) {
        if (curr->data == val) {
            last_occ = curr;
        }
        curr = curr->next;
    }
    return last_occ;
}


void deleteList(List *list) {
    Node *curr = list->first;
    while (curr != nullptr) {
        Node *tmp = curr;
        curr = curr->next;
        delete tmp;
    }
    list->first = nullptr;
    delete list;
}

void printList(const List *list) {
    Node *curr = list->first;
    cout << "(";
    while (curr != nullptr) {
        cout << curr->data;
        if (curr->next != nullptr) cout << ", ";
        curr = curr->next;
    }
    cout << ")" << endl;
}

int main() {

    
    List list = {nullptr};
    appendNode(&list, 8);
    std::cout << list.first->data << std::endl;
    int data[4] = {8, 9, 7, 9};
    ListData list_data = {data, 4};
    List *newList = createList(&list_data);
    List *newnew = joinLists(newList, &list);
    printList(newnew);
    std::cout << isPalindrome(newnew) << std::endl;
    std::cout << sumNodes(newnew, 2) << std::endl;
    List list1 = {nullptr};
    appendNode(&list1, 2);
    List *listos = createList(&list_data);
    List *newnew2 = joinLists(listos, &list1);
    printList(newnew2);
    std::cout << contains(newnew,newnew2) << std::endl;
    List *new3 = deepCopyList(newnew);
    printList(new3);
    Node *last = findLastNodeOccurrence(newnew,9);
    std::cout << last->data << std::endl;

    deleteList(new3);
    deleteList(newnew);
    deleteList(newList);

    return 0;
}
