//
//  TNKCarNaviManager.h
//  TNKNavigation
//
//  Created by tabsong on 2018/3/26.
//  Copyright © 2018年 Tencent. All rights reserved.
//

#import "TNKBaseNaviManager.h"
#import "TNKNaviTTS.h"
#import "TNKCarRouteSearchTypes.h"
#import "TNKCarNavigationData.h"
#import "TNKRouteTrafficStatus.h"
#import "TNKLocationEntryProtocol.h"
#import "TNKLocation.h"

/**
 * @brief  重新算路类型.
 */
typedef NS_ENUM(NSUInteger, TNKCarNaviManagerRecaculateType)
{  
    TNKCarNaviManagerRecaculateTypeOffRoute         = 1,    ///<偏航重算
    TNKCarNaviManagerRecaculateTypeRoadTypeChanged  = 2,    ///<道路类型切换重算
};

NS_ASSUME_NONNULL_BEGIN

@class TNKCarNaviManager;

/**
 * @brief  导航UI事件回调. 用于通知用户导航过程中出现的UI信息改变.
 */
@protocol TNKCarNaviUIDelegate<NSObject>

@optional

/**
 * @brief  导航数据回调.
 * @param manager manager
 * @param data 导航数据
 */
- (void)carNavigationManager:(TNKCarNaviManager *)manager updateNavigationData:(TNKCarNavigationData *)data;

/**
 * @brief  显示路口放大图.
 * @param manager manager
 * @param image 路口放大图
 */
- (void)carNavigationManager:(TNKCarNaviManager *)manager showEnlargedIntersectionImage:(UIImage *)image;

/**
 * @brief  隐藏路口放大图.
 * @param manager manager
 */
- (void)carNavigationManagerHideEnlargedIntersectionImage:(TNKCarNaviManager *)manager;

/**
 * @brief  显示车道线.
 * @param manager manager
 * @param image 车道线
 */
- (void)carNavigationManager:(TNKCarNaviManager *)manager showGuidedLaneImage:(UIImage *)image;

/**
 * @brief  隐藏车道线.
 * @param manager manager
 */
- (void)carNavigationManagerHideGuidedLaneImage:(TNKCarNaviManager *)manager;


/**
 * @brief  更新路线路况数据. 其中包括路线总距离、路线剩余距离及路况情况.
 * @param manager manager
 * @param status 路线路况数据
 */
- (void)carNavigationManager:(TNKCarNaviManager *)manager updateRouteTrafficStatus:(TNKRouteTrafficStatus *)status;

@end

/**
 * @brief  导航事件回调. 用于通知用户导航过程中出现的状态或信息改变.
 */
@protocol TNKCarNaviDelegate<NSObject>

@optional

/**
 * @brief  导航开始.
 * @param manager manager
 */
- (void)carNavigationManagerDidStart:(TNKCarNaviManager *)manager;

/**
 * @brief  导航结束.
 * @param manager manager
 */
- (void)carNavigationManagerDidStop:(TNKCarNaviManager *)manager;

/**
 * @brief  获取TTS回调.
 * @param manager manager
 * @param naviTTS tts信息
 *
 * @return 是否播报该文案.0未播报,1已播报.
 */
- (int)carNavigationManager:(TNKCarNaviManager *)manager
               broadcastTTS:(TNKNaviTTS *)naviTTS;

/**
 * @brief  获取到达终点回调.
 * @param manager manager
 */
- (void)carNavigationManagerDidArriveDestination:(TNKCarNaviManager *)manager;

/**
 * @brief  获取偏航回调.
 * @param manager manager
 */
- (void)carNavigationManagerDidOffRoute:(TNKCarNaviManager *)manager;

/**
 * @brief  获取经过途经点回调.
 * @param manager manager
 * @param index 途经点索引
 */
- (void)carNavigationManager:(TNKCarNaviManager *)manager
           didArriveWaypoint:(int)index;

/**
 * @brief  获取道路类型更新回调.
 * @param manager manager
 * @param type 道路类型
 */
- (void)carNavigationManager:(TNKCarNaviManager *)manager
           didUpdateRoadType:(TNKRoadType)type;

/**
 * @brief  获取导航定位更新回调.
 * @param manager manager
 * @param location 定位信息
 */
- (void)carNavigationManager:(TNKCarNaviManager *)manager
           didUpdateLocation:(TNKLocation *)location;

/**
 * @brief  获取重新算路请求开始回调.
 * @param manager manager
 * @param type 重新算路类型
 */
- (void)carNavigationManager:(TNKCarNaviManager *)manager
     didStartRecaculateRoute:(TNKCarNaviManagerRecaculateType)type;

/**
 * @brief  获取重新算路请求成功回调.
 * @param manager manager
 * @param type 重新算路类型
 * @param result 重新算路成功结果
 */
- (void)carNavigationManager:(TNKCarNaviManager *)manager
   didSuccessRecaculateRoute:(TNKCarNaviManagerRecaculateType)type
                      result:(TNKCarRouteSearchResult *)result;

/**
 * @brief  获取重新算路请求失败回调.
 * @param manager manager
 * @param type 重新算路类型
 * @param error 重新算路失败原因
 */
- (void)carNavigationManager:(TNKCarNaviManager *)manager
      didFailRecaculateRoute:(TNKCarNaviManagerRecaculateType)type
                       error:(NSError *)error;

/**
 * @brief  获取重新算路请求取消回调. 当偏航重新算路未完成但自车位置已驶回原路线时, 重新算路请求会取消并使用原路线继续导航.
 * @param manager manager
 * @param type 重新算路类型
 */
- (void)carNavigationManager:(TNKCarNaviManager *)manager
    didCancelRecaculateRoute:(TNKCarNaviManagerRecaculateType)type;

@end

/**
 * @brief  驾车导航控制类. 用于设置导航状态回调、调用驾车路线规划、启动/停止导航、设置路口放大图/车道线资源加载等.
 */
@interface TNKCarNaviManager : TNKBaseNaviManager

/**
 * @brief  注册对象接收导航事件变化.
 *  注册后可通过该协议获取导航过程中出现的状态或信息改变(如已偏航、经过途经点、到达终点等).
 *  导航事件变化采用广播形式,可同时注册多个对象接收事件变化.
 * @param naviDelegate 接收导航事件变化的对象
 */
- (void)registerNaviDelegate:(nullable id <TNKCarNaviDelegate>)naviDelegate;

/**
 * @brief  注销对象接收导航事件变化.
 * @param naviDelegate naviDelegate
 */
- (void)unregisterNaviDelegate:(nullable id <TNKCarNaviDelegate>)naviDelegate;

/**
 * @brief  注销所有对象接收导航事件变化.
 */
- (void)unregisterAllNaviDelegates;

/**
 * @brief  注册对象接收导航UI数据更新.
 *  注册后可通过该协议获取导航面板所需数据(如道路名称、转向箭头、路口放大图等).
 *  使用导航SDK提供的默认导航界面TNKCarNaviView(其中包括地图和导航面板)需要将其通过本方法注册.
 *  若需要自定义导航面板,则可通过本方法注册从而接收导航UI数据更新.
 *  导航UI数据更新采用广播形式,可同时注册多个对象接收数据更新.
 * @param UIDelegate 接收导航UI数据更新的对象
 */
- (void)registerUIDelegate:(nullable id <TNKCarNaviUIDelegate>)UIDelegate;

/**
 * @brief  注销对象接收导航UI数据更新.
 * @param UIDelegate naviDelegate
 */
- (void)unregisterUIDelegate:(nullable id <TNKCarNaviUIDelegate>)UIDelegate;

/**
 * @brief  注销所有对象接收导航UI数据更新.
 */
- (void)unregisterAllUIDelegates;

/**
 *  @brief  导航开始前最后的位置信息. 设置该字段可提升真实导航开始时的定位速度及准确性, 需在发起导航前设置. 定位经纬度需为GCJ02类型.
 */
@property (nonatomic, strong, nullable) CLLocation *lastLocationBeforeNavigation;

/**
 *  @brief  启动导航. 需要在驾车导航路线规划成功后进行.
 *  @param index 路线索引index. 与路线规划返回的路线结果顺序一致.
 */
- (void)startWithIndex:(NSUInteger)index;

/**
 *  @brief  启动模拟导航. 需要在驾车导航路线规划成功后进行.
 *  @param index 路线索引. 与路线规划返回的路线结果顺序一致.
 *  @param locationEntry 用户自定义的定位数据源入口. 当 locationEntry == nil 时内部会自动使用路径规划的数据来构建模拟定位数据源.
 */
- (void)startSimulateWithIndex:(NSUInteger)index
                 locationEntry:(id <TNKLocationEntry> __nullable)locationEntry;

/**
 *  @brief  结束导航.
 */
- (void)stop;

/**
 *  @brief  是否导航中.
 */
@property (nonatomic, readonly) BOOL isNavigating;

/**
 *  @brief  是否偏航中.
 */
@property (nonatomic, readonly) BOOL isOffRoute;

/**
 *  @brief  导航是否结束.
 */
@property (nonatomic, readonly) BOOL isStoped;

/**
 *  @brief  是否开启路口放大图功能. 若关闭则不会触发路口放大图加载和对应的UI数据回调. 默认开启.
 */
@property (nonatomic, assign) BOOL enableEnlargedIntersection;

/**
 *  @brief  是否开启车道线图功能. 若关闭则不会触发车道线图加载和对应的UI数据回调. 默认开启.
 */
@property (nonatomic, assign) BOOL enableGuidedLane;

/**
 *  @brief  是否开启内置导航语音播报功能. 开启后无法通过TTS回调控制播报状态. 默认关闭.
 */
@property (nonatomic, assign) BOOL enableInternalTTS;

/**
 * @brief  发起驾车导航路线规划. 通过路线规划请求配置起点、终点、途经点(可选)、规划参数(可选)发起路线规划.
 * @param request 路线规划请求
 * @param callback 路线规划完成回调
 *
 * @return 路线规划任务
 *
 * 错误信息参考TNKCarRouteSearchErrorCode, TNKCarRouteSearchErrorDomain
 */
- (TNKSearchTask *)searchNavigationRoutesWithRequest:(TNKCarRouteSearchRequest *)request completion:(void (^)(TNKCarRouteSearchResult *result, NSError *error))callback;

/**
 * @brief  更改导航路线
 * @param type 重新算路类型
 *
 */
- (void)changeNavigationRoute:(TNKCarNaviManagerRecaculateType)type;

@end

NS_ASSUME_NONNULL_END
