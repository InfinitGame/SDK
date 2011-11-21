//
//  kDownload.h
//  iSEXO
//
//  Created by Nguyen Kha on 7/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>



@class kDownload;


@protocol kDownloadDelegate

@optional
- (void)downloadFinish: (kDownload*)nDownload;
- (void)downloadFail: (kDownload*)nDownload didFailWithError:(NSError *)error;

@end




@interface kDownload : NSObject {

@private
	NSMutableData		*dataDownload;
	NSURLConnection		*connectDownload;
    
	id<kDownloadDelegate> delegateDownload;

}


@property (nonatomic, retain)NSMutableData *dataDownload;
@property (nonatomic, assign)id delegateDownload;






- (id)initWithString: (NSString*)nURL;
- (void)dealloc;






- (void)Start;
- (void)Stop;


@end






@class kDownloadManager;


#pragma mark DELEGATE
@protocol kDownloadManagerDelegate

@optional
- (void)downloadFinishAll;
- (void)downloadFinish: (kDownload*)nDownload forKey: (NSString*)key;
- (void)downloadFail: (kDownload*)nDownload forKey: (NSString*)key didFailWithError:(NSError *)error;

@end



@interface kDownloadManager : NSObject <kDownloadDelegate> {
	
@private
	NSMutableDictionary *listDownload;
	
	id<kDownloadManagerDelegate> delegate;
	
}

@property (nonatomic, readonly) int count;
@property (nonatomic, assign) id delegate;





#pragma mark CONTRUCTOR & DETRUCTOR Method
- (id)init;
- (void)dealloc;





#pragma mark PUBLIC METHOD
- (kDownload*)addURL: (NSString*)nUrl forKey: (NSString*)key;
- (kDownload*)addDownload: (kDownload*)nDownload forKey: (NSString*)key;

- (void)removeForKey: (NSString*)key;

- (void)StopAll;

@end