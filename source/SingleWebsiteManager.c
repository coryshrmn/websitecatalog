/*
 * SingleWebsiteManager.c
 * contains functions to
 * parse information from the file pointer
 *
 * Developer:           Gon Kim (imgonkim@gmail.com)
 * Initial Commit:      03162013_215304
 * Last Major Update:   03162013_215304
 *
 */
#include "../header/WebsiteCatalog.h"
#include "../header/SingleWebsiteManager.h"

/*
 * getSingleWebsite
 * parses information from the file pointer:
 *
 *  PRE:    fPtr (file pointer; readonly; from input file stream)
 *
 *  POST:   All fields are completedly parsed from the input file stream
 *
 *  RETURN:  Website (fields are completedly parsed)
 *
 */
Website* getSingleWebsite(FILE* fPtr) {
    Website* curWebsite = NULL; // current `struct Website`
    char *sUrl = NULL;              // safe url
	char *sCompany = NULL;          // safe company name
    int sDailyPageView = 0;    // safe daily page view
	int sRankTraffic = 0;      // safe traffic rank
	int sBackLink = 0;         // safe backlink
	int sWebsiteWorth = 0;     // safe website worth
	/*
	 * `char *usLine;`
	 * unsafe single line read
	 * (may not represent original value)
	 */
	char *usLine = NULL;
	char *sLine = NULL;              // safe single line read
    char *sInput = NULL;
    char *sField = NULL;
    
	usLine = readOneLine(fPtr);
    
	if (NULL == usLine) { /* reached: EOF of input file */
		return NULL;
	} else {
		sLine = usLine; // save sLine pointer
	}
    
    
    
    
    
    
    

    
    
	// set: fields in `curWebsite`
	sUrl = readFirstField(INPUT_TYPE_URL, &usLine);
    D("_%s_: sUrl\n", sUrl);

    
    sCompany = readSingleField(INPUT_TYPE_COMPANY);
    D("_%s_: sCompany\n", sCompany);
    

    sInput = readSingleField(INPUT_TYPE_DAILY_PAGE_VIEW);
    sDailyPageView = atoi(sInput);
	D("_%d_: sDailyPageView\n", sDailyPageView);


	sInput = readSingleField(INPUT_TYPE_RANK_TRAFFIC);
    sRankTraffic = atoi(sInput);
	D("_%d_: sRankTraffic\n", sRankTraffic);


    sInput = readSingleField(INPUT_TYPE_BACK_LINK);
	sBackLink = atoi(sInput);
   	D("_%d_: sBackLink\n", sBackLink);


    sInput = readSingleField(INPUT_TYPE_WEBSITE_WORTH);
    sWebsiteWorth = atoi(sInput);
   	D("_%d_: sWebsiteWorth\n", sWebsiteWorth);

    DD("_%s_: sUrl\n", sUrl);
    DD("_%s_: sCompany\n", sCompany);
	DD("_%d_: sDailyPageView\n", sDailyPageView);
	DD("_%d_: sRankTraffic\n", sRankTraffic);
   	DD("_%d_: sBackLink\n", sBackLink);
   	DD("_%d_: sWebsiteWorth\n", sWebsiteWorth);
    
    printf(BR);
    curWebsite = websiteCreate(sUrl, sCompany, sDailyPageView, sRankTraffic, sBackLink, sWebsiteWorth);
    
    //	while (bContinue && NULL != sUrl && NULL != sCompany
    //           && NULL != sDailyPageView && NULL != sRankTraffic
    //           && NULL != sBackLink && NULL != sWebsiteWorth) {
    //		curWebsite->url = sUrl;
    //
    //		curWebsite->company = sCompany;
    //		curWebsite->dailyPageViewThousands = atoi(sDailyPageView);
    //		curWebsite->rankTraffic = atoi(sRankTraffic);
    //		curWebsite->backLinkThousands = atoi(sBackLink);
    //		curWebsite->websiteWorthThousands = atoi(sWebsiteWorth);
    //
    //        // TODO: create free function for entire Website struct
    //        free(sDailyPageView);
    //		free(sRankTraffic);
    //		free(sBackLink);
    //		free(sWebsiteWorth);
    //		bContinue = false;
    //	}
    //    
    //	free(sLine);

	return curWebsite;
}
