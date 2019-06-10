//
//  QMapServices.h
//  QMapKit
//
//  Copyright (c) 2017年 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * @brief 地图服务类
 */
@interface QMapServices : NSObject

/**
 * @brief 获取单例
 */
+ (nonnull QMapServices *)sharedServices;

/**
 * @brief apikey 在官网申请的服务授权标识的key
 */
@property (nonnull, copy, nonatomic) NSString *APIKey;

/**
 * @brief 获取地图SDK的版本号 (4.2.3.1)
 */
- (NSString * _Nonnull)sdkVersion;

@end
