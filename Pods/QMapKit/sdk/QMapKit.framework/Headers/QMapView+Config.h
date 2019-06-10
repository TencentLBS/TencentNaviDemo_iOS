//
//  QMapView+Config.h
//  QMapKit
//
//  Created by Zhang Tian on 2018/5/9.
//  Copyright © 2018年 tencent. All rights reserved.
//

#import <QMapKit/QMapKit.h>

/**
 * @brief 地图View的配置.
 */
@interface QMapConfig : NSObject

/**
 * @brief 附加 appId, 这里目前是为小程序提供, 传入小程序的 appId.
 */
@property (nonatomic, copy, readonly) NSString *subID;

/**
 * @brief 附加 key, 这里目前是为小程序提供, 需要小程序开发者传入申请的 key.
 */
@property (nonatomic, copy, readonly) NSString *subKey;


/**
 * @brief 初始化 QMapConfig.
 *
 * @param subID  附加 appId.
 * @param subKey 附加 key.
 * @return QMapConfig 对象.
 */
- (instancetype)initWithSubID:(NSString *)subID subKey:(NSString *)subKey;

@end

/**
 * @brief 地图View的配置相关API.
 */
@interface QMapView (Config)

/**
 * @brief 初始化 QMapView
 *
 * @param frame  QMapView 的 frame 矩形.
 * @param config QMapView 的配置属性.
 * @return QMapView 对象.
 */
- (instancetype)initWithFrame:(CGRect)frame config:(QMapConfig *)config;

@end
