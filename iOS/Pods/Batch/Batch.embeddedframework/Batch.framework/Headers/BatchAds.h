//
//  BatchAds.h
//  Batch
//
//  https://batch.com
//  Copyright (c) 2014 Batch SDK. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import "BatchError.h"
#import "BatchNativeAd.h"

#pragma mark -
#pragma mark Ads completion blocks

/*!
 @abstract Completion block to use in your application when loading an interstitial.
 @param placement   : Unique placement string generated in your account.
 @param error       : The error or NULL. @see BatchError
 */
typedef void (^BatchInterstitialLoaded) (NSString *placement, BatchError * error) __attribute__((deprecated(ADS_DEPRECATION_MESSAGE)));

/*!
 @abstract Completion block to use in your application when loading a native ad.
 @param error       : The error or NULL. @see BatchError
 */
typedef void (^BatchNativeAdLoaded) (BatchError *error) __attribute__((deprecated(ADS_DEPRECATION_MESSAGE)));


#pragma mark -
#pragma mark BatchAdsDisplayDelegate delegate

/*!
 @protocol BatchAdDisplayDelegate
 @abstract The delegate called when an Ad is display.
 */
__attribute__((deprecated(ADS_DEPRECATION_MESSAGE)))
@protocol BatchAdsDisplayDelegate <NSObject>

@optional
/*!
 @method adDidAppear:
 @abstract The ad has been displayed.
 @param placement  :   Placement for which the Ad has been clicked.
 @warning The delegate method is always called in the main thread!
 */
- (void)adDidAppear:(NSString *)placement NS_AVAILABLE_IOS(6_0);

/*!
 @method adDidDisappear:
 @abstract The ad has disappeared.
 @param placement  :   Placement for which the Ad has been clicked.
 @warning The delegate method is always called in the main thread!
 */
- (void)adDidDisappear:(NSString *)placement NS_AVAILABLE_IOS(6_0);

/*!
 @method adClicked:
 @abstract Called when the user clicked on the ad.
 @discussion adDidDisappear: will be called afterwards.
 @param placement  :   Placement for which the Ad has been clicked.
 @warning The delegate method is always called in the main thread!
 */
- (void)adClicked:(NSString *)placement NS_AVAILABLE_IOS(6_0);

/*!
 @method adCancelled:
 @abstract Called when the user cancelled the ad.
 @discussion adDidDisappear: will be called afterwards.
 @param placement  :   Placement for which the Ad has been clicked.
 @warning The delegate method is always called in the main thread!
 */
- (void)adCancelled:(NSString *)placement NS_AVAILABLE_IOS(6_0);

/*!
 @method adNotDisplayed:
 @abstract The ad has not been displayed, see logs.
 @param placement  :   Placement for which the Ad has been clicked.
 @warning The delegate method is always called in the main thread!
 */
- (void)adNotDisplayed:(NSString *)placement NS_AVAILABLE_IOS(6_0);

@end


#pragma mark -
#pragma mark BatchAds interface

/*!
 @class BatchAds
 @abstract Call for all you need to display Ads.
 @discussion Actions you can perform in BatchAds.
 */
__attribute__((deprecated(ADS_DEPRECATION_MESSAGE)))
@interface BatchAds : NSObject

/*!
 @method init
 @warning Never call this method.
 */
- (instancetype)init NS_UNAVAILABLE;

/*!
 @method load
 @warning Never call this method.
 */
+ (void)load NS_UNAVAILABLE;

/*!
 @method setupAds
 @abstract Activate Batch Ads system.
 @discussion You can call this method from any thread.
 */
+ (void)setupAds NS_AVAILABLE_IOS(6_0);


#pragma mark -
#pragma mark Interstitial ads

/*!
 @method hasAdForPlacement:
 @abstract Check for the avaibility of Ads.
 @discussion You can call this method from any thread.
 @param placement  : Placement for which you want to check the Ad availability.
 @return YES if an Ad is available for the given placement, NO otherwise.
 */
+ (BOOL)hasInterstitialForPlacement:(NSString *)placement __attribute__((warn_unused_result)) NS_AVAILABLE_IOS(6_0);

/*!
 @method displayAdForPlacement:
 @abstract Show an Ad for a specific placement.
 @discussion You can call this method from any thread.
 @param placement  : Placement for which you want to display an ad.
 @return YES if no error found when displaying the Ad for the given placement, NO otherwise.
 */
+ (BOOL)displayInterstitialForPlacement:(NSString *)placement __attribute__((warn_unused_result)) NS_AVAILABLE_IOS(6_0);

/*!
 @method displayAdForPlacement:withDelegate:
 @abstract Show an Ad for a specific placement.
 @discussion You can call this method from any thread.
 @param placement   : Placement for which you want to display an ad.
 @param delegate    : Object that respond to BatchInterstitialDisplayDelegate for feedback.
 */
+ (void)displayInterstitialForPlacement:(NSString *)placement
              withDelegate:(id<BatchAdsDisplayDelegate>)delegate NS_AVAILABLE_IOS(6_0);

/*!
 @method setAutoLoad:
 @abstract Disable automatic loading of the ads.
 @discussion You will call loadAds before diplaying any ads.
 @discussion You can call this method from any thread.
 @param load   : Set to NO to disable automatic loading.
 */
+ (void)setAutoLoad:(BOOL)load NS_AVAILABLE_IOS(6_0);

/*!
 @method loadAdForPlacement:completion:
 @abstract Trigger ads loading.
 @discussion Calling this method without calling [BatchAds setAutoLoad:NO] will not load anything.
 @param placement   : Placement for which you want to load an ad.
 @param block       : Completion block called after excecution. @see BatchInterstitialLoaded
 @discussion You can call this method from any thread.
 */
+ (void)loadInterstitialForPlacement:(NSString *)placement completion:(BatchInterstitialLoaded)block NS_AVAILABLE_IOS(6_0);


#pragma mark -
#pragma mark Native ads

/*!
 @method loadNativeAd:completion:
 @abstract Trigger native ad loading.
 @discussion You will be notified of the result in the BatchNativeAd you set
 @param nativeAd    : Native Ad you wish to load. It must have been initialized with a placement.
 @param block       : Completion block called after excecution. @see BatchNativeAdLoaded
 @discussion You can call this method from any thread.
 */
+ (void)loadNativeAd:(BatchNativeAd *)nativeAd completion:(BatchNativeAdLoaded)block NS_AVAILABLE_IOS(6_0);

/*!
 @method loadNativeAd:completion:
 @abstract Trigger native ad loading with a specific content.
 @discussion You will be notified of the result in the BatchNativeAd you set
 @param nativeAd    : Native Ad you wish to load. It must have been initialized with a placement.
 @param content     : The content you will not use. @see BatchNativeAdContent
 @param block       : Completion block called after excecution. @see BatchNativeAdLoaded
 @discussion You can call this method from any thread.
 */
+ (void)loadNativeAd:(BatchNativeAd *)nativeAd withContent:(BatchNativeAdContent)content completion:(BatchNativeAdLoaded)block NS_AVAILABLE_IOS(6_0);

/*!
 @method loadNativeAd:completion:
 @abstract Trigger native ad loading with a specific content and image preloading options.
 @discussion You will be notified of the result in the BatchNativeAd you set
 @param nativeAd        : Native Ad you wish to load. It must have been initialized with a placement.
 @param content         : The content you will not use. @see BatchNativeAdContent
 @param preloadUIImages : Whether you want Batch to preload the Ad's UIImages for you. Warning: if set to NO, the iconImage and coverImage properties will always be nil.
 @param block           : Completion block called after excecution. @see BatchNativeAdLoaded
 @discussion You can call this method from any thread.
 */
+ (void)loadNativeAd:(BatchNativeAd *)nativeAd withContent:(BatchNativeAdContent)content preloadUIImages:(BOOL)preloadUIImages completion:(BatchNativeAdLoaded)block NS_AVAILABLE_IOS(6_0);

@end

#import "BatchAdsDeprecated.h"
