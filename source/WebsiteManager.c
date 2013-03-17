/* WebsiteManager.c
 * Group 6
 * Website Manager
 *
 * Cory Sherman
 */

#include "WebsiteCatalog.h"
#include <string.h>
#include <stdio.h>

/*******************************************************************************
 * WebsiteManager Private Prototypes
 ******************************************************************************/
//none


/*******************************************************************************
 * Allocates a new Website. Copies url and company into newly allocated strings.
 * All other fields are copied by value.
 *
 *    Pre: url and company are valid strings, the other parameters are correct.
 *
 *   Post: A new Website has been allocated,
 *         and initialized with the specified data.
 *
 * Return: A pointer to the new Website.
 ******************************************************************************/
Website *websiteCreate(const char *url, const char *company, int dailyPageViewThousands, int rankTraffic, int backLinkThousands, int worthThousands)
{
    Website *output = validate(malloc(sizeof(Website)));
    output->url = validate(malloc(strlen(url) + 1));
    output->company = validate(malloc(strlen(company) + 1));
    strcpyToLower(output->url, url);
    strcpy(output->company, company);
    output->dailyPageViewThousands = dailyPageViewThousands;
    output->rankTraffic = rankTraffic;
    output->backLinkThousands = backLinkThousands;
    output->websiteWorthThousands = worthThousands;
    return output;
}

/*******************************************************************************
 * Frees a Website, including its dynamically allocated url and company name.
 *
 *    Pre: pSite points to a valid Website.
 *
 *   Post: The Website, its url, and its company name are freed.
 *
 * Return: NULL
 ******************************************************************************/
Website *websiteFree(Website *pSite)
{
    if(!pSite)
        return NULL;
    if(pSite->url)
        free(pSite->url);
    if(pSite->company)
        free(pSite->company);
    free(pSite);
    return NULL;
}

/*******************************************************************************
 * Prints a Website's url, followed by a newline.
 *
 *    Pre: pSite points to a valid Website.
 *
 *   Post: The Website is printed.
 *
 * Return: --
 ******************************************************************************/
void websitePrint(Website *pSite)
{
    printf("%s\n", pSite && pSite->url ? pSite->url : "NULL");
}

/*******************************************************************************
 * Prints a Website's url and info, on separate lines, ending with a newline
 *
 *    Pre: pSite points to a valid Website.
 *
 *   Post: The Website is printed.
 *
 * Return: --
 ******************************************************************************/
void websitePrintFull(Website *pSite)
{
    if(!pSite)
    {
        printf("NULL\n");
        return;
    }

    printf("%s\n", pSite->url ? pSite->url : "NULL");

    printf("    Company:         \"%s\"\n", pSite->company ? pSite->company : "NULL");
    
    printf("    Daily Pageviews: ");
    printIntCommas(pSite->dailyPageViewThousands);
    printf(",000\n");
    
    printf("    Traffic Rank:    ");
    printIntCommas(pSite->rankTraffic);
    printf("\n");
    
    printf("    Backlinks:       ");
    printIntCommas(pSite->backLinkThousands);
    printf(",000\n");
    
    printf("    Worth:           $");
    printIntCommas(pSite->websiteWorthThousands);
    printf(",000\n");
}
