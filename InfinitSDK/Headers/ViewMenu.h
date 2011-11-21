

#import <UIKit/UIKit.h>

#import "kDownload.h"

@class InfinitAPI;
@class MBProgressHUD;
@class UIComboBox;


@interface ViewMenu : UIView <UIScrollViewDelegate, UITextFieldDelegate, UITableViewDelegate, UITableViewDataSource, kDownloadManagerDelegate> {

@private
	InfinitAPI		*api;
	
	UIScrollView	*sclView;
	UIPageControl	*pageCtrl;
	
	MBProgressHUD	*loader;
	
	kDownloadManager *downloads;
	
	int				iStopLoader;
    UIInterfaceOrientation oldOrientation;
	
	
	// variable view Infinit
	UIView			*viewInfinit;
    
    // variable view Infinit
	UIView			*viewChoice;
	
	// variable view listGame
	UIView			*viewListGame;
	NSArray			*arrButton;
	
	// variable view tableScore
	UIView			*viewTableScore;
	UITableView		*tblScore;
	NSMutableArray	*arrScore;
	
	// variable view Account
	UIView			*viewAccount;
	UITextField		*txtNickname;
	UITextField		*txtEmail;
	UIComboBox		*cboAge;
	UIComboBox		*cboGender;
    UIButton        *btnAvatar;
    UIButton        *btnUpdate;
    NSURLConnection *connectUdate;
    NSMutableData   *connectData;

}

@property (nonatomic, retain) NSMutableArray *arrScore;




// INIT
- (id)initWithAccount;
- (id)initWithSubscribe;
- (id)initWithScore;





// PUBLIC METHOD
- (void)Show;
- (void)Hide;
- (void)gotoAccount;

@end
