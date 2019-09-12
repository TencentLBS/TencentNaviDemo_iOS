//
//  TNKNaviServices.h
//  TNKNavigation
//
//  Created by tabsong on 2018/5/28.
//  Copyright © 2018年 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@protocol TNKNaviServicesDelegate <NSObject>

// 导航关键日志，有助于定位导航问题
- (void)naviServicesOutputLog:(NSString *)text;

@end

/**
 * @brief 导航服务类.包含鉴权,获取版本号等功能
 */
@interface TNKNaviServices : NSObject

/**
 * @brief 获取单例
 */
+ (TNKNaviServices *)sharedServices;

/**
 * @brief apikey 在官网申请的服务授权标识的key
 */
@property (nonatomic, copy) NSString *APIKey;

/**
 * @brief 获取导航SDK的版本号(5.1.1)
 */
- (NSString *)sdkVersion;

@property (nonatomic, weak, nullable) id<TNKNaviServicesDelegate> delegate;

@end

NS_ASSUME_NONNULL_END
