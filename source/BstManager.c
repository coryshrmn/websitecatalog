/* BstManager.c
 * Group 6
 * BST Manager
 *
 * Cory Sherman
 */

#include "../header/WebsiteCatalog.h"
#include <string.h>
#include <stdio.h>

/*******************************************************************************
 * BstManager Private Prototypes
 ******************************************************************************/
static bool _bstInsert(BstNode **node, Website *pWebsite);
static BstNode *_createNode(Website *pWebsite);
static BstNode *_freeNode(BstNode *node);
static BstNode **_search(BstNode **node, const char *url);
static void _bstFreeAll(BstNode *node);
static void _printIndented(BstNode *node, int spaces);
static void _printInorder(BstNode *node);

/*******************************************************************************
 * Creates a BSTfor the specified ListHead
 *
 *    Pre: pList points to a list with no BST.
 *
 *   Post: The BST has been created and is pointed to by pList->pTree.
 *
 * Return: --
 ******************************************************************************/
void bstCreate(ListHead *pList)
{
    pList->pTree = NULL;
}


/*******************************************************************************
 * Attempts to insert Website into a BST.
 *
 *    Pre: pList points to a list which is initialized and has a valid BST.
 *         pWebsite points to a valid website.
 *
 *   Post: If the BST did not contain a website with the url, it is inserted.
 *         Otherwise, a warning is printed to the screen and the pointer is discarded.
 *
 * Return: true if the website was successfully inserted.
 *         false if the BST already contained an entry for the url.
 ******************************************************************************/
bool bstInsert(ListHead *pList, Website *pWebsite)
{
    return _bstInsert(&pList->pTree, pWebsite);
}

static bool _bstInsert(BstNode **node, Website *pWebsite)
{
    int cmp;
    if(!*node)
    {
        *node = _createNode(pWebsite);
        return true;
    }
    cmp = strcmp(pWebsite->url, (*node)->key);
    if(cmp == 0)
    {
        return false;
    }
    else
    {
        if(cmp > 0)
            node = &(*node)->right;
        else
            node = &(*node)->left;

        return _bstInsert(node, pWebsite);
    }
}

static BstNode *_createNode(Website *pWebsite)
{
    BstNode *output = validate(malloc(sizeof(BstNode)));
    output->left = NULL;
    output->right = NULL;
    output->key = pWebsite->url;
    output->site = pWebsite;
    return output;
}

static BstNode *_freeNode(BstNode *node)
{
    if(node)
    {
        free(node);
    }
    return NULL;
}


/*******************************************************************************
 * Searches a BST for the specified url.
 *
 *    Pre: pList points to a list which is initialized and has a valid hashtable.
 *         url is the url of the website
 *
 *   Post: Nothing is modified, the hashtable has been searched.
 *
 * Return: The website found, or NULL if one was not found.
 ******************************************************************************/
Website *bstSearch(ListHead *pList, const char *url)
{
    BstNode *foundNode = *_search(&pList->pTree, url);
    return foundNode ? foundNode->site : NULL;
}

static BstNode **_search(BstNode **node, const char *url)
{
    int cmp;
    if(!(*node))
        return node;
    cmp = strcmp(url, (*node)->key);
    if(cmp == 0)
        return node;

    if(cmp > 0)
        return _search(&(*node)->right, url);
    else
        return _search(&(*node)->left, url);
}


/*******************************************************************************
 * Searches a BST for the specified url, and removes the found website
 * from the BST.
 *
 *    Pre: pList points to a list which is initialized and has a valid BST.
 *         url is the url of the website
 *
 *   Post: If the BST contained the url, it is removed from the BST.
 *
 * Return: The website removed, or NULL if one was not found.
 ******************************************************************************/
Website *bstRemove(ListHead *pList, const char *url)
{
    bool hasLeft;
    bool hasRight;
    Website *output;
    BstNode **pFoundNode = _search(&pList->pTree, url);
    if(!*pFoundNode)
        return NULL;
    
    output = (*pFoundNode)->site;
    hasLeft = (*pFoundNode)->left != NULL;
    hasRight = (*pFoundNode)->right != NULL;

    //leaf node
    if(!hasLeft && !hasRight)
    {
        _freeNode(*pFoundNode);
        *pFoundNode = NULL;
    }
    //leaf-like node
    else if(hasLeft != hasRight)
    {
        BstNode *replacement = hasLeft ? (*pFoundNode)->left : (*pFoundNode)->right;
        _freeNode(*pFoundNode);
        *pFoundNode = replacement;
    }
    //two-children node
    else
    {
        //find highest on left subtree
        BstNode **highest;
        BstNode *oldHighest;
        for(highest = &(*pFoundNode)->left; (*highest)->right != NULL; highest = &(*highest)->right);
        oldHighest = *highest;
        (*pFoundNode)->key = oldHighest->key;
        (*pFoundNode)->site = oldHighest->site;

        *highest = oldHighest->left;
        free(oldHighest);
    }

    return output;
}


/*******************************************************************************
 * Frees all of the elements and nodes from the BST from the specified ListHead.
 *
 *    Pre: pList points to a list with a valid BST
 *
 *   Post: Every Website in the BST is freed
 *         The BST is freed.
 *         pList->pTree is set to NULL
 *
 * Return: --
 ******************************************************************************/
void bstFreeAll(ListHead *pList)
{
    _bstFreeAll(pList->pTree);
}

static void _bstFreeAll(BstNode *node)
{
    if(!node)
        return;
    _bstFreeAll(node->left);
    _bstFreeAll(node->right);
    websiteFree(node->site);
    _freeNode(node);
}

/*******************************************************************************
 * Creates a QUEUE of the BST's elements in breadth first order.
 *
 *    Pre: pList points to a list with a valid BST
 *
 *   Post: The QUEUE is created and returned.
 *
 * Return: A QUEUE containing every Website* in breadth first order.
 ******************************************************************************/
QUEUE *bstTraverseBreadth(ListHead *pList)
{
    QUEUE *output, *tempQueue;
    BstNode *node;

    output = createQueue();
    tempQueue = createQueue();
    node = pList->pTree;

    while(node)
    {
        enqueue(output, node->site);
        if(node->left)
            enqueue(tempQueue, node->left);
        if(node->right)
            enqueue(tempQueue, node->right);

        if(emptyQueue(tempQueue))
            node = NULL;
        else
            dequeue(tempQueue, (void**)&node);
    }

    destroyQueue(tempQueue);
    return output;
}

/*******************************************************************************
 * Prints a BST formatted with indentation.
 *
 *    Pre: pList points to a list with a valid BST
 *
 *   Post: The BST has been printed to stdout.
 *
 * Return: --
 ******************************************************************************/
void bstPrintIndented(ListHead *pList)
{
    _printIndented(pList->pTree, 0);
}

static void _printIndented(BstNode *node, int spaces)
{
    int i;
    if(!node)
        return;
    
    _printIndented(node->right, spaces + 4);
    for(i = 0; i != spaces; ++i)
        printf(" ");
    websitePrint(node->site);
    _printIndented(node->left, spaces + 4);
}

/*******************************************************************************
 * Prints a BST inorder.
 *
 *    Pre: pList points to a list with a valid BST
 *
 *   Post: The BST has been printed to stdout.
 *
 * Return: --
 ******************************************************************************/
void bstPrintInorder(ListHead *pList)
{
    _printInorder(pList->pTree);
}

static void _printInorder(BstNode *node)
{
    if(!node)
        return;
    _printInorder(node->left);
    websitePrint(node->site);
    _printInorder(node->right);
}
