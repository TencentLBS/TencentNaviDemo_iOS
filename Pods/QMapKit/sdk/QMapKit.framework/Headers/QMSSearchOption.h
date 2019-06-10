//
//  QMSSearchOption.h
//  QMapSearchKit
//
//  Created by xfang on 14/11/5.
//  Copyright (c) 2014年 tencent. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

/*!
 *  @brief 检索参数的基类
 */
@interface QMSSearchOption : NSObject

@end


#pragma mark - 

/*!
 *  @brief 步行路线规划的检索参数
 */
@interface QMSWalkingRouteSearchOption : QMSSearchOption

/*!
 *  @brief  起点坐标 格式：
 *  from=lat<纬度>,lng<经度>
 */
@property (nonatomic, copy) NSString *from;

/*!
 *  @brief  以CLLocationCoordinate2D方式设置起点经纬度
 *
 *  @param coordinate 起点经纬度
 */
- (void)setFromCoordinate:(CLLocationCoordinate2D)coordinate;

/*!
 *  @brief  终点坐标 格式：
 *  to=lat<纬度>,lng<经度>
 */
@property (nonatomic, copy) NSString *to;

/*!
 *  @brief  以CLLocationCoordinate2D方式设置终点点经纬度
 *
 *  @param coordinate 终点经纬度
 */
- (void)setToCoordinate:(CLLocationCoordinate2D)coordinate;

@end

