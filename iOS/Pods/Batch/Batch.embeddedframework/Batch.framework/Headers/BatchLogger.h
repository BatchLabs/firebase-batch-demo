//
//  BatchLogger.h
//  Batch
//
//  https://batch.com
//  Copyright (c) 2015 Batch SDK. All rights reserved.
//

@protocol BatchLoggerDelegate <NSObject>

- (void)logWithMessage:(NSString*)message;

@end
