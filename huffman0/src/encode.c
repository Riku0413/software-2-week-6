#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "encode.h"

#define NSYMBOLS 256

static int symbol_count[NSYMBOLS];

// 以下このソースで有効なstatic関数のプロトタイプ宣言

// ファイルを読み込み、static配列の値を更新する関数
static void count_symbols(const char *filename);

// symbol_count をリセットする関数
static void reset_count(void);

// 与えられた引数でNode構造体を作成し、そのアドレスを返す関数
static Node *create_node(int symbol, int count, Node *left, Node *right, Node *upper);

// Node構造体へのポインタが並んだ配列から、最小カウントを持つ構造体をポップしてくる関数
// n は 配列の実効的な長さを格納する変数を指している（popするたびに更新される）
static Node *pop_min(int *n, Node *nodep[]);

// ハフマン木を構成する関数
static Node *build_tree(void);


// 以下 static関数の実装
static void count_symbols(const char *filename)
{
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
	fprintf(stderr, "error: cannot open %s\n", filename);
	exit(1);
    }
    int c;
    while( ( c = fgetc(fp)) != EOF ){
	symbol_count[c]++;
    }

    fclose(fp);
}

static void reset_count(void)
{
    for (int i = 0 ; i < NSYMBOLS ; i++)
	symbol_count[i] = 0;
}

// 新たなnodeの生成
static Node *create_node(int symbol, int count, Node *left, Node *right, Node *upper)
{
    Node *ret = (Node *)malloc(sizeof(Node));
    *ret = (Node){ .symbol = symbol, .count = count, .left = left, .right = right, .upper = upper};
    return ret;
}

// 各 node を並べた配列から,countが最小のnodeを抽出した上で削除する
static Node *pop_min(int *n, Node *nodep[])
{
    // Find the node with the smallest count
    // カウントが最小のノードを見つけてくる
    int argmin = 0;
    for (int i = 0; i < *n; i++) {
	if (nodep[i]->count < nodep[argmin]->count) {
	    argmin = i;
	}
    }
    
    Node *node_min = nodep[argmin];
    
    // Remove the node pointer from nodep[]
    // 見つかったノード以降の配列を前につめていく
    for (int i = argmin; i < (*n) - 1; i++) {
	nodep[i] = nodep[i + 1];
    }
    // 合計ノード数を一つ減らす
    (*n)--;
    
    return node_min;
}

static Node *build_tree(void)
{
    int n = 0;
    Node *nodep[NSYMBOLS];
    
    for (int i = 0; i < NSYMBOLS; i++) {
	// カウントの存在しなかったシンボルには何もしない
	if (symbol_count[i] == 0) continue;
	
	nodep[n++] = create_node(i, symbol_count[i], NULL, NULL, NULL);
	
    }

    const int dummy = -1; // ダミー用のsymbol を用意しておく
    while (n >= 2) {
	Node *node1 = pop_min(&n, nodep);
	Node *node2 = pop_min(&n, nodep);
	
	// Create a new node
	// 選ばれた2つのノードを元に統合ノードを新規作成
    nodep[n++] = create_node(dummy, node1->count + node2->count, node1, node2, NULL);
    (*node1).upper = nodep[n-1]; // 親ノードにつなげる
    (*node2).upper = nodep[n-1]; // 親ノードにつなげる
	
    }

    // なぜ以下のコードで木を返したことになるか少し考えてみよう
    return (n==0)?NULL:nodep[0];
}



// Perform depth-first traversal of the tree
// 深さ優先で木を走査する
// depth = 0 からスタートする！　depth は index として使う！
void traverse_tree(const int depth, Node *np, char *bit_now, int flag)
{
    if (flag == 0 && np->left != NULL) {
        bit_now[depth] = '0';
        traverse_tree(depth + 1, np->left, bit_now, flag);
    } else if (flag == 0 && (np->upper)->right != np) {

        int cursor_count = 0;

        for (int i = 0; i < 20; i++) {
            np->bit[i] = bit_now[i];
            if (bit_now[i] != '\0') {
                cursor_count++;
            }
        }
        for (int i = 0; i < cursor_count; i++) {
            printf(" ");
        }


        if (np->symbol == '\n') {
            printf("%s : \\n", np->bit);
            cursor_count += 5;
        } else {
            printf("%s : %c", np->bit, np->symbol);
            cursor_count += 4;
        }

        for (int i = 0; i < cursor_count - 1; i++) {
            printf("\b");
        }
        int mode = 0;
        for (int i = 19; i >= 0; i--) {
            if (np->bit[i] == '\0') {
                continue;
            } else if (mode == 0) {
                if (np->bit[i] == '0') {
                    printf("\b\b┬");
                } else {
                    printf("\b\b└");
                    mode = 1;
                }
            } else {
                if (np->bit[i] == '0') {
                    printf("\b\b│"); 
                } else {
                    printf("\b\b "); 
                }
            }
        }
        printf("\n");

        bit_now[depth - 1] = '1';
        traverse_tree(depth, (np->upper)->right, bit_now, flag);
    } else if (flag == 0) {

        int cursor_count = 0;

        for (int i = 0; i < 20; i++) {
            np->bit[i] = bit_now[i];
            if (bit_now[i] != '\0') {
                cursor_count++;
            }
        }
        for (int i = 0; i < cursor_count; i++) {
            printf(" ");
        }

        if (np->symbol == '\n') {
            printf("%s : \\n", np->bit);
            cursor_count += 5;
        } else {
            printf("%s : %c", np->bit, np->symbol);
            cursor_count += 4;
        }

        for (int i = 0; i < cursor_count - 1; i++) {
            printf("\b");
        }
        int mode = 0;
        for (int i = 19; i >= 0; i--) {
            if (np->bit[i] == '\0') {
                continue;
            } else if (mode == 0) {
                if (np->bit[i] == '0') {
                    printf("\b\b┬");
                } else {
                    printf("\b\b└");
                    mode = 1;
                }
            } else {
                if (np->bit[i] == '0') {
                    printf("\b\b│"); 
                } else {
                    printf("\b\b ");
                }
            }
        }
        printf("\n");

        bit_now[depth - 1] = '\0';
        flag = 1;
        traverse_tree(depth - 1, np->upper, bit_now, flag);
    } else if (np->upper != NULL && (np->upper)->right != np) {
        bit_now[depth - 1] = '1';
        flag = 0;
        traverse_tree(depth, (np->upper)->right, bit_now, flag);
    } else if (np->upper != NULL) {
        bit_now[depth - 1] = '\0';
        traverse_tree(depth - 1, np->upper, bit_now, flag);
    } else {
        return;
    }

}

// この関数は外部 (main) で使用される (staticがついていない)
Node *encode(const char *filename)
{
    reset_count();
    count_symbols(filename);
    Node *root = build_tree();
    
    if (root == NULL){
	fprintf(stderr,"A tree has not been constructed.\n");
    }

    return root;
}
