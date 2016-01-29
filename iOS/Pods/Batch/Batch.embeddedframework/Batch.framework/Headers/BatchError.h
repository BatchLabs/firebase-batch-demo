//
//  BatchError.h
//  Batch
//
//  https://batch.com
//  Copyright (c) 2014 Batch SDK. All rights reserved.
//

#import <Foundation/Foundation.h>

/*!
 @enum BatchFailReason
 @abstract Error code types.
 @discussion Change depending on the encountered error.
 */
enum
{
    /*!
     @param NSInteger A network problem occurred.
     */
    BatchFailReasonNetworkError             = -10,
    
    /*!
     @param NSInteger Invalid API key.
     */
    BatchFailReasonInvalidAPIKey            = -20,

    /*!
     @param NSInteger Deactivated API Key.
     */
    BatchFailReasonDeactivatedAPIKey        = -30,

    /*!
     @param NSInteger The given code is invalid.
     */
    BatchFailReasonInvalidCode              = -40,
    
    /*!
     @param NSInteger Another problem occurred. A retry can succeed
     */
    BatchFailReasonUnexpectedError          = -50,
    
    /*!
     @param NSInteger Input code doesn't match the conditions.
     */
    BatchFailReasonMismatchConditions       = -60,
    
    /*!
     @param NSInteger Input placement is unknown.
     */
    BatchFailReasonUnknownPlacement         = -70,
    
    /*!
     @param NSInteger No Ad found for a placement.
     */
    BatchFailReasonNoAdFound                = -80,
    
    /*!
     @param NSInteger Batch Ads module was not configured correctly.
     */
    BatchFailReasonAdsWrongSetup            = -90
};
/*!
 @typedef BatchFailReason
 */
typedef NSInteger BatchFailReason;


// User info dictionary keys.
extern NSString *const BatchFailReasonInvalidCodeKey;           // On BatchErrorCodeInvalidCode, store an NSString code that generates this error.
extern NSString *const BatchFailReasonInvalidCodeErrorKey;      // On BatchErrorCodeInvalidCode, store one of the BatchReasonCode invalid code reasons (see below).
extern NSString *const BatchFailReasonMissingApplicationsKey;   // On BatchErrorCodeMismatchConditions, store an NSArray containing id<BatchApplication>.


/*!
 @enum BatchInvalidCodeError
 @abstract Invalid code error reasons.
 @discussion Change depending on the encountered error.
 */
enum
{
    /*!
     @param NSInteger Value in BatchFailReasonInvalidCodeErrorKey when the offer is paused.
     */
    BatchInvalidCodeErrorOfferPaused                = 100,
    
    /*!
     @param NSInteger Value in BatchFailReasonInvalidCodeErrorKey when the offer has already been acquired by the user.
     */
    BatchInvalidCodeErrorOfferAlreadyAcquired       = 101,
    
    /*!
     @param NSInteger Value in BatchFailReasonInvalidCodeErrorKey when an offercode has already been consumed.
     */
    BatchInvalidCodeErrorAlreadyConsumed            = 102,
    
    /*!
     @param NSInteger Value in BatchFailReasonInvalidCodeErrorKey when the offer cap has been reached.
     */
    BatchInvalidCodeErrorOfferCapped                = 103,
    
    /*!
     @param NSInteger Value in BatchFailReasonInvalidCodeErrorKey when the offer has expired.
     */
    BatchInvalidCodeErrorOfferExpired               = 104,
    
    /*!
     @param NSInteger Value in BatchFailReasonInvalidCodeErrorKey when the given code is unknown.
     */
    BatchInvalidCodeErrorUnknownCode                = 105,
    
    /*!
     @param NSinteger Value in BatchFailReasonInvalidCodeErrorKey when some conditions are missing. Call missingApplications: to get the list of missing applications.
     */
    BatchInvalidCodeErrorMissingConditions          = 106,
    
    /*!
     @param NSinteger Value in BatchFailReasonInvalidCodeErrorKey when the offer doesn't match the library version.
     */
    BatchInvalidCodeErrorOfferUnsupported           = 107,
    
    /*!
     @param NSinteger Value in BatchFailReasonInvalidCodeErrorKey when the offer is not yet started.
     */
    BatchInvalidCodeErrorOfferNotStarted            = 108,
    
    /*!
     @param NSinteger Value in BatchFailReasonInvalidCodeErrorKey when the user is not targeted by your offer (ex: target only new users, etc...).
     */
    BatchInvalidCodeErrorUserNotTargeted            = 109,
    
    /*!
     @param NSinteger Value in BatchFailReasonInvalidCodeErrorKey when the server has an error or an invalid state (ex: unable to retrieve an offer which should be retrievable).
     */
    BatchInvalidCodeErrorServerError                = 110
};
/*!
 @typedef BatchInvalidCodeError
 */
typedef NSInteger BatchInvalidCodeError;


/*!
 @class BatchError(NSError)
 @abstract Error object returned in callbacks.
 @discussion Use the appropriate userInfo depending on the BatchFailReason.
 */
@interface BatchError : NSError

/*!
 @method localizedDescription
 @abstract Override the NSError method providing a more accurate result.
 @return Additional info which may be used to describe the error or nil.
 */
- (NSString *)localizedDescription __attribute__((warn_unused_result));

/*!
 @method invalidCode
 @abstract Helper to find the code that generates a BatchFailReasonInvalidCode error.
 @return The NSString code or nil.
 */
- (NSString *)invalidCode __attribute__((warn_unused_result)) NS_AVAILABLE_IOS(6_0);

/*!
 @method invalidCodeError
 @abstract Helper to find one of the invalid code error reasons generated by a BatchFailReasonInvalidCode error.
 @return One of the reasons described by BatchInvalidCodeError or 0 if the error was not a BatchFailReasonInvalidCode.
 */
- (NSUInteger)invalidCodeError __attribute__((warn_unused_result)) NS_AVAILABLE_IOS(6_0);

/*!
 @method missingApplications
 @abstract Helper to find the applications that generate a BatchInvalidCodeErrorMissingConditions error.
 @return The NSArray of objects implementing BatchApplication protocol. @see BatchApplication
 */
- (NSArray *)missingApplications __attribute__((warn_unused_result)) NS_AVAILABLE_IOS(6_0);

@end


#pragma mark -
#pragma mark BatchApplication protocol

/*!
 @protocol BatchApplication
 @abstract This protocol describes methods an application implements.
 */
@protocol BatchApplication <NSObject>

/*!
 @method scheme
 @abstract Application scheme to open.
 @return The NSURL of the application scheme.
 */
- (NSURL *)scheme __attribute__((warn_unused_result)) NS_AVAILABLE_IOS(6_0);

@end