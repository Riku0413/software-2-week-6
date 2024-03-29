#pragma once

typedef struct node Node;
   
struct node{
    int symbol;
    int count;
    Node *left;
    Node *right;
    Node *upper; // 🔥上へのポインタ
    char bit[100]; // 🔥01の並び列を追加！
};

// ファイルをエンコードし木のrootへのポインタを返す
Node *encode(const char *filename);
// Treeを走査して表示する
void traverse_tree(const int depth, Node *root, char *bit_now, int flag);

