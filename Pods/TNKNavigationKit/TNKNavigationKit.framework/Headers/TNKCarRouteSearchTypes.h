//
//  TNKCarRouteSearchTypes.h
//  TNKNavigation
//
//  Created by fan on 2018/3/27.
//  Copyright © 2018年 Tencent. All rights reserved.
//

#import "TNKSearchTypes.h"

/**
 * @brief 路线规划的错误
 */
extern NSString * _Nonnull TNKCarRouteSearchErrorDomain;

/**
 * @brief 路线规划的错误码
 */
typedef enum _TNKCarRouteSearchErrorCode
{
    TNKCarRouteSearchErrorCode_NetworkError         = 1001,     ///< 网络错误
    TNKCarRouteSearchErrorCode_DataInvalid          = 2001,     ///< 返回数据无效
    TNKCarRouteSearchErrorCode_StartDestPointError  = 2002,     ///< 起终点参数错误
    TNKCarRouteSearchErrorCode_WayPointError        = 2003,     ///< 途经点参数错误
    TNKCarRouteSearchErrorCode_AdsorptionFailed     = 2004,     ///< 吸附失败
    TNKCarRouteSearchErrorCode_CalculateFailed      = 2005,     ///< 算路失败
    TNKCarRouteSearchErrorCode_InvalidKeyError      = 2006,     ///< 鉴权失败
    TNKCarRouteSearchErrorCode_ServerError          = 2999      ///< 服务器内部错误
} TNKCarRouteSearchErrorCode;                           ///< 路线规划的错误码


typedef enum _TNKRoadType
{
    TNKRoadType_None                   = 0,        ///< 无详细类型
    TNKRoadType_Elevated               = 1,        ///< 在桥上
    TNKRoadType_Downstairs             = 2,        ///< 在桥下
    TNKRoadType_MainRoad               = 3,        ///< 在主路
    TNKRoadType_ServingRoad            = 4,        ///< 在辅路
    TNKRoadType_DirectionRoad          = 5,        ///< 在对面
    TNKRoadType_DownstairsMainRoad     = 6,        ///< 在桥下主路
    TNKRoadType_DownstairsServingRoad  = 7,        ///< 在桥下辅路
} TNKRoadType;         ///< 路段的详细类型

typedef enum _TNKCarRouteLimitStatus
{
    TNKCarRouteLimitStatus_NoLimitedArea            = 0,       ///< 没有经过限行区域
    TNKCarRouteLimitStatus_LimitedAreaAvoided       = 1 << 0,  ///< 避开限行区域
    TNKCarRouteLimitStatus_StartAtLimitedArea       = 1 << 1,  ///< 起点在限行区域
    TNKCarRouteLimitStatus_DestAtLimitedArea        = 1 << 2,  ///< 终点在限行区域
    TNKCarRouteLimitStatus_ThroughLimitedArea       = 1 << 3,  ///< 经过限行区域
    TNKCarRouteLimitStatus_NeedToSetCarNumber       = 1 << 4,  ///< 设置车牌号以避开限行区域
} TNKCarRouteLimitStatus;   ///< 路线限行状态

typedef enum _TNKCarRouteClosedStatus
{
    TNKCarRouteClosedStatus_NoClosedRoad    = 0,             ///< 没有经过封路区域
    TNKCarRouteClosedStatus_ClosedAtStart   = 1 << 0,        ///< 起点在封路区域
    TNKCarRouteClosedStatus_ClosedAtMiddle  = 1 << 1,        ///< 途中经过封路区域(暂不支持)
    TNKCarRouteClosedStatus_ClosedAtDest    = 1 << 2,        ///< 终点在封路区域
} TNKCarRouteClosedStatus;  ///< 路线封路状态

typedef enum _TNKCarRouteSearchResultStatus
{
    TNKCarRouteSearchResultStatus_ResultAvailable    = 0,        ///< 有方案可供使用
    TNKCarRouteSearchResultStatus_UseLastResult      = 1,        ///< 继续使用原方案
} TNKCarRouteSearchResultStatus;  ///< 驾车路线规划提供的方案状态



#pragma mark - TNKCarRouteSearchOption

/**
 * @brief 驾车路线规划的参数配置
 *
 * 如，是否走高速，躲避拥堵等
 */
@interface TNKCarRouteSearchOption : TNKSearchOption

/**
 * @brief 驾车路线规划参数: 是否避开收费道路, 默认NO, 即不避开收费道路.
 */
@property (nonatomic, assign) BOOL avoidToll;

/**
 * @brief 驾车路线规划参数: 是否避开高速道路, 默认为NO, 即不避开高速道路.
 */
@property (nonatomic, assign) BOOL avoidHighway;

/**
 * @brief 驾车路线规划参数: 是否结合路况, 默认值NO, 即不结合路况.
 */
@property (nonatomic, assign) BOOL avoidTrafficJam;

/**
 * @brief 驾车路线规划参数: 导航场景. 1表示去接乘客, 2表示去送乘客. 默认值为1.
 */
@property (nonatomic, assign) int navScene;

/**
 * @brief 驾车路线规划参数: 行车方向角度. 沿正北方向顺时针旋转角度值, 有效值区间为[0,360), 默认值为-1.
 */
@property (nonatomic, assign) float angle;
    
/**
 * @brief 起点路段类型：设置详细的起点路段类型, 如在桥下、在辅路等. 设置该字段可以提升路线规划起点位置的准确程度. 默认为无详细起点路段类型.
 */
@property (nonatomic, assign) TNKRoadType startRoadType;

/**
 * @brief 车牌号：设置车牌号后可接收限行信息, 可以为空.
 */
@property (nonatomic, strong, nullable) NSString *carNumber;

@end

#pragma mark - TNKCarRouteSearchRequest

/**
 * @brief 驾车路线规划请求
 */
@interface TNKCarRouteSearchRequest : TNKSearchRequest

/**
 * @brief 路线规划需要经过的途经点,数量不可超过3个,可为空
 */
@property (nonatomic, strong, nullable) NSArray<TNKSearchNaviPoi *> *wayPoints;

/**
 * @brief 驾车路线规划的配置项,不可为空
 */
@property (nonatomic, strong, nonnull) TNKCarRouteSearchOption *searchOption;

@end

#pragma mark - TNKCarRouteSearchResult

@class TNKCarRouteSearchRoutePlan;

/**
 * @brief 驾车路线规划的所有路线结果集合
 */
@interface TNKCarRouteSearchResult : TNKRouteSearchResult

/**
 * @brief 驾车路线规划提供的方案状态.
          导航的首次路线规划会提供1-3条候选路线方案供选择.
          道路类型切换重新算路会提供1条重算路线方案并自动切换至该方案.
          偏航重新算路存在两种情况:
            1.提供1条重算路线方案并自动切换至该方案.
            2.不提供新的重算路线方案,自动切换使用原路线方案. 此时限行状态信息和路线结果不可用.
 */
@property (readonly, nonatomic, assign) TNKCarRouteSearchResultStatus status;

/**
 * @brief 道路限行状态信息. 支持按位组合结果. 例如起点终点均限行，则返回TNKCarRouteLimitStatus_StartAtLimitedArea|TNKCarRouteLimitStatus_DestAtLimitedArea，即limitStatus = 6
 */
@property (readonly, nonatomic, assign) TNKCarRouteLimitStatus limitStatus;

/**
 * @brief 路线结果集合
 */
@property (readonly, nonatomic, strong, nonnull) NSArray<TNKCarRouteSearchRoutePlan *> *routes;

@end


#pragma mark - TNKCarRouteSearchRoutePlan

@class TNKCarRouteSearchRouteSegmentStyle, TNKCarRouteSearchRouteLine;

/**
 * @brief 驾车路线规划的一条可选路线
 */
@interface TNKCarRouteSearchRoutePlan : TNKSearchRoutePlan

/**
 * @brief 路线ID
 */
@property (readonly, nonatomic, copy, nonnull) NSString *routeID;

/**
 * @brief 总距离
 */
@property (readonly, nonatomic) int totalDistance;

/**
 * @brief 总预计时间
 */
@property (readonly, nonatomic) int totalTime;

/**
 * @brief 推荐理由
 */
@property (readonly, nonatomic, copy, nullable) NSString *recommendReason;

/**
 * @brief 道路封路状态信息. 暂不支持按位组合操作
 */
@property (readonly, nonatomic) TNKCarRouteClosedStatus closedStatus;

/**
 * @brief 驾车路线规划的路线数据
 */
@property (readonly, nonatomic, strong, nonnull) TNKCarRouteSearchRouteLine *line;

@end

#pragma mark - TNKCarRouteSearchRoutePlan

/**
 * @brief 驾车路线规划的一条路线中实际线段
 */
@interface TNKCarRouteSearchRouteLine : TNKSearchRouteLine

/**
 * @brief 路线规划的起点
 */
@property (nonatomic, strong, nonnull) TNKSearchNaviPoi   *startPoint;

/**
 * @brief 路线规划的终点
 */
@property (nonatomic, strong, nonnull) TNKSearchNaviPoi   *destinationPoint;

/**
 * @brief 途经点
 */
@property (nonatomic, strong, nullable) NSArray<TNKSearchNaviPoi *>   *wayPoints;

/**
 * @brief 道路信息的坐标点串
 */
@property (readonly, nonatomic, strong, nonnull) NSArray<TNKCoordinatePoint *> *coordinatePoints;

/**
 * @brief 可配置每一子段显示样式的集合
 */
@property (readonly, nonatomic, strong, nonnull) NSArray<TNKCarRouteSearchRouteSegmentStyle *> *segmentStyles;

@end

#pragma mark - TNKCarRouteSearchRouteSegmentStyle

/**
 * @brief 子段显示样式
 */
@interface TNKCarRouteSearchRouteSegmentStyle : NSObject

/**
 * @brief 这段线的起点的索引位置
 */
@property (readonly, nonatomic, assign) NSInteger startNum;

/**
 * @brief 这段线的终点的索引位置
 */
@property (readonly, nonatomic, assign) NSInteger endNum;

/**
 * @brief 这段线的路况颜色索引. 其中0为道路通畅, 1为道路缓行, 2为道路堵塞, 3为未知路况, 4为道路严重堵塞.
 */
@property (readonly, nonatomic, assign) NSUInteger colorIndex;

@end


