#include <stdio.h>
#include "test_avl_tree.h"
#include "../heder/avl_tree.h"
#include "../heder/private_avl_tree_ip.h"
#include "../../clib/heder/clib.h"

void error(tree_node_t* root)
{
    tree_node_t* left = root->left_node, *right = root->right_node;
    printf("\t\t\t\t[DEBUG_INF]is not valid tree\n");

    int pv = *(GET_ATK(int, root));
    int lv = *(GET_ATK(int, left));
    int rv = *(GET_ATK(int, right));

    printf("\t\t\t\t  %d\n", pv);
          
    printf("\t\t\t\t%d  %d\n", lv, rv);
    exit(-1);
}



void 
test_main(avl_tree_t* tree, int size)
{
    for (int i = 0; i < size; ++i)
    {
        int* v = make_int(rand() % 10000);
        printf("insert { %d } to avl tree\t\ti = %d\n", *v, i + 1);

        insert_to_avl_tree(tree, v);        
    }
    
    test_tree(tree, tree->root);
    test_balance_tree(tree);
}

void 
test_balance_tree(tree_t* tree)
{
    balance_t b = balance_check_to_avl_tree(tree);


    if (b == -1 || b == 1 || b == 0)
        return;
    
    printf("\t\t\t\t[DEBUG_INF]disbalance tree = %d\n", b);
    exit(-1);
}

void 
test_tree(avl_tree_t* tree, avl_tree_node_t* root)
{
   if (root->left_node != NULL && root->right_node != NULL)
   {
     if (!tree->is_less(root->left_node->data, root->right_node->data))
        error(root);

      test_tree(tree, root->left_node);
      test_tree(tree, root->right_node);
   }
   else if (root->left_node != NULL && root->right_node == NULL)
   {
     if (!tree->is_more(root->data, root->left_node->data))
        error(root);

      test_tree(tree, root->left_node);
   }
   else if (root->left_node == NULL && root->right_node != NULL)
   {
     if (tree->is_more(root->data, root->right_node->data))
        error(root);

      test_tree(tree, root->right_node);
    }
}
