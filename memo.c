#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
  // int count;
  // int count2;
  char bit[30];
} Node;

// typedef struct node Node;

// struct node{
//     int symbol;
//     int count;
//     Node *left;
//     Node *right;
//     Node *upper; // 🔥上へのポインタ
//     char *bit[100]; // 🔥01の並び列を追加！
// };

int main() {
  printf("%lu\n", sizeof(Node));
  // Node *abc = (Node *)malloc(sizeof(Node));
  // (abc->bit)[0] = 'k';
  // (abc->bit)[1] = 'l';
  // printf("%s\n", *(abc->bit));
  printf("---\n");
  printf("│\n");
  printf("├───\n");
  printf("└┬┬┬───\n"); 
  printf(" ││└─────\n"); 
  printf(" │└─────\n"); 
  printf(" └─────\n"); 
  printf("\n");

  printf("1234567");
  printf("\b\b\b");
  printf("x");
  printf("\b\by");
  printf("\nabc\n");

  // int a = 'K';
  // int c = '└';
  // printf("%d\n", a);
  // printf("%d\n", c);

  printf("\n\n");


        // //
        // char keisen[20];
        // int mode = 0;
        // for (int i = 19; i >= 0; i++) {
        //     if (np->bit[i] == '\0') {
        //         keisen[i] = '\0';
        //     } else if (mode == 0) {
        //         if (np->bit[i] == '0') {
        //             keisen[i] = '┬';
        //         } else {
        //             keisen[i] = '└';
        //             mode = 1;
        //         }
        //     } else {
        //         if (np->bit[i] == '0') {
        //             keisen[i] = '│';
        //         } else {
        //             keisen[i] = ' ';
        //         }
        //     }
        // }
        // printf("%s", keisen);
        // //


  return 0;
}