//
//  InfinitAPI.h
//  InfinitAPISample
//
//  Created by Dev on 3/28/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <StoreKit/StoreKit.h>
#import <SystemConfiguration/SystemConfiguration.h>
#import "JSON.h"


#define __API_UNKNOWN__                 -1
#define __API_NO_ACTION__               0
#define __API_QUIET_LOGIN__             1
#define __API_NEW_EMAIL__               2
#define __API_SEND_SCORE__              3
#define __API_CHANGE_DEVICE__           4
#define __API_CHECK_CURRENT_STATUS__    5
#define __API_RESEND_VALIDATION_EMAIL__ 6
#define __API_PURCHASING__              7
#define __API_EDIT_CUSTOMER__           8

#define __API_PRCSS_BUY__               100         // Launch the purchasing process
#define __API_PRCSS_BUY_CHECK_STATUS__  101         // 
#define __API_PRCSS_BUY_LAUNCH_CE__     102         // 
#define __API_PRCSS_BUY_LAUNCH_CNR__    103         // 

#define __API_PRCSS_SM_RETRY_PURCH__    110         // 

/*
 {"code":"10001", "message":"Email already existing"} 
 {"code":"10002", "message":"The asked game doesn’t exist."}]} 
 {"code":"10003", "message":"The asked game contest doesn’t exist."}
 {"code":"10004", "message":"Email format incorrect"}, 
 {"code":"10005", "message":"No email"}, 
 {"code":"10006", "message":"Gender incorrect"}, 
 {"code":"10007", "message":"The avatar cannot be saved"}
 {"code":"10008", "message":"The subscription pack failed."} 
 {"code":"10009", "message":"Impossible to store the score at this moment."} 
 {"code":"10010", "message":"Impossible to save the subscription in the database"} 
 {"code":"10011","message":"The email for validation has already been sent."}
 */

#define __ERR_EMAIL_EXIST_ALREADY__         10001
#define __ERR_GAME_DOESNT_EXIST__           10002
#define __ERR_GAME_CONTEST_DOESNT_EXIST__   10003
#define __ERR_EMAIL_FORMAT_INCORRECT__      10004
#define __ERR_NO_EMAIL__                    10005
#define __ERR_GENDER_INCORRECT__            10006
#define __ERR_AVATAR_CANNOT_BE_SAVED__      10007
#define __ERR_SUBSCRIPTION_PACK_FAILED__    10008
#define __ERR_IMPOSSIBLE_STORE_SCORE_NOW__  10009
#define __ERR_IMPOSSIBLE___ 10010
#define __ERR_10011__ 10011
#define __ERR_10012__ 10012
#define __ERR_10013__ 10013
#define __ERR_10014__ 10014
#define __ERR_10015__ 10015

#define getSession() ((NSMutableArray*)[[InfinitAPI sharedInstance] getSession])

// Reachability enum
typedef enum {
	NotReachable = 0,
	ReachableViaWiFi,
	ReachableViaWWAN
} iapi_NetworkStatus;

//#define iapi_ReachabilityChangedNotification @"iapi_NetworkReachabilityChangedNotification"

@protocol InfinitAPIDelegate<NSObject>

@optional

- (void)didQuietLoginSuccess:(NSDictionary*)userInfor;
- (void)didQuietLoginFail:(NSString*)error;

- (void)didBuyPackSuccess:(NSString*)receptionId;
- (void)didBuyPackFail:(NSString*)error;

@end

@interface InfinitAPI : NSObject<UIAlertViewDelegate, SKProductsRequestDelegate, SKPaymentTransactionObserver, UITextFieldDelegate> {
	NSURLConnection *quietLoginConnection;
	NSURLConnection *newEmailConnection;
	NSURLConnection *newScoreConnection;
	NSURLConnection *secureSubcriptionConnection;
	NSURLConnection *changeDeviceConnection;
	NSURLConnection *statusCheckConnection;
	NSURLConnection *resendValidationConnection;

	NSMutableData *quietLoginReceivedData;
	NSMutableData *newEmailReceivedData;
	NSMutableData *newScoreReceivedData;
	NSMutableData *secureSubcriptionReceivedData;
	NSMutableData *changeDeviceReceivedData;
	NSMutableData *statusCheckReceivedData;
	NSMutableData *resendValidationReceivedData;
	NSMutableData *junkReceivedData;                // junk received

	UIAlertView *newEmailAlert;                     // Popup displayed when account has no email
	UIAlertView *afterPurchasePackAlert;                      // Popup to ask user to purchase the pack
	UIAlertView *changeDeviceAlert;                 // Popup to ask user to validate the device change
	UIAlertView *resendEmailAlert;                  // Popup to ask user to resend the validation email
    
	UIAlertView *showMessage;                       // Dead-end message popup to lock the app
    
	id<InfinitAPIDelegate> delegate;                // Delegate id
    
	NSString *product_id;                           // product to purchase
    
    NSInteger product_choice ; // day , week , month , year 
    NSString *UDID;                                 // UDID
    NSString *deviceToken;                          // deviceToken
    NSString *locale;                               // Language
    NSString *userStatus;                           // Status
    NSString *userName;                             // Pseudo
    NSString *userEmail;                            // User email
    NSString *userID;                               // Player ID
    NSString *userAvatar;                           // User avatar
    NSString *userAge;                              // User Age.
    NSString *userStartSubscription;                // User subscription start date
    NSString *userEndSubscription;                  // User subscription end date
    NSString *userEmailStatus;                      // User Email status
    NSString *userGender;                           // User Gender
     NSString *priceweek;
     NSString *pricemonth;
    NSString *priceyear;
    NSString *message;                             // Commercial message
    
    NSMutableDictionary *userInformationDict;       // 
    NSArray *categories;                            //  
    NSString *game_id;                              // id of game
    NSInteger localScore;                           // local score of player
    NSString *dateGetScore;                         // date get score
    NSString *receiptionId;                         // 

    NSString *sessionId;                            // get Session ID ( PHP Session ) -- unused --
    NSArray *_cookies;                              // The stored cookies
    NSMutableArray *_cookiesFull;                   // Full cookie jar
    
    NSThread *sendScoreThread;                      // Thread to send score
    NSTimer *runThreadTimer;                        // Thread timer
    
    int currentRetries;                             // Current retries counter
    
    // Modal processing
    // The SDK acts as a proxy for the validation
    // The 2 objects will be used to trigger the event after the succes ( or failure ) of the process
    NSObject *proxyTargetObject;
    SEL      endOfProxyMethod;

    BOOL lock;                                      // 
    int currentOperation;                           // 

    BOOL justPurchased;                             // If the current user purchased from within the current app launching
    BOOL letMeCreateMyProfile;                      // If the user wants to create its profile after purchasing
    
    // Reachability
    BOOL localWiFiRef;
	SCNetworkReachabilityRef reachabilityRef;
    BOOL internetReachable;                         // Is Internet reachable?
    //    InfinitAPI *internetReachabilityNotifier;       // Link to self for reachability notifier

    // Push preferences from the iPhone configuration
    BOOL pushBagdesEnabled;
    BOOL pushSoundsEnabled;
    BOOL pushAlertEnabled;

    NSString *APIKey;                                       // This is your APIKey that has been provided by SerialScreener
    NSInteger PartnerID;                                         // This is your PartnerID that has been provided by SerialScreener
    NSString *appName;                               // This is your appName that has been provided by SerialScreener
    NSString *appVersion;                                   // WILL BE REMOVED, DO NOT USE
    NSString *gameID;                                        // This is the gameID that has been provided by SerialScreener
    NSString *inAppID; 
    NSString *inAppIDweek; 
    NSString *inAppIDmonth; 
    NSString *inAppIDyear; 
    BOOL initprice; 
    //static NSString *inAppID = @"com.infinitgame.infinitgamebeta.Beta1";    // This is the in-app purchase renewal 

    NSInteger levelRequired;             // Default is Customer with Email
    BOOL autoRedirectOnPurchasePack;    // If level required is higher than current level of customer, automatically pop up Pack Purchase

    // If you want the users to be able to play even with no registration ( no email sent ) 
    // then set this to NO
    // Otherwise if you want the users to have to set the email when they log in first time, set this to YES
    BOOL infinitAPIisMandatory;
    BOOL loadInternalProxy;            // will load ViewMenu:purchaseIsSuccessful when reached the purchase process
    // Internal target for the proxy 
    NSObject *proxyInternalTargetObject;
    SEL      endOfInternalProxyMethod;

    NSInteger onConnectionFailureRetryCount; //Number of times retrieve connection
    NSInteger connectionTimeoutInterval; //Timeout interval in miliseconds. Reasonnable range [250, 1000]
}

@property (nonatomic, assign) id<InfinitAPIDelegate> delegate;
@property (nonatomic, copy) NSString *product_id;	//product to purchase
@property (nonatomic , assign ) NSInteger product_choice;
@property (nonatomic, retain) NSArray* _cookies;
@property (nonatomic, retain) NSMutableArray* _cookiesFull;
@property (nonatomic, retain) NSArray *categories;
@property (nonatomic, assign) BOOL lock;
@property (nonatomic, assign) BOOL justPurchased;
@property (nonatomic, assign) BOOL letMeCreateMyProfile;
@property (nonatomic, assign) BOOL pushBadgesEnabled;
@property (nonatomic, assign) BOOL pushSoundsEnabled;
@property (nonatomic, assign) BOOL pushAlertEnabled;
@property (nonatomic, assign) BOOL initprice;
@property (nonatomic, assign) NSObject *proxyTargetObject;
@property (nonatomic, assign) SEL endOfProxyMethod;
@property (nonatomic, assign) NSObject *proxyInternalTargetObject;
@property (nonatomic, assign) SEL endOfInternalProxyMethod;
@property (nonatomic, assign) int currentOperation;
@property (nonatomic, assign) NSURLConnection *quietLoginConnection;
@property (nonatomic, copy) NSString *userStatus;
@property (nonatomic, copy) NSString *userName;
@property (nonatomic, copy) NSString *userEmail;
@property (nonatomic, copy) NSString *userID;
@property (nonatomic, copy) NSString *userAvatar;
@property (nonatomic, copy) NSString *userAge;
@property (nonatomic, copy) NSString *userGender;
@property (nonatomic, copy) NSString *priceweek;
@property (nonatomic, copy) NSString *pricemonth;
@property (nonatomic, copy) NSString *priceyear;
@property (nonatomic, copy) NSString *message;
@property (nonatomic, copy) NSString *UDID;
@property (nonatomic, copy) NSString *deviceToken;
@property (nonatomic, copy) NSString *locale;
@property (nonatomic, copy) NSString *game_id;
@property (nonatomic, assign) NSInteger localScore;
@property (nonatomic, copy) NSString *userStartSubscription;
@property (nonatomic, copy) NSString *userEndSubscription;
@property (nonatomic, copy) NSString *userEmailStatus;
@property (nonatomic, retain) NSMutableDictionary *userInformationDict;

/* API CONFIG VALUES */
@property (nonatomic, copy) NSString *APIKey;
@property (nonatomic, assign) NSInteger PartnerID;
@property (nonatomic, copy) NSString *appName;
@property (nonatomic, copy) NSString *appVersion;
@property (nonatomic, copy) NSString *gameID;
@property (nonatomic, copy) NSString *inAppID;
@property (nonatomic, copy) NSString *inAppIDweek;
@property (nonatomic, copy) NSString *inAppIDmonth;
@property (nonatomic, copy) NSString *inAppIDyear;

@property (nonatomic, assign) NSInteger levelRequired;
@property (nonatomic, assign) BOOL autoRedirectOnPurchasePack;

@property (nonatomic, assign) BOOL infinitAPIisMandatory;
@property (nonatomic, assign) NSInteger onConnectionFailureRetryCount;
@property (nonatomic, assign) NSInteger connectionTimeoutInterval;

@property (nonatomic, assign) BOOL loadInternalProxy;

+ (InfinitAPI*)sharedInstance;
+ (NSString*)getServerURL;

- (void)loadConfig;
- (BOOL)checkKeyChain;
- (NSString*)encrypt:(NSString*)inData;
- (BOOL)openSSLConnection:(NSURL*)url withData:(NSData*)postData;
- (BOOL)callAPIForNewEmail:(NSString*)email;
- (BOOL)callAPIForSendScore:(NSInteger)score at:(NSString*)time;
- (BOOL)callAPIForChangeDevice:(NSString*)email;
- (BOOL)callAPIForCheckUserStatus;
- (BOOL)callAPIForResendEmailValidation;
- (BOOL)callAPIForCheckSubcription;
- (BOOL)callAPIForPurchaseSubcription;
- (BOOL)callAPIForQuietLogin:(NSObject*)target selector:(SEL)selector;
- (BOOL)callAPIForBuyProcess:(BOOL)init buyproduct:(NSInteger)product;

// Easy accessors for 3rd parties
- (BOOL)isLoggedUser;
- (BOOL)hasEmail;
- (BOOL)isEmailValid;
- (BOOL)isValidCustomer;
- (BOOL)isCustomerWithEmail;
- (BOOL)isCustomerNotRenewed;
- (BOOL)isRegisteredCustomer;
- (BOOL)isCustomerAbleToBuy;

// Modal pop-ups
- (NSData*)callModalPopupForAfterPurchasePack:(NSString*)_message;
- (NSData*)callModalPopupForNewEmail:(NSString*)_message;
- (NSData*)callModalPopupForChangeDevice:(NSString*)_message;
- (void)callModalPopupForShowMessage:(NSString*)_message buttonLess:(BOOL)buttonLess cancelButton:(BOOL)cancelButton;
- (void)callModalPopupForChangeDeviceDelegate;
- (NSData*)callModalPopupForResendValidationEmail;

- (void)checkSubscription;
- (NSDictionary*)getUserInformation;

- (NSString*)getUDID;
- (NSString*)getLocale;
- (NSString*)getUserName;
- (NSString*)getUserEmail;
- (NSString*)getUserID;
- (NSString*)getUserAvatar;
- (NSString*)getUserAge;
- (NSString*)getUserGender;
- (NSString*)getUserStartSubscription;
- (NSString*)getUserEndSubscription;
- (NSString*)getUTCFormateDate:(NSDate *)localDate;
- (void)setUserInformationDictionnary:(NSDictionary*)dict;
- (NSString*)getUserStatus;
- (NSString*)getCommercialMessage;
- (NSArray*)getCategories;
- (NSString*)getSessionId;
- (NSString*)getSessionIdHeader;
- (void)prepareURL:(NSMutableURLRequest*)URL;
- (NSMutableArray*)getSession;
- (void)testSession;

- (void)resendScore;

// Lock/Unlock
- (BOOL)lock;
- (void)unlock;
- (BOOL)isLock;
- (BOOL)startModal;

// Set of functions to define the current API Actions and manage
- (void)setCurrentAPIAction:(int)action;
- (void)resetCurrentAPIAction;
- (int)currentAPIAction;
- (NSString*)currentAPIActionAsString;
- (BOOL)isHavingCurrentAPIAction;

// Load proxy object
- (void)loadProxyObject:(NSObject*)target selector:(SEL)selector;
- (void)loadInternalProxyObject:(NSObject*)target selector:(SEL)selector;
// Trigger proxy target method
- (void)triggerProxyTargetMethod;
- (void)triggerInternalProxyTargetMethod;

// email validator
- (BOOL) validateEmail: (NSString *) candidate;

// Delegate UIAlertView
- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex;
- (void)alertViewCancel:(UIAlertView *)alertView;
- (void)didPresentAlertView:(UIAlertView *)alertView;
- (void)alertView:(UIAlertView *)alertView didDismissWithButtonIndex:(NSInteger)buttonIndex;
- (void)alertView:(UIAlertView *)alertView willDismissWithButtonIndex:(NSInteger)buttonIndex;

- (void)alertError:(NSString*)error;

// in-app purchase custom functions
- (void)loadProductsInfo;
- (void)loadProductsInfoInit;
- (void)makePurchase: (SKProduct *) product;
- (BOOL)isPresentNonFinishedTransaction;

// Kha add new method for keychain storing ( offline usage )
- (NSString*)toDataString;
- (void)getDataForm: (NSString*)nString;

- (void)storeToKeyChain;
- (void)loadFromKeyChain;

// Kha add new method for call popup
- (NSData*)callPopupForCommercialMessage;
- (NSData*)callPopupForScore;
- (NSData*)callPopupForSubscriptionScreen;

- (NSData*)callPopupMenu;



// Reachability
- (BOOL)isInternetAvailable;
- (BOOL) iapi_isReachable;
- (BOOL) iapi_isConnectionRequired;

//reachabilityWithHostName- Use to check the reachability of a particular host name. 
- (InfinitAPI*) iapi_reachabilityWithHostName: (NSString*) hostName;

//reachabilityWithAddress- Use to check the reachability of a particular IP address. 
- (InfinitAPI*) iapi_reachabilityWithAddress: (const struct sockaddr_in*) hostAddress;

//reachabilityForInternetConnection- checks whether the default route is available.  
//  Should be used by applications that do not connect to a particular host
- (InfinitAPI*) iapi_reachabilityForInternetConnection;

//reachabilityForLocalWiFi- checks whether a local wifi connection is available.
- (InfinitAPI*) iapi_reachabilityForLocalWiFi;

- (iapi_NetworkStatus) iapi_localWiFiStatusForFlags: (SCNetworkReachabilityFlags) flags;
- (iapi_NetworkStatus) iapi_networkStatusForFlags: (SCNetworkReachabilityFlags) flags;

//Start listening for reachability notifications on the current run loop
- (BOOL) iapi_startNotifier;
- (void) iapi_stopNotifier;

- (iapi_NetworkStatus) iapi_currentReachabilityStatus;
//WWAN may be available, but not active until a connection has been established.
//WiFi may require a connection for VPN on Demand.
- (BOOL) iapi_connectionRequired;

// Callback
- (void) iapi_reachabilityChanged: (NSNotification* )note;

// Updated logic
- (void) updateConnectivityStatus: (InfinitAPI*) curReach;

- (NSString*) localize: (NSString*)tr;

@end