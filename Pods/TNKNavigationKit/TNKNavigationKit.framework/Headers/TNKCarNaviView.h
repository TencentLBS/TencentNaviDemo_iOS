//
//  TNKCarNaviView.h
//  TNKNavigation
//
//  Created by tabsong on 2018/4/8.
//  Copyright © 2018年 Tencent. All rights reserved.
//

#import "TNKBaseNaviView.h"
#import "TNKCarNaviManager.h"
#import <QMapKit/QMapKit.h>

#import "TNKRemainingOverviewData.h"
#import "TNKUserLocationPresentation.h"

typedef enum _TNKCarNaviUIMode
{
    TNKCarNaviUIModeBounce            = 0,    ///< 回弹模式
    TNKCarNaviUIMode3DCarTowardsUp    = 1,    ///< 3D 车头朝上
    TNKCarNaviUIMode2DMapTowardsNorth = 2,    ///< 2D 地图朝北
    TNKCarNaviUIModeOverview          = 3,    ///< 全览模式
    TNKCarNaviUIModeRemainingOverview = 4     ///< 剩余全览模式
} TNKCarNaviUIMode;

typedef enum _TNKCarNaviDayNightMode
{
    TNKCarNaviDayNightModeAuto        = 0,    ///< 自动切换
    TNKCarNaviDayNightModeAlwaysDay   = 1,    ///< 始终白天
    TNKCarNaviDayNightModeAlwaysNight = 2     ///< 始终黑夜
} TNKCarNaviDayNightMode;

typedef enum _TNKCarNaviDayNightStatus
{
    TNKCarNaviDayNightStatusDay       = 0,    ///< 白天
    TNKCarNaviDayNightStatusNight     = 1,    ///< 黑夜
} TNKCarNaviDayNightStatus;


@class TNKCarNaviView;

/**
 *  @brief 驾车导航UI类回调. 用于显示默认导航界面(包括地图和导航面板).
 */
@protocol TNKCarNaviViewDelegate <NSObject>

@optional

/**
 * @brief  获取导航模式改变回调.
 * @param carNaviView view
 * @param mode 导航模式
 */
- (void)carNaviView:(TNKCarNaviView *)carNaviView didChangeUIMode:(TNKCarNaviUIMode)mode;

/**
 * @brief  获取日夜状态改变回调.
 * @param carNaviView view
 * @param status 日夜状态
 */
- (void)carNaviView:(TNKCarNaviView *)carNaviView didChangeDayNightStatus:(TNKCarNaviDayNightStatus)status;

@end

/**
 *  @brief 驾车导航UI类数据源. 用于获取UI类需要的数据.
 */
@protocol TNKCarNaviViewDataSource <NSObject>

@optional

/**
 * @brief  获取剩余全览模式下所需要的数据.
 * @param carNaviView view
 *
 * @return 数据数组
 */
- (NSArray<id<TNKRemainingOverviewData>> *)remainingOverviewDataForCarNaviView:(TNKCarNaviView *)carNaviView;

@end


/**
 *  @brief 驾车导航UI类.
 *
 *  用于显示默认导航UI,包括导航面板,路线,车标,起终点等.
 */
@interface TNKCarNaviView : TNKBaseNaviView <TNKCarNaviUIDelegate>

/**
 *  @brief  TNKCarNaviView的回调,用于接收导航模式、日夜状态等变化.
 */
@property (nonatomic, weak) id <TNKCarNaviViewDelegate> delegate;

/**
 *  @brief  TNKCarNaviView的数据源,用于获取所需的数据.
 */
@property (nonatomic, weak) id <TNKCarNaviViewDataSource> dataSource;

/**
 *  @brief  是否隐藏默认导航面板, 默认为不隐藏默认导航面板.
 */
@property (nonatomic, assign) BOOL hideNavigationPanel;

/**
 *  @brief  导航模式. 导航模式包括3D车头朝上、2D地图朝北、全览和剩余全览4种模式. 默认为3D车头朝上模式.
 *          回弹模式在导航状态下使用手势操作地图时被触发,会在手势操作结束后一段时间切换回之前的导航模式.
 *          该时间可由bounceTime设定,默认回弹时间为5秒.直接设置导航模式为回弹模式将不会被响应.
 */
@property (nonatomic, assign) TNKCarNaviUIMode mode;

/**
 *  @brief  回弹模式的回弹时间，单位为秒，需大于0. 默认为5秒.
 */
@property (nonatomic, assign) NSUInteger bounceTime;

/**
 *  @brief  地图日夜间模式切换策略. 包括自动切换、始终白天、始终黑夜3种模式. 默认为日夜状态自动切换.
 */
@property (nonatomic, assign) TNKCarNaviDayNightMode dayNightMode;

/**
 *  @brief  获取地图当前日夜状态.
 */
@property (nonatomic, readonly) TNKCarNaviDayNightStatus dayNightStatus;

/**
 *  @brief  3D导航时自车点位置在地图上位置的比例 默认值为(0.5,0.75).
 *  x取值范围为[0.25,0.75] 表示从屏幕左边起的宽度比例.
 *  y取值范围为[0.25,0.75] 表示从屏幕上边起的高度比例.
 *  若设置值不在区间内则使用默认值.
 */
@property (nonatomic, assign) CGPoint TNKCarNaviFixCarProportion3D;

/**
 *  @brief  2D导航时自车点位置在地图上位置的比例 默认值为(0.5,0.75).
 *  x取值范围为[0.25,0.75] 表示从屏幕左边起的宽度比例.
 *  y取值范围为[0.25,0.75] 表示从屏幕上边起的高度比例.
 *  若设置值不在区间内则使用默认值.
 */
@property (nonatomic, assign) CGPoint TNKCarNaviFixCarProportion2D;

/**
 *  @brief  设置地图绘制路线的线宽. 默认值为12 px.
 */
@property (nonatomic, assign) NSUInteger routeLineWidth;

/**
 *  @brief  设置导航时已走过路线的处理方式. 0为置灰,1为擦除. 默认为0.
 */
@property (nonatomic, assign) NSUInteger routeLineEraseType;

/**
 *  @brief  设置全览和剩余全览模式下导航路线显示区域距离地图四周的边距.
 *          当在CarNaviView上自定义显示元素时, 为避免与导航路线相互遮挡, 可调用该接口调整导航路线显示区域范围.
 *          默认值为(40,10,20,10), 使得全览和剩余全览模式下导航路线四周有部分留白.
 */
@property (nonatomic, assign) UIEdgeInsets externalEdgeInsets;

/**
 * @brief  panel顶部空隙距离, 单位为px. 默认为全屏状态下避开状态栏. 取值范围为[0,100].
 */
@property (nonatomic, assign) NSUInteger panelTopGap;

/**
 *  @brief  内部持有的地图实例,可以通过该地图实例接收地图事件回调、添加annotation、操作地图视野等.
 */
@property (nonatomic, strong, readonly) QMapView *naviMapView;


/**
 *  @brief  设置显示/隐藏路口放大图. 该方法用于导航状态下控制显示/隐藏路口放大图指引. 非导航过程中调用该方法无效.
 *          路口放大图在3D车头朝上和2D地图朝北模式下会默认显示, 在全览模式和剩余全览模式下会默认隐藏.
 */
- (void)setEnlargedIntersectionEnabled:(BOOL)enabled;

/**
 *  @brief  设置显示/隐藏车道线图.该方法用于导航状态下控制显示/隐藏车道线图指引. 非导航过程中调用该方法无效.
 *          车道线图在3D车头朝上和2D地图朝北模式下会默认显示, 在全览模式和剩余全览模式下会默认隐藏.
 */
- (void)setGuidedLaneEnabled:(BOOL)enabled;

/**
 *  @brief  设置显示/隐藏转弯箭头指引.该方法用于导航状态下控制显示/隐藏下一个转弯箭头指引. 非导航过程中调用该方法无效.
 *          转弯箭头指引在3D车头朝上和2D地图朝北模式下会默认显示, 在全览模式和剩余全览模式下会默认隐藏.
 */
- (void)setTurnArrowEnabled:(BOOL)enabled;

/**
 *  @brief  设置显示/隐藏电子眼标识.该方法用于导航状态下控制显示/隐藏导航路线上的电子眼标识. 非导航过程中调用该方法无效.
 *          电子眼标识在3D车头朝上和2D地图朝北模式下会默认显示, 在全览模式和剩余全览模式下会默认隐藏.
 */
- (void)setElectronicEyeEnabled:(BOOL)enabled;

/**
 *  @brief  设置显示/隐藏自车点罗盘.该方法用于导航状态下控制显示/隐藏自车点罗盘. 非导航过程中调用该方法无效.
 *          自车点罗盘在3D车头朝上模式下会默认显示, 在2D地图朝北、全览模式和剩余全览模式下会默认隐藏.
 */
- (void)setCarCompassEnabled:(BOOL)enabled;

/**
 *  @brief  清除路线相关UI.该方法用于非导航状态下清除路线相关UI,包括导航路线、自车点图标、动态添加的限速/指示标识等. 导航过程中调用该方法无效.
 */
- (void)clearAllRouteUI;

/**
 *  @brief  配置自车位置UI属性. 该方法用于配置导航时自车位置UI属性, 非导航时进行配置会在导航发起后生效, 导航过程中进行配置即时生效.
 */
- (void)configUserLocationPresentation:(TNKUserLocationPresentation *)presentation;

@end
