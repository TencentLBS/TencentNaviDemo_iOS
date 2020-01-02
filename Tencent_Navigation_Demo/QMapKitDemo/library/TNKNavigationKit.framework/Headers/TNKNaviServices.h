//
//  TNKNaviServices.h
//  TNKNavigation
//
//  Created by tabsong on 2018/5/28.
//  Copyright © 2018年 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

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
 * @brief 获取导航SDK的版本号(5.1.7)
 */
- (NSString *)sdkVersion;

/**
 * @brief identifier 设备标识，默认取自idfv。排查问题时需提供此identifier。注意，卸载重装时identifier可能发生变化。
 * 如果希望使用自己业务上的设备标识来排查问题，可以将identifier修改为自己业务上的设备标识。
 */
@property (nonatomic, copy) NSString *identifier;

@end

NS_ASSUME_NONNULL_END
