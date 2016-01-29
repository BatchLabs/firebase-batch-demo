//
//  BatchOffer.h
//  Batch
//
//  https://batch.com
//  Copyright (c) 2014 Batch SDK. All rights reserved.
//

#import <Foundation/Foundation.h>


#pragma mark -
#pragma mark Offer protocol

/*!
 @protocol BatchOffer
 @abstract Redeemed offer.
 @discussion Access to the list of objects that have been redeemed.
 */
@protocol BatchOffer <NSCoding>

@required
/*!
 @method hasFeatures
 @abstract Contains one or more features.
 @return YES if it contains, NO otherwise.
 */
- (BOOL)hasFeatures NS_AVAILABLE_IOS(6_0);

/*!
 @method features
 @abstract All the features that have been redeemed.
 @return A list of redeemed features or NULL.
 @see BatchFeature
 */
- (NSArray *)features NS_AVAILABLE_IOS(6_0);

/*!
 @method containsFeatureWithReference:
 @abstract Search for a feature by its reference.
 @param reference  :   Unique feature reference.
 @return YES if it contains one or more features with this reference, NO otherwise.
 */
- (BOOL)containsFeatureWithReference:(NSString *)reference NS_AVAILABLE_IOS(6_0);

/*!
 @method hasResources
 @abstract Contains one or more resource.
 @return YES if it contains, NO otherwise.
 */
- (BOOL)hasResources NS_AVAILABLE_IOS(6_0);

/*!
 @method resources
 @abstract All the resources that have been redeemed.
 @return A list of redeemed resources or NULL.
 @see BatchResource
 */
- (NSArray *)resources NS_AVAILABLE_IOS(6_0);

/*!
 @method containsResourceWithReference:
 @abstract Search for a resource by its reference.
 @param reference  :   Unique resource reference.
 @return YES if it contains one or more resources with this reference, NO otherwise.
 */
- (BOOL)containsResourceWithReference:(NSString *)reference NS_AVAILABLE_IOS(6_0);

/*!
 @method items
 @abstract All the items that have been redeemed.
 @return A list of redeemed items or NULL.
 @see BatchItem
 */
- (NSArray *)items NS_AVAILABLE_IOS(6_0);

/*!
 @method containsItemWithReference:
 @abstract Search for an item by its reference.
 @param reference  :   Unique item reference.
 @return YES if it contains one or more items with this reference, NO otherwise.
 */
- (BOOL)containsItemWithReference:(NSString *)reference NS_AVAILABLE_IOS(6_0);

/*!
 @method hasBundles
 @abstract Contains one or more bundle.
 @return YES if it contains, NO otherwise.
 */
- (BOOL)hasBundles NS_AVAILABLE_IOS(6_0);

/*!
 @method bundlesReferences
 @abstract All the bundles references that has been redeemed.
 @return A list of redeemed bundles references strings or NULL.
 */
- (NSArray *)bundlesReferences NS_AVAILABLE_IOS(6_0);

/*!
 @method offerReference
 @abstract Offer reference linked to this offer for tracking purposes.
 @return Offer reference string or NULL.
 */
- (NSString *)offerReference NS_AVAILABLE_IOS(6_0);

/*!
 @method offerAdditionalParameters
 @abstract Offer additional parameters.
 @return Dictionary of strings, can be empty.
 */
- (NSDictionary *)offerAdditionalParameters NS_AVAILABLE_IOS(6_0);

@end


#pragma mark -
#pragma mark Item protocol

/*!
 @protocol BatchItem
 @abstract This protocol describes methods an item implements.
 */
@protocol BatchItem <NSCoding>

@required
/*!
 @method reference
 @abstract Item reference.
 @return Reference string.
 */
- (NSString *)reference NS_AVAILABLE_IOS(6_0);

/*!
 @method isInBundle
 @abstract Item contained in a bundle.
 @return YES if the item is in a bundle, NO otherwise.
 */
- (BOOL)isInBundle NS_AVAILABLE_IOS(6_0);

/*!
 @method bundleReference
 @abstract Bundle reference if the item is in a bundle.
 @return The bundle reference string or NULL.
 */
- (NSString *)bundleReference NS_AVAILABLE_IOS(6_0);

@end


#pragma mark -
#pragma mark Feature protocol

/*!
 @protocol BatchFeature(BatchItem)
 @abstract This protocol describes methods a feature implements.
 */
@protocol BatchFeature <BatchItem, NSCoding>

@required
/*!
 @method value
 @abstract Feature value.
 @return The value string or NULL.
 */
- (NSString *)value NS_AVAILABLE_IOS(6_0);

/*!
 @method hasValue
 @abstract Check the value
 @return YES if a non empty and non null value is set.
 */
- (BOOL)hasValue NS_AVAILABLE_IOS(6_0);

/*!
 @method ttl
 @abstract Feature TTL, zero if lifetime.
 @return Seconds of Time To Live of the feature.
 */
- (NSUInteger)ttl NS_AVAILABLE_IOS(6_0);

/*!
 @method isLifetime
 @abstract Feature available lifetime or with a TTL.
 @return YES if the feature is available lifetime, NO if it has a TTL.
 */
- (BOOL)isLifetime NS_AVAILABLE_IOS(6_0);

@end


#pragma mark -
#pragma mark Resource protocol

/*!
 @protocol BatchResource(BatchItem)
 @abstract This protocol describes methods a resource implements.
 */
@protocol BatchResource <BatchItem, NSCoding>

@required
/*!
 @method quantity
 @abstract Resource quantity.
 @return Quantity value.
 */
- (NSUInteger)quantity NS_AVAILABLE_IOS(6_0);

@end