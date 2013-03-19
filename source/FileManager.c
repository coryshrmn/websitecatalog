/*
 * FileManager.c
 * contains necesary information with
 * current and last session management
 *
 * Gon Kim
 * Cory Sherman
 */

#include "WebsiteCatalog.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


/*******************************************************************************
 * FileManager private prototypes
 *
 * static Website *_readWebsite(char *line);
 ******************************************************************************/

/*******************************************************************************
 * Reads a single Website from a line of text
 *
 *    Pre: line is a c-string
 *
 *   Post: line is modified.
 *         A Website is created and returned,
 *         Or NULL is returned if the line was invalid.
 *
 * Return: The new Website, or NULL
 ******************************************************************************/
static Website *_readWebsite(char *line);


/*******************************************************************************
 * FileManager function definitions
 ******************************************************************************/

/*******************************************************************************
 * Appends ".MOD" to a string.
 *
 *    Pre: fname is a null terminated c-string.
 *
 *   Post: A new c-string has been allocated and returned
 *
 * Return: The newly allocated string with fname + ".MOD"
 ******************************************************************************/
char *appendBackupExtension(const char *fname)
{
    char *output;
    int len;
    len = strlen(fname);
    output = malloc(len + 5);
    strncpy(output, fname, len);
    strcpy(output + len, ".BAK");
    return output;
}

/*******************************************************************************
 * Counts the number of lines in a file
 *
 *    Pre: fname is the name of a file
 *
 *   Post: The file has been read and the lines counted.
 *
 * Return: The number of lines in the file, or -1 if the file could not be read.
 ******************************************************************************/
int countLines(const char *fname)
{
    FILE *fin;
    int totalLines;
    char buff[1024];
    fin = fopen(fname, "r");
    if(!fin)
        return -1;

    for(totalLines = 0; fgets(buff, 1024, fin); ++totalLines);

    fclose(fin);

    return totalLines;
}


/*******************************************************************************
 * Reads a file and attempts to insert every valid Website into pHead.
 *
 *    Pre: fname is the name of a file
 *         pHead is a ListHead with a valid BST and Hash
 *
 *   Post: The file has been read and any valid Websites added
 *         An error is printed for every invalid website
 *
 * Return: true if the file was read, false if it could not be read
 ******************************************************************************/
bool readFile(const char *fname, ListHead *pHead)
{
    FILE *fin;
    char buff[1024];
    fin = fopen(fname, "r");
    if(!fin)
        return false;
    while(fgets(buff, 1024, fin))
    {
        Website *pWebsite = _readWebsite(buff);
        if(pWebsite)
            listInsert(pHead, pWebsite);
        else
            printf("Invalid line: %s", buff);
    }
    fclose(fin);
    return true;
}


/*******************************************************************************
 * Reads a single Website from a line of text
 *
 *    Pre: line is a c-string
 *
 *   Post: line is modified.
 *         A Website is created and returned,
 *         Or NULL is returned if the line was invalid.
 *
 * Return: The new Website, or NULL
 ******************************************************************************/
static Website *_readWebsite(char *line)
{
    char *fields[6];

    char *nextSemi;
    int i;
    nextSemi = line - 1;
    for(i = 0; i != 6; ++i)
    {
        fields[i] = nextSemi + 1;
        nextSemi = strchr(nextSemi + 1, ';');
        if(!nextSemi)
            return NULL;
        *nextSemi = '\0';
    }

    return websiteCreate(fields[0],         //url
                         fields[1],         //company name
                         atoi(fields[2]),   //daily page views 
                         atoi(fields[3]),   //traffic rank
                         atoi(fields[4]),   //back links
                         atoi(fields[5]));  //worth
}


/*******************************************************************************
 * Writes every Website in a QUEUE of Websites to a file
 *
 *    Pre: fname is the name of a file
 *         QUEUE is the queue of Websites
 *
 *   Post: The file has been written with every Website in the QUEUE's order.
 *         The QUEUE is destroyed.
 *
 * Return: true if the file was written, false if it could not be written
 ******************************************************************************/
bool writeFile(const char *fname, QUEUE *pQueue)
{
    Website *pWebsite;
    FILE *fout = fopen(fname, "w");
    if(!fout)
    {
        destroyQueue(pQueue);
        return false;
    }

    while(dequeue(pQueue, (void**)&pWebsite))
    {
       fprintf(fout, "%s;%s;%d;%d;%d;%d;\n", pWebsite->url,
                                       pWebsite->company,
                                       pWebsite->dailyPageViewThousands,
                                       pWebsite->rankTraffic,
                                       pWebsite->backLinkThousands,
                                       pWebsite->websiteWorthThousands);
    }
    fclose(fout);
    destroyQueue(pQueue);
    return true;
}

