//
//  QMSSearchResult.h
//  QMapSearchKit
//
//  Created by xfang on 14/11/5.
//  Copyright (c) 2014年 tencent. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <CoreLocation/CoreLocation.h>

/*!
 * @brief 交通方式: 步行
 */
FOUNDATION_EXPORT NSString * const kQMSRouteWalkingMode;


/*!
 *  @brief 检索结果的状态码
 */
typedef NSInteger QMSResultCode;

#pragma mark -

/*!
 *  @brief 检索结果的基类
 */
@interface QMSBaseResult : NSObject

@end

/*!
 *  @brief 检索结果
 */
@interface QMSSearchResult : QMSBaseResult

/*!
 *  @brief  状态码, 0为成功
 */
@property (nonatomic, assign) QMSResultCode status;

/*!
 *  @brief  状态说明
 */
@property (nonatomic, copy) NSString *message;

@end

#pragma mark - Walking

@class QMSRoutePlan, QMSRouteStep;

/*!
 *  @brief  步行路线规划的检索结果
 */
@interface QMSWalkingRouteSearchResult : QMSSearchResult

/*!
 *  @brief  路线方案的数组, 元素类型为QMSRoutePlan
 */
@property (nonatomic, copy) NSArray *routes;

@end

#pragma mark - Walking 的详情

/*!
 *  @brief  路径规划的路线方案
 */
@interface QMSRoutePlan : QMSBaseResult

/*!
 *  @brief  方案交通方式. 固定值, kQMSRouteWalkingMode:步行
 */
@property (nonatomic ,copy) NSString *mode;

/*!
 *  @brief  方案整体距离 单位:米
 */
@property (nonatomic) CGFloat distance;

/*!
 *  @brief  方案估算时间 单位:分钟 四舍五入
 */
@property (nonatomic) CGFloat duration;

/*!
 *  @brief  方案整体方向描述
 */
@property (nonatomic) NSString *direction;

/*!
 *  @brief  方案路线坐标点串, 导航方案经过的点, 每个step中会根据索引取得自己所对应的路段, 类型为encode的CLLocationCoordinate2D
 */
@property (nonatomic, copy) NSArray *polyline;

/*!
 *  @brief  标记如何通过一个路段的信息，类型为QMSRouteStep
 */
@property (nonatomic, copy) NSArray *steps;

@end


/*!
 *  @brief  路径规划的路线步骤
 */
@interface QMSRouteStep : QMSBaseResult

/*!
 *  @brief  阶段路线描述
 */
@property (nonatomic, copy) NSString *instruction;

/*!
 *  @brief  阶段路线路名(非必有)
 */
@property (nonatomic, copy) NSString *road_name;

/*!
 *  @brief  阶段路线方向(如"南", 非必有)
 */
@property (nonatomic, copy) NSString *dir_desc;

/*!
 *  @brief  阶段路线距离 单位:米
 */
@property (nonatomic) CGFloat distance;

/*!
 *  @brief  时间 单位:分钟 四舍五入
 */
@property (nonatomic) CGFloat duration;

/*!
 *  @brief  阶段路线末尾动作(如 ”向南转“, 非必有)
 */
@property (nonatomic, copy) NSString *act_desc;

/*!
 *  @brief  阶段路线坐标点串在方案路线坐标点串的位置
 *
 *  从经纬度数组中 根据索引查询这一段路的途经点。 在WebService原始接口做了除2处理, 数据类型为NSNumber
 *  polyline_idx[0]:起点索引 
 *  polyline_idx[1]:终点索引
 */
@property (nonatomic, copy) NSArray *polyline_idx;

@end
