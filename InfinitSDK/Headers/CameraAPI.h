//
//  CameraAPI.h
//  PuzzleKitchen_iPhone
//
//  Created by Kha on 6/15/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#define DOCSFOLDER [NSHomeDirectory() stringByAppendingPathComponent:@"Documents"]

@protocol CameraAPIDelegate <NSObject>

@optional
- (void)CropImage_Done: (UIImage*)nImage;
@end

@interface CameraAPI : UIImagePickerController <UIImagePickerControllerDelegate,UINavigationControllerDelegate> {

@private
    id <CameraAPIDelegate> delegateCamera;
}

@property (nonatomic, assign) id delegateCamera;

- (id) init:(UIImagePickerControllerSourceType)type;
- (void)Show;
- (void)Hide;

@end
