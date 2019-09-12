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

/*!
 *  @brief  Search检索的主入口
 */
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
/*!
 *  @brief  根据poi查询接口查询poi数据
 *
 *  @param poiSearchOption 查询选项, 参考QMSPoiSearchOption属性字段
 *
 *  @return QMSSearchOperation对象
 */
- (void)searchWithPoiSearchOption:(QMSPoiSearchOption *)poiSearchOption;

/*!
 *  @brief  根据suggestion接口查询, 用于获取输入关键字的补完与提示
 *
 *  @param SuggestionSearchOption 查询选项, 参考QMSSuggestionSearchOption属性字段
 *
 *  @return QMSSearchOperation对象
 */
- (void)searchWithSuggestionSearchOption:(QMSSuggestionSearchOption *)suggestionSearchOption;

/*!
 *  @brief  根据geocoder接口查询, 提供由 坐标 到 坐标所在位置的文字描述 的转换
 *
 *  @param reverseGeoCodeSearchOption 查询选项, 参考QMSReverseGeoCodeSearchOption属性字段
 *
 *  @return QMSSearchOperation对象
 */
- (void)searchWithReverseGeoCodeSearchOption:(QMSReverseGeoCodeSearchOption *)reverseGeoCodeSearchOption;

/*!
 *  @brief  根据geocoder接口查询, 提供由地址描述到所述位置坐标的转换，与逆地址解析的过程正好相反
 *
 *  @param geoCodeSearchOption 查询选项, 参考QMSGeoCodeSearchOption属性字段
 *
 *  @return QMSSearchOperation对象
 */
- (void)searchWithGeoCodeSearchOption:(QMSGeoCodeSearchOption *)geoCodeSearchOption;


/*!
 *  @brief  查询驾车路线
 *
 *  @param drivingRouteSearchOption 查询选项
 *
 *  @return QMSSearchOperation对象
 */
- (void)searchWithDrivingRouteSearchOption:(QMSDrivingRouteSearchOption *)drivingRouteSearchOption;

/*!
 *  @brief  查询公交路线
 *
 *  @param busingRouteSearchOption 查询选项
 *
 *  @return QMSSearchOperation对象
 */
- (void)searchWithBusingRouteSearchOption:(QMSBusingRouteSearchOption *)busingRouteSearchOption;

/*!
 *  @brief  查询全部行政区划列表
 *
 *  list接口： 获取全部行政区划数据
 *
 *  @param districtListSearchOption 查询选项
 *
 *  @return QMSSearchOperation对象
 */
- (void)searchWithDistrictListSearchOption:(QMSDistrictListSearchOption *)districtListSearchOption;

/*!
 *  @brief  查询指定行政区划的子级行政区划
 *
 *  getchildren接口：获取指定行政区划的子级行政区划
 *
 *  @param districtChildrenSearchOption 查询选项
 *
 *  @return QMSSearchOperation对象
 */
- (void)searchWithDistrictChildrenSearchOption:(QMSDistrictChildrenSearchOption *)districtChildrenSearchOption;

/*!
 *  @brief  查询指定关键词的行政区划
 *
 *  search接口：根据关键词搜索行政区划
 *
 *  @param districtSearchSearchOption 查询选项
 *
 *  @return QMSSearchOperation对象
 */
- (void)searchWithDistrictSearchSearchOption:(QMSDistrictSearchSearchOption *)districtSearchSearchOption;

@end

/*!
 *  @brief  Search检索的协议
 */
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

/*!
 *  @brief  poi查询结果回调函数
 *
 *  @param poiSearchOption 查询参数
 *  @param poiSearchResult 查询结果
 */
- (void)searchWithPoiSearchOption:(QMSPoiSearchOption *)poiSearchOption didReceiveResult:(QMSPoiSearchResult *)poiSearchResult;

/*!
 *  @brief  关键字的补完与提示回调接口
 *
 *  @param suggestionSearchOption 查询参数
 *  @param suggestionSearchResult 查询结果
 */
- (void)searchWithSuggestionSearchOption:(QMSSuggestionSearchOption *)suggestionSearchOption didReceiveResult:(QMSSuggestionResult *)suggestionSearchResult;

/*!
 *  @brief  逆地理解析(坐标位置描述)结果回调接口
 *
 *  @param reverseGeoCodeSearchOption 查询参数
 *  @param reverseGeoCodeSearchResult 查询结果
 */
- (void)searchWithReverseGeoCodeSearchOption:(QMSReverseGeoCodeSearchOption *)reverseGeoCodeSearchOption didReceiveResult:(QMSReverseGeoCodeSearchResult *)reverseGeoCodeSearchResult;

/*!
 *  @brief  地址解析(地址转坐标)结果回调接口
 *
 *  @param geoCodeSearchOption 查询参数
 *  @param geoCodeSearchResult 查询结果
 */
- (void)searchWithGeoCodeSearchOption:(QMSGeoCodeSearchOption *)geoCodeSearchOption didReceiveResult:(QMSGeoCodeSearchResult *)geoCodeSearchResult;


/*!
 *  @brief  驾车路径结果回调
 *
 *  @param drivingRouteSearchOption 查询参数
 *  @param drivingRouteSearchResult 查询结果
 */
- (void)searchWithDrivingRouteSearchOption:(QMSDrivingRouteSearchOption *)drivingRouteSearchOption didRecevieResult:(QMSDrivingRouteSearchResult *)drivingRouteSearchResult;

/*!
 *  @brief  公交路径结果回调
 *
 *  @param busingRouteSearchOption 查询参数
 *  @param busingRouteSearchResult 查询结果
 */
- (void)searchWithBusingRouteSearchOption:(QMSBusingRouteSearchOption *)busingRouteSearchOption didRecevieResult:(QMSBusingRouteSearchResult *)busingRouteSearchResult;

/*!
 *  @brief  行政区划结果回调
 *
 *  3种行政区划的查询都使用此回调
 *
 *  @param districtSearchOption 查询参数
 *  @param districtSearchResult 查询结果
 */
- (void)searchWithDistrictSearchOption:(QMSDistrictBaseSearchOption *)districtSearchOption didRecevieResult:(QMSDistrictSearchResult *)districtSearchResult;

@end

NS_ASSUME_NONNULL_END
