#pragma once

typedef struct node Node;
   
struct node{
    int symbol;
    int count;
    Node *left;
    Node *right;
    Node *upper; // 親ノードへのポインタ
    char bit[20]; // 01の符号列を追加
};

// ファイルをエンコードし木のrootへのポインタを返す
Node *encode(const char *filename);
// Treeを走査して表示する
void traverse_tree(const int depth, Node *root, char *bit_now, int flag);
