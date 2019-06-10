//
//  TNKSearchTypes.h
//  TNKNavigation
//
//  Created by 薛程 on 2018/3/5.
//  Copyright © 2018年 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import <UIKit/UIKit.h>
#import "TNKGeometry.h"
#import "TNKSearchTask.h"

typedef enum _TNKSearhType {
    kTNKSearchType_Car,
    kTNKSearchType_Bus,
}
TNKSearchType;


#pragma mark - TNKSearchRequest

@class TNKSearchNaviPoi, TNKSearchOption;

/**
 * @brief 路线规划的起终点类型
 */
@interface TNKSearchRequest : NSObject

/**
 * @brief 路线规划的起点
 */
@property (nonatomic, strong) TNKSearchNaviPoi   *startPoint;

/**
 * @brief 路线规划的终点
 */
@property (nonatomic, strong) TNKSearchNaviPoi   *destinationPoint;

@end


#pragma mark - TNKSearchNaviPoi

/**
 * @brief 路线规划的起终点类型
 */
@interface TNKSearchNaviPoi : NSObject

/**
 * @brief 地点的坐标.
 *
 * @note 途经点只支持coordinate
 */
@property (nonatomic, assign) CLLocationCoordinate2D coordinate;

/**
 * @brief 该地点的唯一标识. 有uid时优先使用uid
 */
@property (nonatomic,strong) NSString        *uid;

@end

#pragma mark - TNKSearchOption

/**
 * @brief 路线规划的参数配置
 */
@interface TNKSearchOption : NSObject

/**
 * @brief 规划类型
 */
@property (nonatomic, assign) TNKSearchType type;

@end


#pragma mark - TNKRouteSearchResult

/**
 * @brief 路线规划的所有路线结果集合
 */
@interface TNKRouteSearchResult : NSObject

@end


#pragma mark - TNKSearchRoutePlan

@class TNKSearchRouteLine;

/**
 * @brief 路线规划的一条可选路线
 */
@interface TNKSearchRoutePlan : NSObject

@end


#pragma mark - TNKSearchRouteLine

/**
 * @brief 路线规划的一条可选路线的子线段
 */
@interface TNKSearchRouteLine : NSObject

@end


