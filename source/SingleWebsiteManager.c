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
	char *sUrl;                 // safe url           
	char *sCompany;             // safe company name
	char *sDailyPageView;       // safe daily page view
	char *sRankTraffic;         // safe traffic rank
	char *sBackLink;            // safe backlink
	char *sWebsiteWorth;        // safe website worth
	bool bContinue = true;      // boolean value for conitnuing the file read
	/*
	 * `char *usLine;`
	 * unsafe single line read
	 * (may not represent original value)
	 */
	char *usLine = NULL;
	char *sLine = NULL;              // safe single line read
    
	MALLOC(curWebsite);
	usLine = _readOneLine(fPtr);
    
	if (NULL == usLine) { /* reached: EOF of input file */
		return NULL;
	} else {
		sLine = usLine;
	}
    
	// set: fields in `curWebsite`
	sUrl = (char*) _readSingleField(INPUT_TYPE_URL, &usLine);
	sCompany = (char*) _readSingleField(INPUT_TYPE_URL, &usLine);
	sDailyPageView = (char*) _readSingleField(INPUT_TYPE_URL, &usLine);
	sRankTraffic = (char*) _readSingleField(INPUT_TYPE_URL, &usLine);
	sBackLink = (char*) _readSingleField(INPUT_TYPE_URL, &usLine);
	sWebsiteWorth = (char*) _readSingleField(INPUT_TYPE_URL, &usLine);
    
	while (bContinue && NULL != sUrl && NULL != sCompany
           && NULL != sDailyPageView && NULL != sRankTraffic
           && NULL != sBackLink && NULL != sWebsiteWorth) {
		curWebsite->url = sUrl;
        
		curWebsite->company = sCompany;
		curWebsite->dailyPageViewThousands = atoi(sDailyPageView);
		curWebsite->rankTraffic = atoi(sRankTraffic);
		curWebsite->backLinkThousands = atoi(sBackLink);
		curWebsite->websiteWorthThousands = atoi(sWebsiteWorth);
		
        // TODO: create free function for entire Website struct
        free(sDailyPageView);
		free(sRankTraffic);
		free(sBackLink);
		free(sWebsiteWorth);
		bContinue = false;
	}
    
	free(sLine);

	return curWebsite;
}

/*
 *  _readOneLine  
 *  reads one line from the input file stream.
 *
 *  PRE:    fPtr (file pointer; readonly; from input file stream)
 *
 *  POST:   read one line from the buffer
 *          excludes delimiter from the buffer string
 *
 *  RETURN: sBuffer (buffer line read from the input file stream)
 *
 */
static char* _readOneLine(FILE* fPtr) {
	int numCharRead = 0;                    // number of characters read
	char usBuffer[MAX_LENGTH_INPUT];        // unsafe buffer  string
	char *sBuffer;                           // safe buffer string
    
	// read: until linebreak or EOF is read
	usBuffer[numCharRead] = fgetc(fPtr);
	if (EOF != usBuffer[numCharRead]) {
		while ('\n' != usBuffer[numCharRead]) {
			numCharRead++;
			usBuffer[numCharRead] = fgetc(fPtr);
		}
	} else {
		return NULL; // reached EOF
	}
    
	// exclude: delimiter from bufferString
	usBuffer[numCharRead] = '\0';
    
	// dynamically allocate: bufferString
	sBuffer = malloc(strlen(usBuffer) + 1);
	if (!sBuffer) {
        exit(EXIT_NOT_ENOUGH_MEMORY);
    }
    
    // copy: unsafe buffer to safe buffer
    strcpy(sBuffer, usBuffer);
	return sBuffer;
}

/*
 *  _readSingleField
 *  reads one field from the line per given input type. Then,
 *  returns the validated field
 *
 *  PRE:    type (input type)
 *          line (buffer input line)
 *
 *  POST:   locate one delimiter; 
 *          parses one field from the buffer line
 *          calls ValidateManager for validation purposes
 * 
 *  RETURN: usField (string type of parsed & validated field) 
 *
 */
static void* _readSingleField(input_type type, char **line) {
    char *usField;          // unsafe field string (processed from `line`)
    char *loc;              // location of the delimiter
    int i;                  // iterating variable
    
    MALLOC(usField);
    // locate: delimiter
    loc = strchr(*line, DELIMITER_SEMICOLON);
    
    // update the location of the stirng pointer
    for(i = 0; i < loc - *line; i++) {
        usField[i] = (*line)[i];
    }
    
    *line = loc + 1;
    
    // validate: single field from the line
    if (INPUT_VALUE_VALID == validateInput(type, usField)) {
        return usField;
    } else {
        // free: invalid field read
        free(usField);
        return NULL;
    }
}


