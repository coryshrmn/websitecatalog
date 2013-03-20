/* HashManager.c
 * Group 6
 * Hash Manager
 *
 * Chris Huang
 * Cory Sherman
 */

#include "WebsiteCatalog.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static const int DEFAULT_BUCKET_SIZE = 3;

/*******************************************************************************
 * HashManager Private Prototypes
 ******************************************************************************/
static int _hashIndex(ListHead *pList, const char *url);
static int _primeAtLeast(int val);
static bool _isPrime(int val);
static int _hashString(const char *val);


/*******************************************************************************
 * Creates a hashtable for the specified ListHead
 *
 *    Pre: pList points to a list with no hashtable.
 *         pList->bucketSize is initialized.
 *         numLines is not negative.
 *
 *   Post: The hashtable has been created and is pointed to by pList->pHash.
 *         Its length is the first prime number at least numLines * 2
 *         Its length is stored to pList->aryLength;
 *
 * Return: --
 ******************************************************************************/
void hashCreate(ListHead *pList, int numLines)
{
    pList->arySize = _primeAtLeast(numLines * 2);
    pList->bucketSize = DEFAULT_BUCKET_SIZE;
    pList->pHash = validate(calloc(pList->arySize * pList->bucketSize, sizeof(HashNode)));
}


static int _primeAtLeast(int val)
{
    if(val < 0)
        val = -val;
    
    if(val <= 2)
        return 2;
    
    //if val is even
    if((val & 1) == 0)
        val++;
    
    while(!_isPrime(val))
    {
        val += 2;
    }
    return val;
}

static bool _isPrime(int val)
{
    int i;
    int endi;
    if(val < 0)
        val = -val;
    if(val < 2)
        return false;
    
    if(val == 2)
        return true;
    
    //if val is even
    if((val & 1) == 0)
        return false;
    
    //could be optimized to endi = sqrt(val)
    endi = val / 2;
    for(i = 3; i < endi; i += 2)
    {
        if(val % i == 0)
            return false;
    }
    return true;
}

/*******************************************************************************
 * Attempts to insert Website into a hashtable.
 *
 *    Pre: pList points to a list which is initialized and has a valid hashtable.
 *         pWebsite points to a valid website.
 *
 *   Post: If the hashtable has room for the website and does not contain
 *         an entry with the same URL, it is inserted.
 *         Otherwise, a warning is printed to the screen and the pointer is discarded.
 *
 * Return: true if the website was successfully inserted.
 *         false if the hashtable already contained an entry for the url,
 *               or if the bucket was full.
 ******************************************************************************/
bool hashInsert(ListHead *pList, Website *pWebsite)
{
    int i;
    int index;


    if(!hashSearch(pList, pWebsite->url))
    {
        index = ((unsigned int)_hashString(pWebsite->url) % (unsigned int)pList->arySize) * pList->bucketSize;
        
        for(i = 0; i < pList->bucketSize; i++)
        {
            if(!pList->pHash[index+i].key)
            {
                pList->pHash[index+i].key = pWebsite->url;
                pList->pHash[index+i].site = pWebsite;
                return true;
            }
        }
        printf("Bucket full, unable to insert!\n");
        return false;
    }
    printf("Website \"%s\" already exsits\n", pWebsite->url);
    return false;
}

/*******************************************************************************
 * Searches a hashtable for the specified url.
 *
 *    Pre: pList points to a list which is initialized and has a valid hashtable.
 *         url is the url of the website
 *
 *   Post: Nothing is modified, the hashtable has been searched.
 *
 * Return: The website found, or NULL if one was not found.
 * ******************************************************************************/
Website *hashSearch(ListHead *pList, const char *url)
{
    int bucket = _hashIndex(pList, url);
    return bucket == -1 ? NULL : pList->pHash[bucket].site;
}

static int _hashIndex(ListHead *pList, const char *url)
{
    int i;
    int index;

    index = ((unsigned int)_hashString(url) % (unsigned int)pList->arySize) * pList->bucketSize;
	if(pList->pHash[index].key)
	{
		for(i = 0; i < pList->bucketSize; i++)
		{
			if(pList->pHash[index + i].key)
			{
				if(!strcmp(pList->pHash[index + i].key, url))
					return index + i;
			}
		}
	}

    return -1;
}



/*******************************************************************************
 * Searches a hashtable for the specified url, and removes the found website
 * from the hashtable.
 *
 *    Pre: pList points to a list which is initialized and has a valid hashtable.
 *         url is the url of the website
 *
 *   Post: If the hashtable contained the url, it is removed from the hashtable.
 *
 * Return: The website removed, or NULL if one was not found.
 ******************************************************************************/
Website *hashRemove(ListHead *pList, const char *url)
{
    int bucketIndex = _hashIndex(pList, url);
    int bucketWhole;
    int bucketPart;
    Website *output;
    if(bucketIndex == -1)
        return NULL;

    output = pList->pHash[bucketIndex].site;
    
    bucketPart = bucketIndex % pList->bucketSize;
    bucketWhole = bucketIndex - bucketPart;

    for(; bucketPart + 1 < pList->bucketSize; ++bucketPart)
    {
        int bucket = bucketWhole + bucketPart;

        pList->pHash[bucket].key = pList->pHash[bucket + 1].key;
        pList->pHash[bucket].site = pList->pHash[bucket + 1].site;
    }

    pList->pHash[bucketWhole + bucketPart].key = NULL;
    pList->pHash[bucketWhole + bucketPart].site = NULL;

    return output;
}

/*******************************************************************************
 * Frees a hashtable from the specified ListHead
 *
 *    Pre: pList points to a list with a valid hashtable
 *
 *   Post: The hashtable is freed.
 *         pList->arySize is set to 0
 *         pList->pHash is set to NULL
 *
 * Return: --
 ******************************************************************************/
void hashFree(ListHead *pList)
{
	free(pList->pHash);
	pList->arySize = 0;
	pList->pHash = NULL;


	return;
}

/*******************************************************************************
 * Prints the efficiency of a hashtable.
 *
 *    Pre: pList points to a list with a valid hashtable
 *
 *   Post: The efficiency has been calculated and printed.
 *
 * Return: --
 ******************************************************************************/
void printEfficiency(ListHead *pList)
{
	double nodesFilled = 0;
	double loadFactor;
	double arySize;
	int i;
	int j;
	int collision = 0;
    //longestBucket will be 1 even if the hash table is empty
	int longestBucket = 1;

	for(i = 0; i < (pList->arySize * pList->bucketSize); i+=pList->bucketSize)
	{
		if(pList->pHash[i].key)
		{
			nodesFilled++;
			for(j = 1; j < pList->bucketSize; j++)
			{
				if(pList->pHash[i+j].key)
					collision++;
			}
			if(longestBucket < j)
				longestBucket = j;
		}
	}
	longestBucket++;
	arySize = pList->arySize;
	loadFactor = (nodesFilled / arySize) * 100;
	printf("The load factor is %.2f%%\n", loadFactor);
	printf("Number of collisions: %d\n", collision);
	printf("Longest Bucket: %d\n", longestBucket - 1);

	return;
}

/*******************************************************************************
 * Lists the contents of a hashtable's buckets.
 *
 *    Pre: pList points to a list with a valid hashtable
 *
 *   Post: The data has been printed to stdout.
 *
 * Return: --
 ******************************************************************************/
void hashPrintList(ListHead *pList)
{
    int bucket;
    int elem;
    for(bucket = 0; bucket < pList->arySize; ++bucket)
    {
        HashNode *bucketOffset = &pList->pHash[bucket * pList->bucketSize];
        printf("bucket (%d)\n", bucket);
        for(elem = 0; elem < pList->bucketSize; ++elem)
        {
            if(bucketOffset[elem].site)
            {
                printf("    ");
                websitePrint(bucketOffset[elem].site);
            }
        }
    }
}

static int _hashString(const char *key)
{
    int h = 0;
    const char *w;

    for(w = key; *w != '\0'; w++)
    {
        h = 31*h + *w;
    }

    return h;
}

