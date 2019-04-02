#include <stdio.h>
#include <stdlib.h>

#include "shortcut.h"
#include "test_avl.h"
#include "avl_tree.h"
#include "node.h"

// Node Tests
TEST(create_node)
{
	Node node = create_node(1);
	ASSERT_FALSE(node == 0, "Node has to be created");
}

TEST(simple_height)
{
	Node node = create_node(1);
	ASSERT_EQUALS(1, get_height(node));
}

TEST(set_height)
{
	Node node = create_node(1);
	set_height(node, 5);
	ASSERT_EQUALS(5, get_height(node));
}

TEST(get_key)
{
	int key = 88;
	Node node = create_node(key);
	ASSERT_EQUALS(key, get_key(node));
}

TEST(left_node)
{
	Node node1 = create_node(1);
	Node node2 = create_node(2);
	set_left(node2, node1);

	Node left_node = get_left(node2);
	ASSERT_EQUALS(1, get_key(left_node));
}

TEST(right_node)
{
	Node node1 = create_node(1);
	Node node2 = create_node(2);
	set_right(node1, node2);

	Node right_node = get_right(node1);
	ASSERT_EQUALS(2, get_key(right_node));
}

// Basic Bin Tree Tests
TEST(get_max)
{
	int smaller = 5;
	int bigger = 6;
	ASSERT_EQUALS(bigger, max(smaller, bigger));
	ASSERT_EQUALS(bigger, max(bigger, smaller));
}

int count_nodes(Node node, int key);
TEST(no_duplicates)
{
	Node root = create_node(20);
	unbalanced_insert(root, 10);
	unbalanced_insert(root, 30);
	unbalanced_insert(root, 10);
	unbalanced_insert(root, 30);
	unbalanced_insert(root, 20);

	ASSERT_EQUALS(1, count_nodes(root, 10));
	ASSERT_EQUALS(1, count_nodes(root, 20));
	ASSERT_EQUALS(1, count_nodes(root, 30));
}

int check_node(Node node, int key, int height, int left_key, int right_key);
TEST(unbalanced_insert)
{
    Node root = create_node(20);
    unbalanced_insert(root, 10);
    unbalanced_insert(root, 30);
    unbalanced_insert(root, 15);
    unbalanced_insert(root, 25);
    unbalanced_insert(root, 35);
    unbalanced_insert(root, 5);
    unbalanced_insert(root, 9);

	ASSERT_EQUALS(1, check_node(root, 9, 1, 0, 0));
	ASSERT_EQUALS(1, check_node(root, 5, 1, 0, 9));
	ASSERT_EQUALS(1, check_node(root, 15, 1, 0, 0));
	ASSERT_EQUALS(1, check_node(root, 10, 1, 5, 15));
	ASSERT_EQUALS(1, check_node(root, 25, 1, 0, 0));
	ASSERT_EQUALS(1, check_node(root, 35, 1, 0, 0));
	ASSERT_EQUALS(1, check_node(root, 30, 1, 25, 35));
	ASSERT_EQUALS(1, check_node(root, 20, 1, 10, 30));
}

// AVL Tree Tests
TEST(get_balance)
{
	Node left = create_node(1);
	Node root = create_node(2);
	Node right = create_node(3);
	Node right2 = create_node(4);
	set_left(root, left);
	set_right(root, right);
	set_right(right, right2);
	set_height(right, 2);

	ASSERT_EQUALS(-1, get_balance(root));
}

TEST(rotate_left)
{
	Node root = create_node(30);
	Node left = create_node(20);
	Node right = create_node(40);
	Node rl = create_node(35);
	Node rr = create_node(50);
	Node rrr = create_node(60);
	set_left(root, left);
	set_right(root, right);
	set_left(right, rl);
	set_right(right, rr);
	set_right(rr, rrr);
	set_height(root, 4);
	set_height(right, 3);
	set_height(left, 1);
	set_height(rl, 1);
	set_height(rr, 2);
	set_height(rrr, 1);

	Node new_root = rotate_left(root);
	ASSERT_EQUALS(40, get_key(new_root));
	ASSERT_EQUALS(1, get_height(left));
	ASSERT_EQUALS(1, get_height(rl));
	ASSERT_EQUALS(2, get_height(root));
	ASSERT_EQUALS(1, get_height(rrr));
	ASSERT_EQUALS(2, get_height(rr));
	ASSERT_EQUALS(3, get_height(right));
}

TEST(rotate_right)
{
	Node root = create_node(30);
	Node left = create_node(20);
	Node right = create_node(40);
	Node lr = create_node(25);
	Node ll = create_node(10);
	Node lll = create_node(5);
	set_left(root, left);
	set_right(root, right);
	set_left(left, ll);
	set_right(left, lr);
	set_left(ll, lll);
	set_height(root, 4);
	set_height(right, 1);
	set_height(left, 3);
	set_height(ll, 2);
	set_height(lr, 1);
	set_height(lll, 1);

	Node new_root = rotate_right(root);
	ASSERT_EQUALS(20, get_key(new_root));
	ASSERT_EQUALS(1, get_height(lll));
	ASSERT_EQUALS(2, get_height(ll));
	ASSERT_EQUALS(1, get_height(lr));
	ASSERT_EQUALS(1, get_height(right));
	ASSERT_EQUALS(2, get_height(root));
	ASSERT_EQUALS(3, get_height(left));
}

TEST(insert_simple)
{
	Node root = insert(0, 20);
	root = insert(root, 10);
	root = insert(root, 30);

	ASSERT_EQUALS(20, get_key(root));
	ASSERT_EQUALS(10, get_key(get_left(root)));
	ASSERT_EQUALS(30, get_key(get_right(root)));
	ASSERT_EQUALS(2, get_height(root));
	ASSERT_EQUALS(1, get_height(get_left(root)));
	ASSERT_EQUALS(1, get_height(get_right(root)));
	ASSERT_EQUALS(0, get_balance(root));
}

TEST(insert_complex)
{
	Node root = insert(0, 10);
	root = insert(root, 20);
	root = insert(root, 30);
	root = insert(root, 40);
	root = insert(root, 50);
	root = insert(root, 25);
	root = insert(root, 26);
	root = insert(root, 27);
	root = insert(root, 39);
	root = insert(root, 35);
	root = insert(root, 10);
	root = insert(root, 60);
	root = insert(root, 5);
	root = insert(root, 1);
	root = insert(root, 65);

	ASSERT_EQUALS(30, get_key(root));

	ASSERT_EQUALS(1, check_node(root, 30, 4, 20, 40));
	ASSERT_EQUALS(1, check_node(root, 20, 3, 5, 26));
	ASSERT_EQUALS(1, check_node(root, 5, 2, 1, 10));
	ASSERT_EQUALS(1, check_node(root, 26, 2, 25, 27));
	ASSERT_EQUALS(1, check_node(root, 40, 3, 39, 60));
	ASSERT_EQUALS(1, check_node(root, 39, 2, 35, 0));
	ASSERT_EQUALS(1, check_node(root, 60, 2, 50, 65));

	ASSERT_EQUALS(0, get_balance(root));
}

int check_node(Node node, int key, int height, int left_key, int right_key)
{
	if (node == 0)
	{
		return 0;
	}
	if (get_key(node) == key)
	{
		if (get_height(node) != height)
		{
			return -1;
		}
		Node left_node = get_left(node);
		Node right_node = get_right(node);
		if ((left_node == 0 && left_key != 0) || (get_key(left_node) != left_key))
		{
			return -1;
		}
		if ((right_node == 0 && right_key != 0) || (get_key(right_node) != right_key))
		{
			return -1;
		}
		return 1;
	}
	else
	{
		int res_l = check_node(get_left(node), key, height, left_key, right_key);
		if (res_l == 0)
		{
			return check_node(get_right(node), key, height, left_key, right_key);
		}
		return res_l;
	}
}

int count_nodes(Node node, int key)
{
	int occurances = 0;
	if (node == 0)
	{
		return 0;
	}
	if (get_left(node) != 0)
	{
		occurances += count_nodes(get_left(node), key);
	}
	if (get_right(node) != 0)
	{
		occurances += count_nodes(get_right(node), key);
	}
	if (get_key(node) == key)
	{
		occurances++;
	}
	return occurances;
}
