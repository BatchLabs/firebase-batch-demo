//
//  BatchAdsDeprecated.h
//  Batch
//
//  https://batch.com
//  Copyright (c) 2014 Batch SDK. All rights reserved.
//

#import "BatchAds.h"

#pragma mark -
#pragma mark Ads completion blocks

/*!
 @abstract Completion block to use in your application when loading an interstitial.
 @param placement   : Unique placement string generated in your account.
 @param error       : The error or NULL. @see BatchError
 @deprecated in version 1.3
 */
typedef void (^BatchAdsLoaded) (NSString *placement, BatchError * error) __attribute__((deprecated("Batch Ads is deprecated")));


#pragma mark -
#pragma mark BatchAds interface

@interface BatchAds ()


#pragma mark -
#pragma mark Interstitial ads deprecation

/*!
 @method hasAdForPlacement:
 @abstract Check for the avaibility of Ads.
 @discussion You can call this method from any thread.
 @param placement  : Placement for which you want to check the Ad availability.
 @return YES if an Ad is available for the given placement, NO otherwise.
 @deprecated in version 1.3
 */
+ (BOOL)hasAdForPlacement:(NSString *)placement __attribute__((warn_unused_result, deprecated("Batch Ads is deprecated")));

/*!
 @method displayAdForPlacement:
 @abstract Show an Ad for a specific placement.
 @discussion You can call this method from any thread.
 @param placement  : Placement for which you want to display an ad.
 @return YES if no error found when displaying the Ad for the given placement, NO otherwise.
 @deprecated in version 1.3
 */
+ (BOOL)displayAdForPlacement:(NSString *)placement __attribute__((warn_unused_result, deprecated("Batch Ads is deprecated")));

/*!
 @method displayAdForPlacement:withDelegate:
 @abstract Show an Ad for a specific placement.
 @discussion You can call this method from any thread.
 @param placement   : Placement for which you want to display an ad.
 @param delegate    : Object that respond to BatchAdsDisplayDelegate for feedback.
 @deprecated in version 1.3
 */
+ (void)displayAdForPlacement:(NSString *)placement
              withDelegate:(id<BatchAdsDisplayDelegate>)delegate __attribute__((deprecated("Batch Ads is deprecated")));

/*!
 @method loadAdForPlacement:completion:
 @abstract Trigger ads loading.
 @discussion Calling this method without calling [BatchAds setAutoLoad:NO] will not load anything.
 @param placement   : Placement for which you want to load an ad.
 @param block       : Completion block called after excecution. @see BatchAdsLoaded
 @discussion You can call this method from any thread.
 @deprecated in version 1.3
 */
+ (void)loadAdForPlacement:(NSString *)placement completion:(BatchAdsLoaded)block __attribute__((deprecated("use method 'loadInterstitialForPlacement:completion:' instead")));

@end