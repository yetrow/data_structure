#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include"DoublyLinkedList.h"

int main(void)
{
    printf("== Doubly Linked List Music Player Demp == \n\n");

    // 1. 创建一个空的播放列表
    printf(">> Initializing an empty playlist...\n");
    DoublyLinkedList* playlist=createList();
    if(!playlist){
        return 1;
    }
    printListForward(playlist);
    puts(" ");

    // 2. 添加初始歌曲（append）
    printf(">> Adding initial songs to the playlist using append().\n");
    append(playlist,(Song){"As It Was","Harry Styles",167});
    append(playlist,(Song){"Levitaing","Dua Lipa",23});
    append(playlist,(Song){"good 4 u","Olivia Rodrigo",178});
    append(playlist,(Song){"Blinding Lights","The weekend",200});
    printListForward(playlist);
    puts(" ");

    // 3. 添加向前和向后遍历
    printf(">> Traversing the playlist forward...\n");
    printListForward(playlist);
    printf(">> Traversing the playlist backward...\n");
    printListBackward(playlist);
    puts(" ");

    // 4. 演示插入操作
    printf(">> Inserting a song after 'good 4 u'...\n");
    Node* targetNode = findByTitle(playlist, "good 4 u");
    if (targetNode) {
        insertAfter(playlist, targetNode, (Song){"STAY", "The Kid LAROI, Justin Bieber", 141});
    }
    printListForward(playlist);
    puts(" ");

    // 5. 演示在头部插入
    printf(">> Inserting a song at the beginning (prepend)...\n");
    prepend(playlist, (Song){"Peaches", "Justin Bieber", 198});
    printListForward(playlist);
    puts(" ");

    // 6. 演示删除操作
    printf(">> Deleting 'Levitaing' from the playlist...\n");
    Node* nodeToDelete = findByTitle(playlist, "Levitaing");
    if (nodeToDelete) {
        deleteNode(playlist, nodeToDelete);
    }
    printListForward(playlist);
    puts(" ");

    // 7. 演示删除头结点
    printf(">> Deleting the head node...\n");
    if (playlist->head) {
        deleteNode(playlist, playlist->head);
    }
    printListForward(playlist);
    puts(" ");

    // 8. 演示删除尾结点
    printf(">> Deleting the tail node...\n");
    if (playlist->tail) {
        deleteNode(playlist, playlist->tail);
    }
    printListForward(playlist);
    puts(" ");

    // 9. 清理工作
    printf(">> Freeing the playlist memory...\n");
    freeList(playlist);
    playlist = NULL;
    printf("Playlist freed.\n");

    return 0;
}