//
//  QMapView.h
//  QMapKit
//
//  Created by tabsong on 17/5/15.
//  Copyright © 2017年 tencent. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "QGeometry.h"
#import "QAnnotation.h"
#import "QAnnotationView.h"
#import "QOverlayView.h"
#import "QBasicMapViewLayer.h"
#import "QTypes.h"
#import "QUserLocationPresentation.h"
#import "QTileOverlay.h"


typedef NS_ENUM(NSInteger, QUserTrackingMode)
{
    QUserTrackingModeNone              = 0,    ///< 不追踪用户的location更新
    QUserTrackingModeFollow            = 1,    ///< 追踪用户的location更新
    QUserTrackingModeFollowWithHeading = 2     ///< 追踪用户的location与heading更新
};

typedef NS_ENUM(NSUInteger, QMapLogoAnchor)
{
    QMapLogoAnchorRightBottom   = 0,    ///< 右下对齐, logo的对齐位置, 默认锚点位置
    QMapLogoAnchorLeftBottom,           ///< 左下对齐
    QMapLogoAnchorLeftTop,              ///< 左上对齐
    QMapLogoAnchorRightTop,             ///< 右上对齐
    QMapLogoAnchorMax                   ///< 边界, 自身无实际意义
};

@class QUserLocation;
@protocol QMapViewDelegate;


#pragma mark - QMapView

/**
 *  @brief  地图view的核心类
 */
@interface QMapView : UIView

#pragma mark - TileOverlay

/**
 *  @brief  是否开启手绘图，默认为 NO
 *
 * @notes 打开手绘图会将最大级别限制为19
 */
@property (nonatomic, assign, getter = isHandDrawMapEnabled) BOOL handDrawMapEnabled;

/**
 *  @brief  是否开启路况图，默认为 NO
 */
@property (nonatomic, assign) BOOL showsTraffic;

#pragma mark - Resources

/**
 * @brief  使用用户传入的地图资源文件(在地图初始化前调用)
 *
 * @param path 资源文件存放目录的全路径
 */
+ (void)loadPrefferedResourceFilesFromDirectory:(NSString *)path DEPRECATED_ATTRIBUTE;

#pragma mark - Basic

/**
 *  @brief 地图回调
 */
@property (nonatomic, weak) id<QMapViewDelegate> delegate;

/*@
 *  @brief  地图类型
 */
@property (nonatomic, assign) QMapType mapType;


/**
 * @brief  设置底图样式，默认为标准样式.
 *
 * @param styleType 用户自定义配置的样式序号.
 *
 * @notes 已弃用, 请使用setMapStyle
 */
- (void)setStyleType:(QMapStyleType)styleType DEPRECATED_ATTRIBUTE;

/**
 * @brief 改变底图样式
 *
 * @notes 值为在官网配置的自定义样式列表中的顺序, 从1开始
 */
- (void)setMapStyle:(int)styleType;

/**
 *  @brief  是否显示比例尺，默认为YES
 */
@property (nonatomic) BOOL showsScale;

/**
 *  @brief  是否显示建筑物，默认为YES
 */
@property (nonatomic) BOOL showsBuildings;

/**
 *  @brief  是否显示建筑物样式为3D效果，默认为YES
 */
@property (nonatomic) BOOL shows3DBuildings;

/**
 *  @brief  是否显示指南针，默认为NO
 */
@property (nonatomic) BOOL showsCompass;

/**
 * @brief 指定底图文字的首选语言
 *
 * 指定底图文字的语言，默认采用中文
 *
 * @param language 指定的语言
 * @see QMapLanguage
 */
- (void)setForeignLanguage:(QMapLanguage)language;

/**
 *  @brief 设置中心点偏移，向下为正. 单位：比例值(-0.25 ~ 0.25)默认为0
 */
- (void)setCenterOffsetY:(float)offset DEPRECATED_ATTRIBUTE;

/**
 *  @brief 设置中心点偏移，向右向下为增长. 单位：屏幕比例值(0.25 ~ 0.75)默认为(0.5, 0.5)
 */
- (void)setCenterOffset:(CGPoint)offset;

/**
 *  @brief 设置中心点偏移
 *
 *  @param offset 中心点偏移，向右向下为正. 单位：屏幕比例值(0.25 ~ 0.75)默认为(0.5, 0.5)
 *  @param animated 是否采用动画
 */
- (void)setCenterOffset:(CGPoint)offset animated:(BOOL)animated;

/**
 * @brief  设置地图Logo偏移
 *
 * @param offset Logo中心的偏移量. 如果offset为CGPointZero则为默认位置
 */
- (void)setLogoOffset:(CGPoint)offset DEPRECATED_ATTRIBUTE;

/**
 * @brief  设置地图Logo位置和大小. 调用后会覆盖默认位置
 *
 * @param margin 基于指定锚点(近边之间)的边距长度值. 单位Point, 默认为(6, 3)
 * @param anchor Logo基于mapview的位置的基准锚点.
 */
- (void)setLogoMargin:(CGPoint)margin anchor:(QMapLogoAnchor)anchor;

/**
 * @brief  设置地图Logo大小.
 *
 * @param scale Logo大小. 基于原始大小的比例值, 默认为1.0. 有效区间[0.7, 1.3]
 */
- (void)setLogoScale:(CGFloat)scale;

/**
 * @brief  设置地图比例尺偏移
 *
 * @param offset 比例尺的偏移量. 如果offset为CGPointZero则为默认位置
 */
- (void)setScaleViewOffset:(CGPoint)offset;

/**
 * @brief  设置是否显示封路事件
 *
 * @param visible yes为显示，否则不显示
 */
- (void)setRoadEventVisible:(BOOL)visible DEPRECATED_ATTRIBUTE;

/**
 * @brief 地图动画Layer.
 * 使用该layer 可以更灵活的组合 {centerCoordinate, zoomLevel, rotation, overlooking} 动画，
 * 并且可以自定义其duration, timingFunction 等CoreAnimation所支持的一切动画属性.
 */
@property (nonatomic, readonly) QBasicMapViewLayer *animationLayer;

#pragma mark - MapStatus

/**
 *  @brief  中心点经纬度
 */
@property (nonatomic, assign) CLLocationCoordinate2D centerCoordinate;

/**
 *  @brief  设置中心点经纬度
 *
 *  @param coordinate  中心点经纬度
 *  @param animated 是否采用动画
 */
- (void)setCenterCoordinate:(CLLocationCoordinate2D)coordinate animated:(BOOL)animated;

/**
 *  @brief  缩放级别, 范围 [minZoomLevel, maxZoomLevel]
 */
@property (nonatomic, assign) CGFloat zoomLevel;

/**
 *  @brief  最小缩放级别, 默认 minZoomLevel = 3
 */
@property (nonatomic, readonly) CGFloat minZoomLevel;

/**
 *  @brief  最大缩放级别, 默认 maxZoomLevel = 20
 */
@property (nonatomic, readonly) CGFloat maxZoomLevel;

/**
 *  @brief  设置最小最大缩放级别, 范围 3 <= minZoomLevel <= maxZoomLevel <= 20
 *
 *  @param minZoomLevel 最小缩放级别
 *  @param maxZoomLevel 最大缩放级别
 */
- (void)setMinZoomLevel:(CGFloat)minZoomLevel maxZoomLevel:(CGFloat)maxZoomLevel;

/**
 *  @brief  设置缩放级别
 *
 *  @param zoomLevel  缩放级别
 *  @param animated 是否采用动画
 */
- (void)setZoomLevel:(CGFloat)zoomLevel animated:(BOOL)animated;

/**
 *  @brief  旋转角度, 正角度向右转, 单位(角度)
 */
@property (nonatomic, assign) CGFloat rotation;

/**
 *  @brief  设置旋转角度, 正角度向右转, 单位(角度)
 *
 *  @param rotation  overlooking
 *  @param animated 是否采用动画
 */
- (void)setRotation:(CGFloat)rotation animated:(BOOL)animated;

/**
 *  @brief  Overlooking, 范围 [0, 45], 单位(角度)
 */
@property (nonatomic, assign) CGFloat overlooking;

/**
 *  @brief  设置overlooking, 范围 [0, 45], 单位(角度)
 *
 *  @param overlooking  overlooking
 *  @param animated 是否采用动画
 */
- (void)setOverlooking:(CGFloat)overlooking animated:(BOOL)animated;

/**
 *  @brief  当前地图可见范围的mapRect
 */
@property (nonatomic) QMapRect visibleMapRect;

/**
 *  @brief  设置当前地图可见范围的mapRect
 *
 *  @param mapRect  目标mapRect
 *  @param animated 是否采用动画
 */
- (void)setVisibleMapRect:(QMapRect)mapRect animated:(BOOL)animated;

/**
 *  @brief  设置当前地图可见范围的mapRect
 *
 *  @param mapRect  目标mapRect
 *  @param insets   要嵌入的边界
 *  @param animated 是否采用动画
 */
- (void)setVisibleMapRect:(QMapRect)mapRect edgePadding:(UIEdgeInsets)insets animated:(BOOL)animated;

/**
 *  @brief  当前地图的经纬度范围，设定的该范围可能会被调整为适合地图窗口显示的范围
 */
@property (nonatomic) QCoordinateRegion region;

/**
 *  @brief  设定当前地图的region
 *
 *  @param region   要设定的地图范围，用经纬度的方式表示
 *  @param animated 是否采用动画
 */
- (void)setRegion:(QCoordinateRegion)region animated:(BOOL)animated;

/**
 *  @brief  设定当前地图的region
 *
 *  @param region   要设定的地图范围，用经纬度的方式表示
 *  @param insets   要嵌入的边界
 *  @param animated 是否采用动画
 */
- (void)setRegion:(QCoordinateRegion)region edgePadding:(UIEdgeInsets)insets animated:(BOOL)animated;

/**
 * @brief  根据边界留宽计算合适的地理范围
 * @param mapRect 待调整的地理范围
 * @return 调整后的地图范围
 */
- (QMapRect)mapRectThatFits:(QMapRect)mapRect edgePadding:(UIEdgeInsets)insets;

/**
 * @brief  根据当前地图View的窗口大小调整传入的mapRect，返回适合当前地图窗口显示的mapRect
 * @param mapRect 待调整的地理范围
 * @param bContainsCalloutView 计算的maprect是否需要包含calloutView
 * @param annotations 要包含的annotation 数组
 * @param insets mapRect四周要预留的边界大小
 * @return 调整后适合当前地图窗口显示的地图范围
 */
- (QMapRect)mapRectThatFits: (QMapRect)mapRect
        containsCalloutView:(BOOL)bContainsCalloutView
                annotations:(NSArray<id<QAnnotation> >*)annotations
                edgePadding:(UIEdgeInsets)insets;

/**
 * @brief  根据边界留宽及地理范围计算合适的级别(2D北朝上场景时)
 * @param mapRect 待调整的地理范围
 * @param outCoordinate 合适的中心点经纬度.
 * @return 合适的级别
 */
- (CGFloat)zoomLevelThatFits:(QMapRect)mapRect edgePadding:(UIEdgeInsets)insets outCenterCoordinate:(CLLocationCoordinate2D *)outCoordinate;

#pragma mark - Gesture Control

/**
 * 设定地图View能否支持用户多点缩放, 默认为YES.
 */
@property(nonatomic, getter=isZoomEnabled) BOOL zoomEnabled;

/**
 * 设定地图View能否支持用户移动地图, 默认为YES.
 */
@property(nonatomic, getter=isScrollEnabled) BOOL scrollEnabled;

/**
 * @brief  是否支持俯视. 默认为YES.
 */
@property (nonatomic, assign, getter=isOverlookingEnabled) BOOL overlookingEnabled;

/**
 * @brief  是否支持旋转. 默认为YES.
 */
@property (nonatomic, assign, getter=isRotateEnabled) BOOL rotateEnabled;

#pragma mark - Coordinate Convert

/**
 * @brief  将经纬度坐标转换为View坐标
 * @param coordinate 待转换的经纬度坐标
 * @param view 指定相对的View
 * @return 转换后的View坐标
 */
- (CGPoint)convertCoordinate:(CLLocationCoordinate2D)coordinate toPointToView:(UIView *)view;

/**
 * @brief  将View坐标转换成经纬度坐标
 * @param point 待转换的View坐标
 * @param view point坐标所在的view
 * @return 转换后的经纬度坐标
 */
- (CLLocationCoordinate2D)convertPoint:(CGPoint)point toCoordinateFromView:(UIView *)view;

/**
 * @brief  将经纬度矩形区域转换为View矩形区域
 * @param region 待转换的经纬度矩形
 * @param view 指定相对的View
 * @return 转换后的View矩形区域
 */
- (CGRect)convertRegion:(QCoordinateRegion)region toRectToView:(UIView *)view;

/**
 * @brief  将View矩形区域转换成经纬度矩形区域
 * @param rect 待转换的View矩形区域
 * @param view rect坐标所在的view
 * @return 转换后的经纬度矩形区域
 */
- (QCoordinateRegion)convertRect:(CGRect)rect toRegionFromView:(UIView *)view;

@end

/**
 *  @brief  地图view的定位相关的API
 */
@interface QMapView (UserLocation)

/**
 * @brief 配置当前位置UI属性 (必须在QMapView 初始化以后, 定位开启之前调用)
 *
 * @param presentation 位置UI属性
 */
- (void)configureUserLocationPresentation:(QUserLocationPresentation *)presentation;

/**
 * @brief 开启定位并展示位置图标.
 */
@property (nonatomic, assign) BOOL showsUserLocation;

/**
 * @brief 当前位置信息
 */
@property (nonatomic, readonly) QUserLocation *userLocation;

/**
 * @brief 设定定位精度。默认为kCLLocationAccuracyBest
 */
@property (nonatomic) CLLocationAccuracy desiredAccuracy;

/**
 * @brief 设定定位的最小更新距离。默认为kCLDistanceFilterNone，会提示任何移动
 */
@property (nonatomic) CLLocationDistance distanceFilter;


/**
 * @brief 设定最小更新角度。默认为1度，设定为kCLHeadingFilterNone会提示任何角度改变
 */
@property (nonatomic) CLLocationDegrees headingFilter;

/**
  * @brief 以上是否允许后台定位。ios9以上可用. 请参考CLLocationManager.allowsBackgroundLocationUpdates
  */
@property(assign, nonatomic) BOOL allowsBackgroundLocationUpdates;

/**
 *  指定定位是否会被系统自动暂停. 默认为YES.
 */
@property(assign, nonatomic) BOOL pausesLocationUpdatesAutomatically;

/**
 *  @brief  定位用户位置的模式
 */
@property (nonatomic) QUserTrackingMode userTrackingMode;

/**
 *  @brief  设置追踪用户位置的模式
 *
 *  @param mode     要使用的模式
 *  @param animated 是否采用动画
 */
- (void)setUserTrackingMode:(QUserTrackingMode)mode animated:(BOOL)animated;

/**
 *  @brief  当前位置在地图中是否可见
 */
@property (nonatomic, readonly, getter=isUserLocationVisible) BOOL userLocationVisible;

/**
 *  @brief  在地图中隐藏位置图标
 */
- (void)setUserLocationHidden:(BOOL)hidden;


@end

/**
 *  @brief  地图view的点覆盖物相关的API
 */
@interface QMapView (Annotation)

/**
 * @brief  当前地图View的已经添加的标注数组
 */
@property(nonatomic, readonly) NSArray *annotations;

/**
 * @brief  当前选中的annotations
 */
@property (nonatomic, readonly) NSArray<id<QAnnotation>> *selectedAnnotations;

/**
 * @brief  向地图窗口添加标注，需要实现QMapViewDelegate的-mapView:viewForAnnotation:函数来生成标注对应的View
 *
 * @param annotation 要添加的标注
 */
- (void)addAnnotation:(id <QAnnotation>)annotation;

/**
 * @brief  向地图窗口添加一组标注，需要实现QMapViewDelegate的-mapView:viewForAnnotation:函数来生成标注对应的View
 * @param annotations 要添加的标注数组
 */
- (void)addAnnotations:(NSArray *)annotations;

/**
 * @brief  移除标注
 * @param annotation 要移除的标注
 */
- (void)removeAnnotation:(id <QAnnotation>)annotation;

/**
 * @brief  移除一组标注
 * @param annotations 要移除的标注数组
 */
- (void)removeAnnotations:(NSArray *)annotations;

/**
 * @brief  查找指定标注对应的View，如果该标注尚未显示，返回nil
 * @param annotation 指定的标注
 * @return 指定标注对应的View
 */
- (QAnnotationView *)viewForAnnotation:(id <QAnnotation>)annotation;

/**
 * @brief  根据指定标识查找一个可被复用的标注View，一般在delegate中使用，用此函数来代替新申请一个View
 * @param identifier 指定标识
 * @return 返回可被复用的标注View
 */
- (QAnnotationView *)dequeueReusableAnnotationViewWithIdentifier:(NSString *)identifier;

/**
 * @brief  将制定的annotation放在最上层渲染.
 *  @param annotation 指定的annotation
 *
 * @note Deprecated 请使用QAnnotationView.zIndex管理顺序（默认会将本annotationView.zIndex设置为当前顶部的zIndex+1）
 */
- (void)bringAnnotationToFront:(id <QAnnotation>)annotation DEPRECATED_ATTRIBUTE;

/**
 * @brief  选中指定的标注
 * @param annotation 指定的标注
 * @param animated 是否支持动画
 */
- (void)selectAnnotation:(id <QAnnotation>)annotation animated:(BOOL)animated;

/**
 * @brief  取消指定的标注的选中状态
 * @param annotation 指定的标注
 * @param animated 是否支持动画
 */
- (void)deselectAnnotation:(id <QAnnotation>)annotation animated:(BOOL)animated;

@end


#pragma mark - Overlay

/**
 *  @brief  地图view的线面覆盖物相关的API
 */
@interface QMapView (Overlay)

/**
 * @brief  当前mapView中已经添加的Overlay数组
 */
@property (nonatomic, readonly) NSArray *overlays;

/**
 * @brief  向地图窗口添加Overlay，需要实现QMapViewDelegate的-mapView:viewForOverlay:函数来生成标注对应的View
 * @param overlay 要添加的overlay
 */
- (void)addOverlay:(id <QOverlay>)overlay;

/**
 * @brief  批量向地图窗口添加Overlay，需要实现QMapViewDelegate的-mapView:viewForOverlay:函数来生成标注对应的View
 * @param overlays 要添加的overlay列表
 */
- (void)addOverlays:(NSArray<id <QOverlay>> *)overlays;

/**
 * @brief  移除Overlay
 * @param overlay 要移除的overlay
 */
- (void)removeOverlay:(id <QOverlay>)overlay;

/**
 * @brief  移除Overlay
 * @param overlays 要移除的overlay列表
 */
- (void)removeOverlays:(NSArray<id <QOverlay>> *)overlays;

/**
 * @brief  返回指定overlay对象的OverlayView
 * @param overlay 待查询的overlay
 * @return 对应的OverlayView
 */
- (QOverlayView *)viewForOverlay:(id <QOverlay>)overlay;

@end

/**
 * @brief  QMapView(TileOverlay):瓦片图相关的API（如热力图）
 */
@interface QMapView (TileOverlay)

/**
 *  @brief  添加tileOverlay
 *
 *  @param tileOverlay 要添加的tileOverlay
 */
- (void)addTileOverlay:(QTileOverlay *)tileOverlay;

/**
 *  @brief  移除tileOverlay
 *
 *  @param tileOverlay 要移除的tileOverlay
 */
- (void)removeTileOverlay:(QTileOverlay *)tileOverlay;

/**
 *  @brief  强制tileOverlay重新加载数据.
 *
 *  @param tileOverlay tileOverlay
 */
- (void)reloadTileOverlay:(QTileOverlay *)tileOverlay;

/**
 *  @brief  当前地图上的tileOverlay数组
 */
@property (nonatomic, readonly) NSArray *tileOverlays;

@end

/**
 * @brief  截图相关API
 */
@interface QMapView (Snapshot)

/**
 *  @brief  截图
 *
 *  @return 截图image
 */
- (UIImage *)takeSnapshot __attribute__ ((deprecated("use - (void)takeSnapshotInRect:(CGRect)rect completion:(void (^)(UIImage *resultImage))completion instead")));

/**
 *  @brief  异步截图 (默认超时时间为2.5秒)
 *
 *  @param rect 范围
 *  @param completion 异步block结果
 */
- (void)takeSnapshotInRect:(CGRect)rect completion:(void (^)(UIImage *resultImage))completion;

/**
 *  @brief  异步截图
 *
 *  @param rect 范围
 *  @param timeout 超时时间.
 *  @param completion 异步block结果
 */
- (void)takeSnapshotInRect:(CGRect)rect timeout:(CFTimeInterval)timeout completion:(void (^)(UIImage *resultImage))completion;

@end


#pragma mark - QPoiInfo

/**
 * @brief 点击底图上文字图标的数据信息
 */
@interface QPoiInfo : NSObject

/**
 * @brief 唯一标识. 预留字段暂无数据
 */
@property (nonatomic, copy) NSString *uid;

/**
 * @brief 名字信息
 */
@property (nonatomic, copy) NSString *name;

/**
 * @brief 经纬坐标
 */
@property (nonatomic, assign) CLLocationCoordinate2D coordinate;

@end

/**
 * @brief 点击室内图上文字图标的数据信息
 */
@interface QIndoorPoiInfo : QPoiInfo

/**
 * @brief 所在室内图楼层
 */
@property (nonatomic, copy) NSString *levelName;

/**
 * @brief 所在室内图唯一标识
 */
@property (nonatomic, copy) NSString *buildingGUID;

/**
 * @brief 所在室内图楼的名称
 */
@property (nonatomic, copy) NSString *buildingName;

@end

/**
 *  @brief  地图view的错误信息, 用于定位问题
 */
@interface QMapView (Debug)

/**
 *  @brief  地图view的错误信息, 用于定位问题
 */
- (NSString *)getDebugError;

@end

#pragma mark - QMapViewDelegate

/**
 * @brief QMapViewDelegate:MapView的Delegate,mapView通过此类来通知用户对应的事件
 **/
@protocol QMapViewDelegate <NSObject>

@optional

/**
 *  @brief  地图数据加载失败时会调用此接口
 *
 *  @param mapView  地图view
 *  @param error 错误信息
 */
- (void)mapViewDidFailLoadingMap:(QMapView *)mapView withError:(NSError *)error;

/**
 * @brief  地图区域即将改变时会调用此接口
 * @param mapView 地图View
 * @param animated 是否动画
 * @param bGesture 是否由手势触发
 */
- (void)mapView:(QMapView *)mapView regionWillChangeAnimated:(BOOL)animated gesture:(BOOL)bGesture;

/**
 * @brief  地图区域改变时会调用此接口. 视野持续变化时本回调可能会被频繁多次调用, 请不要做耗时或复杂的事情
 * @param mapView 地图View
 */
- (void)mapViewRegionChange:(QMapView *)mapView;

/**
 * @brief  地图区域改变完成后会调用此接口,如果是由手势触发，当触摸结束且地图region改变的动画结束后才会触发此回调
 * @param mapView 地图View
 * @param animated 是否动画
 * @param bGesture region变化是否由手势触发
 */
- (void)mapView:(QMapView *)mapView regionDidChangeAnimated:(BOOL)animated gesture:(BOOL)bGesture;

/**
 * @brief  点击地图空白处会调用此接口.
 * @param mapView 地图View
 * @param coordinate 坐标
 */
- (void)mapView:(QMapView *)mapView didTapAtCoordinate:(CLLocationCoordinate2D)coordinate;

/**
 * @brief  点击地图poi图标处会调用此接口.
 * @param mapView 地图View
 * @param poi poi数据
 */
- (void)mapView:(QMapView *)mapView didTapPoi:(QPoiInfo *)poi;

/**
 * @brief 根据anntation生成对应的View
 * @param mapView 地图View
 * @param annotation 指定的标注
 * @return 生成的标注View
 */
- (QAnnotationView *)mapView:(QMapView *)mapView viewForAnnotation:(id <QAnnotation>)annotation;

/**
 * @brief 根据anntationView生成对应的CustomCallout (当标注被选中后会调用)
 * @param mapView 地图View
 * @param annotationView 指定的标注view
 * @return 对应的CustomCallout
 */
- (UIView *)mapView:(QMapView *)mapView customCalloutForAnnotationView:(QAnnotationView *)annotationView;

/**
 * @brief  当mapView新添加annotation views时，调用此接口
 * @param mapView 地图View
 * @param views 新添加的annotation views
 */
- (void)mapView:(QMapView *)mapView didAddAnnotationViews:(NSArray<QAnnotationView *> *)views;

/**
 * @brief  当选中一个annotation view时，调用此接口
 * @param mapView 地图View
 * @param view 选中的annotation view
 */
- (void)mapView:(QMapView *)mapView didSelectAnnotationView:(QAnnotationView *)view;

/**
 * @brief  当取消选中一个annotation view时，调用此接口
 * @param mapView 地图View
 * @param view 取消选中的annotation view
 */
- (void)mapView:(QMapView *)mapView didDeselectAnnotationView:(QAnnotationView *)view;

/**
 *  @brief  拖动annotationView时view的状态变化
 *
 *  @param mapView  地图view
 *  @param view     目标annotationView
 *  @param newState 新状态
 *  @param oldState 旧状态
 */
- (void)mapView:(QMapView *)mapView annotationView:(QAnnotationView *)view didChangeDragState:(QAnnotationViewDragState)newState
   fromOldState:(QAnnotationViewDragState)oldState;

/**
 *  @brief  标注view的accessory view(必须继承自UIControl)被点击时，触发该回调
 *
 *  @param mapView 地图view
 *  @param view    callout所属的标注view
 *  @param control 对应control
 */
- (void)mapView:(QMapView *)mapView annotationView:(QAnnotationView *)view calloutAccessoryControlTapped:(UIControl *)control;

/**
 * @brief  根据overlay生成对应的View
 * @param mapView 地图View
 * @param overlay 指定的overlay
 * @return 生成的覆盖物View
 */
- (QOverlayView *)mapView:(QMapView *)mapView viewForOverlay:(id <QOverlay>)overlay;

/**
 * @brief  当mapView新添加overlay views时，调用此接口
 * @param mapView 地图View
 * @param overlayViews 新添加的overlay views
 */
- (void)mapView:(QMapView *)mapView didAddOverlayViews:(NSArray *)overlayViews;

/**
 * @brief  在地图View将要启动定位时，会调用此函数
 * @param mapView 地图View
 */
- (void)mapViewWillStartLocatingUser:(QMapView *)mapView;

/**
 * @brief  在地图View停止定位后，会调用此函数
 * @param mapView 地图View
 */
- (void)mapViewDidStopLocatingUser:(QMapView *)mapView;

/**
 * @brief 用户位置更新后，会调用此函数
 * @param mapView 地图View
 * @param userLocation 新的用户位置
 * @param fromHeading 是否为heading 变化触发，如果为location变化触发,则为NO
 */
- (void)mapView:(QMapView *)mapView didUpdateUserLocation:(QUserLocation *)userLocation fromHeading:(BOOL)fromHeading;
/**
 * @brief  定位失败后，会调用此函数
 * @param mapView 地图View
 * @param error 错误号，参考CLError.h中定义的错误号
 */
- (void)mapView:(QMapView *)mapView didFailToLocateUserWithError:(NSError *)error;

/**
 * @brief 定位时的userTrackingMode 改变时delegate调用此函数
 *  @param mapView 地图View
 *  @param mode QMUserTrackingMode
 *  @param animated 是否有动画
 */
- (void)mapView:(QMapView *)mapView didChangeUserTrackingMode:(QUserTrackingMode)mode animated:(BOOL)animated;

@end
