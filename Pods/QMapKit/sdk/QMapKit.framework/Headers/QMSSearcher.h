//
//  QMSSearcher.h
//  QMapSearchKit
//
//  Created by fan on 2019/3/14.
//  Copyright © 2019 tencent. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "QMSSearchOption.h"
#import "QMSSearchResult.h"

NS_ASSUME_NONNULL_BEGIN

@protocol QMSSearchDelegate;

@interface QMSSearcher : NSObject

/*!
 *  @brief  实现QMSSearchDelegate协议的对象
 */
@property (nonatomic, weak) id<QMSSearchDelegate> delegate;

/*!
 *  @brief  QMSSearcher初始化函数
 *
 *  @param delegate 实现QMSSearchDelegate协议的对象
 *
 *  @return QMSSearcher对象
 */
- (instancetype)initWithDelegate:(id<QMSSearchDelegate>)delegate;


/*!
 *  @brief  查询步行路线
 *
 *  @param wakingRouteSearchOption 查询选项
 *
 *  @return QMSSearchOperation对象
 */
- (void)searchWithWalkingRouteSearchOption:(QMSWalkingRouteSearchOption *)wakingRouteSearchOption;

@end


@protocol QMSSearchDelegate <NSObject>

@optional

/*!
 *  @brief  查询出现错误
 *
 *  @param searchOption 查询参数
 *  @param error        错误
 */
- (void)searchWithSearchOption:(QMSSearchOption *)searchOption didFailWithError:(NSError*)error;

/*!
 *  @brief  步行路径结果回调
 *
 *  @param walkingRouteSearchOption 查询参数
 *  @param walkingRouteSearchResult 查询结果
 */
- (void)searchWithWalkingRouteSearchOption:(QMSWalkingRouteSearchOption *)walkingRouteSearchOption didRecevieResult:(QMSWalkingRouteSearchResult *)walkingRouteSearchResult;

@end

NS_ASSUME_NONNULL_END
