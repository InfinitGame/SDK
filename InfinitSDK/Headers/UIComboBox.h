//
//  UIComboBox.h
//  ComboBox
//
//  Created by Kha on 5/19/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@class UIComboBox;

@protocol UIComboBoxDelegate <NSObject>

@optional
- (void)ComboBox_ChangeValue: (UIComboBox*)sender;
- (void)ComboBox_Active: (UIComboBox*)sender;
- (void)ComboBox_Deactive: (UIComboBox*)sender;


@end




@interface UIComboBox : UIView <UIPickerViewDelegate, UIActionSheetDelegate>{
    
@private
    UIButton *btnCbo;
    UIButton *btnDone;
	UILabel *lblValue;
    UIPickerView *picker;
    UIActionSheet *actSheet;
    
    NSString *oldValue;
    
    NSArray *arrData;
    
    bool bShow;
    UIInterfaceOrientation orientation;
    
    id <UIComboBoxDelegate> delegate;
}

@property (nonatomic, retain) NSString *ValueCBO;
@property (nonatomic, assign) id delegate;
@property (nonatomic, readonly) int IndexOfSelect;
@property (nonatomic, readonly) bool isShow;
@property (nonatomic) UIInterfaceOrientation orientation;




- (id)initWithArray: (NSArray*)nArray;
- (void)dealloc;




- (void)Show;
- (void)Hide;
- (void)HideWithoutDelegate;

@end
