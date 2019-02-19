//
//  TNKGPSFileLocationManager.h
//  TNKNavigationDebugging
//
//  Created by 薛程 on 2018/6/13.
//  Copyright © 2018年 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import "TNKLocationEntryProtocol.h"

/**
 *  @brief 利用GPS文件进行模拟定位的定位manager. 若使用该类,则文件需要严格遵照文件格式.
 */
@interface TNKGPSFileLocationManager : NSObject<TNKLocationEntry>

/**
 *  @brief  定位协议对象.用于通知导航manager导航过程中出现的定位信息改变.
 */
@property(nonatomic, weak) id<TNKLocationEntryDelegate> delegate;

/**
 *  @brief  模拟定位位置产生速度.默认值为1,按照文件中相邻元素的时间戳确定时间间隔. 速度区间为[0.25,4],取值为4则以4倍速进行,取值 为0.25则以1/4倍速进行.
 */
@property(nonatomic) float rate;

/**
 * @brief  初始化GPS模拟导航manager. 文件格式定义如下:
 *   每个定位数据元素占一行,共有按序排列的八个属性,以逗号分隔,最后一个数据后不带逗号.
 *   八个属性为:经度,纬度,水平精度,角度,速度,时间,时间戳,海拔高度.
 *   例: 116.308086,39.983521,30,313.94,1.72,2014-6-10 11:17:5,1402370225.698,96
 * @param filePath 文件路径
 */
- (id)initWithFilePath:(NSString *)filePath;

/**
 *  @brief  启动定位更新.
 */
- (void)startUpdatingLocation;

/**
 *  @brief  结束定位更新.
 */
- (void)stopUpdatingLocation;

/**
 *  @brief  启动Heading更新.
 */
- (void)startUpdatingHeading;

/**
 *  @brief  停止Heading更新.
 */
- (void)stopUpdatingHeading;

@end
