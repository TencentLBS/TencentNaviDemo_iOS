//
//  TencentLBSLocationManager.h
//  TencentLBS
//
//  Created by mirantslu on 16/4/19.
//  Copyright © 2016年 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import "TencentLBSLocation.h"
//#define IS_MOCK_LOC_TO_SDK // mock 模式，开启后，将不在使用系统的位置，而使用函数传入轨迹-(void)mockLocationWithLat:withLng:withAlt:withAcc:withCourse:withSpeed:withTimeStamp:
//#define BLEDEBUG
NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, TencentLBSRequestLevel) {
    TencentLBSRequestLevelGeo       = 0,
    TencentLBSRequestLevelName      = 1,
    TencentLBSRequestLevelAdminName = 3,
    TencentLBSRequestLevelPoi       = 4,
};

typedef NS_ENUM(NSUInteger, TencentLBSLocationCoordinateType) {
    TencentLBSLocationCoordinateTypeGCJ02 = 0,          //!< 火星坐标，即国测局坐标
    TencentLBSLocationCoordinateTypeWGS84 = 1,          //!< 地球坐标，注：如果是海外，无论设置的是火星坐标还是地球坐标，返回的都是地球坐标
};

typedef NS_ENUM(NSUInteger, TencentLBSLocationError) {
    TencentLBSLocationErrorUnknown = 0,                 //!< 错误码，表示目前位置未知，但是会一直尝试获取
    TencentLBSLocationErrorDenied = 1,                  //!< 错误码，表示定位权限被禁止
    TencentLBSLocationErrorNetwork = 2,                 //!< 错误码，表示网络错误
    TencentLBSLocationErrorHeadingFailure = 3,          //!< 错误码，表示朝向无法确认
    TencentLBSLocationErrorOther = 4,                   //!< 错误码，表示未知错误
};
typedef NS_ENUM(NSUInteger, TencentLBSMotionType) {
    TencentLBSMotionTypeUnknow     = 0,        //!< 未知状态
    TencentLBSMotionTypeStationary = 1,        //!< 静止状态
    TencentLBSMotionTypeWalking    = 2,        //!< 步行状态
    TencentLBSMotionTypeVehicle    = 3,        //!< 机动车：car、bus、moto、train等机动车
    TencentLBSMotionTypeBicycle    = 4,        //!< 骑车状态
    TencentLBSMotionTypeRunning    = 5,        //!< 跑步状态
    TencentLBSMotionTypeTilting    = 6,        //!< 倾斜状态
};
/**
 *  TencentLBSLocatingCompletionBlock 单次定位返回Block
 *
 *  @param location  位置信息 
 *  @param error     错误信息 参考 TencentLBSLocationError
 */
typedef void (^TencentLBSLocatingCompletionBlock)(TencentLBSLocation * _Nullable location, NSError  * _Nullable error);
#ifdef BLEDEBUG
typedef void (^UserLogUploadCallbackBlock)(NSData * _Nullable data, NSError * _Nullable error);
#endif
@protocol TencentLBSLocationManagerDelegate;

@interface TencentLBSLocationManager : NSObject

/**
 *  API Key, 在使用定位SDK服务之前需要先绑定key。
 */
@property (nonatomic, copy) NSString* apiKey;
/**
 *  phoneNumber, 向定位SDK内部设置手机号。重置时设置为nil
 */
@property (nonatomic,copy,nullable)NSString *phoneNumber;
/**
 *  实现了 TencentLBSLocationManagerDelegate 协议的类指针。
 */
@property (nonatomic, weak) id<TencentLBSLocationManagerDelegate> delegate;

/**
 *  设定定位的最小更新距离。默认为 kCLDistanceFilterNone。
 */
@property (nonatomic, assign) CLLocationDistance distanceFilter;

/**
 *  设定定位精度。默认为 kCLLocationAccuracyBest 。
 */
@property (nonatomic, assign) CLLocationAccuracy desiredAccuracy;

/**
 *  指定定位是否会被系统自动暂停。默认为 YES 。
 */
@property (nonatomic, assign) BOOL pausesLocationUpdatesAutomatically;

/**
 *  是否允许后台定位。默认为 NO。
 *  iOS 9.0 以上用户需要设置该选项并且在info.list里面Background Modes 中的 Location updates 处于选中状态才可以使用后台定位权限。iOS 9.0之前可以直接申请总是使用的权限来获得后台定位。
 *
 *  设置为 YES 的时候必须保证 Background Modes 中的 Location updates 处于选中状态，否则会抛出异常。
 */
@property (nonatomic, assign) BOOL allowsBackgroundLocationUpdates;

/**
 *  用户的活动类型
 *
 *  设置用户的活动类型。默认值为 CLActivityTypeOther
 */
@property (nonatomic, assign) CLActivityType activityType;

/**
 * 设置当朝向改变时，每隔多少度调用一次
 * 只有当设备方向的改变值超过该属性值时才激发delegate的方法。
 */
@property(nonatomic, assign) CLLocationDegrees headingFilter;

/**
 * 设置设备当前的朝向
 */
@property(nonatomic, assign) CLDeviceOrientation headingOrientation;

/**
 * 连续定位的逆地理信息请求的Level。默认为TencentLBSRequestLevelGeo
 */
@property (nonatomic, assign) TencentLBSRequestLevel requestLevel;

/**
 *  返回的TencentLBSLocation的location字段的坐标类型。默认为TencentLBSLocationCoordinateTypeGCJ02。
 *
 *  在一次定位过程中，只允许设置一次，不允许重复设置
 */
@property (nonatomic, assign) TencentLBSLocationCoordinateType coordinateType;

/**
 *  指定POI的更新间隔。 默认是10s
 */
@property(nonatomic, assign) NSInteger poiUpdateInterval;

/**
 * 设置定时回调的间隔。默认为1s
 */
@property(nonatomic, assign) NSTimeInterval locCallbackInterval;
/**
 *设置是否允许启动室内pdr。默认为YES
 */
@property (nonatomic, assign) BOOL isAllowIndoorPdrStart;

+(NSString *)getLBSSDKVersion;
+(NSString *)getLBSSDKbuild;


#pragma mark -

- (void)requestWhenInUseAuthorization;

- (void)requestAlwaysAuthorization;

#pragma mark -

/**
 *  单次定位
 *
 *  该方法为下面方法的一层封装。
 *  level默认是TencentLBSRequestLevelPoi
 *  timeout默认是10s
 */
- (BOOL)requestLocationWithCompletionBlock:(TencentLBSLocatingCompletionBlock)completionBlock;

/**
 *  单次定位
 *
 *  注意：不能连续调用该接口，需在上一次返回之后才能再次发起调用。该接口兼容iOS 7.0及以上，因iOS 9.0系统提供单次定位能力，故在9.0以上会调用系统单次定位接口，9.0之前SDK完成封装。可以通过调用cancelRequestLocation来取消。
 *
 *  @param level 可以根据此参数来对应的获取POI信息
 *  @param timeout 表示获取POI的超时时间。
 *  @param completionBlock 单次定位完成后的Block
 */
- (BOOL)requestLocationWithRequestLevel:(TencentLBSRequestLevel)level
                        locationTimeout:(NSTimeInterval)timeout
                        completionBlock:(TencentLBSLocatingCompletionBlock)completionBlock;

/**
 * 取消单次定位
 **/
- (void)cancelRequestLocation;

/**
 *  开始连续定位
 */
- (void)startUpdatingLocation;

/**
 *  停止连续定位
 */
- (void)stopUpdatingLocation;

/**
 * 重启系统定位
 */
- (void)restartSystemLocation;

/**
 *  开启更新定位朝向
 */
- (void)startUpdatingHeading;

/**
 *  结束更新定位朝向
 */
- (void)stopUpdatingHeading;

/**
 *  停止展示定位朝向校准提示
 */
- (void)dismissHeadingCalibrationDisplay;

/**
 *  开启运动状态检测
 */
- (void)startActivityRecognition;
- (void)stopActivityRecognition;

/**
 *  设置向SDK内部传入数据的接口
 */
- (void)setStatusData:(NSString *) key withValue:(NSString *) value;
/**
 * 外部控制VDR是否使用GPS，YES为不使用，NO为使用
 */
- (void)setLBSVdrDebug:(BOOL)isDebug;
// 测试使用
#if TENCENTLBS_DEBUG
+ (void)upLoadData;
+ (NSData *)getLocationLog;
+ (void)newLocationLog;
#endif

#ifdef BLEDEBUG
-(void) uploadpdrlogwith:(UserLogUploadCallbackBlock) block;
#endif

#ifdef IS_MOCK_LOC_TO_SDK
// 模拟坐标点，透传给SDK，需要的参数顺序依次是纬度，经度，高度，精度，方向，速度，时间戳
-(void)mockLocationWithLat:(double)lat withLng:(double)lng withAlt:(double)alt withAcc:(double)acc withCourse:(double)course withSpeed:(double)speed withTimeStamp:(NSDate *)date;
#endif
@end


#pragma mark - TencentLBSLocationManagerDelegate

/**
 *  TencentLBSLocationManagerDelegate
 *  定义了发生错误时的错误回调方法，连续定位的回调方法等。
 */
@protocol TencentLBSLocationManagerDelegate <NSObject>
@optional

/**
 *  当定位发生错误时，会调用代理的此方法
 *
 *  @param manager 定位 TencentLBSLocationManager 类
 *  @param error 返回的错误，参考 TencentLBSLocationError
 */
- (void)tencentLBSLocationManager:(TencentLBSLocationManager *)manager
                 didFailWithError:(NSError *)error;

/**
 *  连续定位回调函数
 *
 *  @param manager 定位 TencentLBSLocationManager 类
 *  @param location 定位结果
 */
- (void)tencentLBSLocationManager:(TencentLBSLocationManager *)manager
                didUpdateLocation:(TencentLBSLocation *)location;

/**
 *  定位权限状态改变时回调函数
 *
 *  @param manager 定位 TencentLBSLocationManager 类
 *  @param status  定位权限状态
 */
- (void)tencentLBSLocationManager:(TencentLBSLocationManager *)manager
     didChangeAuthorizationStatus:(CLAuthorizationStatus)status;

/**
 *  定位朝向改变时回调函数
 *
 *  @param manager 定位 TencentLBSLocationManager 类
 *  @param newHeading  新的定位朝向
 */
- (void)tencentLBSLocationManager:(TencentLBSLocationManager *)manager
                 didUpdateHeading:(CLHeading *)newHeading;

/**
 *  是否展示定位朝向校准提示的回调函数
 *
 *  @param manager 定位 TencentLBSLocationManager 类
 */
- (BOOL)tencentLBSLocationManagerShouldDisplayHeadingCalibration:(TencentLBSLocationManager *)manager;

/**
 *  只是内部调试使用，外部不应实现该接口
 */
- (void)tencentLBSLocationManager:(TencentLBSLocationManager *)manager didThrowLocation:(TencentLBSLocation *)location;
/**
 *  获取当前运动状态回调函数
 *  @param motionType 当前状态值 参考TencentLBSMotionType
 *  @param confidence 当前状态的置信度，取值范围[0,1]
 *  @param allConfidences 长度为7的double数组，分别对应TencentLBSMotionTypeUnknow，TencentLBSMotionTypeStationary，TencentLBSMotionTypeWalking，TencentLBSMotionTypeVehicle，TencentLBSMotionTypeBicycle，TencentLBSMotionTypeRunning，TencentLBSMotionTypeTilting的置信度
 */
- (void)tencentLBSActivityRecognition:(TencentLBSMotionType)motionType motionConfidence:(double)confidence  confidences:(double *)allConfidences;
/**
 * 输出融合后的导航方向
 * 在direction变化大于10度，或accuracy有变化，或provider有变化时会发起回调
 *
 * @param direction 当前手机导航方向; 单位：角度; 范围[0-360); 0表示正北，90表示正东，方向顺时针递增。
 * @param accuracy 3: 高精度； 2:中精度； 1:低精度； 其他:不可用。
 * @param provider "sensor" 传感器方向；"gps" GPS方向。
 */
-(void)tencentLBSLocationManager:(TencentLBSLocationManager *)manager didNaviDirectionChanged:(double)direction accuracy:(double)accuracy provider:(NSString *) provider;
/**
 * 输出GPS方向
 * 在bearing变化大于10度，或accuracy有变化时会发起回调
 *
 * @param bearing 当前用户GPS轨迹方向; 单位：角度; 范围[0-360); 0表示正北，90表示正东，方向顺时针递增。
 * @param accuracy 3: 高精度； 2:中精度； 1:低精度； 其他:不可用。
 */
-(void)tencentLBSLocationManager:(TencentLBSLocationManager *)manager didBearingChanged:(double)bearing accuracy:(double)accuracy;
/**
 * 输出传感器方向
 * 在direction变化大于10度，或accuracy有变化时会发起回调
 *
 * @param direction 当前用户传感器计算的手机头方向; 单位：角度; 范围[0-360); 0表示正北，90表示正东，方向顺时针递增。
 * @param accuracy 3: 高精度； 2:中精度； 1:低精度； 其他:不可用。
 */
-(void)tencentLBSLocationManager:(TencentLBSLocationManager *)manager didSensorDirectionChanged:(double)direction accuracy:(double)accuracy;

#ifdef BLEDEBUG
/*
 * 蓝牙网络定位点回调
 *
 */
- (void)tencentLBSLocationManager:(TencentLBSLocationManager *)manager
                didUpdateBleLocation:(TencentLBSLocation *)location;

-(void)tencentLBSLocationManager:(TencentLBSLocationManager *)manager didUpdateBlePdrFilter:(TencentLBSLocation *)locatioin;
#endif

/**
 * 输出日志的回调函数
 */
//#if TENCENTLBS_DEBUG
-(void)tencentLBSLocationLogWithTAG:(NSString*) TAG outputLog:(NSString*) logstr;
//#endif
@end

NS_ASSUME_NONNULL_END
