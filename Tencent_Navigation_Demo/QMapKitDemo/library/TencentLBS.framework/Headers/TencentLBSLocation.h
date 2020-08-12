//
//  TencentLBSLocation.h
//  TencentLBS
//
//  Created by mirantslu on 16/4/19.
//  Copyright © 2016年 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

NS_ASSUME_NONNULL_BEGIN

#define TENCENTLBS_DEBUG 0
typedef NS_ENUM(NSUInteger, TencentLBSLocationProvider) {
    TencentLBSLocationProviderLocal    = 0,     //!< 由系统提供的位置数据
    TencentLBSLocationProviderNetwork  = 1,     //!< 由服务器提供的位置数据
    TencentLBSLocationProviderFake     = 2,     //!< 作弊的位置数据
};
typedef NS_ENUM(NSUInteger,TencentLBSFusionProvider){
    TencentLBSFusionProviderGPS = 0,//!< GPS 系统回调点的精度小于100
    TencentLBSFusionProviderGPS_DR = 1,//!< GPS 推导点，目前还未输出
    TencentLBSFusionProviderLOW_CONF = 2,//!< 低置信度点，精度大于100；在定位回调之前判断精度是否大于100，大于100将原来的prover点改成low_conf，所以这个点的来源可能来源于GPS，也可能来源于网络推导点，外界使用时需要吸附到路网的距离判断要不要使用这个点
    TencentLBSFusionProviderNETWORK_DR = 3,//!< 网络推导点
};
typedef NS_ENUM(NSInteger,TencentLBSInOutDoorStatus){
    TencentLBSInOutDoorUnkown = -1,
    TencentLBSIndoor = 0,
    TencentLBSOutdoor = 1,
};
typedef NS_OPTIONS(NSUInteger, TencentLBSLocationFake) {
    TencentLBSLocationFakeOK = 0,
    TencentLBSLocationFakeCoordinate = 1 << 0,
    TencentLBSLocationFakeSpeed = 1 << 1,
    TencentLBSLocationFakeCrc = 1 << 2,
    TencentLBSLocationFakeMotion = 1 << 3,
    TencentLBSLocationFakeMotionData = 1 << 4,
    TencentLBSLocationFakeSimulationLocExtra = 1 << 5,
};
@interface TencentLBSPoi : NSObject<NSSecureCoding, NSCopying>

@property (nonatomic, copy) NSString *uid;       //!< 当前POI的uid
@property (nonatomic, copy) NSString *name;      //!< 当前POI的名称
@property (nonatomic, copy) NSString *address;   //!< 当前POI的地址
@property (nonatomic, copy) NSString *catalog;   //!< 当前POI的类别
@property (nonatomic, assign) double longitude;  //!< 当前POI的经度
@property (nonatomic, assign) double latitude;   //!< 当前POI的纬度
@property (nonatomic, assign) double distance;   //!< 当前POI与当前位置的距离

@end

@interface TencentLBSLocation : NSObject<NSSecureCoding, NSCopying>

/**
 *  返回当前位置的来源，用于导航是判断位置点的来源
 */
@property (nonatomic,assign) TencentLBSFusionProvider fusionProvider;
/**
 *  返回当前位置的来源
 */
@property (nonatomic, assign) TencentLBSLocationProvider sourceProvider;

/**
 *  返回判断其作弊的原因
 */
@property (nonatomic, assign) TencentLBSLocationFake fakeType;
/**
 *  返回当前位置是在室内还是室外
 */
@property (nonatomic,assign) TencentLBSInOutDoorStatus inOrOutDoorStatus;
/**
 *  返回当前位置的CLLocation信息
 */
@property (nonatomic, strong) CLLocation *location;

/**
 *  返回当前位置的行政区划, 0-表示中国大陆、港、澳, 1-表示其他
 */
@property (nonatomic, assign) NSInteger areaStat;

/**
 * 返回室内定位楼宇Id
 */
@property (nonatomic, copy, nullable) NSString *buildingId;

/**
 * 返回室内定位楼层
 */
@property (nonatomic, copy, nullable) NSString *buildingFloor;

/**
 * 返回室内定位类型，0表示普通定位结果，1表示蓝牙室内定位结果
 */
@property (nonatomic, assign) NSInteger indoorLocationType;

/**
 *  返回当前位置的名称，
 *  仅当TencentLBSRequestLevel为TencentLBSRequestLevelName或TencentLBSRequestLevelAdminName或TencentLBSRequestLevelPoi有返回值，否则为空
 */
@property (nonatomic, copy, nullable) NSString *name;

/**
 *  返回当前位置的地址
 *  仅当TencentLBSRequestLevel为TencentLBSRequestLevelName或TencentLBSRequestLevelAdminName有返回值，否则为空
 */
@property (nonatomic, copy, nullable) NSString *address;

/**
 *  返回当前位置的国家编码，目前暂不可用
 *  仅当TencentLBSRequestLevel为TencentLBSRequestLevelAdminName或TencentLBSRequestLevelPoi有返回值，否则为0
 */
@property (nonatomic, assign) NSInteger nationCode;

/**
 *  返回当前位置的城市编码
 *  仅当TencentLBSRequestLevel为TencentLBSRequestLevelAdminName或TencentLBSRequestLevelPoi有返回值，否则为空
 */
@property (nonatomic, copy, nullable) NSString *code;

/**
 *  返回当前位置的国家
 *  仅当TencentLBSRequestLevel为TencentLBSRequestLevelAdminName或TencentLBSRequestLevelPoi有返回值，否则为空
 */
@property (nonatomic, copy, nullable) NSString *nation;

/**
 *  返回当前位置的省份
 *  仅当TencentLBSRequestLevel为TencentLBSRequestLevelAdminName或TencentLBSRequestLevelPoi有返回值，否则为空
 */
@property (nonatomic, copy, nullable) NSString *province;

/**
 *  返回当前位置的城市
 *  仅当TencentLBSRequestLevel为TencentLBSRequestLevelAdminName或TencentLBSRequestLevelPoi有返回值，否则为空
 */
@property (nonatomic, copy, nullable) NSString *city;

/**
 *  返回当前位置的区县
 *  仅当TencentLBSRequestLevel为TencentLBSRequestLevelAdminName或TencentLBSRequestLevelPoi有返回值，否则为空
 */
@property (nonatomic, copy, nullable) NSString *district;

/**
 *  返回当前位置的乡镇
 *  仅当TencentLBSRequestLevel为TencentLBSRequestLevelAdminName或TencentLBSRequestLevelPoi有返回值，否则为空
 */
@property (nonatomic, copy, nullable) NSString *town;

/**
 *  返回当前位置的村
 *  仅当TencentLBSRequestLevel为TencentLBSRequestLevelAdminName或TencentLBSRequestLevelPoi有返回值，否则为空
 */
@property (nonatomic, copy, nullable) NSString *village;

/**
 *  返回当前位置的街道
 *  仅当TencentLBSRequestLevel为TencentLBSRequestLevelAdminName或TencentLBSRequestLevelPoi有返回值，否则为空
 */
@property (nonatomic, copy, nullable) NSString *street;

/**
 *  返回当前位置的街道编码
 *  仅当TencentLBSRequestLevel为TencentLBSRequestLevelAdminName或TencentLBSRequestLevelPoi有返回值，否则为空
 */
@property (nonatomic, copy, nullable) NSString *street_no;

/**
 *  返回当前位置周围的POI
 *  仅当TencentLBSRequestLevel为TencentLBSRequestLevelPoi有返回值，否则为空
 */
@property (nonatomic, strong, nullable) NSArray<TencentLBSPoi*> *poiList;

/**
 *  返回两个位置之间的横向距离
 */
- (double)distanceFromLocation:(const TencentLBSLocation *)location;

// 测试使用
#if TENCENTLBS_DEBUG
@property (nonatomic, copy, nullable) NSString *halleyTime;
#endif

@end

NS_ASSUME_NONNULL_END
