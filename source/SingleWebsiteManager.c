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
    
	usLine = readOneLine(fPtr);
    
	if (NULL == usLine) { /* reached: EOF of input file */
		return NULL;
	} else {
		sLine = usLine;
	}
    
	// set: fields in `curWebsite`
<<<<<<< HEAD
	sUrl = readSingleField(INPUT_TYPE_URL, &usLine);
	sCompany = readSingleField(INPUT_TYPE_URL, &usLine);
	
    sInput = readSingleField(INPUT_TYPE_URL, &usLine);
    sDailyPageView = atoi(sInput);
	free(sInput);
  
	sInput = readSingleField(INPUT_TYPE_URL, &usLine);
    sDailyPageView = atoi(sInput);
	free(sInput);
    
    sInput = readSingleField(INPUT_TYPE_URL, &usLine);
	sBackLink = atoi(sInput);
	free(sInput);
	
    sInput = readSingleField(INPUT_TYPE_URL, &usLine);
    sWebsiteWorth = atoi(sInput);
	free(sInput);
    
=======
    //TODO -read the fields correctly
    //     -do not create memory leaks
    //     -pass ints into websiteCreate for the int fields.
	sUrl = (char*) readSingleField(INPUT_TYPE_URL, &usLine);
	sCompany = (char*) readSingleField(INPUT_TYPE_URL, &usLine);
	sDailyPageView = (char*) readSingleField(INPUT_TYPE_URL, &usLine);
	sRankTraffic = (char*) readSingleField(INPUT_TYPE_URL, &usLine);
	sBackLink = (char*) readSingleField(INPUT_TYPE_URL, &usLine);
	sWebsiteWorth = (char*) readSingleField(INPUT_TYPE_URL, &usLine);

>>>>>>> bec9cffd7bdd2d9480d36ef2def067325a7dc40c
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
