//
//  CellScore.h
//  InfinitGame
//
//  Created by Kha on 6/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface CellScore : UITableViewCell {
    
}

- (id)initHeader;
- (id)initWithDictionary: (NSDictionary*)nDict;



- (void)addItem: (NSArray*)nArray;

@end
