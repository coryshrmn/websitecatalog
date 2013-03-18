/* BstManager.c
 * Group 6
 * WebsiteCatalog main
 *
 * Cory Sherman
 */

#include "WebsiteCatalog.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//TODO: delete after debugging
#define Logd(str, val) printf(str "_%d_\n", val)
#define ERR printf("ERROR\n");

int main(int argc, const char * argv[]) {
    ListHead *head; // head of the list
    Website *curWebsite; // website struct
    menu_type menu; // menu type
    FILE *fPtr = NULL; // file pointer
    char *fname = NULL; // file name
    int nLines = 0; // number of input line
    
    
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>LOOP
    fPtr = initFileStream(&fname, &nLines);    
    curWebsite = getSingleWebsite(fPtr);
    
    
    
    

    
    
    //TODO: delete after debugging
    // print `curWebsite`
	printf(HR);
	printf("`curWebsite` fields:\n");
	printf("%s\n%s\n%d\n%d\n%d\n%d\n", curWebsite->url, curWebsite->company,
           curWebsite->dailyPageViewThousands, curWebsite->rankTraffic,
           curWebsite->backLinkThousands, curWebsite->websiteWorthThousands);
	printf(HR);
    //ENDTODO
    
    
    
    
    MenuManager(head);
    
    
    
    //FIXME: websitePrintFull doesn't return the correct result
    websitePrintFull(curWebsite);
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<END LOOP
    
    
    
    
    
    
    
    
    return 0;

     }


/*******************************************************************************
 * WebsiteCatalog Private Prototypes
 ******************************************************************************/


//
///*******************************************************************************
// * Main entry point for the program
// ******************************************************************************/
//int main(void)
//{
//    ListHead head;
//
//    //TODO input
//
//    hashCreate(&head, 371);
//    bstCreate(&head);
//
//
//    listInsert(&head, websiteCreate("google.com", "Google", 1100000, 1, 1388775, 2410000));
//    listInsert(&head, websiteCreate("facebook.com", "Facebook", 550000, 2, 2147484, 1200000));
//    listInsert(&head, websiteCreate("youtube.com", "YouTube", 366667, 3, 806106, 803000));
//    listInsert(&head, websiteCreate("yahoo.com", "Yahoo!", 275000, 4, 0, 602250));
//    listInsert(&head, websiteCreate("baidu.com", "Baidu.com", 220000, 5, 82020, 481800));
//    listInsert(&head, websiteCreate("wikipedia.org", "Wikipedia", 183333, 6, 8038, 401500));
//    listInsert(&head, websiteCreate("live.com", "Windows Live", 157143, 7, 10673, 344150));
//    listInsert(&head, websiteCreate("qq.com", "QQ.COM", 122222, 9, 24231, 267670));
//    listInsert(&head, websiteCreate("amazon.com", "Amazon.com", 137500, 8, 365619, 301130));
//    listInsert(&head, websiteCreate("twitter.com", "Twitter", 110000, 10, 702178, 240900));
//    listInsert(&head, websiteCreate("blogspot.com", "Blogspot.com", 91667, 12, 93, 200750));
//    listInsert(&head, websiteCreate("linkedin.com", "LinkedIn", 78571, 14, 292379, 172070));
//    listInsert(&head, websiteCreate("google.co.in", "Google India", 84615, 13, 1678, 185310));
//    listInsert(&head, websiteCreate("taobao.com", "Taobao.com", 100000, 11, 121934, 219000));
//    listInsert(&head, websiteCreate("yahoo.co.jp", "Yahoo! Japan", 73333, 15, 232454, 160600));
//    listInsert(&head, websiteCreate("bing.com", "Bing", 50000, 22, 45455, 109500));
//    listInsert(&head, websiteCreate("msn.com", "MSN", 57895, 19, 16802, 126790));
//    listInsert(&head, websiteCreate("ebay.com", "eBay", 64706, 17, 182139, 141710));
//    listInsert(&head, websiteCreate("wordpress.com", "WordPress.com", 50000, 22, 4889, 109500));
//    listInsert(&head, websiteCreate("google.de", "Google", 57895, 19, 12839, 126790));
//    listInsert(&head, websiteCreate("google.fr", "Google France", 42308, 26, 6567, 92660));
//    listInsert(&head, websiteCreate("google.co.uk", "Google UK", 40741, 27, 5559, 89220));
//    listInsert(&head, websiteCreate("tumblr.com", "Tumblr", 34375, 32, 52193, 75280));
//    listInsert(&head, websiteCreate("microsoft.com", "Microsoft Corporation", 35484, 31, 105884, 77710));
//    listInsert(&head, websiteCreate("googleusercontent.com", "googleusercontent.com", 28947, 38, 1, 63390));
//    listInsert(&head, websiteCreate("pinterest.com", "Pinterest", 31429, 35, 0, 68830));
//    listInsert(&head, websiteCreate("google.com.br", "Google Brasil", 30556, 36, 1247, 66920));
//    listInsert(&head, websiteCreate("babylon.com", "Babylon", 39286, 28, 9568, 86040));
//    listInsert(&head, websiteCreate("conduit.com", "Conduit", 19298, 57, 2417, 42270));
//    listInsert(&head, websiteCreate("google.ru", "Google", 27500, 40, 3768, 60230));
//    listInsert(&head, websiteCreate("paypal.com", "PayPal", 28947, 38, 259370, 63400));
//    listInsert(&head, websiteCreate("amazon.co.jp", "Amazon.co.jp", 10680, 103, 0, 23390));
//    listInsert(&head, websiteCreate("ask.com", "Ask", 25581, 43, 8878, 56030));
//    listInsert(&head, websiteCreate("blogger.com", "Blogger.com", 24444, 45, 216872, 53540));
//    listInsert(&head, websiteCreate("xvideos.com", "xvideos.com", 22449, 49, 673, 49160));
//    listInsert(&head, websiteCreate("xhamster.com", "xHamster's Free Porn Videos", 25581, 43, 215, 56020));
//    listInsert(&head, websiteCreate("google.it", "Google", 26829, 41, 5549, 58760));
//    listInsert(&head, websiteCreate("hao123.com", "Hao123", 18966, 58, 4376, 41540));
//    listInsert(&head, websiteCreate("avg.com", "AVG | Antivirus and Security Software", 16923, 65, 301, 37060));
//    listInsert(&head, websiteCreate("apple.com", "Apple Inc.", 29730, 37, 55577, 65110));
//    listInsert(&head, websiteCreate("imdb.com", "The Internet Movie Database", 22000, 50, 138244, 48180));
//    listInsert(&head, websiteCreate("adobe.com", "Adobe Systems Incorporated", 17742, 62, 326858, 38860));
//    listInsert(&head, websiteCreate("bbc.co.uk", "BBC Online", 20370, 54, 32862, 44610));
//    listInsert(&head, websiteCreate("amazon.de", "Amazon.de GmbH", 16667, 66, 228235, 36500));
//    listInsert(&head, websiteCreate("google.ca", "Google", 18644, 59, 0, 40830));
//    listInsert(&head, websiteCreate("go.com", "Go", 19643, 56, 60, 43020));
//    listInsert(&head, websiteCreate("pornhub.com", "Pornhub.com", 17188, 64, 997, 37640));
//    listInsert(&head, websiteCreate("mywebsearch.com", "302 Found", 15942, 69, 13, 34910));
//    listInsert(&head, websiteCreate("instagram.com", "instagram.com", 13095, 84, 0, 28680));
//    listInsert(&head, websiteCreate("aol.com", "AOL", 16176, 68, 34279, 35430));
//    listInsert(&head, websiteCreate("tmall.com", "Tmall.com", 18033, 61, 153, 39490));
//    listInsert(&head, websiteCreate("adf.ly", "adf.ly - let your links take flight", 15068, 73, 1, 33000));
//    listInsert(&head, websiteCreate("thepiratebay.se", "The Pirate Bay", 14865, 74, 0, 32550));
//    listInsert(&head, websiteCreate("livejasmin.com", "LiveJasmin.com", 18033, 61, 6322, 39490));
//    listInsert(&head, websiteCreate("flickr.com", "Flickr", 16667, 66, 241852, 36500));
//    listInsert(&head, websiteCreate("livedoor.com", "livedoor", 10476, 105, 113460, 22940));
//    listInsert(&head, websiteCreate("stackoverflow.com", "Stack Overflow", 12941, 85, 65, 28340));
//    listInsert(&head, websiteCreate("cnn.com", "CNN Interactive", 13580, 81, 26206, 29740));
//    listInsert(&head, websiteCreate("blogspot.in", "blogspot.in", 13580, 81, 0, 29740));
//    listInsert(&head, websiteCreate("ebay.de", "eBay International AG", 15068, 73, 163023, 33000));
//    listInsert(&head, websiteCreate("redtube.com", "RedTube", 13580, 81, 265, 29740));
//    listInsert(&head, websiteCreate("imgur.com", "Imgur", 12500, 88, 28, 27380));
//    listInsert(&head, websiteCreate("amazon.co.uk", "Amazon.co.uk", 12222, 90, 217025, 26770));
//    listInsert(&head, websiteCreate("dailymotion.com", "Dailymotion", 12644, 87, 0, 27690));
//    listInsert(&head, websiteCreate("bp.blogspot.com", "bp.blogspot.com", 20000, 55, 0, 43800));
//    listInsert(&head, websiteCreate("google.com.au", "Google Australia", 14667, 75, 2757, 32120));
//    listInsert(&head, websiteCreate("alibaba.com", "Alibaba.com", 13750, 80, 111857, 30110));
//    listInsert(&head, websiteCreate("uol.com.br", "Universo Online", 11458, 96, 1984, 25100));
//    listInsert(&head, websiteCreate("netflix.com", "Netflix", 11957, 92, 2225, 26190));
//    listInsert(&head, websiteCreate("neobux.com", "NeoBux", 10092, 109, 1327, 22100));
//    listInsert(&head, websiteCreate("xnxx.com", "XNXX Galleries", 10680, 103, 284, 23390));
//    listInsert(&head, websiteCreate("youporn.com", "Youporn", 11111, 99, 1571, 24340));
//    listInsert(&head, websiteCreate("huffingtonpost.com", "The Huffington Post", 11957, 92, 34708, 26190));
//    listInsert(&head, websiteCreate("ebay.co.uk", "eBay UK", 12360, 89, 154012, 27070));
//    listInsert(&head, websiteCreate("wordpress.org", "WordPress", 10476, 105, 41889, 22950));
//    listInsert(&head, websiteCreate("globo.com", "Globo", 10092, 109, 4689, 22100));
//    listInsert(&head, websiteCreate("cnet.com", "CNET.com", 10577, 104, 94670, 23170));
//    listInsert(&head, websiteCreate("incredibar.com", "incredibar.com", 10280, 107, 0, 22510));
//    listInsert(&head, websiteCreate("alipay.com", "Alipay.com", 11340, 97, 160588, 24840));
//    listInsert(&head, websiteCreate("mediafire.com", "MediaFire", 10377, 106, 8968, 22730));
//    listInsert(&head, websiteCreate("espn.go.com", "ESPN", 11579, 95, 153, 25360));
//    listInsert(&head, websiteCreate("godaddy.com", "Go Daddy", 9649, 114, 27523, 21130));
//    listInsert(&head, websiteCreate("weather.com", "The Weather Channel", 9091, 121, 19703, 19910));
//    listInsert(&head, websiteCreate("kat.ph", "kat.ph", 9091, 121, 0, 19910));
//    listInsert(&head, websiteCreate("reddit.com", "Reddit", 8209, 134, 0, 17980));
//    listInsert(&head, websiteCreate("yieldmanager.com", "yieldmanager.com", 4721, 233, 0, 10340));
//    listInsert(&head, websiteCreate("ehow.com", "eHow", 8800, 125, 12701, 19270));
//    listInsert(&head, websiteCreate("google.nl", "Google Nederland", 10000, 110, 2245, 21900));
//    listInsert(&head, websiteCreate("google.com.ar", "Google.com.ar", 9322, 118, 423, 20420));
//    listInsert(&head, websiteCreate("directrev.com", "directrev.com", 4846, 227, 0, 10610));
//    listInsert(&head, websiteCreate("nytimes.com", "New York Times", 9565, 115, 39929, 20950));
//    listInsert(&head, websiteCreate("4shared.com", "4shared", 9402, 117, 7830, 20590));
//    listInsert(&head, websiteCreate("dropbox.com", "Dropbox", 8800, 125, 1477, 19270));
//    listInsert(&head, websiteCreate("deviantart.com", "deviantART", 8397, 131, 16661, 18390));
//    listInsert(&head, websiteCreate("tube8.com", "Free sex videos, Sex tube, Free porn movies - Tube8.com", 8209, 134, 633, 17980));
//    listInsert(&head, websiteCreate("bankofamerica.com", "Bank of America", 8943, 123, 1126, 19590));
//    listInsert(&head, websiteCreate("dailymail.co.uk", "The Daily Mail", 8871, 124, 10090, 19430));
//    listInsert(&head, websiteCreate("goo.ne.jp", "goo", 8088, 136, 100557, 17720));
//    listInsert(&head, websiteCreate("vimeo.com", "Vimeo", 9167, 120, 0, 20080));
//    listInsert(&head, websiteCreate("indiatimes.com", "Indiatimes", 8594, 128, 3905, 18820));
//    listInsert(&head, websiteCreate("google.com.eg", "Google.com.eg", 7432, 148, 204, 16280));
//    listInsert(&head, websiteCreate("livejournal.com", "LiveJournal.com", 8527, 129, 67920, 18680));
//    listInsert(&head, websiteCreate("google.co.id", "Google.co.id", 15942, 69, 274, 34910));
//    listInsert(&head, websiteCreate("badoo.com", "Badoo.Com", 7857, 140, 12, 17210));
//    listInsert(&head, websiteCreate("sweetim.com", "SweetIM", 4453, 247, 857, 9750));
//    listInsert(&head, websiteCreate("doublepimp.com", "Double Pimp", 2949, 373, 0, 6460));
//    listInsert(&head, websiteCreate("blogfa.com", "BLOGFA", 8333, 132, 3654, 18250));
//    listInsert(&head, websiteCreate("google.com.pk", "Google.com.pk", 6044, 182, 78, 13240));
//    listInsert(&head, websiteCreate("blogspot.com.br", "Dominio protegido", 837, 1315, 0, 1830));
//    listInsert(&head, websiteCreate("zedo.com", "www.ZEDO.com", 13924, 79, 29, 30500));
//    listInsert(&head, websiteCreate("chase.com", "Chase Bank", 6250, 176, 228, 13690));
//    listInsert(&head, websiteCreate("slideshare.net", "SlideShare", 6790, 162, 0, 14870));
//    listInsert(&head, websiteCreate("searchnu.com", "searchnu.com", 8271, 133, 0, 18110));
//    listInsert(&head, websiteCreate("addthis.com", "Addthis.com", 7483, 147, 837912, 16390));
//    listInsert(&head, websiteCreate("wikimedia.org", "Wikimedia", 6471, 170, 21, 14170));
//    listInsert(&head, websiteCreate("amazonaws.com", "amazonaws.com", 7006, 157, 0, 15340));
//    listInsert(&head, websiteCreate("google.co.za", "Google.co.za", 7333, 150, 156, 16060));
//    listInsert(&head, websiteCreate("softonic.com", "Softonic", 7237, 152, 695, 15850));
//    listInsert(&head, websiteCreate("skype.com", "Skype", 6962, 158, 40972, 15250));
//    listInsert(&head, websiteCreate("answers.com", "1-Click Answers", 6250, 176, 27647, 13690));
//    listInsert(&head, websiteCreate("foxnews.com", "FoxNews.com", 7639, 144, 11384, 16730));
//    listInsert(&head, websiteCreate("secureserver.net", "Object moved", 10000, 110, 155, 21900));
//    listInsert(&head, websiteCreate("mozilla.org", "Mozilla", 6875, 160, 9109, 15060));
//    listInsert(&head, websiteCreate("outbrain.com", "Outbrain.com", 6748, 163, 15, 14780));
//    listInsert(&head, websiteCreate("etsy.com", "etsy.com", 7383, 149, 34103, 16170));
//    listInsert(&head, websiteCreate("walmart.com", "Wal-Mart Online", 9483, 116, 3034, 20770));
//    listInsert(&head, websiteCreate("uploaded.net", "Uploaded.net", 6667, 165, 0, 14600));
//    listInsert(&head, websiteCreate("aweber.com", "AWeber Systems", 6748, 163, 0, 14780));
//    listInsert(&head, websiteCreate("amazon.fr", "Amazon.fr", 6509, 169, 207985, 14260));
//    listInsert(&head, websiteCreate("sourceforge.net", "SourceForge", 6918, 159, 329, 15150));
//    listInsert(&head, websiteCreate("stumbleupon.com", "StumbleUpon", 6667, 165, 515729, 14600));
//    listInsert(&head, websiteCreate("google.cn", "Google", 7857, 140, 23828, 17210));
//    listInsert(&head, websiteCreate("google.co.ve", "Google Venezuela", 3406, 323, 87, 7460));
//    listInsert(&head, websiteCreate("wellsfargo.com", "Wells Fargo", 6358, 173, 458, 13930));
//    listInsert(&head, websiteCreate("liveinternet.ru", "LiveInternet.ru", 6433, 171, 83378, 14090));
//    listInsert(&head, websiteCreate("booking.com", "Booking.com", 5789, 190, 37823, 12680));
//    listInsert(&head, websiteCreate("themeforest.net", "themeforest.net", 5851, 188, 64, 12820));
//    listInsert(&head, websiteCreate("guardian.co.uk", "The Guardian", 5584, 197, 21424, 12230));
//    listInsert(&head, websiteCreate("comcast.net", "Comcast High-speed Internet!", 5023, 219, 0, 11000));
//    listInsert(&head, websiteCreate("fbcdn.net", "Fbcdn.net", 5759, 191, 0, 12610));
//    listInsert(&head, websiteCreate("google.com.my", "Google.com.my", 5023, 219, 233, 11000));
//    listInsert(&head, websiteCreate("yelp.com", "Yelp", 5213, 211, 73733, 11420));
//    listInsert(&head, websiteCreate("leboncoin.fr", "leboncoin.fr", 5213, 211, 0, 11420));
//    listInsert(&head, websiteCreate("ask.fm", "ask.fm", 4681, 235, 2, 10250));
//    listInsert(&head, websiteCreate("google.gr", "Google", 5314, 207, 142, 11640));
//    listInsert(&head, websiteCreate("reference.com", "Dictionary.com", 5288, 208, 17749, 11580));
//    listInsert(&head, websiteCreate("delta-search.com", "delta-search.com", 1618, 680, 0, 3540));
//    listInsert(&head, websiteCreate("nbcnews.com", "NBC News", 5069, 217, 0, 11100));
//    listInsert(&head, websiteCreate("google.com.co", "Google Colombia", 5556, 198, 67, 12170));
//    listInsert(&head, websiteCreate("flipkart.com", "Flipkart", 5140, 214, 1793, 11260));
//    listInsert(&head, websiteCreate("ilivid.com", "ilivid.com", 2750, 400, 1, 6020));
//    listInsert(&head, websiteCreate("theexgirlfriends.com", "theexgirlfriends.com", 1692, 650, 0, 3710));
//    listInsert(&head, websiteCreate("movie2k.to", "movie2k.to", 4400, 250, 54, 9640));
//    listInsert(&head, websiteCreate("google.be", "Google", 5263, 209, 497, 11530));
//    listInsert(&head, websiteCreate("fiverr.com", "Fiverr", 5366, 205, 121, 11750));
//    listInsert(&head, websiteCreate("warriorforum.com", "The Warrior Forum", 5759, 191, 603, 12610));
//    listInsert(&head, websiteCreate("torrentz.eu", "torrentz.eu", 5978, 184, 12, 13090));
//    listInsert(&head, websiteCreate("github.com", "GitHub", 5093, 216, 82, 11150));
//    listInsert(&head, websiteCreate("download.com", "CNET Download.com", 5500, 200, 4558, 12050));
//    listInsert(&head, websiteCreate("hootsuite.com", "HootSuite Social Media Dashboard", 5612, 196, 1505, 12290));
//    listInsert(&head, websiteCreate("w3schools.com", "W3 Schools", 4783, 230, 2262, 10480));
//    listInsert(&head, websiteCreate("soundcloud.com", "SoundCloud", 4783, 230, 1381, 10480));
//    listInsert(&head, websiteCreate("espncricinfo.com", "ESPN Cricinfo", 5670, 194, 1000, 12420));
//    listInsert(&head, websiteCreate("archive.org", "The Internet Archive", 5046, 218, 18512, 11050));
//    listInsert(&head, websiteCreate("indeed.com", "Indeed.com", 4331, 254, 20460, 9490));
//    listInsert(&head, websiteCreate("orange.fr", "Orange", 4400, 250, 653, 9640));
//    listInsert(&head, websiteCreate("google.com.vn", "Google.com.vn", 5238, 210, 721, 11470));
//    listInsert(&head, websiteCreate("aliexpress.com", "AliExpress", 5000, 220, 48534, 10950));
//    listInsert(&head, websiteCreate("google.com.ua", "Google.com.ua", 4955, 222, 471, 10850));
//    listInsert(&head, websiteCreate("cam4.com", "Cam4 - Free Adult Web Cams", 4472, 246, 248, 9790));
//    listInsert(&head, websiteCreate("clicksor.com", "Clicksor", 7190, 153, 556, 15750));
//    listInsert(&head, websiteCreate("blogspot.com.es", "blogspot.com.es", 542, 2030, 0, 1190));
//    listInsert(&head, websiteCreate("rediff.com", "Rediff.com India Ltd.", 5140, 214, 0, 11260));
//    listInsert(&head, websiteCreate("squidoo.com", "Squidoo", 5093, 216, 21521, 11150));
//    listInsert(&head, websiteCreate("hardsextube.com", "hardsextube.com", 4400, 250, 1204, 9640));
//    listInsert(&head, websiteCreate("it168.com", "IT168", 2757, 399, 8263, 6040));
//    listInsert(&head, websiteCreate("gmx.net", "GMX", 4231, 260, 622, 9270));
//    listInsert(&head, websiteCreate("statcounter.com", "StatCounter.com", 5189, 212, 220457, 11370));
//    listInsert(&head, websiteCreate("scribd.com", "Scribd", 4247, 259, 15877, 9300));
//    listInsert(&head, websiteCreate("tripadvisor.com", "TripAdvisor", 4044, 272, 46409, 8860));
//    listInsert(&head, websiteCreate("naver.jp", "naver.jp", 1111, 990, 0, 2430));
//    listInsert(&head, websiteCreate("search-results.com", "search-results.com", 8943, 123, 28, 19590));
//    listInsert(&head, websiteCreate("google.ro", "Google", 4382, 251, 685, 9600));
//    listInsert(&head, websiteCreate("libero.it", "Libero", 4280, 257, 8877, 9380));
//    listInsert(&head, websiteCreate("google.se", "Google", 4603, 239, 559, 10080));
//    listInsert(&head, websiteCreate("rutracker.org", "rutracker.org", 4435, 248, 3, 9720));
//    listInsert(&head, websiteCreate("forbes.com", "Forbes Magazine", 4015, 274, 0, 8790));
//    listInsert(&head, websiteCreate("youjizz.com", "youjizz.com", 4564, 241, 255, 10000));
//    listInsert(&head, websiteCreate("isohunt.com", "isoHunt", 5023, 219, 71, 11000));
//    listInsert(&head, websiteCreate("bet365.com", "Bet365", 3537, 311, 2640, 7750));
//    listInsert(&head, websiteCreate("spiegel.de", "Spiegel Online", 6707, 164, 5393, 14690));
//    listInsert(&head, websiteCreate("google.com.ng", "Google.com.ng", 3943, 279, 0, 8630));
//    listInsert(&head, websiteCreate("profitclicking.com", "Profit Clicking", 4783, 230, 0, 10470));
//    listInsert(&head, websiteCreate("google.com.ph", "Google.com.ph", 3691, 298, 279, 8090));
//    listInsert(&head, websiteCreate("soku.com", "soku.com", 4545, 242, 0, 9960));
//    listInsert(&head, websiteCreate("bild.de", "Bild.de", 4889, 225, 2434, 10710));
//    listInsert(&head, websiteCreate("hulu.com", "Hulu", 3704, 297, 3900, 8110));
//    listInsert(&head, websiteCreate("domaintools.com", "DomainTools.com", 4472, 246, 1491, 9790));
//    listInsert(&head, websiteCreate("taringa.net", "Taringa!", 4280, 257, 6388, 9380));
//    listInsert(&head, websiteCreate("myspace.com", "Myspace", 4721, 233, 462545, 10340));
//    listInsert(&head, websiteCreate("intuit.com", "Intuit Inc.", 1392, 790, 2501, 3050));
//    listInsert(&head, websiteCreate("optmd.com", "optmd.com", 5263, 209, 0, 11530));
//    listInsert(&head, websiteCreate("thefreedictionary.com", "The Free Dictionary", 3630, 303, 14551, 7950));
//    listInsert(&head, websiteCreate("mercadolivre.com.br", "MercadoLivre Brasil", 3887, 283, 14934, 8510));
//    listInsert(&head, websiteCreate("hp.com", "Hewlett-Packard", 4151, 265, 5407, 9090));
//    listInsert(&head, websiteCreate("putlocker.com", "putlocker.com", 4015, 274, 29, 8790));
//    listInsert(&head, websiteCreate("telegraph.co.uk", "Telegraph.co.uk", 4074, 270, 9881, 8920));
//    listInsert(&head, websiteCreate("tagged.com", "Tagged", 3929, 280, 500, 8610));
//    listInsert(&head, websiteCreate("extratorrent.com", "ExtraTorrent.com - The World's Largest BitTorrent System", 3595, 306, 3621, 7870));
//    listInsert(&head, websiteCreate("samsung.com", "Samsung Electronics", 4527, 243, 2252, 9920));
//    listInsert(&head, websiteCreate("pandora.com", "Pandora", 3887, 283, 5909, 8510));
//    listInsert(&head, websiteCreate("irs.gov", "Internal Revenue Service", 684, 1608, 1248, 1500));
//    listInsert(&head, websiteCreate("linkbucks.com", "Linkbucks.com", 3630, 303, 377, 7950));
//    listInsert(&head, websiteCreate("pof.com", "pof.com", 3819, 288, 0, 8370));
//    listInsert(&head, websiteCreate("popads.net", "popads.net", 3819, 288, 7, 8360));
//    listInsert(&head, websiteCreate("1channel.ch", "1channel.ch", 3254, 338, 8, 7130));
//    listInsert(&head, websiteCreate("wordreference.com", "WordReference,com", 4583, 240, 3867, 10040));
//    listInsert(&head, websiteCreate("informer.com", "informer.com", 2850, 386, 4550, 6240));
//    listInsert(&head, websiteCreate("rapidgator.net", "rapidgator.net", 3729, 295, 0, 8170));
//    listInsert(&head, websiteCreate("google.com.sg", "Google.com.sg", 3642, 302, 111, 7980));
//    listInsert(&head, websiteCreate("salesforce.com", "Salesforce.com", 5946, 185, 599, 13020));
//    listInsert(&head, websiteCreate("pengyou.com", "pengyou.com", 5446, 202, 0, 11930));
//    listInsert(&head, websiteCreate("adnxs.com", "adnxs.com", 3284, 335, 0, 7190));
//    listInsert(&head, websiteCreate("weebly.com", "Weebly", 3470, 317, 1148, 7600));
//    listInsert(&head, websiteCreate("google.ch", "Google Schweiz", 3704, 297, 760, 8110));
//    listInsert(&head, websiteCreate("t-online.de", "www.t-online.de", 3090, 356, 4162, 6770));
//    listInsert(&head, websiteCreate("depositfiles.com", "depositfiles.com", 5946, 185, 77, 13020));
//    listInsert(&head, websiteCreate("reuters.com", "Reuters Group PLC", 3470, 317, 23005, 7600));
//    listInsert(&head, websiteCreate("ups.com", "UPS", 4545, 242, 4140, 9960));
//    listInsert(&head, websiteCreate("bestbuy.com", "Best Buy Co., Inc.", 5584, 197, 2226, 12230));
//    listInsert(&head, websiteCreate("ikea.com", "IKEA", 3754, 293, 1415, 8220));
//    listInsert(&head, websiteCreate("twoo.com", "Twoo", 3618, 304, 0, 7920));
//    listInsert(&head, websiteCreate("detik.com", "Detik.com", 3274, 336, 1174, 7170));
//    listInsert(&head, websiteCreate("google.cl", "Google Chile", 3986, 276, 575, 8730));
//    listInsert(&head, websiteCreate("google.pt", "Google", 3514, 313, 178, 7700));
//    listInsert(&head, websiteCreate("goodgamestudios.com", "Goodgame Studios - Altigi GmbH", 3364, 327, 0, 7370));
//    listInsert(&head, websiteCreate("iminent.com", "IMbooster official website", 1923, 572, 8, 4210));
//    listInsert(&head, websiteCreate("csdn.net", "CSDN", 4280, 257, 2217, 9380));
//    listInsert(&head, websiteCreate("goal.com", "Goal.com", 3406, 323, 5842, 7460));
//    listInsert(&head, websiteCreate("drtuber.com", "drtuber.com", 3514, 313, 56, 7700));
//    listInsert(&head, websiteCreate("9gag.com", "9Gag", 3374, 326, 4, 7390));
//    listInsert(&head, websiteCreate("uimserv.net", "uimserv.net", 3929, 280, 0, 8600));
//    listInsert(&head, websiteCreate("target.com", "Target Corporation", 5340, 206, 6804, 11700));
//    listInsert(&head, websiteCreate("usps.com", "United States Postal Service (USPS)", 3833, 287, 1767, 8400));
//    listInsert(&head, websiteCreate("doubleclick.com", "Double Click", 9483, 116, 513, 20770));
//    listInsert(&head, websiteCreate("adultfriendfinder.com", "Adult Friendfinder", 3691, 298, 1905, 8090));
//    listInsert(&head, websiteCreate("clixsense.com", "Clixsense.com", 3323, 331, 257, 7280));
//    listInsert(&head, websiteCreate("wsj.com", "The Wall Street Journal Interactive Edition", 3537, 311, 1907, 7750));
//    listInsert(&head, websiteCreate("php.net", "PHP: Hypertext Preprocessor", 3986, 276, 82499, 8730));
//    listInsert(&head, websiteCreate("shutterstock.com", "Shutterstock", 3274, 336, 4285, 7170));
//    listInsert(&head, websiteCreate("marca.com", "MARCA.com", 3125, 352, 5058, 6850));
//    listInsert(&head, websiteCreate("aili.com", "aili.com", 520, 2116, 0, 1140));
//    listInsert(&head, websiteCreate("mashable.com", "Mashable", 3385, 325, 372, 7410));
//    listInsert(&head, websiteCreate("kaskus.co.id", "Kaskus.co.id / Kaskus.com", 3143, 350, 0, 6880));
//    listInsert(&head, websiteCreate("java.com", "Java.com", 2880, 382, 2367, 6310));
//    listInsert(&head, websiteCreate("goodreads.com", "Goodreads", 3056, 360, 12940, 6690));
//    listInsert(&head, websiteCreate("ign.com", "IGN", 3134, 351, 26449, 6870));
//    listInsert(&head, websiteCreate("yourlust.com", "YourLust Tube", 3481, 316, 88, 7620));
//    listInsert(&head, websiteCreate("nih.gov", "National Institutes of Health (NIH)", 3134, 351, 4184, 6870));
//    listInsert(&head, websiteCreate("terra.com.br", "Terra", 3170, 347, 0, 6940));
//    listInsert(&head, websiteCreate("nba.com", "NBA.com", 3073, 358, 4580, 6730));
//    listInsert(&head, websiteCreate("livedoor.biz", "livedoor.biz", 2489, 442, 0, 5450));
//    listInsert(&head, websiteCreate("exoclick.com", "exoclick.com", 2696, 408, 0, 5900));
//    listInsert(&head, websiteCreate("in.com", "IN.com", 3571, 308, 4353, 7820));
//    listInsert(&head, websiteCreate("akamaihd.net", "akamaihd.net", 2902, 379, 0, 6360));
//    listInsert(&head, websiteCreate("etao.com", "eTao.com", 1815, 606, 0, 3980));
//    listInsert(&head, websiteCreate("ku6.com", "Ku6", 3143, 350, 0, 6880));
//    listInsert(&head, websiteCreate("gsmarena.com", "GSM Arena", 2926, 376, 395, 6410));
//    listInsert(&head, websiteCreate("dell.com", "Dell Inc.", 3560, 309, 2322, 7800));
//    listInsert(&head, websiteCreate("bleacherreport.com", "Bleacher Report", 2716, 405, 322, 5950));
//    listInsert(&head, websiteCreate("nifty.com", "@nifty", 2957, 372, 18676, 6480));
//    listInsert(&head, websiteCreate("webs.com", "Webs", 2902, 379, 3589, 6360));
//    listInsert(&head, websiteCreate("google.com.bd", "Google.com.bd", 735, 1496, 212, 1610));
//    listInsert(&head, websiteCreate("pch.com", "Publishers Clearing House", 2778, 396, 11, 6080));
//    listInsert(&head, websiteCreate("mixi.jp", "mixi", 2933, 375, 67, 6430));
//    listInsert(&head, websiteCreate("seomoz.org", "SEOmoz.org", 2771, 397, 1858, 6070));
//    listInsert(&head, websiteCreate("pixiv.net", "pixiv", 1348, 816, 13111, 2950));
//    listInsert(&head, websiteCreate("match.com", "Match.com", 2730, 403, 2154, 5980));
//    listInsert(&head, websiteCreate("wix.com", "Wix", 2757, 399, 4457, 6040));
//    listInsert(&head, websiteCreate("buzzfeed.com", "Buzzfeed.com", 2638, 417, 3923, 5780));
//    listInsert(&head, websiteCreate("constantcontact.com", "Constant Contact - Do-It-Yourself Email Marketing", 3207, 343, 10293, 7030));
//    listInsert(&head, websiteCreate("stackexchange.com", "stackexchange.com", 2052, 536, 1, 4500));
//    listInsert(&head, websiteCreate("blogspot.co.uk", "blogspot.co.uk", 2910, 378, 0, 6370));
//    listInsert(&head, websiteCreate("jobrapido.com", "jobrapido.com", 2376, 463, 0, 5200));
//    listInsert(&head, websiteCreate("histats.com", "Histats.com", 2455, 448, 65749, 5380));
//    listInsert(&head, websiteCreate("avito.ru", "avito.ru", 2439, 451, 546, 5340));
//    listInsert(&head, websiteCreate("beeg.com", "beeg.", 2703, 407, 3, 5920));
//    listInsert(&head, websiteCreate("ebay.in", "eBay India", 2676, 411, 8894, 5860));
//    listInsert(&head, websiteCreate("repubblica.it", "La Repubblica", 2376, 463, 6334, 5210));
//    listInsert(&head, websiteCreate("ebay.it", "Ebay", 3264, 337, 26462, 7150));
//    listInsert(&head, websiteCreate("ebay.com.au", "eBay.com.au", 3354, 328, 141871, 7350));
//    listInsert(&head, websiteCreate("google.co.hu", "Google", 2821, 390, 50, 6180));
//    listInsert(&head, websiteCreate("empowernetwork.com", "empowernetwork.com", 2316, 475, 0, 5070));
//    listInsert(&head, websiteCreate("wikihow.com", "wikiHow", 2529, 435, 1291, 5540));
//    listInsert(&head, websiteCreate("torrentz.in", "torrentz.in", 1903, 578, 0, 4170));
//    listInsert(&head, websiteCreate("4dsply.com", "4dsply.com", 3385, 325, 0, 7410));
//    listInsert(&head, websiteCreate("att.com", "AT&T", 2973, 370, 7434, 6510));
//    listInsert(&head, websiteCreate("fedex.com", "FedEx", 2926, 376, 3171, 6410));
//    listInsert(&head, websiteCreate("seznam.cz", "Seznam", 2792, 394, 4796, 6120));
//    listInsert(&head, websiteCreate("washingtonpost.com", "Washington Post", 3014, 365, 16638, 6600));
//    listInsert(&head, websiteCreate("bannersbroker.com", "bannersbroker.com", 2644, 416, 0, 5790));
//    listInsert(&head, websiteCreate("americanexpress.com", "American Express", 3274, 336, 2241, 7170));
//    listInsert(&head, websiteCreate("mgid.com", "MGID Traffic Generation", 4472, 246, 43, 9790));
//    listInsert(&head, websiteCreate("webmd.com", "WebMD", 2582, 426, 13921, 5660));
//    listInsert(&head, websiteCreate("ezinearticles.com", "EzineArticles.com", 2466, 446, 154, 5400));
//    listInsert(&head, websiteCreate("groupon.com", "Groupon", 3081, 357, 1457, 6750));
//    listInsert(&head, websiteCreate("olx.in", "OLX India", 2423, 454, 1217, 5310));
//    listInsert(&head, websiteCreate("hurriyet.com.tr", "Hurriyet", 3293, 334, 3341, 7210));
//    listInsert(&head, websiteCreate("hdfcbank.com", "HDFC Bank Ltd.", 2523, 436, 24, 5530));
//    listInsert(&head, websiteCreate("usatoday.com", "USA Today", 2625, 419, 23203, 5750));
//    listInsert(&head, websiteCreate("nuvid.com", "nuvid.com", 2743, 401, 0, 6010));
//    listInsert(&head, websiteCreate("123rf.com", "123RF Royalty Free Stock Photos", 2607, 422, 0, 5710));
//    listInsert(&head, websiteCreate("zillow.com", "Zillow.com", 2148, 512, 15120, 4710));
//    listInsert(&head, websiteCreate("joomla.org", "Joomla!", 2613, 421, 30542, 5720));
//    listInsert(&head, websiteCreate("searchfunmoods.com", "searchfunmoods.com", 2981, 369, 0, 6530));
//    listInsert(&head, websiteCreate("naukri.com", "Naukri.com", 2263, 486, 0, 4960));
//    listInsert(&head, websiteCreate("businessinsider.com", "businessinsider.com", 2716, 405, 2250, 5950));
//    listInsert(&head, websiteCreate("zippyshare.com", "Zippyshare.com - Free File Hosting", 2494, 441, 307, 5460));
//    listInsert(&head, websiteCreate("google.ie", "Google", 2918, 377, 421, 6390));
//    listInsert(&head, websiteCreate("milliyet.com.tr", "Milliyet Gazetesi / Son Dakika haberleri", 2997, 367, 1403, 6570));
//    listInsert(&head, websiteCreate("youdao.com", "Youdao.com", 4490, 245, 7792, 9830));
//    listInsert(&head, websiteCreate("chip.de", "Chip", 2965, 371, 3052, 6500));
//    listInsert(&head, websiteCreate("51job.com", "www.51job.com", 3188, 345, 3048, 6980));
//    listInsert(&head, websiteCreate("clickbank.com", "ClickBank", 2632, 418, 172, 5760));
//    listInsert(&head, websiteCreate("xe.com", "XE.com", 2657, 414, 4618, 5820));
//    listInsert(&head, websiteCreate("maktoob.com", "Maktoob.com Inc.", 2196, 501, 1221, 4810));
//    listInsert(&head, websiteCreate("google.no", "Google", 2689, 409, 239, 5890));
//    listInsert(&head, websiteCreate("ero-advertising.com", "Ero-Advertising :: Advertising &amp Publishing", 3943, 279, 1688, 640));
//    listInsert(&head, websiteCreate("rapidshare.com", "RapidShare", 4089, 269, 1072, 8960));
//    listInsert(&head, websiteCreate("speedtest.net", "Speedtest.net", 2607, 422, 2475, 5710));
//    listInsert(&head, websiteCreate("abcnews.go.com", "ABCNews.com", 2576, 427, 505, 5640));
//    listInsert(&head, websiteCreate("ndtv.com", "NDTV", 2709, 406, 871, 5940));
//    listInsert(&head, websiteCreate("outlook.com", "You Have Reached Outlook", 2301, 478, 78, 5040));
//    listInsert(&head, websiteCreate("myfreecams.com", "MyFreeCams.com - The #1 adult webcam community. Free live webcams and video-chat.", 2287, 481, 418, 5010));
//    listInsert(&head, websiteCreate("sergey-mavrodi.com", "sergey-mavrodi.com", 3492, 315, 0, 7650));
//    listInsert(&head, websiteCreate("turbobit.net", "File Sharing Turbobit.net", 2771, 397, 316, 6070));
//    listInsert(&head, websiteCreate("google.dz", "Google.dz", 2412, 456, 0, 5280));
//    listInsert(&head, websiteCreate("bravotube.net", "bravotube.net", 2477, 444, 1, 5430));
//    listInsert(&head, websiteCreate("elmundo.es", "El Mundo", 2743, 401, 8100, 6010));
//    listInsert(&head, websiteCreate("microsoftonline.com", "microsoftonline.com", 1703, 646, 0, 3730));
//    listInsert(&head, websiteCreate("biglobe.ne.jp", "BIGLOBE", 6180, 178, 11416, 13540));
//    listInsert(&head, websiteCreate("mailchimp.com", "Mail Chimp", 2529, 435, 602, 5540));
//    listInsert(&head, websiteCreate("commentcamarche.net", "Comment Ca Marche", 2477, 444, 4668, 5430));
//    listInsert(&head, websiteCreate("claro-search.com", "claro-search.com", 2026, 543, 0, 4440));
//    listInsert(&head, websiteCreate("abril.com.br", "Abril", 2326, 473, 1123, 5090));
//    listInsert(&head, websiteCreate("examiner.com", "Examiner.com", 2296, 479, 13087, 5030));
//    listInsert(&head, websiteCreate("quikr.com", "Quikr India: free local Classifieds Ads and Want Ads for Housing, Apartments, Furniture, Matrimonials, Pets, Jobs, Resumes, Cars, Services, Events, Discussions and more.", 2249, 489, 5330, 4930));
//    listInsert(&head, websiteCreate("amazon.it", "Amazon.it", 2041, 539, 0, 4470));
//    listInsert(&head, websiteCreate("meetup.com", "Meetup", 2056, 535, 34364, 4500));
//    listInsert(&head, websiteCreate("hubpages.com", "HubPages", 2397, 459, 97, 5250));
//    listInsert(&head, websiteCreate("atwiki.jp", "atwiki.jp", 2651, 415, 3, 5810));
//    listInsert(&head, websiteCreate("letitbit.net", "Letitbit.net", 2423, 454, 55, 5310));
//    listInsert(&head, websiteCreate("888.com", "888", 2124, 518, 178, 4650));
//    listInsert(&head, websiteCreate("latimes.com", "Los Angeles Times", 1978, 556, 16080, 4330));
//    listInsert(&head, websiteCreate("odesk.com", "oDesk", 2222, 495, 844, 4870));
//    listInsert(&head, websiteCreate("typepad.com", "TypePad", 3416, 322, 15340, 7480));
//    listInsert(&head, websiteCreate("icicibank.com", "ICICI Bank", 2236, 492, 28, 4900));
//    listInsert(&head, websiteCreate("capitalone.com", "Capital One Financial Corp.", 2311, 476, 96, 5060));
//    listInsert(&head, websiteCreate("softpedia.com", "Softpedia", 2366, 465, 6010, 5180));
//    listInsert(&head, websiteCreate("google.fi", "Google Suomi", 2263, 486, 389, 4960));
//    listInsert(&head, websiteCreate("blackhatworld.com", "BlackHatWorld.com", 2174, 506, 189, 4760));
//    listInsert(&head, websiteCreate("xtendmedia.com", "XTEND Media", 781, 1409, 1, 1710));
//    listInsert(&head, websiteCreate("yoka.com", "yoka.com", 1174, 937, 0, 2570));
//    listInsert(&head, websiteCreate("linkwithin.com", "linkwithin.com", 4029, 273, 22282, 8830));
//    listInsert(&head, websiteCreate("w3.org", "World Wide Web Consortium", 2200, 500, 61743, 4820));
//    listInsert(&head, websiteCreate("bloomberg.com", "Bloomberg.com", 2119, 519, 11060, 4640));
//    listInsert(&head, websiteCreate("engadget.com", "Engadget", 2683, 410, 24227, 5880));
//    listInsert(&head, websiteCreate("cj.com", "Commission Junction", 2407, 457, 91, 5270));
//    listInsert(&head, websiteCreate("largeporntube.com", "largeporntube.com", 2254, 488, 1, 4940));
//    listInsert(&head, websiteCreate("surveymonkey.com", "SurveyMonkey", 2095, 525, 26741, 4590));
//    listInsert(&head, websiteCreate("accuweather.com", "AccuWeather", 1900, 579, 8927, 4160));
//
//
//    printf("hashPrintList(&head)\n");
//    hashPrintList(&head);
//
//    printf("\n\nbstPrintIndented(&head)\n");
//    bstPrintIndented(&head);
//
//    printf("\n\nbstPrintInorder(&head)\n");
//    bstPrintInorder(&head);
//
//
//    //TODO menu
//
//    //TODO quit
//
//    hashFree(&head);
//    bstFreeAll(&head);
//    return EXIT_SUCCESS;
//}
//
