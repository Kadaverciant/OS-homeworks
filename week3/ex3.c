#include <stdio.h>

struct Node{
    int val;
    struct Node* nextNode;
    struct Node* prevNode;
};

struct LinkedList{
    struct Node* head;
};

int inList(struct LinkedList* ll, struct Node* node) {
    int ok=0;
    struct Node* temp=ll->head;
    while (temp!=NULL) {
        if(node==temp) {
            ok=1;
            break;
        }
        temp=temp->nextNode;
    }
    return ok;
}

void print_list(struct LinkedList* ll) {
    struct Node* temp=ll->head;
    while (temp!=NULL) {
        printf("%d ",temp->val);
        temp=temp->nextNode;
    }
    printf("\n");
}

void insert_node(struct LinkedList* ll, struct Node* newNode, struct Node* prevNode) {
    if(inList(ll,prevNode)&&!(inList(ll,newNode))) {
        struct Node* temp=ll->head;
        while (temp!=prevNode || temp==NULL) {
            temp=temp->nextNode;
        }
        if (temp->nextNode==NULL) {
            temp->nextNode=newNode;
            newNode->prevNode=temp;
        } else {
            newNode->nextNode=temp->nextNode;
            temp->nextNode=newNode;
            newNode->prevNode=temp;
        }
    } else {
        if(!inList(ll,prevNode)) {
            printf("ERROR:Previous node isn't in list!\n");
        }
        if(inList(ll,newNode)) {
            printf("ERROR:Node is already in list!\n");
        }
    }
}

void delete_node(struct LinkedList* ll, struct Node* deletedNode) {
    if (inList(ll,deletedNode)) {
        if (deletedNode->nextNode==NULL) {
            deletedNode->prevNode->nextNode=NULL;
        } else if (deletedNode->prevNode==NULL) {
            ll->head=deletedNode->nextNode;
            deletedNode->nextNode->prevNode=NULL;
        } else {
            deletedNode->prevNode->nextNode=deletedNode->nextNode;
            deletedNode->nextNode->prevNode=deletedNode->prevNode;
        }
        deletedNode->nextNode=NULL;
        deletedNode->prevNode=NULL;
    } else {
        printf("ERROR:Node isn't in list!\n");
    }

}

int main() {
    struct LinkedList list;
    list.head->val=0;
    list.head->nextNode=NULL;
    list.head->prevNode=NULL;
    print_list(&list);
    struct Node first = {1,NULL,NULL};
    struct Node second = {2,NULL,NULL};
    struct Node third = {3,NULL,NULL};
    struct Node forth = {4,NULL,NULL};
    struct Node fifth = {5,NULL,NULL};

    insert_node(&list,&first,list.head);
    insert_node(&list,&second,&first);
    insert_node(&list,&third,&second);
    print_list(&list);

    insert_node(&list,&second,&third);
    print_list(&list);

    insert_node(&list,&fifth,&forth);
    print_list(&list);

    insert_node(&list,&third,&forth);
    print_list(&list);

    delete_node(&list,&first);
    print_list(&list);

    delete_node(&list,&third);
    print_list(&list);

    delete_node(&list,list.head);
    print_list(&list);

    delete_node(&list,&third);
    print_list(&list);
}