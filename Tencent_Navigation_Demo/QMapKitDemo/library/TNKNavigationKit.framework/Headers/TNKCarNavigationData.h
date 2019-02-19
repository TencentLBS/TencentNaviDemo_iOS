//
//  TNKCarNavigationData.h
//  TNKNavigation
//
//  Created by 薛程 on 2018/4/19.
//  Copyright © 2018年 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

/**
 *  @brief 导航面板数据类.包含路名，距离，时间等数据.
 */
@interface TNKCarNavigationData : NSObject

#pragma mark Road Name

/**
 * @brief 下一段路名
 */
@property (nonatomic, strong) NSString *nextRoadName;

/**
 * @brief 当前路名
 */
@property (nonatomic, strong) NSString *currentRoadName;

#pragma mark Distance

/**
 * @brief 到下一段的距离 单位:米
 */
@property (nonatomic) int nextDistanceLeft;

/**
 * @brief 到下一段的距离字符串 无单位
 */
@property (nonatomic, strong) NSString *nextDistanceLeftString;

/**
 * @brief 到下一段的距离单位
 */
@property (nonatomic, strong) NSString *nextDistanceLeftUnit;

/**
 * @brief 剩余总距离 单位:米
 */
@property (nonatomic) int totalDistanceLeft;

/**
 * @brief 剩余总距离字符串 无单位
 */
@property (nonatomic, strong) NSString *totalDistanceLeftString;

/**
 * @brief 剩余总距离单位
 */
@property (nonatomic, strong) NSString *totalDistanceLeftUnit;

#pragma mark Time

/**
 * @brief 剩余时间 单位:分钟
 */
@property (nonatomic) int totalTimeLeft;

#pragma mark Speed

/**
 * @brief 限速值，单位: 公里／小时
 */
@property (nonatomic) int limitSpeed;

/**
 * @brief 当前速度值，单位: 公里／小时 数值为负时当前速度值无效
 */
@property (nonatomic) int currentSpeed;;

#pragma mark Intersection Image

/**
 * @brief 路口箭头图片
 */
@property (nonatomic, strong) UIImage *intersectionImage;


@end
