//
//  QMapView+Indoor.h
//  QMapKit
//
//  Created by fan on 2017/11/21.
//  Copyright © 2017年 tencent. All rights reserved.
//

#import "QMapView.h"
#import "QIndoorBuilding.h"
#import "QIndoorLevel.h"
#import "QIndoorInfo.h"

/**
 * @brief QMapView室内图的Delegate. 与QMapViewDelegate共用delegate
 */
@protocol QMapViewIndoorDelegate <NSObject>

/**
 * @brief 更新 激活态室内图 后会调用此函数
 *  @param mapView 地图View
 *  @param building 激活态室内图
 */
- (void)mapView:(QMapView *)mapView didChangeActiveBuilding:(QIndoorBuilding *)building;

/**
 * @brief 更新 激活态室内图楼层 后会调用此函数
 *  @param mapView 地图View
 *  @param level 室内图楼层
 */
- (void)mapView:(QMapView *)mapView didChangeActiveLevel:(QIndoorLevel *)level;

@end

/**
 * @brief QMapView室内图的相关API
 */
@interface QMapView (Indoor)

/**
 * @brief  室内图开关. 默认为NO.
 */
- (void)setIndoorEnabled:(BOOL)indoorEnabled;

/**
 * @brief  是否使用内置的楼层选择控件. 默认为YES.
 */
@property(nonatomic, assign) BOOL indoorPicker;

/**
 * @brief  默认的楼层选择控件偏移位置. 向右下增长
 */
@property(nonatomic, assign) CGPoint indoorPickerOffset;

/**
 * @brief  当前处于激活态的整个室内图数据
 */
@property(nonatomic, strong, readonly) QIndoorBuilding *activeBuilding;

/**
 * @brief  当前正在展示的室内楼层.
 */
@property(nonatomic, strong) QIndoorLevel *activeLevel;

/**
 * @brief 手动切换到指定的室内图及楼层
 */
- (void)setActiveIndoorInfo:(QIndoorInfo *)indoorInfo;

@end
