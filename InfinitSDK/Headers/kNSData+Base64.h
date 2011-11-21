//
//  kkNSData+Base64.h
//  InfinitGame-r33
//
//  Created by Kha on 7/19/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface kNSData_Base64 : NSObject {
    
}
+ (NSData *)iapi_dataFromBase64String:(NSString *)nString;
+ (NSString *)iapi_base64EncodedString: (NSData*)nData;

@end
