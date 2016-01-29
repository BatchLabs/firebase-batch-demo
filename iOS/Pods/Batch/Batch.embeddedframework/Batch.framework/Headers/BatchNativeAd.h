//
//  BatchNativeAd.h
//  batch
//
//  https://batch.com
//  Copyright (c) 2015 Batch SDK. All rights reserved.
//

#import <Foundation/Foundation.h>

#define ADS_DEPRECATION_MESSAGE "Batch Ads has been discontinued"

/*!
 @enum BatchNativeAdState
 @abstract The different BatchNativeAd states.
 */
__attribute__((deprecated(ADS_DEPRECATION_MESSAGE)))
typedef NS_ENUM(NSInteger, BatchNativeAdState)
{
    // Ad is created but not loaded.
    BatchNativeAdStateNotLoaded = 0,
    
    // Ad is loading.
    BatchNativeAdStateLoading = 1,
    
    // Ad has fail to load.
    BatchNativeAdStateLoadFailed = 2,
    
    // Ad is ready to display.
    BatchNativeAdStateReady = 3,
    
    // Ad has expire: Do NOT display it.
    BatchNativeAdStateExpired = 4
};


/*!
 @enum BatchNativeAdContent
 @abstract The optional ad content.
 */
__attribute__((deprecated(ADS_DEPRECATION_MESSAGE)))
typedef NS_OPTIONS(NSUInteger, BatchNativeAdContent)
{
    // Remove all the optional content.
    BatchNativeAdContentAll         = 0,
    
    // Do not download the cover image.
    BatchNativeAdContentNoCover     = 1 << 0
};

/*!
 @class BatchNativeAd
 @abstract Native ad object.
 @discussion Class that manage the lifecycle and the content of a native ad.
 */
__attribute__((deprecated(ADS_DEPRECATION_MESSAGE)))
@interface BatchNativeAd : NSObject <NSCoding>

/*!
 @property state
 @abstract lifecycle state of this ad. @see BatchNativeAdState
 */
@property (readonly) BatchNativeAdState state;

/*!
 @property placement
 @abstract Placement for which you want to display this ad.
 */
@property (readonly) NSString *placement;

/*!
 @property title
 @abstract Native ad title.
 */
@property (readonly) NSString *title;

/*!
 @property body
 @abstract Native ad body text.
 */
@property (readonly) NSString *body;

/*!
 @property rating
 @abstract Native ad rating float value > 0.0 and <= to 5.0
 */
@property (readonly) NSNumber *starRating;

/*!
 @property callToAction
 @abstract Call to action text.
 */
@property (readonly) NSString *callToAction;

/*!
 @property iconImage
 @abstract Icon resource to look for.
 */
@property (readonly) UIImage *iconImage;

/*!
 @property iconImagePath
 @abstract Icon resource to look for.
 */
@property (readonly) NSString *iconImagePath;

/*!
 @property coverImage
 @abstract Big cover image (optional).
 */
@property (readonly) UIImage *coverImage;

/*!
 @property coverImagePath
 @abstract Big cover image (optional).
 */
@property (readonly) NSString *coverImagePath;

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
 @method initWithPlacement:andContent:
 @abstract Create a native ad object. You are in charge of keeping a reference to this object.
 @param placement   : The placement for which you create this object.
 @return An instance of BatchNativeAdState or nil.
 */
- (instancetype)initWithPlacement:(NSString *)placement __attribute__((warn_unused_result)) NS_AVAILABLE_IOS(6_0);

/*!
 @method registerView:
 @abstract Give the container view as soon as you have it.
 @param view    : The UIView in which you set the ad content.
 */
- (void)registerView:(UIView *)view NS_AVAILABLE_IOS(6_0);

/*!
 @method unregisterView
 @abstract Call this method when you unbind the ad content.
 */
- (void)unregisterView NS_AVAILABLE_IOS(6_0);

/*!
 @method performClickAction
 @abstract Call this method on your UIButton action or any clic action.
 @discussion This will trigger the action depending on the ad (open application store, open a web site…)
 */
- (void)performClickAction NS_AVAILABLE_IOS(6_0);

@end