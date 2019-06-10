//
//  TNKLocationEntryProtocol.h
//  TNKNavigation
//
//  Created by 薛程 on 2018/3/28.
//  Copyright © 2018年 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol TNKLocationEntryDelegate;

/**
 * @brief  定位协议. 定义定位入口需要实现的属性及方法.
 */
@protocol TNKLocationEntry <NSObject>

@required

/**
 *  @brief  回调
 */
@property(nonatomic, weak) id<TNKLocationEntryDelegate> delegate;

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

/**
 * @brief  定位协议. 用于通知导航manager导航过程中出现的定位信息改变.
 */
@protocol TNKLocationEntryDelegate <NSObject>

@optional

/**
 * @brief  定位位置回调.
 * @param entry entry
 * @param location 定位数据.
 */
- (void)locationEntry:(id<TNKLocationEntry>)entry didUpdateLocation:(CLLocation *)location;

/**
 * @brief  定位发生错误.
 * @param entry entry
 * @param error 错误
 */
- (void)locationEntry:(id<TNKLocationEntry>)entry didFailWithError:(NSError *)error;

/**
 * @brief  定位Heading回调.
 * @param entry entry
 * @param heading Heading数据.
 */
- (void)locationEntry:(id<TNKLocationEntry>)entry didUpdateHeading:(CLHeading *)heading;

@end
