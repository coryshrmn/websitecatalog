/* InsertManager.c
 * Group 6
 * Insert Manager
 *
 * Cory Sherman
 */

#include "WebsiteCatalog.h"

/*******************************************************************************
 * Insert Manager Private Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Attempts to insert a Website into a hash table and BST.
 *
 *    Pre: pList points to a list with a hash table and BST.
 *         pWebsite is initialized.
 *
 *   Post: The Website has been inserted or destroyed.
 *
 * Return: true iff the Website was successfully inserted.
 ******************************************************************************/
bool listInsert(ListHead *pList, Website *pWebsite)
{
    if(hashInsert(pList, pWebsite))
    {
        bstInsert(pList, pWebsite);
        return true;
    }
    else
    {
        websiteFree(pWebsite);
        return false;
    }
}

/*******************************************************************************
 * Attempts to remove a Website from a hash table and BST.
 *
 *    Pre: pList points to a list with a hash table and BST.
 *         url is the url of the Website to remove.
 *
 *   Post: The hash table and BST do not contain a website with that URL.
 *         If they did, it has been destroyed.
 *
 * Return: true if the Website was successfully removed,
 *         false if it was not found.
 ******************************************************************************/
bool listRemove(ListHead *pList, const char *url)
{
    Website *pWebsite;
    pWebsite = hashRemove(pList, url);
    if(pWebsite)
    {
        bstRemove(pList, url);
        websiteFree(pWebsite);
        return true;
    }
    else
    {
        return false;
    }
}

