//
//  BatchUnlock.h
//  Batch
//
//  https://batch.com
//  Copyright (c) 2014 Batch SDK. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "BatchOffer.h"
#import "BatchError.h"

#pragma mark -
#pragma mark BatchUnlock delegate

/*!
 @protocol BatchUnlockDelegate
 @abstract Required delegate to use all the unlock functions.
 */
@protocol BatchUnlockDelegate <NSObject>

@required
/*!
 @method automaticOfferRedeemed:
 @abstract Called when an offer has been automatically redeemed.
 @discussion This method can be called many times depending on the number of automatic offers not already redeemed.
 @discussion You can call this method from any thread.
 @param offer   :   Redeemed offer. @see BatchOffer
 @warning The delegate method is always called in the main thread!
 */
- (void)automaticOfferRedeemed:(id<BatchOffer>)offer NS_AVAILABLE_IOS(6_0);

@optional
/*!
 @method URLWithCodeFound:
 @abstract Called when a Batch code has been found in the URL given in [Batch handleURL:(NSURL *)url].
 @discussion You can call this method from any thread.
 @param code    :   The found code.
 @warning The delegate method is always called in the main thread!
 */
- (void)URLWithCodeFound:(NSString *)code NS_AVAILABLE_IOS(6_0);

/*!
 @method URLWithCodeRedeemed:
 @abstract Called when everything run ok when a code has been found.
 @discussion You can call this method from any thread.
 @param offer   :   Redeemed offer or NULL. @see BatchOffer
 @warning The delegate method is always called in the main thread!
 */
- (void)URLWithCodeRedeemed:(id<BatchOffer>)offer NS_AVAILABLE_IOS(6_0);

/*!
 @method URLWithCodeFailed:
 @abstract Called when something is wrong treating the code found in the URL.
 @discussion You can call this method from any thread.
 @param error   :   The encoutered error. @see BatchError
 @warning The delegate method is always called in the main thread!
 */
- (void)URLWithCodeFailed:(BatchError *)error NS_AVAILABLE_IOS(6_0);

@end


#pragma mark -
#pragma mark Completion blocks

/*!
 @abstract Completion block to use in your application.
 @param offer       :   Redeemed offer or NULL. @see BatchOffer
 */
typedef void (^BatchSuccess) (id<BatchOffer> offer);

/*!
 @abstract Completion block to use for restore items.
 @param features    :   List of restored features. @see BatchFeature
 */
typedef void (^BatchRestoreSuccess) (NSArray *features);

/*!
 @abstract Completion block to use in your application.
 @param error       :   The error or NULL. @see BatchError
 */
typedef void (^BatchFail) (BatchError * error);


#pragma mark -
#pragma mark BatchUnlock interface

/*!
 @class BatchUnlock
 @abstract Call for all you need for content redeem actions.
 @discussion Actions you can perform in BatchUnlock.
 */
@interface BatchUnlock : NSObject

/*!
 @method init
 @warning Never call this method.
 */
- (instancetype)init NS_UNAVAILABLE;

/*!
 @method setupUnlockWithDelegate:
 @abstract Give Batch the unlock delegate and activate Batch Unlock system.
 @discussion You can call this method from any thread.
 @param delegate    : The Batch unlock object implementing BatchUnlockDelegate.
 @warning The delegates methods are always called in the main thread!
 */
+ (void)setupUnlockWithDelegate:(id<BatchUnlockDelegate>)delegate NS_AVAILABLE_IOS(6_0);

/*!
 @method redeemCode:success:failure:
 @abstract Redeem an offer using a code.
 @discussion You can call this method from any thread.
 @param code            :   The input code to get an offer from.
 @param successBlock    :   Callback when all has succeded. @see BatchSuccess
 @param failBlock       :   Callback when an error occured. @see BatchFail
 @warning The completion block is always called in the main thread!
 */
+ (void)redeemCode:(NSString *)code success:(BatchSuccess)successBlock failure:(BatchFail)failBlock NS_AVAILABLE_IOS(6_0);

/*!
 @method restoreFeatures:failure:
 @abstract Restore redeemed features.
 @discussion You can call this method from any thread.
 @param success     :   Callback when all has succeded. @see BatchRestoreSuccess
 @param fail        :   Callback when an error occured. @see BatchFail
 @warning The completion block is always called in the main thread!
 */
+ (void)restoreFeatures:(BatchRestoreSuccess)success failure:(BatchFail)fail NS_AVAILABLE_IOS(6_0);

@end
