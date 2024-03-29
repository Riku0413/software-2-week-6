# software-2-week-6

### このリポジトリについて

- 「工学部電子情報工学科 2022年度2Aセメスター講義 ソフトウェアⅡ 第6回」で作成したプログラム
- C言語により、ハフマン符号化とその結果の可視化を実装

### 課題1

#### - 実行方法 -

まず以下のコードによりディレクトリを移動する.
```
cd ./huffman0
```

続いて次のようにmakeする.
```
make
```

最後に以下のコードにより実行する.
```
./bin/huffman0 news.txt
```

すると次のような出力となる.
```
┬┬┬┬┬00000 : m
││││└00001 : u
│││└┬┬000100 : w
│││ │└000101 : b
│││ └┬┬0001100 : \n
│││  │└┬00011010 : x
│││  │ └00011011 : .
│││  └000111 : y
││└001 : e
│└┬┬0100 : s
│ │└0101 : r
│ └┬┬01100 : c
│  │└01101 : h
│  └0111 : o
└┬┬┬1000 : i
 ││└1001 : n
 │└┬1010 : a
 │ └┬10110 : d
 │  └┬101110 : g
 │   └101111 : f
 └┬┬┬11000 : l
  ││└┬┬1100100 : v
  ││ │└┬┬110010100 : '
  ││ │ │└┬1100101010 : j
  ││ │ │ └┬11001010110 : z
  ││ │ │  └11001010111 : q
  ││ │ └11001011 : k
  ││ └110011 : p
  │└1101 : t
  └111 :  
```

#### - プログラムのポイント -

まず以下のようにNode構造体に,親ノードへのポインタとハフマン符号の符号列を新たなメンバとして追加した.
```
typedef struct node Node;

struct node{
    int symbol;
    int count;
    Node *left;
    Node *right;
    Node *upper; // 親ノードへのポインタ
    char bit[20]; // 01の符号列を追加
};
```

続いて,深さ優先の二分木探索を効率的に進めるためにtraverse_tree()にint型の引数flagを追加した.
```
void traverse_tree(const int depth, Node *root, char *bit_now, int flag);
```

次にbuild_tree()関数内で,各ノードに親ノードへのポインタを渡すコードを追加した.
```
(*node1).upper = nodep[n-1]; // 親ノードにつなげる
(*node2).upper = nodep[n-1]; // 親ノードにつなげる
```

最後にtraverse_tree()関数内では以下の4つの機能を実装した.

1. flagと現在のノードの従属関係に応じて次のノードに移動
2. ハフマン符号の作成
3. 符号列とそれに対応する文字をプリント
4. '\b'を使いながらツリー構造を表示
