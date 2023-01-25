#include <stdio.h>
#include <stdlib.h>
#include "encode.h"

int main(int argc, char **argv)
{
    if (argc != 2) {
	fprintf(stderr, "usage: %s <filename>\n",argv[0]);
	exit(1);
    }
    
    Node *root = encode(argv[1]);

    // 現在地点における符号列
    char bit_now[20];
    for (int i = 0; i < 20; i++) {
        bit_now[i] = '\0';
    }

    int flag = 0;
    traverse_tree(0, root, bit_now, flag);
    
    return EXIT_SUCCESS;
}
