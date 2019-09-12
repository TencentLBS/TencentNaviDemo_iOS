//
//  QPointAnnotation.h
//  QMapKit
//
//  Created by tabsong on 17/5/18.
//  Copyright © 2017年 tencent. All rights reserved.
//

#import "QShape.h"
#import "QAnnotation.h"
#import <CoreLocation/CoreLocation.h>

/**
 * @brief 点标注数据. 代表一个经纬度点位置的点状覆盖物的数据
 */
@interface QPointAnnotation : QShape <QAnnotation>

/**
 *  @brief  经纬度
 */
@property (nonatomic, assign) CLLocationCoordinate2D coordinate;

/**
 *  @brief  标题
 */
@property (copy) NSString *title;

/**
 *  @brief  副标题
 */
@property (copy) NSString *subtitle;

/**
 *  @brief  室内位置
 *
 * 添加完后修改无效
 */
@property (nonatomic, strong) QIndoorInfo *indoorInfo;

@end
